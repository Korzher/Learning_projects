-- SQL DML statement
WITH RECURSIVE paths AS (
    SELECT 
        point1,
        point2,
        cost,
        point1 || ',' || point2 AS path,
        1 AS depth
    FROM tours
    WHERE point1 = 'a'
    
    UNION ALL
    
    SELECT 
        paths.point1,
        tours.point2,
        paths.cost + tours.cost AS total_cost,
        paths.path || ',' || tours.point2 AS path,
        paths.depth + 1 AS depth
    FROM paths
    JOIN tours ON paths.point2 = tours.point1
    WHERE 
        paths.path NOT LIKE '%' || tours.point2 || '%'
        AND paths.depth < 3
),
tour_costs AS (
    SELECT 
        cost + (SELECT cost FROM tours WHERE point1 = right(path, 1) AND point2 = 'a') AS total_cost,
        '{' || path || ',a}' AS tour
    FROM paths 
    WHERE depth = 3
)
SELECT total_cost, tour
FROM tour_costs
WHERE total_cost = (SELECT MIN(total_cost) FROM tour_costs)
	OR total_cost = (SELECT MAX(total_cost) FROM tour_costs)
ORDER BY total_cost, tour;