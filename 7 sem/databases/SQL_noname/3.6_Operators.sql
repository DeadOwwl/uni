--1. простого оператора CASE ();
SELECT NICK, BIRTH,
    CASE
        WHEN SEX LIKE 'Male'
            THEN 'M'
        WHEN SEX LIKE 'Female'
            THEN 'F'
        ELSE 'N/A'
    END AS SEX
    FROM HORSES


--2. поискового оператора CASE();
SELECT NAME, WEIGHT, HEIGHT,
    CASE
        WHEN WEIGHT + HEIGHT < 250
            THEN 'OK'
        ELSE NULL
    END
    FROM JOCKEYS


--3. оператора WITH();
WITH horse AS (SELECT * FROM HORSES)
SELECT * FROM horse WHERE Sex = 'Male'


--4. встроенного представления();
SELECT JOCKEY_NAME, OWNER_NAME, NICK AS HORSE_NICK FROM
    (SELECT OWNER_ID, JOCKEY_ID, NICK FROM HORSES) H
    JOIN (SELECT ID, NAME AS OWNER_NAME FROM OWNERS) O
    ON O.ID = H.OWNER_ID
    JOIN (SELECT ID, NAME AS JOCKEY_NAME FROM JOCKEYS) J
    ON J.ID = H.JOCKEY_ID


--5. некоррелированного запроса (Вывести имена жокеев старше 25 лет)
SELECT NAME FROM JOCKEYS WHERE MONTHS_BETWEEN (SYSDATE, BIRTH) / 12 > 25


--6. коррелированного запроса (Вывести имена жокеев, лошади которых принадлежат 'Mr Sammers')
SELECT NAME FROM JOCKEYS J
    JOIN (SELECT JOCKEY_ID FROM HORSES H
        JOIN (SELECT ID FROM OWNERS WHERE NAME = 'Mr Sammers') O
            ON H.OWNER_ID = O.ID) I
        ON J.ID = I.JOCKEY_ID


--7. функции NULLIF
SELECT NAME, ADDRESS, WEIGHT, HEIGHT, BIRTH, NULLIF(HEIGHT, 182) FROM JOCKEYS


--8. функции NVL2
SELECT NAME, NVL2(HEIGHT, HEIGHT, 0) FROM JOCKEYS


--9. TOP-N анализа (Вывести TOP-3 по всем заездам).
SELECT *
    FROM (SELECT *
        FROM RESULTS
        ORDER BY POSITION DESC)
    WHERE ROWNUM <= 3;


--10. функции ROLLUP(). Вывести статистику занимаемых позиций каждой лошадью
SELECT HORSE_ID, POSITION, COUNT(POSITION)
    FROM RESULTS
    GROUP BY ROLLUP(HORSE_ID, POSITION)

--11. Составьте запрос на использование оператора MERGE языка манипулирования данными.
CREATE TABLE
    NEW_RaceAreas
    (
        RaceArea_ID NUMBER(10) PRIMARY KEY,
        RaceArea_Address VARCHAR2(300) NOT NULL,
        RaceArea_MaxNumOfGuests NUMBER(10) NOT NULL
            CHECK (RaceArea_MaxNumOfGuests > 0),
        RaceArea_Square NUMBER(10)
            CHECK (RaceArea_Square > 0)
    );

INSERT INTO NEW_RaceAreas VALUES
    (1, 'Knighton, Powys LD7 1DL, United Kingdom', 3000, 5000);

INSERT INTO NEW_RaceAreas VALUES
    (2, 'Ketley Bank, Telford, Telford and Wrekin TF2 0EB, United Kingdom', 12000, 11000);

INSERT INTO NEW_RaceAreas VALUES
    (3, '85 Llanelian Rd, Old Colwyn, Colwyn Bay, Conwy LL29 8UN, Great Bitain', 3000, 4000);

CREATE TABLE
    RaceAreas
    (
        RaceArea_ID NUMBER(10) PRIMARY KEY,
        RaceArea_Address VARCHAR2(300) NOT NULL,
        RaceArea_MaxNumOfGuests NUMBER(10) NOT NULL
            CHECK (RaceArea_MaxNumOfGuests > 0),
        RaceArea_Square NUMBER(10)
            CHECK (RaceArea_Square > 0)
    );

CREATE SEQUENCE RaceArea_ID_Generator
    INCREMENT BY 1
    START WITH 1
    NOMAXVALUE
    NOCYCLE;

MERGE INTO RaceAreas ra
    USING (SELECT *
        FROM NEW_RaceAreas) newra
        ON (ra.RaceArea_Address = newra.RaceArea_Address)
    WHEN MATCHED THEN
        UPDATE SET ra.RaceArea_MaxNumOfGuests = newra.RaceArea_MaxNumOfGuests
    WHEN NOT MATCHED THEN
        INSERT (ra.RaceArea_ID, ra.RaceArea_Address, ra.RaceArea_MaxNumOfGuests, ra.RaceArea_Square)
        VALUES (RaceArea_ID_Generator.NEXTVAL, newra.RaceArea_Address, newra.RaceArea_MaxNumOfGuests, newra.RaceArea_Square);

SELECT * FROM RaceAreas;