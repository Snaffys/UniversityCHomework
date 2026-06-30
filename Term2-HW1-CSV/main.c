#include "include/csvConverter.h"

int main()
{
    const int PATH_LIMIT = 100;

    // open .csv file
    char csvPath[PATH_LIMIT];
    printf("Enter .csv path:\n");
    if (fgets(csvPath, PATH_LIMIT, stdin) == NULL) {
        printf("input error!\n");
        return 1;
    }
    csvPath[strcspn(csvPath, "\n")] = '\0';
    FILE* csvFile = fopen(csvPath, "r");
    if (csvFile == NULL) {
        printf("file not found!");
        return 1;
    }

    // open .txt file
    char txtPath[PATH_LIMIT];
    printf("Enter .txt path:\n");
    if (fgets(txtPath, PATH_LIMIT, stdin) == NULL) {
        printf("input error!\n");
        return 1;
    }
    txtPath[strcspn(txtPath, "\n")] = '\0';
    FILE* txtFile = fopen(txtPath, "w");
    if (txtFile == NULL) {
        printf("can't write into file!");
        fclose(csvFile);
        return 1;
    }

    int result = convertCsvToTxt(csvFile, txtFile);

    fclose(csvFile);
    fclose(txtFile);

    return result;
}
