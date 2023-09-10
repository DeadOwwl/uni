--1. Найти имена специалистов, оказавших услуги с минимальной стоимостью.
SELECT surname FROM doctor RIGHT JOIN visit ON doctor.id_doctor = visit.id_doctor
WHERE visit.code_srv IN (SELECT services.code_srv FROM services
                         WHERE services.price = (SELECT MIN(price) FROM services));

--2. Найти имена сотрудников, работавших в тот же день,
-- когда был визит пациента с именем Безенчук Федор Николаевич.
SELECT surname, date_visit FROM doctor RIGHT JOIN visit ON doctor.id_doctor = visit.id_doctor
WHERE visit.date_visit IN (SELECT visit.date_visit FROM visit INNER JOIN patient
                           ON patient.n_card = visit.id_patient
                           WHERE patient.surname IN ('Безенчук', 'Федор', 'Николаевич'));

--3. Найти имена сотрудников, обслуживающих пациентов
-- Паниковский, Щукина, Корейко.(Повторяется)
SELECT surname FROM doctor RIGHT JOIN visit ON doctor.id_doctor = visit.id_doctor
WHERE visit.id_patient IN (SELECT patient.n_card FROM patient
                           WHERE surname IN ('Паниковский','Щукина','Корейко'));

--4. Найти сведения о номерах сотрудников,
-- работавших 15, 20 и 24 сентября..
SELECT visit.id_doctor FROM visit
WHERE visit.date_visit = ANY(ARRAY[TO_DATE('15.09.2022', 'DD.MM.YYYY'),
                                   TO_DATE('20.09.2022', 'DD.MM.YYYY'),
                                   TO_DATE('24.09.2022', 'DD.MM.YYYY')]);

--5. Найти сведения о номерах сотрудников, оказывающих какие-либо услуги из тех,
-- которые были оказаны 12 и 13 сентября..
SELECT DISTINCT visit.id_doctor FROM visit
WHERE visit.code_srv IN (SELECT visit.code_srv FROM visit
                         WHERE visit.date_visit = ANY(ARRAY[TO_DATE('12.09.2022', 'DD.MM.YYYY'),
                                                            TO_DATE('13.09.2022', 'DD.MM.YYYY')]));

--6. Определить в какие дни были оказаны услуги, средняя суточная стоимость которых
--   была больше общей средней стоимости всех имеющихся услуг.

-- SELECT date_visit FROM visit hv LEFT JOIN services hs ON hs.code_srv = hv.code_srv
-- GROUP BY hv.date_visit
-- HAVING AVG(hs.price) > (SELECT AVG(price) FROM services);

--7. Определить коды специальностей сотрудников,
-- оказавших услуги во время визитов с 15 по 20 сентября.
SELECT DISTINCT code_spec_number FROM doctor
WHERE doctor.id_doctor IN (SELECT id_doctor FROM visit
                           WHERE date_visit BETWEEN TO_DATE('15.09.2022','DD.MM.YYYY')
                                                AND TO_DATE('20.09.2022','DD.MM.YYYY'));

--8. Определить коды специальностей сотрудников,
-- обслуживающих пациентов, которым были оказаны услуги с кодами 110 - 150.
SELECT DISTINCT code_spec_number FROM doctor LEFT JOIN visit ON doctor.id_doctor = visit.id_doctor
WHERE EXISTS (SELECT code_srv FROM visit
              WHERE code_srv BETWEEN 110 AND 150);

--9. Определить коды специальностей сотрудников,
-- которые не обслуживали пациентов в период с 15 по 20 сентября.
SELECT DISTINCT code_spec_number FROM doctor LEFT JOIN visit ON doctor.id_doctor = visit.id_doctor
WHERE NOT EXISTS (SELECT date_visit FROM visit
                  WHERE date_visit BETWEEN TO_DATE('15.09.2022','DD.MM.YYYY')
                                      AND TO_DATE('20.09.2022','DD.MM.YYYY'));

--10. Вывести сведения о специальности сотрудников с указанием названий вместо их кодов.
WITH spec_title AS (SELECT code_spec, tittle FROM speciality)
SELECT surname, spec_title.tittle FROM doctor, spec_title
WHERE doctor.code_spec_number = spec_title.code_spec;

--11. Определить целую часть средней стоимости услуг, по датам
-- SELECT date_visit, CAST(AVG(services.price) AS INTEGER) FROM visit LEFT JOIN services
--                                                         ON visit.code_srv = services.code_srv
-- GROUP BY date_visit;

--12. Разделите список услуг по стоимостным категориям:
-- A) до 5 руб.;
-- B) 5 - 10 руб.;
-- C) 10 – 50 руб.;
-- D) более 50 руб.
SELECT tittle,
CASE
WHEN price < 5  THEN 'A'
WHEN price < 10 AND price >=5 THEN 'B'
WHEN price < 50 AND price>=10 THEN 'C'
WHEN price >= 50 THEN 'D'
END price_category
FROM services;

--13. Перекодируйте номера пациентов,
-- добавив перед номером буквы AM для номеров <=200000,
-- буквы  NV для номеров >=20000.
SELECT surname,
CASE
WHEN n_card <= 200000 THEN 'AM' || '' || n_card::varchar(255)
WHEN n_card > 200000 THEN 'NV' || '' || n_card::varchar(255)
END card_number
FROM patient;

--14. Выдать информацию о сотрудниках,
-- из(за)менив отсутствие имени или отчество строкой, состоящей из 5 пробелов.
SELECT id_doctor,
COALESCE(surname, '     '),
COALESCE(name, '     '),
COALESCE(middle_name, '     '),
code_spec_number FROM doctor;