#include "../include/avlAirport.h"

void testCreateAVLNode()
{
    AVLNode* node = createAVLNode("LED", "Pulkovo Airport");
    if (node == NULL) {
        printf("FAIL testCreateAVLNode: node is NULL\n");
        return;
    }
    if (strcmp(node->code, "LED") != 0 || strcmp(node->name, "Pulkovo Airport") != 0) {
        printf("FAIL testCreateAVLNode: expected LED:Pulkovo Airport, got %s:%s\n", node->code, node->name);
    } else {
        printf("PASS testCreateAVLNode\n");
    }
    free(node);
    node = NULL;
}

void testAddAndFindAVLNode()
{
    AVLNode* root = NULL;
    root = addAVLNode(root, "LED", "Pulkovo Airport");
    root = addAVLNode(root, "AMS", "Amsterdam Airport Schiphol");

    AVLNode* res1 = findAVLNode(root, "LED");
    AVLNode* res2 = findAVLNode(root, "AMS");
    AVLNode* res3 = findAVLNode(root, "JFK");

    if (res1 == NULL || strcmp(res1->name, "Pulkovo Airport") != 0)
        printf("FAIL testAddAndFindAVLNode: LED not found or wrong name\n");
    else if (res2 == NULL || strcmp(res2->name, "Amsterdam Airport Schiphol") != 0)
        printf("FAIL testAddAndFindAVLNode: AMS not found or wrong name\n");
    else if (res3 != NULL)
        printf("FAIL testAddAndFindAVLNode: JFK should not be found\n");
    else
        printf("PASS testAddAndFindAVLNode\n");

    freeAVLTree(root);
    root = NULL;
}

void testAddExistingUpdatesName()
{
    AVLNode* root = NULL;
    root = addAVLNode(root, "AAA", "Old Name");
    root = addAVLNode(root, "AAA", "New Name");

    AVLNode* res = findAVLNode(root, "AAA");
    if (res == NULL || strcmp(res->name, "New Name") != 0)
        printf("FAIL testAddExistingUpdatesName: expected 'New Name', got '%s'\n", (res != NULL) ? res->name : "NULL");
    else
        printf("PASS testAddExistingUpdatesName\n");

    freeAVLTree(root);
    root = NULL;
}

void testDeleteAVLNode()
{
    AVLNode* root = NULL;
    root = addAVLNode(root, "LED", "Pulkovo Airport");
    root = addAVLNode(root, "AMS", "Amsterdam Airport Schiphol");
    root = addAVLNode(root, "JFK", "John F Kennedy International Airport");

    root = deleteAVLNode(root, "JFK");
    AVLNode* res1 = findAVLNode(root, "JFK");
    AVLNode* res2 = findAVLNode(root, "AMS");
    AVLNode* res3 = findAVLNode(root, "LED");

    if (res1 != NULL)
        printf("FAIL testDeleteAVLNode: JFK should be deleted\n");
    else if (res2 == NULL || res3 == NULL)
        printf("FAIL testDeleteAVLNode: other nodes missing after deletion\n");
    else
        printf("PASS testDeleteAVLNode\n");

    freeAVLTree(root);
    root = NULL;
}

void testAVLHeightBalance()
{
    AVLNode* root = NULL;
    root = addAVLNode(root, "B", "B");
    root = addAVLNode(root, "A", "A");
    root = addAVLNode(root, "C", "C");

    int h = getAVLHeight(root);
    int balance = getAVLBalance(root);

    if (h != 1)
        printf("FAIL testAVLHeightBalance: unexpected height %d\n", h);
    else if (balance != 0)
        printf("FAIL testAVLHeightBalance: unexpected balance %d\n", balance);
    else
        printf("PASS testAVLHeightBalance\n");

    freeAVLTree(root);
    root = NULL;
}

#ifdef TEST_MAIN
int main()
{
    testCreateAVLNode();
    testAddAndFindAVLNode();
    testAddExistingUpdatesName();
    testDeleteAVLNode();
    testAVLHeightBalance();

    printf("All tests executed\n");
    return 0;
}
#endif
