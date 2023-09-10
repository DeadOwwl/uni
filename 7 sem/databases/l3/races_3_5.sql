-- 1. Составьте запрос на выборку данных
-- с использованием рефлексивного соединения для таблицы:
-- Выводим имя лощади, пол и ее породу. !!!
SELECT h.name, h.sex, hb.racehorse_breed FROM horse h JOIN horse_breed hb ON h.breed = hb.id_horse_breed;

-- 2. ...простого оператора CASE:
-- Выводим результаты для награждения лошадей за заезд
-- для последнего проведенного соревнования.
SELECT h.name, r.id_competition, r.place,
CASE
WHEN place = 1 THEN 'Золото'
WHEN place = 2 THEN 'Серебро'
WHEN place = 3 THEN 'Бронза'
ELSE 'Не награжден'
END race_results
FROM race r JOIN horse h ON r.id_horse = h.id_horse
WHERE r.id_competition = (SELECT MAX(id_competition) FROM race);

-- 3. поискового оператора CASE:
-- Проводим классификацию всех имеющихся лошадей по возрасту.
SELECT name, age,
CASE
WHEN age BETWEEN 5 AND 9 THEN 'Молодая'
WHEN age BETWEEN 9 AND 20 THEN 'Взрослая'
ELSE 'Старая'
END AS age_classification
FROM horse;

-- 4. ...оператора WITH.
-- Выводим владельца лошадей с наибольшим количеством лошадей.
WITH count_horses AS ( SELECT COUNT(*) AS ho, id_owner FROM horse GROUP BY id_owner)
SELECT h.name, ho FROM horse_owner h JOIN count_horses c USING (id_owner)
WHERE c.ho = (SELECT MAX(ho) FROM count_horses);

-- 5. ...встроенного представления:
-- Выводим владельцев лошадей с более чем 1 лошадью
SELECT h.name, c.ho AS number_of_horses
FROM horse_owner h JOIN (
  SELECT COUNT(*) AS ho, id_owner FROM horse
  GROUP BY id_owner)
c USING (id_owner)
WHERE c.ho > 1;

-- 6. ...некоррелированного запроса:
-- Выводим имена жокеев и именя лошадей, которые принадлежат выбранным владельцам
SELECT jockey.name AS jockey_name, horse.name AS horse_name
FROM jockey JOIN horse ON jockey.id_jockey = horse.id_jockey
WHERE horse.id_owner IN (
  -- некоррелированный подзпрос образует список значений идентификаторов владельцев лошадей
      SELECT id_owner FROM horse_owner
      WHERE horse_owner.name IN ('Хансен', 'Андерсен', 'Йенсен'));

-- 7. ... коррелированного запроса:
-- Выводим имена лошадей, возраст лошадей и владельцев тех лошадей,
-- возраст которых больше среднего.
SELECT horse.name as horse_name, horse.age as horse_age, horse_owner.name as owner
FROM horse JOIN horse_owner ON horse.id_owner = horse_owner.id_owner
WHERE horse.age >
  -- коррелированный подзапрос
    (SELECT AVG(age) FROM horse WHERE id_owner = horse_owner.id_owner);

-- 8. функции NULLIF:
-- Выводим данные владельцах и о породах лошадей, которые есть у владельца.
SELECT hb.racehorse_breed AS breed, ho.name AS owner_name,
       NULLIF(h.breed, hb.id_horse_breed) AS "Порода присутствует у владельца"
FROM horse h JOIN horse_breed hb ON h.breed = hb.id_horse_breed
             JOIN horse_owner ho ON h.id_owner = ho.id_owner;

-- 9. ... функции NVL2:
--
CREATE FUNCTION nvl2(var1 INTEGER, var2 TEXT, var3 TEXT) RETURNS TEXT
LANGUAGE plpgsql
AS $$
BEGIN
RETURN CASE WHEN var1 IS NOT NULL THEN var2 ELSE var3 END;
END;
$$;

SELECT name, age, NVL2(jockey.age, '+', 'n/a') AS age
FROM jockey;

-- 10. ...TOP-N анализа:
-- Выводим 5 жокеев с наибольшей массой тела.
SELECT name, weight FROM (SELECT * FROM jockey ORDER BY weight DESC) AS jw LIMIT 5;

-- 11. ...функции ROLLUP:
-- Выводим информацию по тому, с какими лошадьми по полу работают жокеи
SELECT ho.id_jockey AS horse_owner, h.sex AS horse, COUNT(*) AS horses_num
FROM horse h JOIN jockey ho USING(id_jockey)
GROUP BY ROLLUP(ho.id_jockey, h.sex);

-- 12. ...запрос на использование оператора MERGE языка манипулирования данными:
--
-- создание архивной таблицы
CREATE TABLE archive_competition_results (
  competition_name VARCHAR(64),
  horse_name       VARCHAR(20),
  horse_breed      VARCHAR(64),
  place            INTEGER
);

-- перенос данных в архивную таблицу с помощью оператора MERGE
MERGE INTO archive_competition_results ca
USING (SELECT competition.name AS competition, horse.name AS horse,
              horse_breed.racehourse_breed AS breed, race.place AS place
        FROM horse JOIN horse_breed ON horse.breed = horse_breed.id_horse_breed
                   JOIN race ON horse.id_horse = race.id_horse
                   JOIN competition ON competition.id_competition = rase.id_competition) S
WHEN NOT MATCHED THEN
  INSERT VALUES (S.competition, S.horse, S.breed, S.place);

