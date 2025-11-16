--  DDL for table creation with INSERTs of data
CREATE TABLE tours (
  point1 CHAR(1), 
  point2 CHAR(1), 
  cost INT
);

INSERT INTO tours (point1, point2, cost) VALUES
('a', 'b', 10),
('b', 'a', 10),
('a', 'c', 15),
('c', 'a', 15),
('a', 'd', 20),
('d', 'a', 20),
('b', 'd', 25),
('d', 'b', 25),
('c', 'd', 30),
('d', 'c', 30),
('b', 'c', 35),
('c', 'b', 35);

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
ORDER BY total_cost, tour;