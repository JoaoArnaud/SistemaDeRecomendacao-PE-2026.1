CC = gcc
CXX = g++

CFLAGS = -Wall -Wextra -Iinclude
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

BUILD = build
PROGRAMA = $(BUILD)/programa

OBJETOS = \
	$(BUILD)/main.o \
	$(BUILD)/ler_dados.o \
	$(BUILD)/lista_compras.o

all: $(PROGRAMA)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/main.o: src/main.c | $(BUILD)
	$(CC) $(CFLAGS) -c src/main.c -o $(BUILD)/main.o

$(BUILD)/ler_dados.o: src/ler_dados.c | $(BUILD)
	$(CC) $(CFLAGS) -c src/ler_dados.c -o $(BUILD)/ler_dados.o

$(BUILD)/lista_compras.o: src/lista_compras.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c src/lista_compras.cpp -o $(BUILD)/lista_compras.o

$(PROGRAMA): $(OBJETOS)
	$(CXX) $(OBJETOS) -o $(PROGRAMA)

run: $(PROGRAMA)
	./$(PROGRAMA)

clean:
	rm -rf $(BUILD)

.PHONY: all run clean