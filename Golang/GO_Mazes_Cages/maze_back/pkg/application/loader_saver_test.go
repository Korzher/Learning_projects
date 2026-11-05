package application

import (
	"os"
	"testing"
)

func TestSaveLoad(t *testing.T) {
	m := GenerateEller(5, 5)

	file := "test_tmp.txt"
	defer os.Remove(file)

	if err := SaveToFile(m, file); err != nil {
		t.Fatal(err)
	}

	loaded, err := LoadFromFile(file)
	if err != nil {
		t.Fatal(err)
	}

	if loaded.Width != m.Width || loaded.Height != m.Height {
		t.Fatal("wrong size after load")
	}
}

func TestSaveNilMaze(t *testing.T) {
	err := SaveToFile(nil, "x.txt")
	if err == nil {
		t.Fatal("expected error for nil maze")
	}
}

func TestSaveAddsTxtExtension(t *testing.T) {
	m := GenerateEller(3, 3)

	file := "test_noext"
	defer os.Remove(file + ".txt")

	if err := SaveToFile(m, file); err != nil {
		t.Fatal(err)
	}

	if _, err := os.Stat(file + ".txt"); err != nil {
		t.Fatal("file with .txt not created")
	}
}

func TestLoadWrongExtension(t *testing.T) {
	_, err := LoadFromFile("maze.bin")
	if err == nil {
		t.Fatal("expected error for wrong extension")
	}
}

func TestLoadMissingFile(t *testing.T) {
	_, err := LoadFromFile("missing.txt")
	if err == nil {
		t.Fatal("expected error for missing file")
	}
}

func TestLoadCorruptedFile(t *testing.T) {
	file := "bad.txt"
	defer os.Remove(file)

	os.WriteFile(file, []byte("abc"), 0644)

	_, err := LoadFromFile(file)
	if err == nil {
		t.Fatal("expected error for corrupted file")
	}
}

func TestSaveFileCreateError(t *testing.T) {
	m := GenerateEller(3, 3)
	err := SaveToFile(m, "/invalid/path/file.txt")
	if err == nil {
		t.Fatal("expected error")
	}
}

func TestLoadEmptyFile(t *testing.T) {
	file := "empty.txt"
	defer os.Remove(file)

	os.WriteFile(file, []byte(""), 0644)

	_, err := LoadFromFile(file)
	if err == nil {
		t.Fatal("expected error for empty file")
	}
}
