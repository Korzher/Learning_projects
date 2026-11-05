SELECT pizzeria.name AS pizzeria_name
FROM person_visits
JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
JOIN person ON person_visits.person_id = person.id
GROUP BY pizzeria.name
HAVING COUNT(*) FILTER (WHERE person.gender = 'female') <> COUNT(*) FILTER (WHERE person.gender = 'male')
ORDER by pizzeria_name
