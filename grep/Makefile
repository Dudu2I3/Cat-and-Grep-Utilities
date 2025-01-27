CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

SRC = grep.c

BIN = grep


all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
test: $(BIN)
	@echo "Running tests..."
	@$(MAKE) run_tests

run_tests:
	# Файлы для тестов
	@echo "Creating test files..."
	@echo "Hello World" > input1.txt
	@echo "Hello School21" >> input1.txt
	@echo "Goodbye World" >> input1.txt
	@echo "Another test file" > input2.txt
	@echo "Some more content" >> input2.txt
	@echo "hello School21" >> input2.txt
	@echo "Hello World" > input3.txt
	@echo "test file" >> input3.txt

	# Создаем файл с регулярными выражениями для флага -f
	@echo "Hello" > regex.txt
	@echo "World" >> regex.txt

	# Тест 1: Стандартный grep vs grep с флагом -e "Hello"
	@echo "Running Test 1: Standard grep vs grep with -e \"Hello\""
	@./$(BIN) -e "Hello" input1.txt > result1.txt
	@grep -e "Hello" input1.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 1 failed"; exit 1; }

	# Тест 2: Стандартный grep vs custom grep с флагом -i (регистронезависимый поиск)
	@echo "Running Test 2: Standard grep vs custom grep with -i (case-insensitive)"
	@./$(BIN) -i -e "hello" input2.txt > result1.txt
	@grep -i -e "hello" input2.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 2 failed"; exit 1; }

	# Тест 3: Стандартный grep vs custom grep с флагом -v (исключить совпадения)
	@echo "Running Test 3: Standard grep vs custom grep with -v (exclude matches)"
	@./$(BIN) -v -e "Hello" input3.txt > result1.txt
	@grep -v -e "Hello" input3.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 3 failed"; exit 1; }

	# Тест 4: Стандартный grep vs custom grep с флагом -f (получение регулярных выражений из файла)
	@echo "Running Test 4: Standard grep vs custom grep with -f (using file with regex)"
	@./$(BIN) -f regex.txt input1.txt > result1.txt
	@grep -f regex.txt input1.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 4 failed"; exit 1; }

	# Тест 5: Стандартный grep vs custom grep с флагом -c (подсчет совпадений)
	@echo "Running Test 5: Standard grep vs custom grep with -c (count matches)"
	@./$(BIN) -c -e "Hello" input1.txt > result1.txt
	@grep -c -e "Hello" input1.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 5 failed"; exit 1; }

	# Тест 6: Стандартный grep vs custom grep с флагом -l (выводит только имена файлов)
	@echo "Running Test 6: Standard grep vs custom grep with -l (list file names)"
	@./$(BIN) -l -e "Hello" input1.txt input2.txt > result1.txt
	@grep -l -e "Hello" input1.txt input2.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 6 failed"; exit 1; }

	# Тест 7: Стандартный grep vs custom grep с комбинацией флагов -i и -v
	@echo "Running Test 7: Standard grep vs custom grep with -i and -v"
	@./$(BIN) -i -v -e "hello" input2.txt > result1.txt
	@grep -i -v -e "hello" input2.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 7 failed"; exit 1; }

	# Тест 8: Стандартный grep vs custom grep с комбинацией флагов -i и -c
	@echo "Running Test 8: Standard grep vs custom grep with -i and -c"
	@./$(BIN) -i -c -e "hello" input2.txt > result1.txt
	@grep -i -c -e "hello" input2.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 8 failed"; exit 1; }

	# Тест 9: Стандартный grep vs custom grep с комбинацией флагов -l и -v
	@echo "Running Test 9: Standard grep vs custom grep with -l and -v"
	@./$(BIN) -l -v -e "hello" input2.txt input3.txt > result1.txt
	@grep -l -v -e "hello" input2.txt input3.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 9 failed"; exit 1; }

	# Тест 10: Стандартный grep vs custom grep с комбинацией флагов -i, -v, -c
	@echo "Running Test 10: Standard grep vs custom grep with -i, -v, -c"
	@./$(BIN) -i -v -c -e "hello" input2.txt > result1.txt
	@grep -i -v -c -e "hello" input2.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 10 failed"; exit 1; }

	# Тест 11: Стандартный grep vs custom grep с флагом -n (номер строки перед выводом)
	@echo "Running Test 11: Standard grep vs custom grep with -n (line number)"
	@./$(BIN) -n -e "Hello" input1.txt > result1.txt
	@grep -n -e "Hello" input1.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 11 failed"; exit 1; }

	# Тест 12: Стандартный grep vs custom grep с флагом -h (без имени файла)
	@echo "Running Test 12: Standard grep vs custom grep with -h (no filename)"
	@./$(BIN) -h -e "Hello" input1.txt input2.txt > result1.txt
	@grep -h -e "Hello" input1.txt input2.txt > result2.txt
	@diff result1.txt result2.txt || { echo "Test 12 failed"; exit 1; }

	# Очистка тестовых файлов
	@rm -f input1.txt input2.txt input3.txt result1.txt result2.txt regex.txt
	@echo "All tests passed!"