package application

import "testing"

func TestValidate(t *testing.T) {
	m := GenerateEller(5, 5)
	if err := Validate(m); err != nil {
		t.Fatal(err)
	}
}

func TestIsPerfect(t *testing.T) {
	m := GenerateEller(5, 5)
	if !IsPerfect(m) {
		t.Fatal("maze not perfect")
	}
}

func TestIsPerfectNil(t *testing.T) {
	if IsPerfect(nil) {
		t.Fatal("nil maze cannot be perfect")
	}
}

func TestValidateNil(t *testing.T) {
	if err := Validate(nil); err == nil {
		t.Fatal("expected error for nil maze")
	}
}

func TestValidateZeroSize(t *testing.T) {
	m := &Maze{Width: 0, Height: 0}
	if err := Validate(m); err == nil {
		t.Fatal("expected error for zero size")
	}
}

func TestValidateTooLarge(t *testing.T) {
	m := &Maze{Width: 100, Height: 100}
	if err := Validate(m); err == nil {
		t.Fatal("expected size limit error")
	}
}

func TestValidateRightWallMismatch(t *testing.T) {
	m := GenerateEller(3, 3)

	m.Cells[0][0].Right = true
	m.Cells[0][1].Left = false

	if err := Validate(m); err == nil {
		t.Fatal("expected right wall mismatch")
	}
}

func TestValidateBottomWallMismatch(t *testing.T) {
	m := GenerateEller(3, 3)

	m.Cells[0][0].Bottom = true
	m.Cells[1][0].Top = false

	if err := Validate(m); err == nil {
		t.Fatal("expected bottom wall mismatch")
	}
}

func TestValidateMissingRightBorder(t *testing.T) {
	m := GenerateEller(3, 3)

	m.Cells[0][2].Right = false

	if err := Validate(m); err == nil {
		t.Fatal("expected missing right border")
	}
}

func TestValidateMissingBottomBorder(t *testing.T) {
	m := GenerateEller(3, 3)

	m.Cells[2][0].Bottom = false

	if err := Validate(m); err == nil {
		t.Fatal("expected missing bottom border")
	}
}

func TestValidateMissingLeftBorder(t *testing.T) {
	m := GenerateEller(3, 3)

	m.Cells[0][0].Left = false

	if err := Validate(m); err == nil {
		t.Fatal("expected missing left border")
	}
}

func TestValidateMissingTopBorder(t *testing.T) {
	m := GenerateEller(3, 3)

	m.Cells[0][0].Top = false

	if err := Validate(m); err == nil {
		t.Fatal("expected missing top border")
	}
}
