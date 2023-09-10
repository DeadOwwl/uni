DROP TABLE stable_obj_table; 
DROP TABLE stable_ref_table; 

-- Создать объект
CREATE OR REPLACE TYPE stable_ty AS OBJECT
    (name VARCHAR(50),
    address VARCHAR(300),
    email VARCHAR(50),
    owner_id NUMBER(3),
    MEMBER FUNCTION getOwner RETURN VARCHAR
    );

CREATE OR REPLACE TYPE BODY stable_ty AS
    MEMBER FUNCTION getOwner RETURN VARCHAR IS 
            owner_var VARCHAR(300);
        BEGIN 
            SELECT name INTO owner_var
                FROM owners
                WHERE id = owner_id; 
            RETURN owner_var; 
        END; 
    END;

-- Создать таблицу-объект
CREATE TABLE stable_obj_table OF stable_ty;

-- Выполнить вставку строк в таблицу-объект
INSERT INTO stable_obj_table VALUES ('Конюшня №1', '10, Artem Moroz Rd, London', 'konushnya1@gmail.com', 1);
INSERT INTO stable_obj_table VALUES ('Конюшня №2', '15, SUBD Ln, London', 'konushnya2@gmail.com', 1);
INSERT INTO stable_obj_table VALUES ('Конюшня №3', '100, 5th Av, NYC', 'konushnya3@gmail.com', 2);
INSERT INTO stable_obj_table VALUES ('Конюшня №4', '1, Battery Prk, NYC', 'konushnya4@gmail.com', 2);

-- создать таблицу, содержащую столбец-объект
CREATE TABLE stable_ref_table (
    id NUMBER PRIMARY KEY,
    stable REF stable_ty);

-- Заполнить столбец-объект, т.е. указать данные, на которые ссылается столбец-объект
INSERT INTO stable_ref_table
    SELECT 1, REF(b) 
        FROM stable_obj_table b 
        WHERE name = 'Конюшня №1';

INSERT INTO stable_ref_table
    SELECT 2, REF(b) 
        FROM stable_obj_table b 
        WHERE name = 'Конюшня №2';

INSERT INTO stable_ref_table
    SELECT 3, REF(b) 
        FROM stable_obj_table b 
        WHERE name = 'Конюшня №3';

INSERT INTO stable_ref_table
    SELECT 4, REF(b) 
        FROM stable_obj_table b 
        WHERE name = 'Конюшня №4';

-- Выполнить выборку данных из таблицы, содержащей столбец-объект
SELECT *
    FROM stable_obj_table p;

SELECT id, DEREF(stable).name AS "Название", DEREF(stable).address AS "Адрес", DEREF(stable).getOwner() AS "Владелец" 
    FROM stable_ref_table;

-- Выполнить обновление данных  таблицы, содержащей столбец-объект
UPDATE stable_obj_table
    SET address = 'Париж'
    WHERE name = 'Конюшня №1';

UPDATE stable_obj_table
    SET address = '10, Artem Moroz Rd, London'
    WHERE name = 'Конюшня №1';

-- Выполнить удаление данных из таблицы, содержащей столбец-объект
DELETE FROM stable_obj_table
    WHERE name = 'Конюшня №4';