CC = gcc
CXX = g++
SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin
BIN_NAME = linker
INCLUDES = -I inc/

SRC_EXT = cpp

SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)

OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)

DEPS = $(OBJECTS:.o=.d)

CXXFLAGS = -g 
CPPFLAGS =
LIBS = 

TEST_PATH = tests
TEST_NEXT = ../zadatak3/tests

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)

.PHONY: test
test:
	$(BIN_PATH)/$(BIN_NAME) -hex $(TEST_PATH)/t2.o -place=ivt@0x0000 -place=text@0x1000 $(TEST_PATH)/t3.o -o $(TEST_PATH)/out.hex
	$(BIN_PATH)/$(BIN_NAME) -linkable $(TEST_PATH)/t2.o -place=ivt@0x0000 -place=text@0x1000 $(TEST_PATH)/t3.o -o $(TEST_PATH)/out.o

.PHONY: supply
supply:
	rm -r $(TEST_NEXT)/out.hex
	cp $(TEST_PATH)/out.hex $(TEST_NEXT)/

.PHONY: dirs
dirs:
	@echo "${GREEN}Creating directories${NC}"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

.PHONY: clean
clean: 
	@echo "${GREEN}Cleaning project${NC}"
	@rm -rf $(BIN_PATH)
	@rm -rf $(BUILD_PATH)


$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "${GREEN}Linking: $@${NC}"
	$(CXX) $(OBJECTS) -o $@ ${LIBS}

-include $(DEPS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "${GREEN}Compiling: $< -> $@${NC}"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
	
