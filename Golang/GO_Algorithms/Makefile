GO      := go
SRC     := ./...
BIN     := graph_console
CMD     := ./cmd

GRAPH_PKG := ./s21_graph
ALGO_PKG  := ./s21_graph_algorithms

.PHONY: all run test s21_graph s21_graph_lib s21_graph_algorithms_lib clean

all: s21_graph

run: s21_graph
	./$(BIN)

s21_graph: s21_graph_lib s21_graph_algorithms_lib
	$(GO) build -o $(BIN) $(CMD)

s21_graph_lib:
	$(GO) build $(GRAPH_PKG)

s21_graph_algorithms_lib:
	$(GO) build $(ALGO_PKG)

test:
	$(GO) test $(GRAPH_PKG) $(ALGO_PKG) -v -cover

clean:
	rm -f $(BIN)
	$(GO) clean -cache -testcache

# sudo apt install graphviz
# dot -Tpng graph.dot -o graph.png
