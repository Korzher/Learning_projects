CREATE UNIQUE INDEX idx_menu_unique ON menu (pizzeria_id, pizza_name);

SET enable_seqscan = OFF;

EXPLAIN ANALYZE
SELECT pizzeria_id, pizza_name, price
FROM menu
WHERE pizzeria_id = 1 AND pizza_name = 'cheese pizza';

SET enable_seqscan = ON;