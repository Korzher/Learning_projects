WITH pizzas AS (SELECT * FROM menu)
                
SELECT p1.pizza_name AS pizza_name, pz2.name AS pizzeria_name_1, pz1.name AS pizzeria_name_2, p1.price
FROM pizzas p1
INNER JOIN pizzas p2 ON p1.price = p2.price AND p1.pizzeria_id < p2.pizzeria_id AND p1.pizza_name = p2.pizza_name
INNER JOIN pizzeria pz1 ON p1.pizzeria_id = pz1.id
INNER JOIN pizzeria pz2 ON p2.pizzeria_id = pz2.id
ORDER BY pizza_name;