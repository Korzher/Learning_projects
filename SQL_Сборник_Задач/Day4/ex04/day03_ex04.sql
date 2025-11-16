SELECT pizzeria.name AS pizzeria_name
FROM person_order
JOIN menu ON person_order.menu_id = menu.id
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
JOIN person ON person_order.person_id = person.id
GROUP BY pizzeria.name
HAVING COUNT(*) FILTER (WHERE person.gender = 'male') = 0 AND
	   COUNT(*) FILTER (WHERE person.gender = 'female') > 0
UNION
SELECT pizzeria.name AS pizzeria_name
FROM person_order
JOIN menu ON person_order.menu_id = menu.id
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
JOIN person ON person_order.person_id = person.id
GROUP BY pizzeria.name
HAVING COUNT(*) FILTER (WHERE person.gender = 'female') = 0 AND
	   COUNT(*) FILTER (WHERE person.gender = 'male') > 0
ORDER by pizzeria_name