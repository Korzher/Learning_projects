INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
VALUES ((SELECT MAX(person_visits.id) from person_visits) + 1, 
        (SELECT id from person
         WHERE person.name = 'Denis'), 
        (SELECT id FROM pizzeria
         WHERE pizzeria.name = 'Dominos'), 
         '2022-02-24');
        
        
INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
VALUES (
    (SELECT MAX(person_visits.id) FROM person_visits) + 1, 
    (SELECT id FROM person
     WHERE person.name = 'Irina'), 
    (SELECT id FROM pizzeria 
     WHERE pizzeria.name = 'Dominos'), 
    '2022-02-24'
);
