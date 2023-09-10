DELETE FROM visit;
DELETE FROM patient;
DELETE FROM services;
DELETE FROM doctor;
DELETE FROM speciality;


-- Добавление данных Специальности
INSERT INTO speciality VALUES(NEXTVAL('seq_spec'), 'Терапевт');
INSERT INTO speciality VALUES(NEXTVAL('seq_spec'), 'Хирург');
INSERT INTO speciality VALUES(NEXTVAL('seq_spec'), 'Невролог');
INSERT INTO speciality VALUES(NEXTVAL('seq_spec'), 'Офтальмолог');
INSERT INTO speciality VALUES(NEXTVAL('seq_spec'), 'Травмвматолог');
INSERT INTO speciality VALUES(NEXTVAL('seq_spec'), 'Дерматовенеролог');
INSERT INTO speciality VALUES(NEXTVAL('seq_spec'), 'Медсестра');
INSERT INTO speciality VALUES(NEXTVAL('seq_spec'), 'Интерн');
INSERT INTO speciality VALUES(NEXTVAL('seq_spec'), 'Кардиолог');

-- Добавление данных Врачи
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Быков', 'Андрей', 'Евгеньевич', 1401);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Кисегач', 'Анастасия', 'Константиновна', 1401);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Купитман', 'Иван', 'Натанович', 1406);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Скрябина', 'Любовь', 'Михайловна', 1407);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Королева', 'Маргарита', 'Павловна', 1407);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Левин', 'Борис', 'Аркадьевич', 1404);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Черноус', 'Варвара', 'Николаевна', 1408);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Романенко', 'Глеб', 'Викторович', 1401);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Лобанов', 'Семен', 'Семенович', 1408);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Ричардс', 'Фил', NULL, 1406);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Ульянова', 'Полина', 'Сергеевна', 1408);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Корнеев', 'Максим', 'Леонидович', 1402);
INSERT INTO doctor VALUES(NEXTVAL('seq_doc'), 'Калинина', 'Софья', 'Яковлевна ', 1405);

-- Добавление данных Пациенты
INSERT INTO patient VALUES(NEXTVAL('seq_patient_1'),'Безенчук', 'Федор', 'Николаевич', 'г. Артемовск', '+375256788098');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_2'),'Берлага', 'Михаил', 'Александрович','г. Южногорск', '+375331234579');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_1'),'Грицацуева', 'Нина', 'Ивановна','г. Прокопьевск', '+375299089096');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_1'),'Паниковский', 'Самюэль','Михайлович', 'г. Криворуков', '+375244777881');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_1'),'Христофоров', 'Эрнест', 'Ричардович','г. Бердянск', '+375991456682');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_2'),'Щукина', 'Элла', 'Аркадьевна','г. Урюпинск', '+375113451173');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_1'),'Бендер', 'Остап', 'Ибрагимович','г. Черноморск', '+375000000000');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_1'),'Балаганов', 'Александр', 'Николаевич', 'г. Черноморск', '+375444567799');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_1'),'Корейко', 'Александр', 'Иванович','г. Урюпинск', '+375337777777');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_1'),'Козлевич','Адам', 'Казимирович', 'г. Верхнехолмск', '+375172061544');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_2'),'Растопыркин ', 'Григорий', 'Феликсович','г. Урюпинск', '+375173076553');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_2'),'Рукоблудов', 'Леонид', 'Ильич', 'г. Криворуков', '+375172061544' );
INSERT INTO patient VALUES(NEXTVAL('seq_patient_2'),'Филинов', 'Василий', 'Денисович', 'г. Артемовск', '+375552347890');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_2'),'Тугодумов', 'Василий', 'Федорович', 'г. Верхнехолмск', '+375297777777');
INSERT INTO patient VALUES(NEXTVAL('seq_patient_2'),'Заныкин', 'Андрей', 'Данилович', 'г. Артемовск', '+375172124689');

-- Добавление данных Услуги
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'Консультация', 50.00);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'Первичный осмотр', 15.30);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'Рефлексотерапия', 185.60);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'Физиолечение', 5.30);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'Курс терапевтического лечения', 47.75);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'Курс профилактического лечения', 300.00);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'Ренгеноскопия', 10.00);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'ЭКГ', 0.85);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'Компьютерная томография', 450.99);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'МРТ', 560.70);
INSERT INTO services VALUES(NEXTVAL('seq_srv'), 'Анализ крови', 0.35);

-- Добавление данных Визиты
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 13, 116002, TO_DATE('12.09.2022','DD.MM.YYYY'), 110);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 21, 116003, TO_DATE('12.09.2022','DD.MM.YYYY'), 110);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 11, 216002, TO_DATE('12.09.2022','DD.MM.YYYY'), 150);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 20, 116006, TO_DATE('13.09.2022','DD.MM.YYYY'), 160);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 18, 216003, TO_DATE('13.09.2022','DD.MM.YYYY'), 120);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 11, 116007, TO_DATE('14.09.2022','DD.MM.YYYY'), 150);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 20, 216004, TO_DATE('15.09.2022','DD.MM.YYYY'), 160);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 14, 116008, TO_DATE('19.09.2022','DD.MM.YYYY'), 210);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 19, 216001, TO_DATE('19.09.2022','DD.MM.YYYY'), 170);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 21, 116003, TO_DATE('19.09.2022','DD.MM.YYYY'), 110);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'),NULL,216005, TO_DATE('20.09.2022','DD.MM.YYYY'), 170);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 18, 216002, TO_DATE('21.09.2022','DD.MM.YYYY'), 140);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 16, 116004, TO_DATE('21.09.2022','DD.MM.YYYY'), 110);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 18, NULL,   TO_DATE('22.09.2022','DD.MM.YYYY'), 120);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'),NULL,216001, TO_DATE('23.09.2022','DD.MM.YYYY'), 210);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 22, 216007, TO_DATE('26.09.2022','DD.MM.YYYY'), 130);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 21, 116003, TO_DATE('26.09.2022','DD.MM.YYYY'), 110);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'),NULL,216001, TO_DATE('27.09.2022','DD.MM.YYYY'), 170);
INSERT INTO visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 22, 116008, TO_DATE('28.09.2022','DD.MM.YYYY'), 130);
Insert into visit (N_Visit,ID_Doctor,ID_Patient,Date_Visit,Code_Srv) VALUES (NEXTVAL('seq_visit'), 12, 116007, TO_DATE('29.09.2022','DD.MM.YYYY'), 200);