SELECT 
	person.name AS name, 
    menu.pizza_name AS pizza_name, 
    menu.price AS price, 
    CAST(menu.price - (menu.price * person_discounts.discount) / 100 AS INT) as discount_price, 
    pizzeria.name AS pizzeria_name
FROM person_discounts
JOIN pizzeria on pizzeria.id = person_discounts.pizzeria_id
JOIN person ON person.id = person_discounts.person_id
JOIN menu ON menu.pizzeria_id = pizzeria.id
JOIN person_order ON person_order.person_id = person.id AND person_order.menu_id = menu.id
ORDER BY person.name, menu.pizza_name;