CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall
LDFLAGS = 
SRC_DIR = srcs
DEMO_DIR = demo
INCLUDE_DIR = include
BUILD_DIR = build
TARGET = $(DEMO_DIR)/demo_app

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(DEMO_DIR)/demo.cpp
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/demo.o: $(DEMO_DIR)/demo.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean