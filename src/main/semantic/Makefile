CXX      ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -Wno-sign-compare

TARGET    := compilador
BUILD_DIR := build

GRAM_FILE   ?= gramatica-ruby/gramatica-ruby.site
TABELA_FILE ?= gramatica-ruby/tabela_lr1.conf

# Diretórios de include
CORE_DIR  := src/core
GRAM_DIR  := src/gram-ruby
FRAME_DIR := src/frame

# Fontes
CORE_SRCS  := $(wildcard $(CORE_DIR)/*.cpp) src/sol.cpp
GRAM_SRCS  := $(wildcard $(GRAM_DIR)/*.cpp)
FRAME_SRCS := $(wildcard $(FRAME_DIR)/*.cpp)
SRCS       := $(CORE_SRCS) $(GRAM_SRCS) $(FRAME_SRCS)

OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run runex

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(CORE_DIR) -I$(GRAM_DIR) -I$(FRAME_DIR) -Isrc -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(GRAM_FILE) $(TABELA_FILE)

runex: $(TARGET)
	./$(TARGET) $(GRAM_FILE) $(TABELA_FILE) ins/$(EX).params < ins/$(EX).tokens

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)
