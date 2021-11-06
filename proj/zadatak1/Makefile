CC = gcc
CXX = g++
SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin
BIN_NAME = asembler
INCLUDES = -I inc/

SRC_EXT = cpp

SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)

OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)

DEPS = $(OBJECTS:.o=.d)

CXXFLAGS = -g 
CPPFLAGS =
LIBS = 

TEST_PATH = tests
NEXT_TEST = ../zadatak2/tests

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)

.PHONY: lexer
lexer: src/lexer.cpp

.PHONY: parser
parser: src/parser.cpp

inc/lexer.hpp: src/lexer.cpp

inc/parser.hpp: src/parser.cpp

src/lexer.cpp: src/lexer.l inc/util.hpp
	@echo "${GREEN}Building lexer${NC}"
	flex --outfile=src/lexer.cpp --header-file=inc/lexer.hpp ./src/lexer.l

src/parser.cpp: src/parser.y src/lexer.l inc/util.hpp
	@echo "${GREEN}Building parser${NC}"
	bison --output=src/parser.cpp --defines=inc/parser.hpp ./src/parser.y

.PHONY: test
test:
	$(BIN_PATH)/$(BIN_NAME) $(TEST_PATH)/t1.s
	$(BIN_PATH)/$(BIN_NAME) $(TEST_PATH)/t2.s
	$(BIN_PATH)/$(BIN_NAME) $(TEST_PATH)/t3.s

.PHONY: supply
supply:
	rm -r $(NEXT_TEST)/t1.o
	rm -r $(NEXT_TEST)/t2.o
	rm -r $(NEXT_TEST)/t3.o
	cp $(TEST_PATH)/t1.o $(NEXT_TEST)/
	cp $(TEST_PATH)/t2.o $(NEXT_TEST)/
	cp $(TEST_PATH)/t3.o $(NEXT_TEST)/

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
	@rm -r src/lexer.cpp
	@rm -r inc/lexer.hpp
	@rm -r inc/parser.hpp
	@rm -r src/parser.cpp


$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "${GREEN}Linking: $@${NC}"
	$(CXX) $(OBJECTS) -o $@ ${LIBS}

-include $(DEPS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "${GREEN}Compiling: $< -> $@${NC}"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
	
