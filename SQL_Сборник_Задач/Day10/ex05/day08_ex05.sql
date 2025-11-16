-- Окна №1 и №2
SHOW TRANSACTION ISOLATION LEVEL; -- Проверим, что уровень изоляции установлен корректно
BEGIN; -- Начнем транзакции в обоих окнах

-- Окно №1
SELECT SUM(rating) AS total_rating FROM pizzeria; -- Вывод суммы значений рейтингов пиццерий

-- Окно №2
INSERT INTO pizzeria (id, name, rating) VALUES (10, 'Kazan Pizza', 5); -- Вставка новой пиццерии
COMMIT;

-- Окно №1
SELECT SUM(rating) AS total_rating FROM pizzeria; -- Вывод суммы значений рейтингов пиццерий
-- Выводит новое значение суммы рейтингов пиццерий в этой же транзакции.
COMMIT;
SELECT SUM(rating) AS total_rating FROM pizzeria; -- Верный вывод обновленной суммы значений рейтингов пиццерий в первом окне

-- Окно №2
SELECT SUM(rating) AS total_rating FROM pizzeria; -- Верный вывод обновленной суммы значений рейтингов пиццерий во втором окне