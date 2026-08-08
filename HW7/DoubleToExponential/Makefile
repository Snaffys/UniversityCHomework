CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRC = main.c src/doubleToExponential.c
TEST_SRC = tests/tests.c

OUT = program
TEST_OUT = testProgram

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

test: $(TEST_SRC) src/doubleToExponential.c
	$(CC) $(CFLAGS) -DTEST_MAIN src/doubleToExponential.c $(TEST_SRC) -o $(TEST_OUT)

clean:
	rm -f $(OUT) $(TEST_OUT)

format:
	find . -path ./build -prune -o -type f \( -path "./src/*" -o -path "./include/*" -o -path "./tests/*" -o -name "main.c" \) \( -name '*.c' -o -name '*.h' \) -print | xargs clang-format --style=file -i

format-check:
	find . -path ./build -prune -o -type f \( -path "./src/*" -o -path "./include/*" -o -path "./tests/*" -o -name "main.c" \) \( -name '*.c' -o -name '*.h' \) -print | xargs clang-format --style=file --dry-run -Werror
    
