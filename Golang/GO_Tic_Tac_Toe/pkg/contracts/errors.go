package contracts

import "errors"

var (
	//Service - game
	ErrGameNotFound   = errors.New("game not found")
	ErrInvalidMove    = errors.New("invalid move")
	ErrGameFinished   = errors.New("game is already finished")
	ErrNotPlayersTurn = errors.New("not your turn")
	ErrCellOccupied   = errors.New("cell is already occupied")
	ErrUserNotAuth    = errors.New("user not authenticated")
	ErrInvGameType    = errors.New("Invalid game type. Use 'vs_computer' or 'vs_player'")
	ErrNotInProg      = errors.New("game is not in progress")
	ErrGameNotWait    = errors.New("Game not waiting for players")
	ErrYourOwnGame    = errors.New("Can not join your own game")
	ErrInvalidPlayer  = errors.New("invalid player")
	ErrNoMoves        = errors.New("no valid move found")
	//Service - user
	ErrLoginEmpty      = errors.New("Login cannot be empty")
	ErrLoginTooLong    = errors.New("Login too long (max 50 chars)")
	ErrPasswordEmpty   = errors.New("Password cannot be empty")
	ErrPasswordTooLong = errors.New("Password too long (max 255 characters)")
	ErrUserFailedCheck = errors.New("failed to check user existence")
	ErrUserExist       = errors.New("Username already exist")
	ErrFailedToSave    = errors.New("Failed to save data")
	ErrFailedEncode    = errors.New("Failed encoding")
	ErrInvalidFormat   = errors.New("Invalid format, expected login:password")
	ErrUserNotFound    = errors.New("User does not found")
	ErrWrongPW         = errors.New("Password does not match")
	ErrFailedAuth      = errors.New("authentication failed")
	ErrInvalidCred     = errors.New("invalid credentials")
	//Datasource
	ErrNilGame           = errors.New("game cannot be nil")
	ErrNilModel          = errors.New("model cannot be nil")
	ErrInvalidGameData   = errors.New("invalid game data")
	ErrFailedToUpdate    = errors.New("failed to update game")
	ErrFailedToQueryG    = errors.New("failed to query game")
	ErrFailedToQueryU    = errors.New("failed to query user")
	ErrFailedToQueryUs   = errors.New("failed to query users")
	ErrFailedToQueryID   = errors.New("failed to query user")
	ErrFailedScan        = errors.New("Failed to scan game from db")
	ErrInvalidGameFormat = errors.New("invalid game id format")
	ErrUnmarshJSON       = errors.New("failed to unmarshal JSON")
	ErrInvalidBoard      = errors.New("invalid board value")
	ErrInvalidStatus     = errors.New("invalid game status")
	ErrInvalidNext       = errors.New("invalid next player value")
	ErrInvalidX          = errors.New("invalid player X format")
	ErrInvalidO          = errors.New("invalid player O format")
	ErrInvalidWinner     = errors.New("invalid winner format")
	ErrMarshJSON         = errors.New("failed to marshal board to JSON")
	//Database
	ErrFailedParseDB = errors.New("failed to parse db-connection string")
	ErrFailedCon     = errors.New("failed to create connection")
	ErrFailedPing    = errors.New("failed to ping db")
	ErrFailedTable   = errors.New("failed to create table")
	ErrFailedToScan  = errors.New("Failed to scan user")
	//Handlers
	ErrInvalidReq   = "invalid request body"
	ErrGameType     = "invalid game type. Use 'vs_computer' or 'vs_player'"
	ErrGameID       = "game ID required"
	ErrInvGameID    = "invalid game ID"
	ErrCoords       = "Invalid coordinates, must be 0-2"
	ErrPlayerID     = "Player id required"
	ErrToken        = "Token required"
	ErrInvalidToken = "Token is invalid"
	ErrInvalidNum   = "Height of leaderboard must be a correct positive integer"
	ErrParseID      = "Failed to parse ID"
	ErrFetch        = "Failed to fetch users"
	ErrAuth         = "User is not authorized"
	//Middleware
	ErrHeaderMid = errors.New("Authorization header is required")
	ErrInvAuth   = errors.New("Wrong Authorization format")
	ErrInvEncode = errors.New("Invalid base64 encoding")
)
