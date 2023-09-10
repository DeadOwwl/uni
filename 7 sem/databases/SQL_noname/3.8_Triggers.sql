CREATE OR REPLACE TRIGGER JOCKEY_CHECK
    BEFORE INSERT ON JOCKEYS
    FOR EACH ROW
BEGIN
    IF :NEW.HEIGHT IS NULL THEN
        RAISE_APPLICATION_ERROR(-20510,'Height is needed!');
    END IF;

    IF :NEW.HEIGHT < 150 THEN
        RAISE_APPLICATION_ERROR(-20511, 'Too short to be a jockey!');
    END IF;
    
    IF :NEW.HEIGHT > 190 THEN
        RAISE_APPLICATION_ERROR(-20512, 'Too high to be a jockey!');
    END IF;

    IF :NEW.WEIGHT IS NULL THEN
        RAISE_APPLICATION_ERROR(-20510,'Weight is needed!');
    END IF;

    IF :NEW.WEIGHT < 50 THEN
        RAISE_APPLICATION_ERROR(-20511, 'Too thin to be a jockey!');
    END IF;
    
    IF :NEW.WEIGHT > 75 THEN
        RAISE_APPLICATION_ERROR(-20512, 'Too chubby to be a jockey!');
    END IF;
END;

INSERT INTO JOCKEYS VALUES
    (5, 'Arseniy', 'Mogilev', 149, 68, to_date('17-06-2002', 'dd-mm-yyyy'));

INSERT INTO JOCKEYS VALUES
    (6, 'Max', 'Serobronx', 191, 80, to_date('04-03-2002', 'dd-mm-yyyy'));

INSERT INTO JOCKEYS VALUES
    (7, 'Danik', 'Hrushevka', 160, 82, to_date('05-08-2002', 'dd-mm-yyyy'));