-- Окна №1 и №2
BEGIN; -- Начнем транзакции в обоих окнах

-- Окно №1
UPDATE pizzeria SET rating = 5 WHERE id = 1;

-- Окно №2
UPDATE pizzeria SET rating = 4 WHERE id = 2;

-- Окна №1
UPDATE pizzeria SET rating = 4.5 WHERE id = 2;
-- Команда зависает

-- Окно №2
UPDATE pizzeria SET rating = 3 WHERE id = 1;
-- На вызове этой команды во втором окне Postgresql обнаруживает deadlock и отменяет транзакцию