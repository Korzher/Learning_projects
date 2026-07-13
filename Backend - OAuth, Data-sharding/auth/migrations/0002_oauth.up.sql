CREATE TABLE IF NOT EXISTS oauth_states (
    state varchar(255) PRIMARY KEY,
    expires_at TIMESTAMP WITH TIME ZONE NOT NULL
);