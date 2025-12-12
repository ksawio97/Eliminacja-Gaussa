CC = cc
SRC_DIR = ./src
BUILD_DIR = ./build
BIN_DIR = ./bin
# get all src files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
# convert ./src prefix to ./build
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/app

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -g $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)
