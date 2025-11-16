SELECT 
    person.address,
    pizzeria.name AS pizzeria_name,
    COUNT(*) AS count_of_orders
FROM person_order
JOIN person ON person.id = person_order.person_id
JOIN menu ON person_order.menu_id = menu.id
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
WHERE person.address = (SELECT address FROM person WHERE person.id = person_order.person_id)
GROUP BY person.address, pizzeria.name
ORDER BY person.address, pizzeria.name;