#include <stdio.h>


typedef struct node
{
    int data;
    struct node *left ;
    struct node *right;
    int height ;
}node ;

node * newnode(int data) {
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data;
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

int max(int a, int b) {
    return (a > b) ? a : b;
}
int height(node *n) {
    return n ? n->height : 0;
}

node * getBalance(node *root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}
node * insert(node *root, int data) {
    if (root == NULL) return newnode(data);
    if (data < root->data) root->left = insert(root->left, data);
    else if (data > root->data) root->right = insert(root->right, data);
    else return root; // No duplicates

    // Update height and balance factor
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main(void) {
    return 0;
}