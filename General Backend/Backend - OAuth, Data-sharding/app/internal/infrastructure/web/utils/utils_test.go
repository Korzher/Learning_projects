package utils

import (
	"encoding/json"
	"net/http"
	"net/http/httptest"
	"testing"
)

func TestRespondJSON(t *testing.T) {
	rec := httptest.NewRecorder()
	RespondJSON(rec, http.StatusCreated, map[string]string{"token": "abc"})

	if rec.Code != http.StatusCreated {
		t.Fatalf("status = %d, want %d", rec.Code, http.StatusCreated)
	}
	if ct := rec.Header().Get("Content-Type"); ct != "application/json" {
		t.Fatalf("Content-Type = %q, want application/json", ct)
	}

	var body map[string]string
	if err := json.Unmarshal(rec.Body.Bytes(), &body); err != nil {
		t.Fatalf("body not JSON: %v", err)
	}
	if body["token"] != "abc" {
		t.Fatalf("body[token] = %q, want abc", body["token"])
	}
}

func TestRespondJSONString(t *testing.T) {
	rec := httptest.NewRecorder()
	RespondJSON(rec, http.StatusBadRequest, "missing field")

	var msg string
	if err := json.Unmarshal(rec.Body.Bytes(), &msg); err != nil {
		t.Fatalf("string body not JSON: %v", err)
	}
	if msg != "missing field" {
		t.Fatalf("msg = %q, want %q", msg, "missing field")
	}
}

func TestRespondImage(t *testing.T) {
	rec := httptest.NewRecorder()
	data := []byte{1, 2, 3, 4}
	RespondImage(rec, http.StatusOK, data)

	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, want %d", rec.Code, http.StatusOK)
	}
	if ct := rec.Header().Get("Content-Type"); ct != "application/octet-stream" {
		t.Fatalf("Content-Type = %q, want application/octet-stream", ct)
	}
	if rec.Body.Len() != len(data) {
		t.Fatalf("body length = %d, want %d", rec.Body.Len(), len(data))
	}
}
