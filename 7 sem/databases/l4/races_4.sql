-- 1. Добавить  в базу данных сведения о новом участнике соревнований.
-- На период соревнований наезднику выделяется самая молодая лошадь.
INSERT INTO jockey VALUES (NEXTVAL('seq_jk'), 'Бондер', 'Осло',
                           TO_DATE('19.02.2003','DD.MM.YYYY'), 1.65, 55);
UPDATE horse SET id_jockey = (SELECT MAX(id_jockey) FROM jockey)
WHERE horse_date_birth = (SELECT MAX(horse_date_birth) FROM horse);

-- 2. Перенести время проведения заезда на 2 дня,
-- если количество участников менее 10.
WITH competition_memebers AS (SELECT DISTINCT comp.id_competition, COUNT(hrs.id_jockey) AS members_num
    FROM competition comp JOIN race rc ON comp.id_competition = rc.id_competition
                          JOIN horse hrs ON rc.id_horse = hrs.id_horse
                          JOIN jockey jck ON hrs.id_jockey = jck.id_jockey
    GROUP BY comp.id_competition)
UPDATE competition SET competition_date = competition_date - INTERVAL '2 DAYS'
WHERE competition.id_competition = (SELECT competition_memebers.id_competition
                                    FROM competition_memebers
                                    WHERE competition_memebers.members_num < 10);

-- 3.Удалить из базы данных сведения о жокеях, которые не принимали участия в 5 соревнованиях подряд.
-- Сохранить архивную информацию: имя, кличка лошади, дата последнего участия, количество призовых мест.
CREATE TABLE archive_jockey (
    jockey_name VARCHAR(60) NOT NULL PRIMARY KEY,
    horse_name  VARCHAR(60) NOT NULL,
    last_competition_date DATE NOT NULL,
    num_price_places INTEGER NOT NULL
);

WITH jockey_horse_name AS (SELECT j.id_jockey, j.name AS jockey_name, h.id_horse, h.name AS horse_name,
                                  c.competition_date, r.place AS place
                                            FROM jockey j JOIN horse h ON j.id_jockey = h.id_jockey
                                            JOIN race r ON r.id_horse = h.id_horse
                                            JOIN competition c ON c.id_competition = r.id_competition
    WHERE j.id_jockey IN (SELECT id_jockey FROM horse
                       WHERE id_horse NOT IN (SELECT id_horse FROM race
                       WHERE race.id_competition IN
                            (SELECT id_competition FROM
                            (SELECT id_competition FROM competition ORDER BY id_competition DESC)
                                AS jw LIMIT 5)))
    AND j.id_jockey NOT IN (SELECT id_jockey FROM horse
                       WHERE id_horse IN (SELECT id_horse FROM race
                       WHERE race.id_competition IN
                            (SELECT id_competition FROM
                            (SELECT id_competition FROM competition ORDER BY id_competition DESC)
                                AS jw LIMIT 5))))
INSERT INTO archive_jockey (SELECT jockey_name, horse_name, TO_DATE('19.02.2003','DD.MM.YYYY'),
                                    COUNT(place) FROM jockey_horse_name
WHERE place IN (1, 2, 3)
GROUP BY (jockey_name, horse_name));

UPDATE archive_jockey
SET last_competition_date = (SELECT MAX(competition_date) FROM competition
                                   JOIN race ON competition.id_competition = race.id_competition
                                   JOIN horse ON race.id_horse = horse.id_horse
                                   JOIN jockey j on horse.id_jockey = j.id_jockey
                                   JOIN archive_jockey ON archive_jockey.jockey_name = j.name
                WHERE archive_jockey.jockey_name IN (SELECT j.name AS jockey_name
                                    FROM jockey j JOIN horse h ON j.id_jockey = h.id_jockey
                                    JOIN race r ON r.id_horse = h.id_horse
                                    JOIN competition c ON c.id_competition = r.id_competition
                WHERE j.id_jockey IN (SELECT id_jockey FROM horse
                       WHERE id_horse NOT IN (SELECT id_horse FROM race
                       WHERE race.id_competition IN
                            (SELECT id_competition FROM
                            (SELECT id_competition FROM competition ORDER BY id_competition DESC)
                                AS jw LIMIT 5)))
                AND j.id_jockey NOT IN (SELECT id_jockey FROM horse
                       WHERE id_horse IN (SELECT id_horse FROM race
                       WHERE race.id_competition IN
                            (SELECT id_competition FROM
                            (SELECT id_competition FROM competition ORDER BY id_competition DESC)
                                AS jw LIMIT 5)))))
WHERE archive_jockey.jockey_name IN (SELECT j.name AS jockey_name
                                            FROM jockey j JOIN horse h ON j.id_jockey = h.id_jockey
                                            JOIN race r ON r.id_horse = h.id_horse
                                            JOIN competition c ON c.id_competition = r.id_competition
    WHERE j.id_jockey IN (SELECT id_jockey FROM horse
                       WHERE id_horse NOT IN (SELECT id_horse FROM race
                       WHERE race.id_competition IN
                            (SELECT id_competition FROM
                            (SELECT id_competition FROM competition ORDER BY id_competition DESC)
                                AS jw LIMIT 5)))
    AND j.id_jockey NOT IN (SELECT id_jockey FROM horse
                       WHERE id_horse IN (SELECT id_horse FROM race
                       WHERE race.id_competition IN
                            (SELECT id_competition FROM
                            (SELECT id_competition FROM competition ORDER BY id_competition DESC)
                                AS jw LIMIT 5))));

UPDATE horse SET id_jockey = (SELECT id_jockey FROM jockey
        WHERE jockey_date_birth = (SELECT MIN(jockey_date_birth) FROM jockey))
WHERE horse.name = (SELECT horse_name FROM archive_jockey);

DELETE FROM jockey
WHERE jockey.name IN (SELECT jockey_name FROM archive_jockey);