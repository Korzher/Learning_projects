CREATE FUNCTION fnc_trg_person_update_audit()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO person_audit (id, name, age, gender, address, row_id, type_event)
    VALUES (
        nextval('person_audit_id_seq'),
        OLD.name,
        OLD.age,
        OLD.gender,
        OLD.address,
        OLD.id,
        'U'
    );
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_update_audit
AFTER UPDATE ON person
FOR EACH ROW
EXECUTE FUNCTION fnc_trg_person_update_audit();

UPDATE person SET name = 'Bulat' WHERE id = 10;

UPDATE person SET name = 'Damir' WHERE id = 10;

-- Проверка срабатывания триггера 
SELECT * FROM person_audit ORDER BY created;