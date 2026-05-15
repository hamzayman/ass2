#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>


typedef struct node
{
    char word[100];
    struct node *left ;
    struct node *right;
    int height ;
}node ;

int max(int a, int b) {
    return (a > b) ? a : b;
}
int height(node *n) {
    return n ? n->height : 0;
}

int  getBalance(node *root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

node * newnode(char *word) {
    node *temp = (node *)malloc(sizeof(node));
    strncpy(temp->word, word,100);
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}


node * leftRotate(node *x) {
    node *y = x->right;
    node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    // Return new root
    return y;
}
node * rightRotate(node *y) {
    node *x = y->left;
    node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    // Return new root
    return x;
}


node * insert(node *root, char*word) {
    if (root == NULL) return newnode(word);
    if (strcasecmp(word,root->word)<0) root->left = insert(root->left,word);
    else if (strcasecmp(word,root->word)>0) root->right = insert(root->right, word);
    else return root; // No duplicates

    // Update height and balance factor
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && strcasecmp(word,root->left->word)<0)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && strcasecmp(word,root->right->word)>0)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && strcasecmp(word,root->left->word)>0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && strcasecmp(word,root->right->word)<0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;




}

int main(void) {
    return 0;
}