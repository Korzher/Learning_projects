-- +migrate Up
-- +migrate StatementBegin
CREATE TABLE IF NOT EXISTS user_table (
    id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    email VARCHAR(100) NOT NULL UNIQUE,
    first_name VARCHAR(59) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    phone VARCHAR(50) NOT NULL,
    user_password VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT NOW()
);

INSERT INTO user_table (id, email, first_name, last_name, phone, user_password)
VALUES (
    '880e8400-e29b-41d4-a716-446655440099', 
    'test@testify.com', 
    'Test', 
    'Testington', 
    '8-800-555-35-35', 
    '$2a$10$YgKqJzK9cQZ9cQZ9cQZ9cuO9cQZ9cQZ9cQZ9cQZ9cQZ9cQZ9cQZ9cQ'
)
ON CONFLICT (email) DO NOTHING;
-- +migrate StatementEnd