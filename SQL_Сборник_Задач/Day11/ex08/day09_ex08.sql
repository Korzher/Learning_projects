CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop integer DEFAULT 10)
RETURNS TABLE (fibonacci_number integer) AS $$
    WITH RECURSIVE fibonacci AS (
        SELECT 0 as num, 1 as next_num
        UNION ALL
        SELECT next_num, num + next_num
        FROM fibonacci
        WHERE num < pstop
    )
    SELECT num AS fibonacci_number
    FROM fibonacci
    WHERE num < pstop;
$$ LANGUAGE SQL;


-- Проверка срабатывания функции
select * from fnc_fibonacci(100);
select * from fnc_fibonacci();