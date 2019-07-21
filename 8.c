#include <stdio.h>
#include <stdlib.h>

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
void find_prev_next(Node* cur_node, int a, int *cosest_from_bottom, int *closest_from_top);

int main(){
    List l;
    l.head = NULL;
    int prev=-1, next=-1;
    l.head = add_node(l.head, 50);
    l.head = add_node(l.head, 4);
    l.head = add_node(l.head, 2);
    l.head = add_node(l.head, 6);
    l.head = add_node(l.head, 100);
    l.head = add_node(l.head, 96);
    l.head = add_node(l.head, 202);

    find_prev_next(l.head, 1, &prev, &next);
    printf("prev: %d\tnext: %d",prev,next);
//    print_tree(l.head);

    return 0;
}

/*  input: tree, number, and a pointer to a variable that will hold the
 *              closest value to the number from below and a variable
 *              that will hold the smallest number from above
 *  output: none
 *
 *  function assigns the closest to from below and from above
 * */
void find_prev_next(Node* cur_node, int a, int *closest_from_bottom, int *closest_from_top){
    if (!cur_node) {
        return;
    }
    if (cur_node->key > a) { // if key is bigger than a, check if it's the closest from above
        if (*closest_from_top == -1 || cur_node->key < *closest_from_top) {
            *closest_from_top = cur_node->key;
        }
    } else if (cur_node->key < a) {// if key is smaller than a, check if it's the closest from below
        if (*closest_from_bottom == -1 || cur_node->key > *closest_from_bottom) {
            *closest_from_bottom = cur_node->key;
        }
    }
    find_prev_next(cur_node->left, a, closest_from_bottom, closest_from_top);
    find_prev_next(cur_node->right, a, closest_from_bottom, closest_from_top);
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
