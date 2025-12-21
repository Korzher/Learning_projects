package service

import (
	"errors"
	"math"
	"tic-tac-toe/internal/domain"
)

type MinimaxAlgorithm struct {}

func (m *MinimaxAlgorithm) GetBestMove(board domain.Board, player domain.CellValue) (int, int, error) {
	if player != domain.O && player != domain.X {
		return -1, -1, errors.New("invalid player")
	}
	opponent := domain.O
	if player == domain.O {
		opponent = domain.X
	}
	bestScore := math.Inf(-1)
	bestRow, bestCol := -1, -1

	for row := 0; row < 3; row++ {
		for col := 0; col < 3; col++ {
			if board[row][col] == domain.Empty {
				newBoard := board
				newBoard[row][col] = player
				score := m.minimax(newBoard, 0, false, player, opponent)

				if score > bestScore {
					bestScore = score
					bestRow, bestCol = row, col
				}
			}
		}
	}

	if bestRow == -1 || bestCol == -1 {
		return -1, -1, errors.New("no valid move found")
	}
	return bestRow, bestCol, nil
}

func (m *MinimaxAlgorithm) minimax(
	board domain.Board,
	depth int,
	isMaximazing bool,
	player domain.CellValue,
	opponent domain.CellValue,
) float64 {
	status := evaluateBoard(board, player, opponent)
	if status == 10 {
		return 10 - float64(depth)
	}
	if status == -10 {
		return float64(depth) - 10
	}
	if status == 0 {
		return 0
	}

	if isMaximazing {
		bestScore := math.Inf(-1)
		for row := 0; row < 3; row++ {
			for col := 0; col < 3; col++ {
				if board[row][col] == domain.Empty {
					newBoard := board
					newBoard[row][col] = player
					score := m.minimax(newBoard, depth + 1, false, player, opponent)
					bestScore = math.Max(bestScore, score)
				}
			}
		}
		return bestScore
	} else {
		bestScore := math.Inf(1)
		for row := 0; row < 3; row++ {
			for col := 0; col < 3; col++ {
				if board[row][col] == domain.Empty {
					newBoard := board
					newBoard[row][col] = opponent
					score := m.minimax(newBoard, depth+1, true, player, opponent)
					bestScore = math.Min(bestScore, score)
				}
			}
		}
		return bestScore
	}
}

func evaluateBoard(board domain.Board, player domain.CellValue, opponent domain.CellValue) int {
	if checkWinner(board, player) {
		return 10
	}
	if checkWinner(board, opponent) {
		return -10
	}
	for row := 0; row < 3; row++{
		for col := 0; col < 3; col++ {
			if board[row][col] == domain.Empty {
				return 1
			}
		}
	}
	return 0
}

func checkWinner(board domain.Board, player domain.CellValue) bool {
    for row := 0; row < 3; row++ {
        if board[row][0] == player && 
           board[row][1] == player && 
           board[row][2] == player {
            return true
        }
    }
    
    for col := 0; col < 3; col++ {
        if board[0][col] == player && 
           board[1][col] == player && 
           board[2][col] == player {
            return true
        }
    }

    if board[0][0] == player && 
       board[1][1] == player && 
       board[2][2] == player {
        return true
    }
    
    if board[0][2] == player && 
       board[1][1] == player && 
       board[2][0] == player {
        return true
    }
    
    return false
}