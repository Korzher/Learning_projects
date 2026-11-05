SELECT menu.pizza_name as pizza_name, menu.price as price, pizzeria.name as pizzeria_name, person_visits.visit_date as visit_date
FROM person
LEFT JOIN person_visits
ON person.id = person_visits.person_id
LEFT JOIN pizzeria
ON person_visits.pizzeria_id = pizzeria.id
LEFT JOIN menu
ON pizzeria.id = menu.pizzeria_id
WHERE person.name = 'Kate' and menu.price BETWEEN 800 AND 1000
ORDER BY pizza_name, price, pizzeria_name