CXX = g++
CXXFLAGS = -Wall -Wextra -Werror --std=c++17
LDFLAGS = -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage -lstdc++ -lm
VAFLAGS = -lgtest -lgtest_main
VALGRIND = valgrind
VALGRINDFLAGS = --leak-check=full --error-exitcode=1
MAIN = main/matrix_cpp_main.cpp
HEADER = headers/matrix_cpp.h
TEST = tests/test.cpp
BUILD_DIR = build
COV_DIR = coverage
VAL_DIR = valgrind

all: clean format cppcheck test valgrind coverage open_coverage

clean:
	rm -rf $(BUILD_DIR) $(COV_DIR) Coverage_Report.info $(VAL_DIR)

test:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST) $(MAIN) $(LDFLAGS) -o $(BUILD_DIR)/matrix

format:
	clang-format -i $(MAIN) $(HEADER) $(TEST)

cppcheck:
	cppcheck --language=c++ --std=c++17 $(MAIN) $(TEST) $(HEADER)

valgrind:
	mkdir -p $(VAL_DIR)
	$(CXX) $(CXXFLAGS) $(TEST) $(MAIN) $(VAFLAGS) -o $(VAL_DIR)/matrix
	$(VALGRIND) $(VALGRINDFLAGS) ./$(VAL_DIR)/matrix

run:
	./$(BUILD_DIR)/matrix

coverage: $(BUILD_DIR)/matrix
	mkdir -p $(COV_DIR)
	./$(BUILD_DIR)/matrix
	lcov --capture --directory . --output-file Coverage_Report.info --rc branch_coverage=1 --no-external --exclude '*/tests/*'
	genhtml Coverage_Report.info --output-directory $(COV_DIR)


open_coverage:
	@google-chrome $(COV_DIR)/index.html || open $(COV_DIR)/index.html || echo "Unable to open coverage report."

.PHONY: all clean test run coverage open_coverage valgrind format cppcheck
