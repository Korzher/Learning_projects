-- views из пятого дня sql
CREATE VIEW v_persons_female
AS SELECT * FROM person
WHERE gender = 'female';
CREATE VIEW v_persons_male
AS SELECT * FROM person
WHERE gender = 'male';

-- Функция для возврата женщин
CREATE FUNCTION fnc_persons_female()
RETURNS TABLE (
    id bigint,
    name varchar,
    age integer,
    gender varchar,
    address varchar
) AS $$
    SELECT id, name, age, gender, address 
    FROM person 
    WHERE gender = 'female';
$$ LANGUAGE SQL;

-- Функция для возврата мужчин
CREATE FUNCTION fnc_persons_male()
RETURNS TABLE (
    id bigint,
    name varchar,
    age integer,
    gender varchar,
    address varchar
) AS $$
    SELECT id, name, age, gender, address 
    FROM person 
    WHERE gender = 'male';
$$ LANGUAGE SQL;



-- Проверка срабатывания функций
SELECT *
FROM fnc_persons_male();

SELECT *
FROM fnc_persons_female();