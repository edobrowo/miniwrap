### Options ###

CC			:= g++

CFLAGS		:= -g -Werror -Wall -Wpedantic
CPPFLAGS	:= -std=c++20 -I/opt/homebrew/include -D_THREAD_SAFE -MMD -MP
LDFLAGS		:= -L/opt/homebrew/lib -lSDL2
# LDLIBS		:= -lLIB

SRC_DIR		:= src
OBJ_DIR		:= objects
BIN_DIR		:= .
EXEC		:= main

### Files ###

SRC			:= $(wildcard $(SRC_DIR)/*.cpp)
OBJ			:= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXEC		:= $(BIN_DIR)/$(EXEC)

### Rules ###

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	@echo "Build successful!"

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(EXEC) $(OBJ_DIR)

-include $(OBJ:.o=.d)