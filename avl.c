#include <stdio.h>
#include <stdlib.h>
 
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};
 
int getHeight(struct Node *n){
    if(n==NULL)
        return 0;
    return n->height;
}
 
struct Node *createNode(int key){
    struct Node* node = (struct Node *) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}
 
int max (int a, int b){
    return (a>b)?a:b;
}
 
int getBalanceFactor(struct Node * n){
    if(n==NULL){
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;
    while (current->left != NULL)
    current = current->left;
    return current;
}
 
struct Node* rightRotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
 
    return x;
}
 
struct Node* leftRotate(struct Node* x){
    struct Node* y = x->right;
    struct Node* T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
 
    return y;
}
 
struct Node *insert(struct Node* node, int key){
    if (node == NULL)
        return  createNode(key);
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
 
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);
 
    // Left Left Case
        if(bf>1 && key < node->left->key){
            return rightRotate(node);
        }
    // Right Right Case
        if(bf<-1 && key > node->right->key){
            return leftRotate(node);
        }
    // Left Right Case
    if(bf>1 && key > node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    // Right Left Case
    if(bf<-1 && key < node->right->key){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    return node;
}

struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
                free(temp);
        }
        else
        {
            struct Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    
    if (root == NULL)
        return root;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalanceFactor(root);
    if (balance > 1 && getBalanceFactor(root->left) >=0)
        return rightRotate(root);
    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <=0)
        return leftRotate(root);
    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
 
void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node *root) {
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void postOrder(struct Node *root) {
    if(root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}
 
int main(){
    struct Node * root = NULL;
    int val, ch;
    while(1)
    {
        printf("\n1.Insert\n2.Delete\n3.Display\n4.EXIT\nEnter Choice: ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
            printf("\nEnter value: ");
            scanf("%d", &val);
            root=insert(root, val);
            break;
            case 2:
            printf("\nEnter value: ");
            scanf("%d", &val);
            root=deleteNode(root, val);
            break;
            case 3:
            printf("\nPreOrder: ");
            preOrder(root);
            printf("\nInOrder: ");
            inOrder(root);
            printf("\nPostOrder: ");
            postOrder(root);
            break;
            case 4:
            exit(0);
            break;

        }
    }
    return 0;
}










