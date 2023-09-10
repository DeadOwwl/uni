DROP TABLE jockey CASCADE;
DROP TABLE horse_owner CASCADE;
DROP TABLE horse CASCADE;
DROP TABLE race CASCADE;
DROP TABLE competition CASCADE;
DROP TABLE horse_breed CASCADE;
DROP SEQUENCE seq_cp CASCADE;
DROP SEQUENCE seq_h CASCADE;
DROP SEQUENCE seq_hb CASCADE;
DROP SEQUENCE seq_jk CASCADE;
DROP SEQUENCE seq_ow CASCADE;
DROP SEQUENCE seq_rd CASCADE;


CREATE TABLE jockey (
    id_jockey INTEGER NOT NULL,
    name      VARCHAR(64) NOT NULL,
    address   VARCHAR(128),
    jockey_date_birth DATE NOT NULL,
    height    VARCHAR(6) NOT NULL,
    weight    INTEGER NOT NULL
);

ALTER TABLE jockey
ADD CONSTRAINT pk_jockey_id PRIMARY KEY (id_jockey);

CREATE SEQUENCE seq_jk
    START 11
    INCREMENT BY 11
    MAXVALUE  1100;


CREATE TABLE horse_owner (
    id_owner INTEGER NOT NULL,
    name 	 VARCHAR(64) NOT NULL,
    address  VARCHAR(128)
);

ALTER TABLE horse_owner
ADD CONSTRAINT pk_horse_owner_id PRIMARY KEY (id_owner);

CREATE SEQUENCE seq_ow
    START 5
    INCREMENT BY 5
    MAXVALUE  100;


CREATE TABLE horse (
    id_horse   INTEGER NOT NULL UNIQUE,
    name       VARCHAR(64) NOT NULL,
    breed      INTEGER NOT NULL,
    horse_date_birth DATE NOT NULL CHECK
        ((DATE_PART('year', NOW() :: DATE) - DATE_PART('year', horse_date_birth :: DATE)) >= 5),
    sex        VARCHAR(7) NOT NULL,
    id_owner   INTEGER NOT NULL,
    id_jockey  INTEGER NOT NULL
);

ALTER TABLE horse
ADD CONSTRAINT pk_horse_id PRIMARY KEY (id_horse, id_owner);

ALTER TABLE horse
ADD CONSTRAINT fk_owner_id FOREIGN KEY (id_owner) REFERENCES horse_owner (id_owner);

ALTER TABLE horse
ADD CONSTRAINT fk_jockey_id FOREIGN KEY (id_jockey) REFERENCES jockey (id_jockey);

CREATE SEQUENCE seq_h
    START 1001
    INCREMENT BY 1
    MAXVALUE  2001;


CREATE TABLE competition (
    id_competition    INTEGER NOT NULL,
    competition_date  DATE NOT NULL,
    competition_time  TIME,
    location 	      VARCHAR(128) DEFAULT 'пос. Ратомка',
    name 	          VARCHAR(64) NOT NULL,
    number_of_races   INTEGER NOT NULL,
    type 	          VARCHAR(128) CHECK
        (type IN ('Выездка', 'Конкур',  'Троеборье', 'Рейнинг', 'Драйвинг', 'Вольтижировка'))
);

ALTER TABLE competition
ADD CONSTRAINT pk_competition_id PRIMARY KEY (id_competition);

CREATE OR REPLACE FUNCTION check_competition_date() RETURNS TRIGGER AS $$
BEGIN
IF NEW.competition_date > CURRENT_DATE OR NEW.competition_date < CURRENT_DATE - INTERVAL '2 YEAR' THEN
RAISE NOTICE 'Неверная дата проведения соревнований. Актуальность: 2 года!';
END IF;
RETURN NEW;
END;
$$ LANGUAGE PLPGSQL;

CREATE TRIGGER trig_check_competition_date
BEFORE UPDATE ON competition
FOR EACH ROW EXECUTE FUNCTION check_competition_date();

CREATE SEQUENCE seq_cp
    START 500
    INCREMENT BY 10
    MAXVALUE  4000;


CREATE TABLE race (
    id_competition INTEGER NOT NULL,
    id_race  INTEGER NOT NULL,
    id_horse INTEGER NOT NULL,
    place    INTEGER NOT NULL
);

ALTER TABLE race
ADD CONSTRAINT fk_horse_id FOREIGN KEY (id_horse) REFERENCES horse (id_horse);

ALTER TABLE race
ADD CONSTRAINT fk_competition_id FOREIGN KEY (id_competition) REFERENCES competition (id_competition);

CREATE SEQUENCE seq_rd
    START 101
    INCREMENT BY 1
    MAXVALUE  1001;


CREATE TABLE horse_breed (
    id_horse_breed  INTEGER NOT NULL,
    racehorse_breed VARCHAR(64) NOT NULL,
    body_type       VARCHAR(64) NOT NULL CHECK (body_type in ('Пони', 'Легкий', 'Тяжелый'))
);

ALTER TABLE horse_breed
ADD CONSTRAINT pk_horse_breed_id PRIMARY KEY (id_horse_breed);

ALTER TABLE horse
ADD CONSTRAINT fk_horse_breed_id FOREIGN KEY (breed) REFERENCES horse_breed (id_horse_breed);

CREATE SEQUENCE seq_hb
    START 100
    INCREMENT BY 10
    MAXVALUE  1000;