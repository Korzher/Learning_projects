SELECT person.name as person_name, menu.pizza_name as pizza_name, pizzeria.name as pizzeria_name
FROM person_order
JOIN person on person.id = person_order.person_id
JOIN menu on menu.id = person_order.menu_id
JOIN pizzeria on menu.pizzeria_id = pizzeria.id
ORDER BY person_name asc, pizza_name asc, pizzeria_name asc