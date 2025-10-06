# Number Sorter / Сортировка чисел

Program for sorting integers with counting of moved elements.
Программа для сортировки целых чисел с подсчётом перемещённых элементов.

## Build / Сборка

```bash
gcc main.c insertionSort.s -o sorter
```

## Run / Запуск

```bash
# Keyboard input / Ввод с клавиатуры
./sorter
# Then enter numbers separated by spaces, press Enter
# Затем введите числа через пробел, нажмите Enter

# Direct input via echo / Прямой ввод через echo
echo "5 2 8 1 3" | ./sorter
```

## Check result / Проверка результата

```bash
echo "5 2 8 1 3" | ./sorter
echo $?  # Shows count of moved elements / Покажет количество перемещённых элементов
```

## File structure / Структура файлов

- `main.c` - main C code (I/O) / основной код на C (ввод/вывод)
- `insertionSort.s` - sorting algorithm in assembly / алгоритм сортировки на ассемблере
- `README.md` - this instruction / данная инструкция

## Requirements / Требования

- GCC compiler / компилятор GCC
- Linux/Unix system / Linux/Unix система
