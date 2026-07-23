CXX ?= g++

CPPFLAGS := -Iinclude
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic

BUILD_DIR := build
TARGET := $(BUILD_DIR)/programa

SOURCES := \
	src/testador.cpp \
	src/lista_compras.cpp \
	src/similaridade.cpp \
	src/recomendacao.cpp \
	src/menu.cpp

OBJECTS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDENCIES := $(OBJECTS:.o=.d)

.DEFAULT_GOAL := all

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET) $(if $(ARGS),$(ARGS),entrega1)

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPENDENCIES)

.PHONY: all run clean
