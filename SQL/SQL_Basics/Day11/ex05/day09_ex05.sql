DROP FUNCTION IF EXISTS fnc_persons_female();
DROP FUNCTION IF EXISTS fnc_persons_male();

CREATE FUNCTION fnc_persons(pgender varchar DEFAULT 'female')
RETURNS TABLE (
    id bigint,
    name varchar,
    age integer,
    gender varchar,
    address varchar
) AS $$
    SELECT id, name, age, gender, address 
    FROM person 
    WHERE gender = pgender;
$$ LANGUAGE SQL;



-- Проверка срабатывания функций
SELECT *
FROM fnc_persons();

SELECT *
FROM fnc_persons(pgender := 'male');

SELECT *
FROM fnc_persons(pgender := 'female');