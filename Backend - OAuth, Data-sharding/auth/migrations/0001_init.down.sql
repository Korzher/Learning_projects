-- +migrate Down
-- +migrate StatementBegin
DROP TABLE IF EXISTS user_table;
-- +migrate StatementEnd