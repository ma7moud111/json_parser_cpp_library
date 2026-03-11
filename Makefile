CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC = src/json_parser.cpp \
      src/json_serializer.cpp \
      src/simple_json.cpp

TEST = tests/test_json.cpp

BUILD_DIR = build

OBJ = $(SRC:src/%.cpp=$(BUILD_DIR)/%.o)

TARGET = $(BUILD_DIR)/test_json


all: $(TARGET)


$(TARGET): $(OBJ) $(TEST) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ) $(TEST) -o $(TARGET)


$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


clean:
	rm -rf $(BUILD_DIR)


run: all
	./$(TARGET)