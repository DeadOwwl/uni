-- 1
-- Требуется представить имя каждого сотрудника таблицы EMP, а также имя его руководителя.
SELECT A.EMPNAME, B.EMPNAME AS EMP_MANAGER 
FROM EMP A 
JOIN EMP B 
ON A.MANAGER_ID = B.EMPNO
ORDER BY A.MANAGER_ID; 

-- 2
-- Требуется представить имя каждого сотрудника таблицы EMP (даже сотрудника, которому не назначен руководитель) и имя его руководителя.
SELECT EMPNAME, PRIOR EMPNAME AS EMP_MANAGER
FROM EMP
START WITH MANAGER_ID IS NULL
CONNECT BY PRIOR EMPNO = MANAGER_ID; 

-- 3
-- Требуется показать иерархию от CLARK до JOHN KLINTON.
SELECT LTRIM(SYS_CONNECT_BY_PATH(EMPNAME, ' -> '), ' -> ') AS EMP_TREE
FROM EMP
WHERE EMPNAME = 'JOHN KLINTON'
START WITH EMPNAME = 'CLARK'
CONNECT BY EMPNO = PRIOR MANAGER_ID;

-- 4
-- Требуется получить результирующее множество, описывающее иерархию всей таблицы.
SELECT (LTRIM(SYS_CONNECT_BY_PATH(EMPNAME, ' -> '), ' -> ')) AS TREE
FROM EMP
START WITH MANAGER_ID IS NULL
CONNECT BY PRIOR EMPNO = MANAGER_ID;

-- 5
-- Требуется показать уровень иерархии каждого сотрудника.
SELECT rpad('*', LEVEL, '*') || EMPNAME AS TREE
FROM EMP
START WITH MANAGER_ID IS NULL
CONNECT BY PRIOR EMPNO = MANAGER_ID
ORDER BY LEVEL;

-- 6
-- Требуется найти всех служащих, которые явно или неявно подчиняются ALLEN.
SELECT EMPNAME
FROM EMP
START WITH EMPNAME = 'ALLEN'
CONNECT BY PRIOR EMPNO = MANAGER_ID;