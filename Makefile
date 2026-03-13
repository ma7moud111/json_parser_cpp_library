CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC = src/json_parser.cpp \
      src/json_serializer.cpp \
      src/simple_json.cpp

TEST = tests/test_json.cpp
CLI  = tools/jcli.cpp

BUILD_DIR = build

OBJ = $(SRC:src/%.cpp=$(BUILD_DIR)/%.o)

TARGET = $(BUILD_DIR)/test_json
CLI_TARGET = $(BUILD_DIR)/jcli
LIB = $(BUILD_DIR)/libsimplejson.a


all: $(LIB) $(TARGET) $(CLI_TARGET)


$(TARGET): $(OBJ) $(TEST) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ) $(TEST) -o $(TARGET)


$(CLI_TARGET): $(OBJ) $(CLI) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ) $(CLI) -o $(CLI_TARGET)


$(LIB): $(OBJ) | $(BUILD_DIR)
	ar rcs $(LIB) $(OBJ)


$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


lib: $(LIB)

jcli: $(CLI_TARGET)

test: $(TARGET)

run: $(TARGET)
	./$(TARGET)


clean:
	rm -rf $(BUILD_DIR)