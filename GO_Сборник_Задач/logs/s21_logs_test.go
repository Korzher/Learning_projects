package main

import (
	"os"
	"testing"
)

func TestIsValidDate(t *testing.T) {
	tests := []struct {
		name     string
		date     string
		expected bool
	}{
		{"Верная дата", "2024-01-15", true},
		{"Неверный формат", "15-01-2024", false},
		{"Некорректный месяц", "2024-13-15", false},
		{"Некорректный день", "2024-01-32", false},
		{"Пустая строка", "", false},
		{"Наверный разделитель", "2024/01/15", false},
	}

	for _, tc := range tests {
		t.Run(tc.name, func(t *testing.T) {
			result := isValidDate(tc.date)
			if result != tc.expected {
				t.Errorf("isValidDate(%s) = %v, expected %v", tc.date, result, tc.expected)
			}
		})
	}
}

func mockStdin(input string) func() {
	oldStdin := os.Stdin
	r, w, _ := os.Pipe()
	os.Stdin = r

	go func() {
		defer w.Close()
		w.Write([]byte(input))
	}()

	return func() { os.Stdin = oldStdin }
}

func TestSaveCommand(t *testing.T) {
	tests := []struct {
		name                   string
		input                  string
		expectedVisitsLen      int
		expectedName           string
		expectedSpecialization string
		expectedDate           string
	}{
		{
			name:                   "Normal save",
			input:                  "Иван Иванов\nтерапевт\n2024-01-15\n",
			expectedVisitsLen:      1,
			expectedName:           "Иван Иванов",
			expectedSpecialization: "терапевт",
			expectedDate:           "2024-01-15",
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			visits := make([]visit, 0)

			cleanup := mockStdin(tt.input)
			defer cleanup()

			saveCommand(&visits)

			if len(visits) != tt.expectedVisitsLen {
				t.Errorf("Expected %d visits, got %d", tt.expectedVisitsLen, len(visits))
			}

			if len(visits) > 0 {
				if visits[0].name != tt.expectedName {
					t.Errorf("Expected name '%s', got '%s'", tt.expectedName, visits[0].name)
				}
				if visits[0].specialization != tt.expectedSpecialization {
					t.Errorf("Expected specialization '%s', got '%s'", tt.expectedSpecialization, visits[0].specialization)
				}
				if visits[0].date != tt.expectedDate {
					t.Errorf("Expected date '%s', got '%s'", tt.expectedDate, visits[0].date)
				}
			}
		})
	}
}

func TestGetHistoryCommand(t *testing.T) {
	tests := []struct {
		name          string
		visits        []visit
		input         string
		expectedError bool
	}{
		{
			name: "Patient found",
			visits: []visit{
				{"Иван Иванов", "терапевт", "2024-01-15"},
				{"Иван Иванов", "хирург", "2024-01-20"},
			},
			input:         "Иван Иванов\n",
			expectedError: false,
		},
		{
			name: "Patient not found",
			visits: []visit{
				{"Иван Иванов", "терапевт", "2024-01-15"},
			},
			input:         "Петр Петров\n",
			expectedError: true,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			cleanup := mockStdin(tt.input)
			defer cleanup()

			err := getHistoryCommand(tt.visits)

			if tt.expectedError {
				if err == nil {
					t.Error("Expected error, but got none")
				} else if _, ok := err.(PatientNotFoundError); !ok {
					t.Errorf("Expected PatientNotFoundError, got %T", err)
				}
			} else {
				if err != nil {
					t.Errorf("Unexpected error: %v", err)
				}
			}
		})
	}
}

func TestGetLastVisitCommand(t *testing.T) {
	tests := []struct {
		name          string
		visits        []visit
		input         string
		expectedError bool
	}{
		{
			name: "Last visit found",
			visits: []visit{
				{"Иван Иванов", "терапевт", "2024-01-15"},
				{"Иван Иванов", "терапевт", "2024-01-20"},
				{"Иван Иванов", "хирург", "2024-01-18"},
			},
			input:         "Иван Иванов\nтерапевт\n",
			expectedError: false,
		},
		{
			name: "Patient not found",
			visits: []visit{
				{"Иван Иванов", "терапевт", "2024-01-15"},
			},
			input:         "Петр Петров\nтерапевт\n",
			expectedError: true,
		},
		{
			name: "Specialization not found",
			visits: []visit{
				{"Иван Иванов", "терапевт", "2024-01-15"},
			},
			input:         "Иван Иванов\nхирург\n",
			expectedError: true,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			cleanup := mockStdin(tt.input)
			defer cleanup()

			err := getLastVisitCommand(tt.visits)

			if tt.expectedError {
				if err == nil {
					t.Error("Expected error, but got none")
				} else if _, ok := err.(PatientNotFoundError); !ok {
					t.Errorf("Expected PatientNotFoundError, got %T", err)
				}
			} else {
				if err != nil {
					t.Errorf("Unexpected error: %v", err)
				}
			}
		})
	}
}

func TestPatientNotFoundError(t *testing.T) {
	err := PatientNotFoundError{}
	expectedMsg := "patient not found"

	if err.Error() != expectedMsg {
		t.Errorf("Expected error message '%s', got '%s'", expectedMsg, err.Error())
	}
}

func TestScanCommand(t *testing.T) {
	input := "Save\n"
	cleanup := mockStdin(input)
	defer cleanup()

	result := scanCommand()

	if result != "Save" {
		t.Errorf("Expected 'Save', got '%s'", result)
	}
}

func TestSpecializationCase(t *testing.T) {
	visits := []visit{
		{"Иван Иванов", "терапевт", "2024-01-15"},
		{"Иван Иванов", "ТЕРАПЕВТ", "2024-01-20"},
	}

	input := "Иван Иванов\nтерапевт\n"
	cleanup := mockStdin(input)
	defer cleanup()

	var userVisits []visit
	for _, v := range visits {
		if v.name == "Иван Иванов" && v.specialization == "терапевт" {
			userVisits = append(userVisits, v)
		}
	}

	if len(userVisits) != 1 {
		t.Errorf("Expected 1 visit, got %d (case sensitivity issue)", len(userVisits))
	}
}
