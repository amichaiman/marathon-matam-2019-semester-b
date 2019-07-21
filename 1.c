#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;

typedef struct{
    Node *head;
} List;

void print_tree(Node *cur_node);
int is_order_tree(Node* cur_node);
Node* find_max_in_ordered_tree(Node* cur_node);

int main() {
    List l;
    Node n1 = {75, NULL, NULL};
    Node n2 = {80, NULL, NULL};
    Node n3 = {196, NULL, NULL};
    Node n4 = {202, NULL, NULL};
    Node n5 = {70, &n1, &n2};
    Node n6 = {100, &n3, &n4};
    Node n7 = {10, &n5, &n6};
    l.head = &n7;

    printf("The tree is%s an ordered tree\n", is_order_tree(l.head) ? "" : "n't");
    printf("max node in ordred tree: %d\n", find_max_in_ordered_tree(l.head)->key);

    return 0;
}

int is_leaf(Node* cur_node) {
    return !cur_node->left && !cur_node->right;
}

int is_order_tree(Node* cur_node) {
    /* no tree of leaf */
    if (!cur_node || is_leaf(cur_node)) {
        return 1;
    }

    /* doesn't have 2 sons */
    if (!cur_node->right || !cur_node->left) {
        return 0;
    }
    return cur_node->right->key > cur_node->left->key && //right son must be bigger than left
        cur_node->left->key > cur_node->key           && //cur node's key must be smaller than both sons
        is_order_tree(cur_node->left)                 &&
        is_order_tree(cur_node->right);
}

Node* find_max_in_ordered_tree(Node* cur_node) {
    if (!cur_node || is_leaf(cur_node)) {
        return cur_node;
    }

    Node* max_left = find_max_in_ordered_tree(cur_node->left);
    Node* max_right = find_max_in_ordered_tree(cur_node->right);

    return max_left->key > max_right->key ? max_left : max_right;
}

void print_tree(Node *cur_node){
    if (!cur_node){
        return;
    }
    print_tree(cur_node->left);
    printf("%d\t",cur_node->key);
    print_tree(cur_node->right);
}
