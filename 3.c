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
int is_same_tree(Node* cur_node1, Node* cur_node2);

int main(){
    List l;
    l.head = NULL;

    l.head = add_node(l.head, 50);
    l.head = add_node(l.head, 25);
    l.head = add_node(l.head, 75);
    l.head = add_node(l.head, 30);
    l.head = add_node(l.head, 15);
    l.head = add_node(l.head, 100);
    l.head = add_node(l.head, 60);

    printf("the trees are%s the same\n", is_same_tree(l.head,l.head) ? "" : " not");

//    print_tree(l.head);

    return 0;
}

/*  input: 2 trees
 *  output: 1 if trees are identical. 0 otherwise.
 * */
int is_same_tree(Node* cur_node1, Node* cur_node2){
    if (!cur_node1 && !cur_node2) {
        return 1;
    }
    if (!cur_node1 || !cur_node2) {
        return 0;
    }
    return cur_node1->key == cur_node2->key            &&
        is_same_tree(cur_node1->left, cur_node2->left) &&
        is_same_tree(cur_node1->right, cur_node2->right);
}


Node *add_node(Node *cur_node, int key) {
    if (!cur_node){
        Node* new_node = (Node*) malloc (sizeof(Node));
        new_node->key = key;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
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

