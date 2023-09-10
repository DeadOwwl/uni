--1
ALTER TABLE salary ADD(tax number(15))

--2 а)
DECLARE
    yearsalary number(10);
    CURSOR some_cursor IS SELECT * FROM salary FOR UPDATE OF tax;
    some_cursor_row some_cursor%rowtype;
BEGIN
    OPEN some_cursor;
    LOOP
        fetch some_cursor into some_cursor_row;
        exit when some_cursor%notfound;
        select sum(salvalue) into yearsalary from salary
            where salary.empno = some_cursor_row.empno and salary.month <= some_cursor_row.month and salary.year = some_cursor_row.year;
        IF yearsalary <= 20000 THEN
            update salary set tax = some_cursor_row.salvalue * 0.09
                where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
        ELSIF yearsalary <= 30000 THEN
            update salary set tax = some_cursor_row.salvalue * 0.12
                where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
        ELSE
            update salary set tax = some_cursor_row.salvalue * 0.15
                where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
        END IF;
    END LOOP;
    CLOSE some_cursor;
    COMMIT;
END;

--2 б)
DECLARE
    yearsalary number(10);
    CURSOR some_cursor is select * from salary for update of tax;
    some_cursor_row some_cursor%rowtype;
BEGIN
    OPEN some_cursor;
    LOOP
        fetch some_cursor into some_cursor_row;
        exit when some_cursor%notfound;
        select sum(salvalue) into yearsalary from salary
            where salary.empno = some_cursor_row.empno and salary.month <= some_cursor_row.month and salary.year = some_cursor_row.year;
        update salary set tax =
            CASE
                WHEN yearsalary <= 20000 THEN some_cursor_row.salvalue * 0.09
                WHEN yearsalary <= 30000 THEN some_cursor_row.salvalue * 0.12
                ELSE some_cursor_row.salvalue * 0.15
            END
            where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
    END LOOP;
    CLOSE some_cursor;
    COMMIT;
END;

--2 в)
DECLARE
    cursor some_cursor is select * from salary for update of tax;
    some_cursor_row some_cursor%rowtype;
    yearsalary number(10);
BEGIN
    FOR some_cursor_row in some_cursor
    LOOP        
        select sum(salvalue) into yearsalary from salary
            where salary.empno = some_cursor_row.empno and salary.month <= some_cursor_row.month and salary.year = some_cursor_row.year;
        update salary set tax =
            CASE
                WHEN yearsalary <= 20000 THEN some_cursor_row.salvalue * 0.09
                WHEN yearsalary <= 30000 THEN some_cursor_row.salvalue * 0.12
                ELSE some_cursor_row.salvalue * 0.15
            END
            where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
    END LOOP;
    COMMIT;
END;

--2 г)
DECLARE
    cursor some_cursor(empid number) is 
          select * from salary where empno = empid for update of tax;
    some_cursor_row some_cursor%rowtype;
    yearsalary number(10);
BEGIN
    FOR empid in (select empno from emp)
    LOOP
        OPEN some_cursor(empid.empno);
          LOOP
              fetch some_cursor into some_cursor_row;
              exit when some_cursor%notfound;
                   select sum(salvalue) into yearsalary from salary
                          where salary.empno = empid.empno and salary.month <= some_cursor_row.month and salary.year = some_cursor_row.year;
                   update salary set tax =
                          CASE
                              WHEN yearsalary <= 20000 THEN some_cursor_row.salvalue * 0.09
                              WHEN yearsalary <= 30000 THEN some_cursor_row.salvalue * 0.12
                              ELSE some_cursor_row.salvalue * 0.15
                          END
                  where empno = empid.empno and month = some_cursor_row.month and year = some_cursor_row.year;
           END LOOP;
           CLOSE some_cursor;
    END LOOP;
END;

--3 а)
create or replace procedure tax_count_function as
    cursor some_cursor is select * from salary for update of tax;
    some_cursor_row some_cursor%rowtype;
    yearsalary number(10);
BEGIN
    OPEN some_cursor;
    LOOP
        fetch some_cursor into some_cursor_row;
        exit when some_cursor%notfound;
        select sum(salvalue) into yearsalary from salary
            where salary.empno = some_cursor_row.empno and salary.month <= some_cursor_row.month and salary.year = some_cursor_row.year;
        IF yearsalary <= 20000 THEN
            update salary set tax = some_cursor_row.salvalue * 0.09
                where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
        ELSIF yearsalary <= 30000 THEN
            update salary set tax = some_cursor_row.salvalue * 0.12
                where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
        ELSE
            update salary set tax = some_cursor_row.salvalue * 0.15
                where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
        END IF;
    END LOOP;
    CLOSE some_cursor;
    COMMIT;
END tax_count_function;
BEGIN
    tax_count_function;
END;

--3 б)
create or replace procedure tax_count_function as
    cursor some_cursor is select * from salary for update of tax; 
    some_cursor_row some_cursor%rowtype;
	yearsalary number(10);
BEGIN
    OPEN some_cursor;
    LOOP
        fetch some_cursor into some_cursor_row;
        exit when some_cursor%notfound;
        select sum(salvalue) into yearsalary from salary
            where salary.empno = some_cursor_row.empno and salary.month <= some_cursor_row.month and salary.year = some_cursor_row.year;
        update salary set tax =
            CASE
                WHEN yearsalary <= 20000 THEN some_cursor_row.salvalue * 0.09
                WHEN yearsalary <= 30000 THEN some_cursor_row.salvalue * 0.12
                ELSE some_cursor_row.salvalue * 0.15
            END
            where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
    END LOOP;
    CLOSE some_cursor;
    COMMIT;
END tax_count_function;
BEGIN
    tax_count_function;
END;

--3 в)
create or replace procedure tax_count_function as
    cursor some_cursor is select * from salary for update of tax; 
    some_cursor_row some_cursor%rowtype;
    yearsalary number(10);
BEGIN
    for some_cursor_row in some_cursor
    LOOP
        select sum(salvalue) into yearsalary from salary
            where salary.empno = some_cursor_row.empno and salary.month <= some_cursor_row.month and salary.year = some_cursor_row.year;
        update salary set tax =
            CASE
                WHEN yearsalary <= 20000 THEN some_cursor_row.salvalue * 0.09
                WHEN yearsalary <= 30000 THEN some_cursor_row.salvalue * 0.12
                ELSE some_cursor_row.salvalue * 0.15
            END
            where empno = some_cursor_row.empno and month = some_cursor_row.month and year = some_cursor_row.year;
    END LOOP;
    COMMIT;
END tax_count_function;
BEGIN
    tax_count_function;
END;

--3 г)
create or replace procedure tax_count_function as 
    cursor some_cursor(empid number) is 
          select * from salary where empno = empid for update of tax;
    some_cursor_row some_cursor%rowtype;
    yearsalary number(10);
BEGIN
    for empid in (select empno from emp)
    LOOP
        OPEN some_cursor(empid.empno);
          LOOP
              fetch some_cursor into some_cursor_row;
              exit when some_cursor%notfound;
                   select sum(salvalue) into yearsalary from salary
                          where salary.empno = empid.empno and salary.month <= some_cursor_row.month and salary.year = some_cursor_row.year;
                   update salary set tax =
                          CASE
                              WHEN yearsalary <= 20000 THEN some_cursor_row.salvalue * 0.09
                              WHEN yearsalary <= 30000 THEN some_cursor_row.salvalue * 0.12
                          ELSE some_cursor_row.salvalue * 0.15
                          END
                  where empno = empid.empno and month = some_cursor_row.month and year = some_cursor_row.year;
           END LOOP;
           CLOSE some_cursor;
    END LOOP;
END tax_count_function;
BEGIN
    tax_count_function;
END;

--4
create or replace procedure tax_count_by_id(tax1 number, tax2 number, tax3 number, id number) as
    cursor some_cursor is select * from salary
        where empno = id
        for update of tax;
    yearsalary number(10);
BEGIN
    for ind in some_cursor LOOP
       select sum(salvalue) into yearsalary from salary
            where salary.empno = ind.empno and month <= ind.month and year = ind.year;
        update salary set tax =
            CASE
                WHEN yearsalary <= 20000 THEN ind.salvalue * tax1
                WHEN yearsalary <= 30000 THEN ind.salvalue * tax2
                ELSE ind.salvalue * tax3
            END
            where empno = ind. empno and month = ind.month and year = ind.year;
    END LOOP;
    COMMIT;
END tax_count_by_id;
BEGIN
    tax_count_by_id(0.09, 0.12, 0.15, 8000);
END;

--5
create or replace function count_total_tax(tax1 number, tax2 number, tax3 number, empid number) return number as
    cursor some_cursor is select * from salary
        where empno = empid;
    yearsalary number(10);
    count_total_tax number(6);
BEGIN
    count_total_tax := 0;
    for ind in some_cursor LOOP
        select sum(salvalue) into yearsalary from salary
            where salary.empno = ind.empno and month <= ind.month and year = ind.year;
        count_total_tax := count_total_tax +
            CASE
                WHEN yearsalary <= 20000 THEN ind.salvalue * tax1
                WHEN yearsalary <= 30000 THEN ind.salvalue * tax2
                ELSE ind.salvalue * tax3
            END;
    END LOOP;
    RETURN count_total_tax;
END;
select empno, count_total_tax(0.09, 0.12, 0.15, empno) from salary;

--6
create or replace package count_taxes_package as
    procedure tax_all;
    procedure  tax_emp(id number);
    function sum_total_tax(id number, tax1 number, tax2 number, tax3 number) return number;
END count_taxes_package;
create or replace package body count_taxes_package as
    procedure tax_all as
        cursor cursor_all is
                select * from salary for update of tax;
        some_cursor_row cursor_all%rowtype;
        yearsalary number(10);
        BEGIN
          for some_cursor_row in cursor_all
          LOOP
              select sum(salvalue) into yearsalary from salary
              where empno = some_cursor_row.empno and year = some_cursor_row.year and month <= some_cursor_row.month;
              update salary set tax = 
		CASE
			WHEN yearsalary <= 20000 THEN some_cursor_row.salvalue * 0.09
			WHEN yearsalary <= 30000 THEN some_cursor_row.salvalue * 0.12
			ELSE some_cursor_row.salvalue * 0.15
		END
            where empno = some_cursor_row.empno and year = some_cursor_row.year and month = some_cursor_row.month and salvalue = some_cursor_row.salvalue;
            END LOOP;
	COMMIT;
        END;
procedure tax_emp(id number) as	
	cursor cursor_emp is
                select * from salary where empno = id for update of tax;
        yearsalary number(10);	
BEGIN
	for ind in cursor_emp LOOP
		select sum(salvalue) into yearsalary from salary
			where salary.empno = ind.empno and month <= ind.month and year = ind.year;
		update salary set tax =
			CASE
				WHEN yearsalary <= 20000 THEN ind.salvalue * 0.09
				WHEN yearsalary <= 30000 THEN ind.salvalue * 0.12
				ELSE ind.salvalue * 0.15
			END
			where empno = ind.empno and month = ind.month and year = ind.year;
		END LOOP;
		COMMIT;
END tax_emp;
	function sum_total_tax(tax1 number, tax2 number, tax3 number, id number) return number as
	yearsalary number(10);
    total_tax number(6);
	BEGIN
        total_tax := 0;
        select sum(salvalue) into yearsalary from salary
                  where empno = id;
            total_tax := 
		CASE
			WHEN yearsalary <= 20000 THEN yearsalary * tax1
			WHEN yearsalary <= 30000 THEN yearsalary * tax2
			ELSE yearsalary * tax3
		END;
            RETURN total_tax;
        END;
END count_taxes_package;
BEGIN
    count_taxes_package.tax_all;
END;
BEGIN
    count_taxes_package.tax_emp(7790);
END;
BEGIN
    select empno, count_taxes_package.sum_total_tax(0.09, 0.12, 0.15, empno) from salary;
END;

--7
create or replace trigger salary_trigger
    before update of salvalue on salary
    for each row
DECLARE
    cursor cursor_sal(id number) is
        select minsalary from job join career on (job.jobno = career.jobno) where career.enddate is null;
    cursor_row job.minsalary%type;
    BEGIN
        OPEN cursor_sal(:new.empno);
	fetch cursor_sal into cursor_row;
	IF (:new.salvalue < cursor_row) THEN
		:new.salvalue := :old.salvalue;
	END IF;
	CLOSE cursor_sal;
    END;

--8
create or replace trigger career_trigger
    before delete on career
    for each row
BEGIN
    IF :old.enddate is null THEN
        dbms_output.put_line('ENDDATE field is NULL');
    END IF;
END;

--9
create or replace trigger birthdate_trigger
    before insert or update on emp
    for each row
    BEGIN
        IF :new.birthdate is null THEN
            dbms_output.put_line('birthdate is null');
        END IF;
        IF :new.birthdate < to_date('01-01-1940', 'dd-mm-yyyy') THEN
            dbms_output.put_line('pentiona');
        END IF;
        :new.empname := upper(:new.empname);
    END;

--10
create or replace function varchar2_to_number(str varchar2) return number as
    BEGIN
        return to_number(str);
    EXCEPTION
        WHEN value_error THEN
             dbms_output.put_line('error: argument is not a number');
             return null;
        WHEN others THEN
             raise_application_error(-20000, 'unexpected error');
             return null;
    END;
BEGIN
    dbms_output.put_line(varchar2_to_number('10'));
    dbms_output.put_line(varchar2_to_number('2,7182818'));
    dbms_output.put_line(varchar2_to_number('3.1415926'));
    dbms_output.put_line(varchar2_to_number('some_word'));
END;