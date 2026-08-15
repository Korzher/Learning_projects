CREATE OR REPLACE FUNCTION func_minimum(VARIADIC arr numeric[])
RETURNS numeric AS $$
    SELECT MIN(unnested_value)
    FROM UNNEST(arr) AS unnested_value;
$$ LANGUAGE SQL;

-- Проверка срабатывания функции
SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);