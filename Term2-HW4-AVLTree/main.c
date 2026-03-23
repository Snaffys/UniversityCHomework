#include "include/avlAirport.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Недостаточное количество аргументов\nКорректное использование: %s airports.txt\n", argv[0]);
        return 1;
    }

    int loadCount = 0;
    AVLNode* root = loadFile(argv[1], &loadCount);

    printf("Загружено %d аэропортов. Система готова к работе.\n", loadCount);

    char cmd[CODE_LENGTH + NAME_LENGTH + 4];

    while (1) {
        printf("> ");
        if (!fgets(cmd, sizeof(cmd), stdin)) {
            break;
        }
        cmd[strcspn(cmd, "\n")] = '\0';

        if (strncmp(cmd, "find ", 5) == 0) {
            char* code = cmd + 5;
            AVLNode* res = findAVLNode(root, code);

            if (res != NULL) {
                printf("%s → %s\n", code, res->name);
            } else {
                printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
            }
        } else if (strncmp(cmd, "add ", 4) == 0) {
            char* data = cmd + 4;
            char* colon = strchr(data, ':');

            if (colon == NULL)
                continue;

            *colon = '\0';
            char* code = data;
            char* name = colon + 1;

            root = addAVLNode(root, code, name);
            if (root != NULL) {
                printf("Аэропорт '%s' добавлен в базу.\n", code);
            }
        } else if (strncmp(cmd, "delete ", 7) == 0) {
            char* code = cmd + 7;
            root = deleteAVLNode(root, code);
            printf("Аэропорт '%s' удалён из базы.\n", code);
        } else if (strcmp(cmd, "save") == 0) {
            FILE* file = fopen(argv[1], "w");
            if (file == NULL) {
                printf("Ошибка при сохранении файла.\n");
                continue;
            }
            int saveCount = saveToFile(root, file);
            fclose(file);
            printf("База сохранена: %d аэропортов.\n", saveCount);
        } else if (strcmp(cmd, "quit") == 0) {
            freeAVLTree(root);
            root = NULL;
            break;
        }
    }

    return 0;
}
