SELECT pizzeria.name AS pizzeria_name
FROm person_visits
JOIn pizzeria ON pizzeria.id = person_visits.pizzeria_id
JOIN person ON person.id = person_visits.person_id
WHERE person.name = 'Andrey'
EXCEPT
SELECT pizzeria.name AS pizzeria_name
FROm person_order
JOIN menu on menu.id = person_order.menu_id
JOIn pizzeria ON pizzeria.id = menu.pizzeria_id
JOIN person ON person.id = person_order.person_id
WHERE person.name = 'Andrey'
ORDER by pizzeria_name