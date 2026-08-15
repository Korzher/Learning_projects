WITH order_counts AS (
    SELECT 
        pizzeria.name,
        COUNT(*) AS count,
        'order' AS action_type
    FROM person_order
    JOIN menu ON person_order.menu_id = menu.id
    JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
    GROUP BY pizzeria.name
),
visit_counts AS (
    SELECT 
        pizzeria.name,
        COUNT(*) AS count,
        'visit' AS action_type
    FROM person_visits
    JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
    GROUP BY pizzeria.name
),
total AS (
    SELECT name, count, action_type FROM order_counts
    UNION ALL
    SELECT name, count, action_type FROM visit_counts
)

SELECT 
    name,
    SUM(count) AS total_count
FROM total
GROUP BY name
ORDER BY total_count DESC, name ASC;