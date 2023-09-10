-- 1. Вывести список участников каждого соревнования.
DROP VIEW view_competitors CASCADE;

CREATE VIEW view_competitors AS (SELECT c.name AS competition,
                                 STRING_AGG(DISTINCT j.name, ', ') AS jockeys
                                       FROM jockey j
                                       JOIN horse h ON j.id_jockey = h.id_jockey
                                       JOIN race r ON r.id_horse = h.id_horse
                                       JOIN competition C ON r.id_competition = C.id_competition
                                       GROUP BY c.name
                                       ORDER BY c.name);

SELECT * FROM view_competitors;

-- 2. Определить средний возраст лошади в каждом заезде.
DROP VIEW view_average_age CASCADE;

CREATE VIEW view_average_age AS (SELECT id_competition, id_race,
                        AVG(DATE_PART('YEAR', AGE(horse_date_birth)))::INT AS average_horse_age
                            FROM race JOIN horse ON race.id_horse = horse.id_horse
                            GROUP BY (id_competition, id_race)
                            ORDER BY (id_competition, id_race));

SELECT * FROM view_average_age;

-- 3. Вывести список самых результативных участников соревнований в каждой категории.
DROP VIEW view_the_best_jockeys CASCADE;

CREATE VIEW view_the_best_jockeys AS (WITH grouped_table AS
    (SELECT c2.type AS competition_type, j2.name AS jockey_name, AVG(place) AS average
     FROM race r2 JOIN competition c2 ON r2.id_competition = c2.id_competition
                  JOIN horse h2 ON r2.id_horse = h2.id_horse
                  JOIN jockey j2 ON h2.id_jockey = j2.id_jockey
     GROUP BY c2.type, j2.name
     ORDER BY (c2.type, j2.name))
SELECT g.competition_type, g.jockey_name
FROM (SELECT competition_type, MIN(AVERAGE) AS mn FROM grouped_table GROUP BY competition_type) as t
JOIN grouped_table g ON g.competition_type = t.competition_type AND g.average = t.mn);

SELECT * FROM view_the_best_jockeys;
