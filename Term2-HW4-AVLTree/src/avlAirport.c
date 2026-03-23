#include "../include/avlAirport.h"

AVLNode* createAVLNode(const char* code, const char* name)
{
    AVLNode* node = malloc(sizeof(AVLNode));
    if (node == NULL) {
        printf("Ошибка при выделении памяти.\n");
        return NULL;
    }
    strncpy(node->code, code, CODE_LENGTH - 1);
    node->code[CODE_LENGTH - 1] = '\0';
    strncpy(node->name, name, NAME_LENGTH - 1);
    node->name[NAME_LENGTH - 1] = '\0';
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int getAVLHeight(AVLNode* node) { return (node == NULL) ? -1 : node->height; }

int getMax(int a, int b) { return (a > b) ? a : b; }

int getAVLBalance(AVLNode* node) { return (node == NULL) ? 0 : getAVLHeight(node->left) - getAVLHeight(node->right); }

AVLNode* rotateRight(AVLNode* node)
{
    AVLNode* nodeChild = node->left;
    AVLNode* nodeRightGrandchild = nodeChild->right;

    nodeChild->right = node;
    node->left = nodeRightGrandchild;

    node->height = getMax(getAVLHeight(node->left), getAVLHeight(node->right)) + 1;
    nodeChild->height = getMax(getAVLHeight(nodeChild->left), getAVLHeight(nodeChild->right)) + 1;

    return nodeChild;
}

AVLNode* rotateLeft(AVLNode* node)
{
    AVLNode* nodeChild = node->right;
    AVLNode* nodeLeftGrandchild = nodeChild->left;

    nodeChild->left = node;
    node->right = nodeLeftGrandchild;

    node->height = getMax(getAVLHeight(node->left), getAVLHeight(node->right)) + 1;
    nodeChild->height = getMax(getAVLHeight(nodeChild->left), getAVLHeight(nodeChild->right)) + 1;

    return nodeChild;
}

AVLNode* findAVLNode(AVLNode* root, const char* code)
{
    if (root == NULL) {
        return NULL;
    }

    int cmp = strcmp(code, root->code);

    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return findAVLNode(root->left, code);
    } else {
        return findAVLNode(root->right, code);
    }
}

AVLNode* addAVLNode(AVLNode* root, const char* code, const char* name)
{
    if (root == NULL) {
        return createAVLNode(code, name);
    }

    int cmp = strcmp(code, root->code);

    if (cmp < 0) {
        root->left = addAVLNode(root->left, code, name);
    } else if (cmp > 0) {
        root->right = addAVLNode(root->right, code, name);
    } else {
        strncpy(root->name, name, NAME_LENGTH - 1);
        root->name[NAME_LENGTH - 1] = '\0';
        return root;
    }

    int oldHeight = root->height;

    root->height = 1 + getMax(getAVLHeight(root->left), getAVLHeight(root->right));

    if (root->height == oldHeight) {
        return root;
    }

    int balance = getAVLBalance(root);

    if (balance > 1 && strcmp(code, root->left->code) < 0)
        return rotateRight(root);
    if (balance < -1 && strcmp(code, root->right->code) > 0)
        return rotateLeft(root);
    if (balance > 1 && strcmp(code, root->left->code) > 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && strcmp(code, root->right->code) < 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

AVLNode* minValueNode(AVLNode* node)
{
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

AVLNode* deleteAVLNode(AVLNode* root, const char* code)
{
    if (root == NULL) {
        return root;
    }

    int cmp = strcmp(code, root->code);

    if (cmp < 0) {
        root->left = deleteAVLNode(root->left, code);
    } else if (cmp > 0) {
        root->right = deleteAVLNode(root->right, code);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = (root->left != NULL) ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }

            free(temp);
        } else {
            AVLNode* temp = minValueNode(root->right);
            strncpy(root->code, temp->code, CODE_LENGTH - 1);
            root->code[CODE_LENGTH - 1] = '\0';
            strncpy(root->name, temp->name, NAME_LENGTH - 1);
            root->name[NAME_LENGTH - 1] = '\0';
            root->right = deleteAVLNode(root->right, temp->code);
        }
    }

    if (root == NULL)
        return root;

    int oldHeight = root->height;
    root->height = 1 + getMax(getAVLHeight(root->left), getAVLHeight(root->right));
    if (root->height == oldHeight) {
        return root;
    }

    int balance = getAVLBalance(root);

    if (balance > 1 && getAVLBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getAVLBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getAVLBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getAVLBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

AVLNode* loadFile(const char* filename, int* count)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return NULL;
    }

    AVLNode* root = NULL;
    char line[CODE_LENGTH + NAME_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        char* colon = strchr(line, ':');
        if (colon == NULL) {
            printf("В читаемом файле обнаружена неправильно заполненная строка.\n");
            continue;
        }

        *colon = '\0';
        char* code = line;
        char* name = colon + 1;

        name[strcspn(name, "\n")] = '\0';

        root = addAVLNode(root, code, name);
        if (root != NULL) {
            ++(*count);
        }
    }

    fclose(file);
    return root;
}

int saveToFile(AVLNode* root, FILE* file)
{
    if (root == NULL) {
        return 0;
    }

    int count = 0;

    count += saveToFile(root->left, file);
    fprintf(file, "%s:%s\n", root->code, root->name);
    ++count;
    count += saveToFile(root->right, file);

    return count;
}

void freeAVLTree(AVLNode* root)
{
    if (root == NULL) {
        return;
    }

    freeAVLTree(root->left);
    freeAVLTree(root->right);
    free(root);
}
