package middleware

import (
	"context"
	"encoding/json"
	"errors"
	"net/http"
	"net/http/httptest"
	"testing"
)

type fakeVerifier struct {
	valid bool
	err   error
}

func (f fakeVerifier) VerifyToken(_ context.Context, _ string) (bool, error) {
	return f.valid, f.err
}

func runRequest(t *testing.T, authHeader string, v TokenVerifier) *httptest.ResponseRecorder {
	t.Helper()

	downstream := http.HandlerFunc(func(w http.ResponseWriter, _ *http.Request) {
		w.WriteHeader(http.StatusOK)
		_, _ = w.Write([]byte("ok"))
	})

	handler := AuthMiddleware(v)(downstream)
	req := httptest.NewRequest(http.MethodGet, "/api/v1/clients", nil)
	if authHeader != "" {
		req.Header.Set("Authorization", authHeader)
	}

	rec := httptest.NewRecorder()
	handler.ServeHTTP(rec, req)
	return rec
}

func TestAuthMiddlewareMissingHeader(t *testing.T) {
	rec := runRequest(t, "", fakeVerifier{valid: true})

	if rec.Code != http.StatusUnauthorized {
		t.Fatalf("status = %d, want %d", rec.Code, http.StatusUnauthorized)
	}
}

func TestAuthMiddlewareMalformedHeader(t *testing.T) {
	rec := runRequest(t, "Token abc", fakeVerifier{valid: true})

	if rec.Code != http.StatusUnauthorized {
		t.Fatalf("status = %d, want %d", rec.Code, http.StatusUnauthorized)
	}
}

func TestAuthMiddlewareVerifierError(t *testing.T) {
	rec := runRequest(t, "Bearer some-token", fakeVerifier{err: errors.New("grpc down")})

	if rec.Code != http.StatusUnauthorized {
		t.Fatalf("status = %d, want %d", rec.Code, http.StatusUnauthorized)
	}
}

func TestAuthMiddlewareInvalidToken(t *testing.T) {
	rec := runRequest(t, "Bearer some-token", fakeVerifier{valid: false})

	if rec.Code != http.StatusUnauthorized {
		t.Fatalf("status = %d, want %d", rec.Code, http.StatusUnauthorized)
	}
}

func TestAuthMiddlewareValidTokenPassesThrough(t *testing.T) {
	rec := runRequest(t, "Bearer valid-token", fakeVerifier{valid: true})

	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, want %d", rec.Code, http.StatusOK)
	}
	if rec.Body.String() != "ok" {
		t.Fatalf("body = %q, want %q", rec.Body.String(), "ok")
	}
}

func TestAuthMiddlewareRejectsNonJSONBodyOnAuthFailure(t *testing.T) {
	rec := runRequest(t, "Bearer some-token", fakeVerifier{valid: false})

	var msg string
	if err := json.Unmarshal(rec.Body.Bytes(), &msg); err != nil {
		t.Fatalf("response body is not valid JSON: %v (body=%q)", err, rec.Body.String())
	}
	if rec.Code != http.StatusUnauthorized {
		t.Fatalf("status = %d, want %d", rec.Code, http.StatusUnauthorized)
	}
}
