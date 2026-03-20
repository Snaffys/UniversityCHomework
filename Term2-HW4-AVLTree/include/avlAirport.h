#define CODE_LENGTH 4
#define NAME_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNode {
    char code[CODE_LENGTH];
    char name[NAME_LENGTH];
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

AVLNode* createAVLNode(const char* code, const char* name);

int getAVLHeight(AVLNode* node);
int getMax(int a, int b);
int getAVLBalance(AVLNode* node);

AVLNode* rotateRight(AVLNode* node);
AVLNode* rotateLeft(AVLNode* node);

AVLNode* findAVLNode(AVLNode* root, const char* code);

AVLNode* addAVLNode(AVLNode* root, const char* code, const char* name);

AVLNode* minValueNode(AVLNode* node);
AVLNode* deleteAVLNode(AVLNode* root, const char* code);

AVLNode* loadFile(const char* filename, int* count);
int saveToFile(AVLNode* root, FILE* file);

void freeAVLTree(AVLNode* root);
