SELECT menu.id AS menu_id
FROM menu
WHERE menu.id NOT in (SELECT person_order.menu_id
                      FROM person_order)
ORDER by menu_id