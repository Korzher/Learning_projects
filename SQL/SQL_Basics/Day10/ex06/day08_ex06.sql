-- Окна №1 и №2
BEGIN; -- Начнем транзакции в обоих окнах
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ; -- Установим необходимый уровень изоляции
SHOW TRANSACTION ISOLATION LEVEL; -- Проверим, что уровень изоляции установлен корректно

-- Окно №1
SELECT SUM(rating) AS total_rating FROM pizzeria; -- Вывод суммы значений рейтингов пиццерий

-- Окно №2
INSERT INTO pizzeria (id, name, rating) VALUES (11, 'Kazan Pizza 2', 4); -- Вставка новой пиццерии
COMMIT;

-- Окно №1
SELECT SUM(rating) AS total_rating FROM pizzeria; -- Вывод суммы значений рейтингов пиццерий
-- Выводит верное значение (как до внесения изменений) суммы рейтингов пиццерий в транзакции.
COMMIT;
SELECT SUM(rating) AS total_rating FROM pizzeria; -- Верный вывод обновленной суммы значений рейтингов пиццерий в первом окне

-- Окно №2
SELECT SUM(rating) AS total_rating FROM pizzeria; -- Верный вывод обновленной суммы значений рейтингов пиццерий во втором окне