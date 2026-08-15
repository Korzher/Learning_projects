package contracts

type CreateUserRequest struct {
	Email     string
	FirstName string
	LastName  string
	Phone     string
	Password  string
}

type CreateUserResponse struct {
	AccessToken  string
	RefreshToken string
	UserID       string
}

type AuthenticateRequest struct {
	Email    string
	Password string
}

type AuthenticateResponse struct {
	AccessToken  string
	RefreshToken string
	UserID       string
}

type ChangePasswordRequest struct {
	Token       string
	OldPassword string
	NewPassword string
}

type ResetPasswordRequest struct {
	Email string
}
