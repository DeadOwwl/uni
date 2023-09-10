--1. Выдать информацию о местоположении пациента  Паниковский Самюэль Михайлович.
SELECT address FROM patient
WHERE surname = 'Паниковский' AND name = 'Самюэль' AND middle_name = 'Михайлович';

--2. Выдать информацию о пациентах,
-- проживающих в Урюпинске и Черноморске.
SELECT * FROM patient
WHERE address = 'г. Урюпинск' OR address = 'г. Черноморск';

--3. Найти услуги с минимальной стоимостью.
SELECT * FROM services
WHERE price = (SELECT MIN(price) FROM services);

--4. Выдать информацию обо всех визитах,
-- состоявшихся не позднее 20 сентября 2022 года.
SELECT * FROM visit
WHERE date_visit >= TO_DATE('20.09.2022','DD.MM.YYYY');

--5. Подсчитать число специалистов,
-- сведения о которых имеются в базе данных.
SELECT COUNT(*) FROM speciality;

--6. Найти работников, имена которых начинаются на букву А.
-- Имена выдать на нижнем регистре.
SELECT surname, LOWER(name), middle_name FROM doctor
WHERE name LIKE 'А%';

--7. Выдать информацию о визитах,
-- указав дату в формате день(число), месяц(название), год.
SELECT *, TO_CHAR(date_visit, 'DD Month YYYY') FROM visit;

--8. Выдать информацию о специальностях,
-- изменив названия “Хирург” и “Травматолог” на “Костоправ”.
SELECT code_spec,
CASE tittle
WHEN 'Хирург' THEN 'Костоправ'
WHEN 'Травмвматолог' THEN 'Костоправ'
ELSE tittle
END
FROM speciality;

--9. Определите среднюю стоимость услуг которые оказывались не менее 3 раз в день.
-- SELECT tittle, date_visit, AVG(price) AS average FROM visit
-- INNER JOIN services ON visit.code_srv = services.code_srv
-- GROUP BY tittle, date_visit
-- HAVING COUNT(*) >= 3;

--10. Выдать сведения о специалистах каждой специальности.
SELECT * FROM doctor LEFT JOIN speciality ON doctor.code_spec_number = speciality.code_spec;

--11. Укажите сведения об оказанных пациентам услугах, попадающих в вилку:
-- минимальная стоимость услуги - минимальная стоимость плюс 50.
-- Укажите соответствующую вилке  услугу.
SELECT tittle, price FROM services JOIN visit ON services.code_srv = visit.code_srv
WHERE services.price BETWEEN (SELECT MIN(price) FROM services)
                     AND (SELECT MIN(price) FROM services) + 50;

--12. Укажите сведения о визитах,
-- где были оказаны услуги с максимальной стоимостью, с указанием этих услуг.
SELECT * FROM visit INNER JOIN services ON services.code_srv = visit.code_srv
WHERE services.price = (SELECT MAX(price) FROM services);

--13. Найдите  сведения о сотрудниках каждой специальности.
SELECT * FROM doctor JOIN speciality ON doctor.code_spec_number = speciality.code_spec;

--14. Найдите  сведения о визитах пациентов с указанием вместо номера пациента его имени.
SELECT surname, n_visit, id_doctor, date_visit FROM visit
    INNER JOIN patient ON patient.n_card = visit.id_patient;

--15. Выдайте сведения о визитах пациентов
-- с указанием имени пациента и обслуживающего специалиста.
SELECT code_srv , date_visit,
       doctor.surname AS doctor_surname,
       patient.surname AS patient_surname FROM visit
INNER JOIN patient ON patient.n_card = visit.id_patient
INNER JOIN doctor ON visit.id_doctor = doctor.id_doctor;

--16. Выдайте сведения о специалистах,
-- обслуживающих визиты в период с 15 по 22 сентября с указанием их имён.
SELECT doctor.id_doctor, doctor.surname, doctor.name, doctor.middle_name, doctor.code_spec_number
FROM doctor RIGHT JOIN visit ON doctor.id_doctor = visit.id_doctor
WHERE visit.date_visit BETWEEN TO_DATE('15.09.2022','DD.MM.YYYY')
                           AND TO_DATE('22.09.2022','DD.MM.YYYY') ;

--17. Выдайте сведения о вакантных специальностях.
-- Какой вид внешнего объединения Вы использовали? LEFT JOIN.
SELECT * FROM speciality LEFT JOIN doctor ON doctor.code_spec_number = speciality.code_spec
WHERE doctor.id_doctor IS NULL;

--18. Составьте запрос с использованием противоположного вида соединения.
SELECT * FROM speciality RIGHT JOIN doctor ON doctor.code_spec_number = speciality.code_spec
WHERE doctor.id_doctor IS NULL;

--19. Составьте запрос с использованием полного внешнего соединения.
SELECT * FROM speciality FULL JOIN doctor ON doctor.code_spec_number = speciality.code_spec
WHERE doctor.id_doctor IS NULL;