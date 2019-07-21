#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int key;
    struct node* left;
    struct node* right;
} Node;

typedef struct{
    Node *head;
} List;

Node *add_node(Node *cur_node, int key);
void print_tree(Node *cur_node);
int symmetric_count(Node *cur_node, int *height);

int main(){
    List l;
    l.head = NULL;

    l.head = add_node(l.head, 50);
    l.head = add_node(l.head, 25);
    l.head = add_node(l.head, 75);
    l.head = add_node(l.head, 30);
    l.head = add_node(l.head, 15);
    l.head = add_node(l.head, 100);
//    l.head = add_node(l.head, 60);

    printf("symmetry count is %d\n", symmetric_count(l.head,NULL));

    print_tree(l.head);

    return 0;
}

/*  input: tree
 *  output: number of nodes that the height of their right son's tree
 *                  is equal to the height of their left son's tree
 * */
int symmetric_count(Node *cur_node, int *height){
    if (!cur_node) {
        *height = 0;
        return 0;
    }
    int height_left, height_right;

    int symmetric_count_left = symmetric_count(cur_node->left, &height_left);
    int symmetric_count_right = symmetric_count(cur_node->right, &height_right);

    if (height) {
        *height = (height_left > height_right ? height_left : height_right) + 1;
    }

    return symmetric_count_left + symmetric_count_right + (height_left == height_right);
}

Node *add_node(Node *cur_node, int key) {
    if (!cur_node){
        Node* newNode = (Node*) malloc (sizeof(Node));
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (key > cur_node->key){
        cur_node->right = add_node(cur_node->right, key);
    } else {
        cur_node->left = add_node(cur_node->left, key);
    }
    return cur_node;
}

void print_tree(Node *cur_node){
    if (!cur_node){
        return;
    }
    print_tree(cur_node->left);
    printf("%d\t",cur_node->key);
    print_tree(cur_node->right);
}

