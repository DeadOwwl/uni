-- 1. Создайте функцию, вычисляющую премию за всё время начислений для
-- конкретного сотрудника. Входной параметр – фамилия или идентификатор
-- сотрудника. Выходной параметр – значение суммы премии.
CREATE FUNCTION premia (INTEGER) RETURNS NUMERIC AS'
SELECT COALESCE(100*count(n_visit), 0) AS doctor_premia FROM doctor
LEFT JOIN visit ON visit.id_doctor = doctor.id_doctor
WHERE doctor.id_doctor = $1
GROUP BY doctor.id_doctor;
' LANGUAGE sql;

SELECT premia(11);

-- 2. Создайте функцию, вычисляющую сумму оплаты за услуги для конкретного
-- пациента за указанный период. Входные параметры – фамилия или номер
-- карты пациента, начало и конец периода (необязательный). Выходной
-- параметр – значение суммы.
CREATE FUNCTION total_price (INTEGER, DATE, DATE DEFAULT current_date) RETURNS NUMERIC AS'
SELECT SUM(price) AS price FROM visit v
INNER JOIN services s ON s.code_srv = v.code_srv
WHERE id_patient = $1 AND date_visit BETWEEN $2 AND $3
group by id_patient
' LANGUAGE sql;

SELECT total_price(216004, TO_DATE('2022-09-14 BC', 'yyyy-mm-dd BC'));


-- 3. Создайте функцию для вычисления размера скидки при оплате услуг для
-- указанного пациента. Входные параметры – фамилия или номер карты
-- пациента. Выходной параметр – размер скидки в процентах. Размер скидки
-- определяется следующим образом: если общая сумма оплаты за услуги
-- составляет менее 50 руб. – размер скидки 3%; от 50 до 100 руб. – 10%; от 100
-- до 200 руб. – 20%; от 200 до 400 руб. – 30%; свыше 400 руб. – 40%.
CREATE FUNCTION discount (INTEGER) RETURNS INTEGER AS'
SELECT CASE WHEN SUM(price)<50 THEN 3
	     	WHEN SUM(price) BETWEEN 50 AND 100 THEN 10
			WHEN SUM(price) BETWEEN 100 AND 200 THEN 20
			WHEN sum(price) BETWEEN 200 AND 400 THEN 30
			ELSE 40
		END AS discount
FROM visit v
INNER JOIN services s ON s.code_srv = v.code_srv
WHERE id_patient = $1
GROUP BY id_patient
' LANGUAGE sql;

SELECT discount(116003);

-- 4. Создайте функцию определения количества принятых специалистом
-- пациентов. Входные параметры – фамилия или идентификатор сотрудника.
-- Выходной параметр – количество пациентов.
CREATE FUNCTION count_patients (INTEGER) RETURNS INTEGER AS'
SELECT COUNT(n_visit) FROM visit
WHERE id_doctor = $1
' LANGUAGE sql;

SELECT count_patients(11);

-- 5. Создайте функцию, вычисляющую максимальную разность количества
-- принятых специалистом пациентов за определенный период. Входные
-- параметры – начальная дата, конечная дата (необязательный параметр).
-- Выходной параметр – максимальная разность количества пациентов и
-- фамилии специалистов.
CREATE FUNCTION count_patients (DATE, DATE DEFAULT current_date)
RETURNS RECORD AS'
SELECT DISTINCT (SELECT COUNT(n_visit) AS c FROM visit
		GROUP BY id_doctor
		ORDER BY c DESC
LIMIT 1) - (SELECT COUNT(n_visit) AS c FROM visit
			GROUP BY id_doctor
			ORDER BY c
			LIMIT 1),
(SELECT surname FROM visit
INNER JOIN doctor d ON d.id_doctor = visit.id_doctor
		GROUP BY d.id_doctor
		HAVING d.id_doctor IS NOT NULL
		ORDER BY count(n_visit) DESC
		LIMIT 1),
(SELECT surname FROM visit
INNER JOIN doctor d ON d.id_doctor = visit.id_doctor
		GROUP BY d.id_doctor
		HAVING d.id_doctor IS NOT NULL
		ORDER BY count(n_visit)
		LIMIT 1)
FROM visit
INNER JOIN doctor ON doctor.id_doctor = visit.id_doctor
WHERE date_visit BETWEEN $1 AND $2
' LANGUAGE sql;

SELECT count_patients(TO_DATE('2022-09-09 BC', 'yyyy-mm-dd BC'));

-- 6. Процедура начисления премии специалистам.
ALTER TABLE doctor ADD COLUMN bonus NUMERIC(9,2);

CREATE OR REPLACE PROCEDURE insert_premia(
	id_doc INTEGER)
LANGUAGE plpgsql
AS $$
BEGIN
UPDATE doctor
SET bonus = (SELECT CASE WHEN SUM(price) <50 THEN 10
	     	WHEN SUM(price) BETWEEN 50 AND 100 THEN 15
			WHEN SUM(price) BETWEEN 100 AND 400 THEN 30
			ELSE 50
		END
FROM visit v
INNER JOIN services s ON s.code_srv = v.code_srv
WHERE id_doctor = id_doc
GROUP BY id_doctor)
WHERE id_doctor = id_doc;
 COMMIT;
END;$$;

CREATE OR REPLACE PROCEDURE insert_premia(
	sname CHARACTER VARYING)
LANGUAGE plpgsql
AS $$
BEGIN
UPDATE doctor
SET bonus = (SELECT CASE WHEN SUM(price) <50 THEN 10
	     	WHEN SUM(price) BETWEEN 50 AND 100 THEN 15
			WHEN SUM(price) BETWEEN 100 AND 400 THEN 30
			ELSE 50
		END
FROM visit v
INNER JOIN services s ON s.code_srv = v.code_srv
WHERE id_doctor = (SELECT id_doctor FROM doctor WHERE surname = sname)
GROUP BY id_doctor)
WHERE surname = sname;
 COMMIT;
END;$$;

CREATE FUNCTION premia_doc (NUMERIC) RETURNS INTEGER AS'
SELECT CASE WHEN SUM(price) <50 THEN 10
WHEN SUM(price) BETWEEN 50 AND 100 THEN 15
WHEN SUM(price) BETWEEN 100 AND 400 THEN 30
ELSE 50
END
FROM visit v
INNER JOIN services s ON s.code_srv = v.code_srv
WHERE id_doctor = $1
GROUP BY id_doctor
' LANGUAGE sql;


CREATE OR REPLACE PROCEDURE insert_premia_all(
	spec CHARACTER VARYING)
LANGUAGE plpgsql
AS $$
BEGIN
UPDATE doctor
SET bonus = premia_doc(id_doctor)
WHERE code_spec_number IN (SELECT code_spec FROM speciality WHERE tittle=spec);
 COMMIT;
END;$$;

CREATE OR REPLACE PROCEDURE insert_premia()
LANGUAGE plpgsql
AS $$
BEGIN
UPDATE doctor
SET bonus = premia_doc(id_doctor);
 COMMIT;
END;$$;

CALL insert_premia(13);
CALL insert_premia('Кисегач');
CALL insert_premia();
CALL insert_premia_all('Хирург');


-- 7. Создайте процедуру зачисления нового сотрудника.
CREATE FUNCTION free_vacancy () RETURNS INTEGER AS'
SELECT s.code_spec FROM speciality s
LEFT JOIN doctor d ON s.code_spec = d.code_spec_number
GROUP BY s.code_spec
ORDER BY COUNT(id_doctor)
LIMIT 1
' LANGUAGE sql;


CREATE OR REPLACE PROCEDURE insert_doctor(
surn CHARACTER VARYING,
nam CHARACTER VARYING,
midname CHARACTER VARYING,
spec CHARACTER VARYING DEFAULT 'Интерн')
LANGUAGE plpgsql
AS $$
BEGIN
IF spec NOT IN (SELECT tittle FROM speciality) THEN
	INSERT INTO speciality VALUES (NEXTVAL('seq_spec'), spec);
END IF;
IF spec = 'Интерн' THEN
	UPDATE doctor
	SET code_spec_number = free_vacancy()
	WHERE id_doctor = (SELECT id_doctor FROM doctor WHERE code_spec_number = 1408 LIMIT 1);
END IF;
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), surn, nam, midname,
						   (SELECT code_spec FROM speciality WHERE tittle = spec));
 COMMIT ;
END;$$;

CALL insert_doctor('ccc2','cc2','c2');

-- 8. Создайте процедуру регистрации нового пациента.
CREATE OR REPLACE PROCEDURE insert_patient(
surn CHARACTER VARYING,
nam CHARACTER VARYING,
midname CHARACTER VARYING,
addres CHARACTER VARYING DEFAULT NULL,
ph CHARACTER VARYING DEFAULT NULL)
LANGUAGE plpgsql
AS $$
BEGIN
INSERT INTO patient VALUES(
	(SELECT CASE
	    WHEN addres IN ('г.Артемовск', 'г.Черноморск', 'г.Верхнехолмск', 'г.Южногорск')
	        THEN NEXTVAL('seq_patient_1')
	    WHEN addres IN ('г.Бердянск', 'г.Прокопьевск', 'г.Криворуков', 'г.Урюпинск')
	        THEN NEXTVAL('seq_patient_2')
	    ELSE NEXTVAL('seq_patient_3')
	    END), surn, nam, midname, addres, ph);
 COMMIT;
END;$$;

CALL insert_patient('ss', 'sss', 's', 'г.Черноморск', '+375291987456');
CALL insert_patient('ss2', 'sss2', 's2', 'г.Минск', '+375333734567');

-- 9. Создайте процедуру для переноса визитов на другую дату.
CREATE OR REPLACE PROCEDURE update_date_visit(
start_date DATE,
end_date DATE,
OUT count_visit NUMERIC)
LANGUAGE plpgsql
AS $$
BEGIN
count_visit = (SELECT COUNT(n_visit) FROM visit WHERE date_visit = start_date);
UPDATE visit
SET date_visit = end_date
WHERE date_visit = start_date;
 COMMIT ;
END;$$;


DO
$$
DECLARE
result NUMERIC;
BEGIN
CALL update_date_visit(TO_DATE('2022-09-19 BC', 'yyyy-mm-dd BC'),
					   TO_DATE('2022-09-14 BC', 'yyyy-mm-dd BC'),result);
RAISE NOTICE '%', result;
END;
$$;

-- 10. Создайте процедуру для удаления сведений о визитах, состоявшихся в указанный период.
CREATE OR REPLACE PROCEDURE delete_visit(
start_date DATE,
end_date DATE,
OUT count_visit NUMERIC)
LANGUAGE plpgsql
AS $$
BEGIN
count_visit = (SELECT COUNT(n_visit) FROM visit WHERE date_visit BETWEEN start_date AND end_date);
INSERT INTO tmp_visit (SELECT * FROM visit WHERE date_visit BETWEEN start_date AND end_date);
DELETE FROM visit
WHERE date_visit BETWEEN start_date AND end_date;
 COMMIT;
END;$$;

DO
$$
DECLARE
result NUMERIC;
BEGIN
CALL delete_visit(to_date('2022-09-12 BC', 'yyyy-mm-dd BC'),
					   to_date('2022-09-13 BC', 'yyyy-mm-dd BC'),result);
RAISE NOTICE '%', result;
END;
$$;
