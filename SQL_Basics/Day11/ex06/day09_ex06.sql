CREATE FUNCTION fnc_person_visits_and_eats_on_date(
    pperson varchar DEFAULT 'Dmitriy',
    pprice numeric DEFAULT 500,
    pdate date DEFAULT '2022-01-08'
)
RETURNS TABLE (
    pizzeria_name varchar
) AS $$
BEGIN
    RETURN QUERY
    SELECT DISTINCT pz.name AS pizzeria_name
    FROM person_visits pv
    JOIN person p ON p.id = pv.person_id
    JOIN pizzeria pz ON pz.id = pv.pizzeria_id
    JOIN menu m ON m.pizzeria_id = pz.id
    WHERE p.name = pperson
      AND m.price < pprice
      AND pv.visit_date = pdate;
END;
$$ LANGUAGE plpgsql;



-- Проверка срабатывания функций
select *  
from fnc_person_visits_and_eats_on_date(pprice := 800);

select *  
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');