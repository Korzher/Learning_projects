PROJECT = maze
INSTALL_DIR = install/$(PROJECT)
BUILD_DIR = build
WAILS_TAGS = webkit2_41

all: build

build:
	cd maze_back && go build -o $(BUILD_DIR)/$(PROJECT)-cli ./cmd/maze
	export PATH=$$PATH:$(shell go env GOPATH)/bin && cd maze_gui && wails build -o ../$(BUILD_DIR) -clean -tags $(WAILS_TAGS)

install: build
	mkdir -p $(INSTALL_DIR)
	cp maze_back/build/maze-cli $(INSTALL_DIR) 
	cp maze_gui/build/build $(INSTALL_DIR)/maze-gui

uninstall:
	rm -f $(INSTALL_DIR)/$(PROJECT)*

run: install
	cd install/maze/ && ./maze-gui

runweb:
	cd web/backend/ && go run main.go

runconsole: install
	cd install/maze/ && ./maze-cli

dvi: 
	xelatex readme.tex
	xelatex readme.tex

dist: build install
	mkdir -p dist
	tar -czf dist/$(PROJECT).tar.gz -C install .

tests:
	cd maze_back && go test -v -cover ./pkg/...
	cd cave_back && go test -v -cover ./...

clean:
	rm -rf install maze_back/build maze_gui/build dist readme.aux readme.dvi readme.log readme.pdf maze_back/coverage*

.PHONY: dvi clean
