INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
VALUES(
	(SELECT MAX(id) FROM person_visits) + 1,
	(SELECT id FROM person WHERE person.name = 'Dmitriy'),
    (SELECT pizzeria.id FROM pizzeria
     JOIN menu ON pizzeria.id = menu.pizzeria_id
     WHERE pizzeria.name != 'Papa Johns'
     AND menu.price < 800
     LIMIT 1),
    '2022-01-08');

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;