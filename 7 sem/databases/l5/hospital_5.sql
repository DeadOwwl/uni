-- 1. Создайте представление, содержащее данные о терапевтах.
CREATE VIEW vw_ter AS (SELECT * FROM doctor
                       WHERE code_spec_number = (SELECT code_spec FROM speciality
                                                  WHERE tittle = 'Терапевт'));

-- Представление с данными о терапевтах:
SELECT * FROM vw_ter;

-- 2. Создайте представление, содержащее данные о сотрудниках,
-- не работавших на визитах: фамилия, имя сотрудника, дата визита, специальность.
CREATE VIEW vw_no_visit_doctors AS (SELECT * FROM doctor d
                                    WHERE d.id_doctor NOT IN (SELECT DISTINCT v.id_doctor FROM visit v));

SELECT * FROM vw_no_visit_doctors;

-- 3. Создайте представление, содержащее фамилию сотрудника, специальность,
-- количество принятых пациентов за период с 15.09.22 по 19.09.22 включительно.
-- Первый столбец назвать Sotrudnik, второй – Specialty, третий – Kol_patients.
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv)
VALUES (NEXTVAL('seq_visit'), 20, 116002, TO_DATE('16.09.2022','DD.MM.YYYY'), 110);
DROP VIEW vw_patient_num;
CREATE VIEW vw_patient_num AS (SELECT doctor.id_doctor, surname AS Sotrudnik, tittle AS Specialty, COUNT(*) AS Kol_patients
                                FROM doctor JOIN visit ON doctor.id_doctor = visit.id_doctor
                                            JOIN speciality ON doctor.code_spec_number = speciality.code_spec
                                WHERE date_visit BETWEEN TO_DATE('15.09.2022', 'DD.MM.YYYY') AND
                                                         TO_DATE('20.09.2022', 'DD.MM.YYYY')
                                GROUP BY (doctor.id_doctor, surname, tittle));

SELECT * FROM vw_patient_num;

-- 4. На основе представления из задания 3 и таблицы Services создайте представление,
-- содержащее данные о сотрудниках, обслуживающих пациентов в период с 15.09.22 по 19.09.22,
-- которые оказывали более 2 платных услуг в день.
-- В созданном представлении число даты визита зарплаты
-- и сумму стоимости оказанных услуг вывести в одном столбце,
-- в качестве разделителя использовать запятую.
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv)
VALUES (NEXTVAL('seq_visit'), 20, 116002, TO_DATE('16.09.2022','DD.MM.YYYY'), 160);

CREATE VIEW vw_patient_num_date AS (SELECT sotrudnik, CONCAT(date_visit,', ', SUM(s.price)) AS date_sum
                                        FROM vw_patient_num vpn
                                        INNER JOIN visit v ON v.id_doctor = vpn.id_doctor
	                                    INNER JOIN services s ON s.code_srv = v.code_srv
	                                    GROUP BY sotrudnik, date_visit
	                                    HAVING COUNT(v.n_visit) >= 2);

SELECT * FROM vw_patient_num_date;