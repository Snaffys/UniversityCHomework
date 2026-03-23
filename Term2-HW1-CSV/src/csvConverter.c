#include "../include/csvConverter.h"

void printRowSeparation(
    const char* lSymb, const char* mSymb, const char* rSymb, const char* symb, int cols, int colLength, FILE* file)
{
    fprintf(file, "%s", lSymb);
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < colLength + 2; ++j)
            fprintf(file, "%s", symb);
        if (i < cols - 1)
            fprintf(file, "%s", mSymb);
    }
    fprintf(file, "%s\n", rSymb);
}

int isDouble(const char* str)
{
    char* endptr;

    while (isspace((unsigned char)*str))
        ++str;

    if (*str == '\0')
        return 0;

    strtod(str, &endptr);
    while (isspace((unsigned char)*endptr))
        ++endptr;

    return (*endptr == '\0');
}

char* readLine(FILE* f)
{
    int size = 4;
    int len = 0;

    char* buffer = malloc(size);
    if (!buffer)
        return NULL;

    int c;
    while ((c = fgetc(f)) != EOF && c != '\n') {
        if (len + 1 >= size) {
            size *= 2;
            char* tmp = realloc(buffer, size);
            if (!tmp) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[len++] = c;
    }

    if (len == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

int trimCsvField(char* field)
{
    int len = strlen(field);

    if (len >= 2 && field[0] == '"' && field[len - 1] == '"') {
        memmove(field, field + 1, len - 2);
        field[len - 2] = '\0';
        len -= 2;
    }

    char* src = field;
    char* dst = field;
    while (*src) {
        if (*src == '"' && *(src + 1) == '"') {
            *dst++ = '"';
            src += 2;
        } else
            *dst++ = *src++;
    }
    *dst = '\0';
    return dst - field;
}

int getTrimmedLen(const char* start, int len)
{
    if (len >= 2 && start[0] == '"' && start[len - 1] == '"') {
        start++;
        len -= 2;
    }

    int trimmedLen = 0;
    int i = 0;
    while (i < len) {
        if (start[i] == '"' && i + 1 < len && start[i + 1] == '"')
            i += 2;
        else
            ++i;
        ++trimmedLen;
    }

    return trimmedLen;
}

int convertCsvToTxt(FILE* csvFile, FILE* txtFile)
{
    int maxCols = 0;
    int maxColLen = 0;

    // pass 1 (compute maxCols and maxColLength)
    char* line;
    while ((line = readLine(csvFile)) != NULL) {
        int cols = 0;
        int inQuotes = 0;
        char* start = line;
        char* ptr = line;
        while (1) {
            if (*ptr == '"') {
                if (*(ptr + 1) == '"')
                    ++ptr;
                else
                    inQuotes = !inQuotes;
            }

            if ((*ptr == ',' && (!inQuotes)) || *ptr == '\0') {
                ++cols;
                if (cols > maxCols)
                    maxCols = cols;

                int len = ptr - start;
                int fieldLen = getTrimmedLen(start, len);
                if (fieldLen > maxColLen)
                    maxColLen = fieldLen;

                if (*ptr == '\0')
                    break;

                start = ptr + 1;
            }
            ++ptr;
        }
        free(line);

        if (inQuotes) {
            printf("unmatched quote in .csv file.\n");
            return 1;
        }
    }

    if (maxCols == 0)
        return 0;

    rewind(csvFile);

    // pass 2 (read from csv file and writo into txt file)
    int rowInd = 0;
    char* nextLine = readLine(csvFile);
    while (nextLine != NULL) {
        line = nextLine;
        nextLine = readLine(csvFile);

        if (rowInd == 0)
            printRowSeparation("╔", "╦", "╗", "═", maxCols, maxColLen, txtFile);

        fprintf(txtFile, "║");

        int printedCols = 0;
        int inQuotes = 0;
        char* start = line;
        char* ptr = line;
        while (1) {
            if (*ptr == '"') {
                if (*(ptr + 1) == '"')
                    ++ptr;
                else
                    inQuotes = !inQuotes;
            }
            if ((*ptr == ',' && (!inQuotes)) || *ptr == '\0') {
                int len = ptr - start;
                char* field = malloc(len + 1);
                memcpy(field, start, len);
                field[len] = '\0';
                int fieldLen = trimCsvField(field);

                if (rowInd == 0) {
                    fprintf(txtFile, " %s", field);
                    for (int i = 0; i < maxColLen - fieldLen; ++i)
                        fputc(' ', txtFile);
                    fprintf(txtFile, " ║");
                } else {
                    if (isDouble(field)) {
                        for (int i = 0; i < maxColLen - fieldLen + 1; ++i)
                            fputc(' ', txtFile);
                        fprintf(txtFile, "%s ", field);
                    } else {
                        fprintf(txtFile, " %s", field);
                        for (int i = 0; i < maxColLen - fieldLen + 1; ++i)
                            fputc(' ', txtFile);
                    }

                    if (printedCols == maxCols - 1)
                        fprintf(txtFile, "║");
                    else
                        fprintf(txtFile, "│");
                }

                free(field);
                ++printedCols;

                if (*ptr == '\0')
                    break;

                start = ptr + 1;
            }
            ++ptr;
        }

        if (inQuotes) {
            printf("unmatched quote in .csv file.\n");
            free(line);
            return 1;
        }

        while (printedCols < maxCols) {
            for (int i = 0; i < maxColLen + 1; ++i)
                fputc(' ', txtFile);

            if (printedCols == maxCols - 1)
                fprintf(txtFile, " ║");
            else
                fprintf(txtFile, " │");

            ++printedCols;
        }

        fputc('\n', txtFile);

        if (nextLine != NULL) {
            if (rowInd == 0)
                printRowSeparation("╠", "╬", "╣", "═", maxCols, maxColLen, txtFile);
            else
                printRowSeparation("╠", "┼", "╣", "─", maxCols, maxColLen, txtFile);
        }

        free(line);

        ++rowInd;
    }

    printRowSeparation("╚", "╧", "╝", "═", maxCols, maxColLen, txtFile);

    return 0;
}
