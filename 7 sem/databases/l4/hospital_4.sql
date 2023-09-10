-- 1. Поднимите нижнюю границу стоимости услуг в таблице Services до 1 руб.
UPDATE services SET price = price + 1
WHERE price = (SELECT MIN(price) FROM services);

-- 2. Поднимите стоимость услуг в таблице Services на 10%
-- для услуг ценовой категории C (см. запрос 12 из ЛР 3_2), кроме рентгеноскопии.
UPDATE services SET price = 1.1 * price
WHERE price BETWEEN 10 AND 50 AND tittle != 'Ренгеноскопия';

-- 3. Поднимите стоимость услуг в таблице Services на 10% для услуг терапевтов
-- и на 20% для неврологов (одним оператором).
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Шульц', 'Евгений', 'Ярославович ', 1403);
INSERT INTO visit VALUES (NEXTVAL('seq_visit'), 31, 216006, TO_DATE('03.10.2022','DD.MM.YYYY'), 130);

UPDATE services SET price = CASE
    WHEN code_srv IN (SELECT code_srv FROM visit WHERE id_doctor IN
                     (SELECT d.id_doctor FROM doctor AS d WHERE code_spec_number =
                     (SELECT sp.code_spec FROM speciality AS sp WHERE tittle='Терапевт')))
        THEN 1.1 * price
    WHEN code_srv IN (SELECT code_srv FROM visit WHERE id_doctor IN
                     (SELECT d.id_doctor FROM doctor AS d WHERE code_spec_number =
                     (SELECT sp.code_spec from speciality as sp where tittle='Невролог')))
        THEN 1.2 * price
ELSE price
END;

-- 4. Установите минимальную стоимость услуг хирурга равной 90% от средней стоимости услуг терапевта.
UPDATE services SET price = 0.9 * (SELECT avg(s2.price) FROM services AS s2
                                   WHERE s2.code_srv IN (SELECT v.code_srv FROM visit AS v
                                   WHERE id_doctor IN (SELECT d.id_doctor FROM doctor AS d
                                   WHERE code_spec_number = (SELECT sp.code_spec FROM speciality AS sp
                                   WHERE tittle='Терапевт'))))
WHERE code_srv IN (SELECT code_srv FROM visit
                   WHERE id_doctor IN (SELECT d.id_doctor FROM doctor AS d
				   WHERE code_spec_number = (SELECT sp.code_spec from speciality AS sp
				   WHERE tittle = 'Хирург')));

--5. Приведите в таблице Doctor имена специалистов, начинающиеся на букву ‘С’, к нижнему регистру.
UPDATE doctor SET name = lower(name)
WHERE name LIKE 'С%';

--6. Измените в таблице Doctor фамилии специалистов, состоящие из двух слов,
-- так, чтобы оба слова в имени начинались с заглавной буквы,
-- а продолжались прописными (например, фамилия Бендер-задунайский изменяется на Бендер Задунайский).
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Складовская-кюри', 'Мари', NULL, 1404);

UPDATE doctor SET surname = INITCAP(REPLACE(surname,'-',' '))
WHERE surname LIKE '%-%';

-- 7. Приведите в таблице Doctor фамилии специалистов к верхнему регистру.
UPDATE doctor SET surname = UPPER(surname);

-- 8. Перенесите визиты консультации(Visit) к другому специалисту той же специальности (Specialty).
UPDATE visit AS h1 SET id_doctor = (SELECT h2.id_doctor FROM doctor AS h2
				 WHERE h1.id_doctor != h2.id_doctor AND
				 h2.code_spec_number = (SELECT code_spec_number FROM doctor h3
								  WHERE id_doctor = h1.id_doctor)
				 LIMIT 1);

-- 9. Добавьте нового сотрудника в таблицу Doctor.
-- Его имя и фамилия должны совпадать с Вашими, записанными латинскими буквами согласно паспорту,
-- дата рождения также совпадает с Вашей.
INSERT INTO doctor VALUES(nextval('seq_doc'), 'KRAHEL', 'ALINA', NULL, 1402);

-- 10. Определите нового сотрудника (см. предыдущее задание) на работу в качестве интерна.
-- Назначьте ему первый визит на текущую дату.
UPDATE doctor SET code_spec_number = 1408
WHERE surname = 'KRAHEL';

INSERT INTO visit VALUES (NEXTVAL('seq_visit'), (SELECT id_doctor FROM doctor WHERE surname='KRAHEL'),
	   NULL, TO_DATE('29.11.2022', 'DD.MM.YYYY'), 110);

-- 11. Создайте таблицу TMP_Doc со структурой, аналогичной структуре таблицы Doctor.
-- Добавьте в нее информацию о сотрудниках,
-- которые работали с пациентами на всем протяжении зарегистрированных визитов.
DROP TABLE TMP_Doc;

CREATE TABLE TMP_Doc (
     id_doctor INTEGER NOT NULL,
     surname VARCHAR(50),
     name VARCHAR(50),
     middle_name VARCHAR (50),
     code_spec_number INTEGER NOT NULL);
ALTER TABLE TMP_Doc ADD CONSTRAINT pk_tmp_id_doctor PRIMARY KEY (id_doctor);

DROP SEQUENCE SEQ_TMP_DOC CASCADE;
CREATE SEQUENCE  SEQ_TMP_DOC
    MINVALUE 1
    MAXVALUE 999
    INCREMENT BY 1
    START WITH 11;

INSERT INTO TMP_Doc (SELECT * FROM doctor d
                    WHERE d.id_doctor IN (SELECT DISTINCT v.id_doctor FROM visit v));

-- 12. Удалите из таблицы TMP_Doc всю информацию.
DELETE FROM TMP_Doc;

-- 13. Добавьте в таблицу TMP_Doc информацию о тех сотрудниках,
-- которые не работали с пациентами в период с 12 по 17 сентября.
INSERT INTO TMP_Doc (SELECT * FROM doctor d
                    WHERE d.id_doctor NOT IN (SELECT DISTINCT v.id_doctor FROM visit v
                                            WHERE date_visit BETWEEN
                                            TO_DATE('12.09.2022', 'DD.MM.YYYY') AND
                                            TO_DATE('17.09.2022', 'DD.MM.YYYY')));

-- 14. Выполните тот же запрос для тех сотрудников, которые никогда не работали на визитах.
INSERT INTO TMP_Doc (SELECT * FROM doctor d
                    WHERE d.id_doctor NOT IN (SELECT DISTINCT v.id_doctor FROM visit v));

-- 15. Создайте таблицу TMP_Spec со структурой, аналогичной структуре таблицы Specialty.
-- Добавьте в нее информацию по тем специальностям, которые в настоящий момент являются вакантными.
DROP TABLE TMP_Spec;

CREATE TABLE TMP_Spec (
     code_spec INTEGER NOT NULL ,
     title VARCHAR (50));
ALTER TABLE TMP_Spec ADD CONSTRAINT pk_code_spec_2 PRIMARY KEY (code_spec);

DROP SEQUENCE SEQ_TMP_Spec CASCADE;

CREATE SEQUENCE SEQ_TMP_Spec
  START WITH 1401
  MAXVALUE 1755;

INSERT INTO tmp_spec (SELECT * FROM speciality s
                    WHERE s.code_spec NOT IN (SELECT DISTINCT d.code_spec_number FROM doctor d) );

-- 16. Удалите данные о визитах за первую неделю.
DELETE FROM visit WHERE date_visit BETWEEN (SELECT MIN(date_visit) FROM visit) AND
                                           (SELECT MIN(date_visit) + INTERVAL '7 DAYS' FROM visit);

-- 17. Удалите информацию о визитах сотрудников, которые в последний день не работали с пациентами.
DELETE FROM visit
    WHERE id_doctor NOT IN (SELECT DISTINCT id_doctor FROM visit
					            WHERE date_visit = (SELECT MAX(date_visit) FROM visit));

-- 18. Удалите информацию об оказанных услугах сотрудников,
-- которые в последний день не работали с пациентами (можно использовать результаты работы предыдущего запроса).
DELETE FROM services
WHERE code_srv = (SELECT v.code_srv FROM visit v
				 WHERE v.id_doctor NOT IN (SELECT DISTINCT id_doctor FROM visit
					            WHERE date_visit = (SELECT MAX(date_visit) FROM visit)));

-- 19. Удалите записи из таблицы Doctor для тех сотрудников, которые никогда не работали на визитах.
DELETE FROM doctor
WHERE id_doctor IN (SELECT d2.id_doctor FROM doctor d2
	WHERE d2.id_doctor NOT IN (SELECT DISTINCT v.id_doctor FROM visit v));

-- 20. Удалите из таблиц TMP_Doc и TMP_Spec всю информацию.
DELETE FROM tmp_doc;
DELETE FROM tmp_spec;