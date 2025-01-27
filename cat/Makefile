CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

SRC = cat.c

BIN = cat

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

test: $(BIN)
	@echo "Running tests..."
	@$(MAKE) run_tests

run_tests:
	# Create test files
	@echo "Creating test files..."
	@echo "Hello World" > input1.txt
	@echo "Hello School" >> input1.txt
	@echo "" >> input1.txt
	@echo "Goodbye World" >> input1.txt
	@echo "" >> input1.txt
	@echo "" >> input1.txt
	@echo "Another test file" > input2.txt
	@echo "Some more\tcontent" >> input2.txt
	@echo "hello School" >> input2.txt
	@echo "Hello World" > input3.txt
	@echo "test file" >> input3.txt

	# Test 1: Standard cat vs custom cat with -n flag (line numbering)
	@echo "Running Test 1: Standard cat vs custom cat with -n"
	@./$(BIN) -n input1.txt > result1.txt
	@cat -n input1.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 1 failed"; exit 1; }

	# Test 2: Standard cat vs custom cat with -s flag (squeeze blank lines)
	@echo "Running Test 2: Standard cat vs custom cat with -s"
	@./$(BIN) -s input1.txt > result1.txt
	@cat -s input1.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 2 failed"; exit 1; }

	# Test 3: Standard cat vs custom cat with -b flag (number non-blank lines)
	@echo "Running Test 3: Standard cat vs custom cat with -b"
	@./$(BIN) -b input3.txt > result1.txt
	@cat -b input3.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 3 failed"; exit 1; }

	# Test 4: Standard cat vs custom cat with -e flag (show end of line as $)
	@echo "Running Test 4: Standard cat vs custom cat with -e"
	@./$(BIN) -e input1.txt > result1.txt
	@cat -e input1.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 4 failed"; exit 1; }

	# Test 5: Standard cat vs custom cat with -t flag (show tabs as ^I)
	@echo "Running Test 5: Standard cat vs custom cat with -t"
	@./$(BIN) -t input2.txt > result1.txt
	@cat -t input2.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 5 failed"; exit 1; }

	# Test 6: Standard cat vs custom cat with multiple files
	@echo "Running Test 6: Standard cat vs custom cat with multiple files"
	@./$(BIN) input1.txt input2.txt > result1.txt
	@cat input1.txt input2.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 6 failed"; exit 1; }

	# Cleanup test files
	@rm -f input1.txt input2.txt input3.txt result1.txt result2.txt
	@echo "All tests passed!"