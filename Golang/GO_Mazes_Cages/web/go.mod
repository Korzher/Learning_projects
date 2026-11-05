module web

go 1.25.3

replace maze => ../maze_back

replace cave => ../cave_back

require (
	cave v0.0.0
	maze v0.0.0
)
