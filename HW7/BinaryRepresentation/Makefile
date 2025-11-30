CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRC = main.c src/logic.c
TEST_SRC = tests/tests.c

OUT = program
TEST_OUT = testProgram

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

test: src/logic.c tests/tests.c
	$(CC) $(CFLAGS) -DTEST_MAIN src/logic.c tests/tests.c -o $(TEST_OUT)

clean:
	rm -f $(OUT) $(TEST_OUT)

format:
	find . -path ./build -prune -o -type f \( -path "./src/*" -o -path "./include/*" -o -path "./tests/*" -o -name "main.c" \) \( -name '*.c' -o -name '*.h' \) -print | xargs clang-format --style=file -i

format-check:
	find . -path ./build -prune -o -type f \( -path "./src/*" -o -path "./include/*" -o -path "./tests/*" -o -name "main.c" \) \( -name '*.c' -o -name '*.h' \) -print | xargs clang-format --style=file --dry-run -Werror

