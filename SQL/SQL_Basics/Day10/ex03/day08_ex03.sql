-- Окна №1 и №2
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut'; -- Обновим рейтинг после прошлой транзакции аномалии
SHOW TRANSACTION ISOLATION LEVEL; -- Проверим, что необходимый уровень изоляции

-- Окно №1
BEGIN;

-- Окно №2
BEGIN;

-- Окно №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

-- Окно №2
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut'; -- Обновление рейтинга пиццерии
COMMIT;

-- Окно №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга
-- В одной и той же транзакции один и тот же запрос выводит разные результаты. 
COMMIT;
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

-- Окно №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга