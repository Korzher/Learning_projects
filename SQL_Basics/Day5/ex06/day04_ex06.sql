CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS
SELECT pizzeria.name AS pizzeria_name
FROM person_visits
LEFT JOIN (SELECT *
           FROM person
           WHERE person.name = 'Dmitriy') AS client
           ON client.id = person_visits.person_id
LEFT JOIN pizzeria
ON person_visits.pizzeria_id = pizzeria.id
LEFT JOIN menu
ON pizzeria.id = menu.pizzeria_id
WHERE menu.price < 800 AND person_visits.visit_date = '2022-01-08' AND client.name IS NOT NULL
ORDER BY pizzeria_name;