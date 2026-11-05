-- Окна №1 и №2
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut'; -- Обновим рейтинг после прошлой транзакции аномалии
BEGIN; -- Начнем транзакции в обоих окнах
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ; -- Установим необходимый уровень изоляции
SHOW TRANSACTION ISOLATION LEVEL; -- Проверим, что уровень изоляции установлен корректно

-- Окно №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

--Окно №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

-- Окно №1
UPDATE pizzeria SET rating = 4 WHERE name = 'Pizza Hut'; -- Обновление рейтинга пиццерии

--Окно №2
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut'; -- Обновление рейтинга пиццерии

-- Выполнение команды UPDATE во втором окне снова зависает до введения команды COMMIT в первом окне (SCR 1)

-- Окно №1
COMMIT; -- Внесение изменений в базу

-- В окне 2 появляется ошибка "ОШИБКА:  не удалось сериализовать доступ из-за параллельного изменения"
--Окно №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

-- В окне 2 игнорируются команды до конца блока транзакции
-- Окно №2
COMMIT; -- Внесение изменений в базу
-- Происходит откат изменений

-- Окна №1 и №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- Просмотр рейтинга

-- Итоговым значением остается первое обновление (рейтинг 4)