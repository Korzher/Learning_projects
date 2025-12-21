package domain

type CellValue int

const (
	Empty CellValue = iota
	X
	O
)

type Board [3][3]CellValue