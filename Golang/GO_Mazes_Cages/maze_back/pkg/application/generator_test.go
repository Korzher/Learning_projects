package application

import "testing"

func TestGenerateEller(t *testing.T) {
	m := GenerateEller(5, 5)
	if m == nil {
		t.Fatal("maze is nil")
	}
	if m.Width != 5 || m.Height != 5 {
		t.Fatal("wrong size")
	}
}

func TestGenerateInvalid(t *testing.T) {
	if GenerateEller(0, 5) != nil {
		t.Fatal("expected nil")
	}
}
