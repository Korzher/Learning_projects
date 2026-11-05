SELECT menu.pizza_name AS pizza_name, pizzeria.name AS pizzeria_name
FROM person_order
LEFT JOIN (SELECT *
           FROM person
           WHERE person.name = 'Denis' OR person.name = 'Anna') AS client
           ON client.id = person_order.person_id
LEFT JOIN menu
ON person_order.menu_id = menu.id
LEFT JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id
WHERE client.name IS NOT NULL
ORDER BY pizza_name, pizzeria_name