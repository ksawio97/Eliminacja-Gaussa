CC = cc
SRC_DIR = ./src
BUILD_DIR = ./build
BIN_DIR = ./bin
TEST_FILE = $(SRC_DIR)/test.c

# We explicitly exclude main.c and test.c here to handle them separately
COMMON_SRCS = $(filter-out $(SRC_DIR)/main.c $(SRC_DIR)/test.c, $(wildcard $(SRC_DIR)/*.c))
COMMON_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(COMMON_SRCS))

APP_EXEC = $(BIN_DIR)/app
TEST_EXEC = $(BIN_DIR)/test_runner

all: $(APP_EXEC)

build: $(APP_EXEC)

test: $(TEST_EXEC)
	@# runs test from i = [1 to inf], if one of the files A{i}.txt B{i}.txt C{i}.txt don't exist it stops
	@echo "--- Running Test Suite ---"
	@fail=0; i=1; while [ $$fail -eq 0 ]; do \
		pathA="./res/A$$i.txt"; pathB="./res/B$$i.txt"; pathC="./res/C$$i.txt"; \
		if [ -f "$$pathA" ] && [ -f "$$pathB" ] && [ -f "$$pathC" ]; then \
			./$(TEST_EXEC) $$i $$pathA $$pathB $$pathC; \
		else \
			fail=1; \
		fi; \
		i=$$((i+1)); \
	done
# It links Common Objects + main.o
$(APP_EXEC): $(COMMON_OBJS) $(BUILD_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -g -o $@ $(LDFLAGS)

# It links Common Objects + test.o
$(TEST_EXEC): $(COMMON_OBJS) $(BUILD_DIR)/test.o
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

# Generic rule to compile any .c file to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -g -c $< -o $@
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)
