INSERT INTO person_order (id, person_id, menu_id, order_date)
VALUES ((SELECT MAX(person_order.id) from person_order) + 1, 
        (SELECT id from person
         WHERE person.name = 'Denis'), 
        (SELECT id FROM menu
         WHERE menu.pizza_name = 'sicilian pizza'), 
         '2022-02-24');
        
        
INSERT INTO person_order (id, person_id, menu_id, order_date)
VALUES ((SELECT MAX(person_order.id) from person_order) + 1, 
        (SELECT id from person
         WHERE person.name = 'Irina'), 
        (SELECT id FROM menu
         WHERE menu.pizza_name = 'sicilian pizza'), 
         '2022-02-24');