#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct node
{
    char word[100];
    struct node *left ;
    struct node *right;
    int height ;
}node ;

node *newnode(char word[]) {
    node *temp = (node *)malloc(sizeof(node));
    strcpy(temp->word, word);
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
int gheight(node *n) {
    return n ? n->height : 0;
}

node * leftRotate(node *x) {
    if (x == NULL || x->right == NULL)
        return x;
    node *y = x->right;
    node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(gheight(x->left), gheight(x->right));
    y->height = 1 + max(gheight(y->left), gheight(y->right));

    // Return new root
    return y;
}
node * rightRotate(node *y) {
    if (y == NULL || y->left == NULL)
        return y;
    node *x = y->left;
    node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(gheight(y->left), gheight(y->right));
    x->height = 1 + max(gheight(x->left), gheight(x->right));

    // Return new root
    return x;
}



int getBalance(node *root) {
    if (root == NULL) return 0;
    return gheight(root->left) - gheight(root->right);
}
node * insert(node *root, char word[]) {
    if (root == NULL) return newnode(word);
    int compare = strcasecmp(word, root->word);
    if (compare < 0) root->left = insert(root->left, word);
    else if (compare > 0) root->right = insert(root->right, word);
    else return root; // No duplicates

    // Update height and balance factor
    root->height = 1 + max(gheight(root->left), gheight(root->right));
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && compare < 0)
        return rightRotate(root);

    // Right Right Case
    if (balance   // prevent crash
 < -1 && compare > 0)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && compare > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && compare < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
node *searchword(node *root,char word[] ,node **last)//searches for the word in the tree and returns the node if found
    {
        while (root!=NULL){
        *last=root;
        int compare=strcasecmp(word,root->word);
        if (compare==0) return root;
        else if (compare<0) root=root->left;
        else root=root->right;
    }
    return NULL;
}
 node*predecessor(node *root,node *target)//searches for the word smaller than the searchword alphabetically
 {
    node *pred=NULL;
    while(root!=NULL){
        int compare=strcasecmp(target->word,root->word);
        if(compare>0){
            pred=root;
            root=root->right;
        }
        else root=root->left;
    }
    return pred;

 }
 node*successor(node *root,node *target)//searches for the word bigger than the searchword alphabetically
 {
    node *succ=NULL;
    while(root!=NULL){
        int compare=strcasecmp(target->word,root->word);
        if(compare<0){
            succ=root;
            root=root->left;
        }
        else root=root->right;
    }
    return succ;
 }

int count(node *root) {
    if (root == NULL) return 0;
    return 1 + count(root->left) + count(root->right);
 }

int main(void) {
    node *root = NULL;
    FILE *f= fopen("Dictionary.txt", "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    char words[100];
    while (fscanf(f, "%s", words) != EOF) {
        root = insert(root, words);
    }
    fclose(f);

    printf("Tree Size = %d\n", count(root));
    printf("Tree Height = %d\n", gheight(root));
    char sentence[200];

    printf("Enter a sentence:\n");
    fgets(sentence, sizeof(sentence), stdin);
    // remove newline
    sentence[strcspn(sentence, "\n")] = 0;
    char *token = strtok(sentence, " ");
    while (token != NULL) {
        node *last = NULL;
        node *found = searchword(root, token, &last);
        if (found) {
            printf("%s is CORRECT.\n", token);
        } else {
            printf("%s is NOT CORRECT.\n", token);
            node *pred = predecessor(root, last);
            node *succ = successor(root, last);
            printf("Suggestions:%s %s %s\n",last->word,pred->word, succ->word);
            
        }
        token = strtok(NULL, " ");
    }
    
    return 0;
}