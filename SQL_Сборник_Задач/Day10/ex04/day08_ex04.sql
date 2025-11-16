-- Окна №1 и №2
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut'; -- Обновим рейтинг после прошлой транзакции аномалии
BEGIN; -- Начнем транзакции в обоих окнах
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE; -- Установим необходимый уровень изоляции
SHOW TRANSACTION ISOLATION LEVEL; -- Проверим, что уровень изоляции установлен корректно

-- Окно №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

-- Окно №2
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut'; -- Обновление рейтинга пиццерии
COMMIT;

-- Окно №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга
-- В одной и той же транзакции один и тот же запрос выводит тот же результат, что и до введения команды COMMIT во втором окне. 
COMMIT;
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга
-- Выводит обновленный во втором окне рейтинг пиццерии

-- Окно №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга