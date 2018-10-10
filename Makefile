.PHONY:test_run test_build

TEST_TARGET=./debug/test

TESTS= ./test/test.cpp

TEST_FLAG=-lpthread -lgmock -lgtest

vpath %.h ./include
vpath %.cpp ./src
vpath %.cpp ./test

build_test: 
	g++ -o $(TEST_TARGET) ./src/main.cpp $(TESTS) $(TEST_FLAG)


test_run:
	@make build_test
	@clear
	@$(TEST_TARGET)