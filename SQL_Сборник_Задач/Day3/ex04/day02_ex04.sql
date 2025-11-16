SELECT menu.pizza_name as pizza_name, pizzeria.name as pizzeria_name, menu.price AS price
FROM menu
LEFT JOIN pizzeria
on pizzeria.id = menu.pizzeria_id
WHERE pizza_name LIKE '%mushroom%' OR pizza_name LIKE '%pepperoni%'
ORDER BY pizza_name, pizzeria_name