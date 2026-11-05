package datalayer

import (
	"APG-P01/internal/domain"
	"encoding/json"
	"errors"
	"os"
	"sort"
	"time"
)

const (
	saveFileName        = "savegame.json"
	leaderboardFileName = "leaderboard.json"
)

var ErrNoSave = errors.New("no saved game")

type LevelStats struct {
	GameState       domain.GameState `json:"game_state"`
	LevelReached    int              `json:"level"`
	Treasures       int              `json:"treasures"` // Сколько сокровищ собрал
	EnemiesDefeated int              `json:"enemies"`   // Сколько врагов убил
	FoodConsumed    int              `json:"food"`      // Сколько еды съел
	ElixirsUsed     int              `json:"elixirs"`   // Сколько эликсиров выпил
	ScrollsRead     int              `json:"scrolls"`   // Сколько свитков прочитал
	AttackDealt     int              `json:"attacks"`   // Сколько атак сделал
	AttackReceived  int              `json:"missed"`    // Сколько атак промазал
	StepsTaken      int              `json:"moves"`     // Сколько шагов сделал
	IsWin           bool             `json:"is_win"`
	FinishedAt      time.Time        `json:"finished_at"`
}

type SaveData struct {
	LastSession *domain.GameSession `json:"last_session"`
}

type LeaderboardData struct {
	Attempts []LevelStats `json:"attempts"`
}

func loadSaveFile() (*SaveData, error) {
	f, err := os.Open(saveFileName)
	if errors.Is(err, os.ErrNotExist) {
		return &SaveData{
			LastSession: nil,
		}, nil
	}
	if err != nil {
		return nil, err
	}
	defer f.Close()

	var data SaveData
	if err := json.NewDecoder(f).Decode(&data); err != nil {
		return nil, err
	}
	return &data, nil
}

func saveSaveFile(data *SaveData) error {
	f, err := os.Create(saveFileName)
	if err != nil {
		return err
	}
	defer f.Close()

	enc := json.NewEncoder(f)
	enc.SetIndent("", "  ")
	return enc.Encode(data)
}

func loadLeaderboardFile() (*LeaderboardData, error) {
	f, err := os.Open(leaderboardFileName)
	if errors.Is(err, os.ErrNotExist) {
		return &LeaderboardData{
			Attempts: make([]LevelStats, 0),
		}, nil
	}
	if err != nil {
		return nil, err
	}
	defer f.Close()

	var data LeaderboardData
	if err := json.NewDecoder(f).Decode(&data); err != nil {
		return nil, err
	}
	if data.Attempts == nil {
		data.Attempts = make([]LevelStats, 0)
	}
	return &data, nil
}

func saveLeaderdoardFile(data *LeaderboardData) error {
	f, err := os.Create(leaderboardFileName)
	if err != nil {
		return err
	}
	defer f.Close()

	enc := json.NewEncoder(f)
	enc.SetIndent("", " ")
	return enc.Encode(data)
}

func SaveGame(session *domain.GameSession, isWin bool) error {
	if session == nil || session.Character == nil {
		return errors.New("game session or character is nil")
	}

	saveData, err := loadSaveFile()
	if err != nil {
		return err
	}

	saveData.LastSession = session
	return saveSaveFile(saveData)
}

func SaveToLeaderboard(session *domain.GameSession, isWin bool) error {
	if session == nil || session.Character == nil {
		return errors.New("game session or character is nil")
	}

	LeaderboardData, err := loadLeaderboardFile()
	if err != nil {
		return err
	}
	treasures := 0
	if session.Character.Backpack != nil && session.Character.Backpack.Treasures != nil {
		treasures = session.Character.Backpack.Treasures.Value
	}

	levelReached := session.CurrentLevel.LevelNum
	if levelReached > 21 {
		levelReached = 21
	}

	stat := LevelStats{
		GameState:       session.GameState,
		LevelReached:    levelReached,
		Treasures:       treasures,
		EnemiesDefeated: session.Character.EnemiesDefeated,
		FoodConsumed:    session.Character.FoodConsumed,
		ElixirsUsed:     session.Character.ElixirsUsed,
		ScrollsRead:     session.Character.ScrollsRead,
		AttackDealt:     session.Character.AttackDealt,
		AttackReceived:  session.Character.AttackReceived,
		StepsTaken:      session.Character.StepsTaken,
		IsWin:           isWin,
		FinishedAt:      time.Now(),
	}

	LeaderboardData.Attempts = append(LeaderboardData.Attempts, stat)
	return saveLeaderdoardFile(LeaderboardData)
}


func LoadLastSession() (*domain.GameSession, error) {
	data, err := loadSaveFile()
	if err != nil {
		return nil, err
	}
	if data.LastSession == nil {
		return nil, ErrNoSave
	}
	return data.LastSession, nil
}

func BestAttempts(limit int) ([]LevelStats, error) {
	data, err := loadLeaderboardFile()
	if err != nil {
		return nil, err
	}

	stats := make([]LevelStats, len(data.Attempts))
	copy(stats, data.Attempts)

	// сортируем по количеству сокровищ, затем по счёту
	sort.Slice(stats, func(i, j int) bool {
		if stats[i].Treasures == stats[j].Treasures {
			return stats[i].FinishedAt.Before(stats[j].FinishedAt)
		}
		return stats[i].Treasures > stats[j].Treasures
	})

	if limit <= 0 {
		return []LevelStats{}, nil
	}

	if limit > len(stats) {
		limit = len(stats)
	}
	return stats[:limit], nil
}
