CREATE VIEW v_price_with_discount
AS SELECT person.name AS person_name, menu.pizza_name AS pizza_name, menu.price AS real_price, CAST(menu.price - menu.price * 0.1 AS INTEGER)
FROM person_order
INNER JOIN person ON person.id = person_order.person_id
INNER JOIn menu ON menu.id = person_order.menu_id
ORDER by person_name, pizza_name;