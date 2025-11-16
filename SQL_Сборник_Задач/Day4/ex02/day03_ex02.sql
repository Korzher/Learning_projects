SELECT menu.pizza_name AS pizza_name, menu.price as price, (SELECT name
                                                            FROM pizzeria
                                                            WHERE id = menu.pizzeria_id) as pizzeria_name
FROM menu
WHERE menu.id NOT in (SELECT person_order.menu_id
                      FROM person_order)
ORDER by pizza_name, price