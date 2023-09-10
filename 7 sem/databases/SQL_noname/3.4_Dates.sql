-- 1
-- Требуется используя значения столбца START_DATE получить дату за десять дней до и после приема на работу, 
-- полгода до и после приема на работу, год до и после приема на работу сотрудника JOHN KLINTON.
SELECT STARTDATE, 
ENDDATE,
(STARTDATE - 10), 
(ENDDATE + 10),
ADD_MONTHS(STARTDATE, -6), 
ADD_MONTHS(ENDDATE, 6), 
ADD_MONTHS(STARTDATE, -12), 
ADD_MONTHS(ENDDATE, 12)
FROM CAREER 
WHERE EMPNO = (SELECT EMPNO FROM EMP WHERE EMPNAME = 'JOHN KLINTON');

-- 2
-- Требуется найти разность между двумя датами и представить результат в днях. 
-- Вычислите разницу в днях между датами приема на работу сотрудников JOHN MARTIN и ALEX BOUSH.
SELECT 
((SELECT STARTDATE 
         FROM CAREER 
         WHERE EMPNO = (SELECT EMPNO FROM EMP WHERE EMPNAME = 'ALEX BOUSH')) - 
(SELECT STARTDATE 
        FROM CAREER 
        WHERE EMPNO = (SELECT EMPNO FROM EMP WHERE EMPNAME = 'JOHN MARTIN'))) AS RESULT
FROM DUAL;

-- 3
-- Требуется найти разность между двумя датами в месяцах и в годах.
SELECT 
MONTHS_BETWEEN(SYSDATE, TO_DATE('08-26-1999', 'MM-DD-YYYY')), 
(MONTHS_BETWEEN(SYSDATE, TO_DATE('08-26-1999', 'MM-DD-YYYY')) / 12) AS RESULT
FROM DUAL;

-- 4
-- Требуется определить интервал времени в днях между двумя датами. 
-- Для каждого сотрудника 20-го отделе найти сколько дней прошло между датой его приема на работу и датой приема на работу следующего сотрудника.
SELECT STARTDATE, 
      ((LEAD(STARTDATE, 1) OVER (ORDER BY STARTDATE)) - STARTDATE) AS DAYS_BETWEEN 
FROM CAREER 
WHERE DEPTNO = '20';

-- 5
-- Требуется подсчитать количество дней в году по столбцу START_DATE.
SELECT EXTRACT(YEAR FROM STARTDATE) AS YEAR, 
       (ADD_MONTHS(TRUNC(STARTDATE, 'y'), 12) - TRUNC(STARTDATE, 'y')) AS DAYS
FROM CAREER;

-- 6
-- Требуется разложить текущую дату на день, месяц, год, секунды, минуты, часы. Результаты вернуть в численном виде.
SELECT TO_CHAR(SYSDATE, 'DD.MM.YYYY HH24:MI:SS') AS DATE_CHAR, 
       TO_NUMBER(TO_CHAR(SYSDATE, 'DDMMYYYYHH24MISS')) AS DATE_NUMBER 
FROM DUAL;

-- 7
-- Требуется получить первый и последний дни текущего месяца.
SELECT TRUNC(LAST_DAY(SYSDATE) - 1, 'mm') AS FIRST_DAY,
       SYSDATE,
       LAST_DAY(SYSDATE) AS LAST_DAY
FROM DUAL;

-- 8
-- Требуется возвратить даты начала и конца каждого из четырех кварталов данного года.
SELECT LEVEL AS QUARTER,
       ADD_MONTHS(trunc(sysdate, 'YEAR'), (LEVEL - 1) * 3) AS QUARTER_START,
       ADD_MONTHS(trunc(sysdate, 'YEAR'), LEVEL * 3) - 1 AS QUARTER_END
FROM DUAL 
CONNECT BY LEVEL <= 4;

-- 9
-- Требуется найти все даты года, соответствующие заданному дню недели. Сформируйте список понедельников текущего года.
SELECT * 
FROM (SELECT (trunc(sysdate, 'YEAR') + LEVEL - 1)  AS DAY 
             FROM DUAL
             CONNECT BY LEVEL <= 366)
WHERE TO_CHAR(DAY, 'fmday') = 'monday';