#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node* next;
} Node;

typedef struct{
    Node *head;
} List;

void add_node(List *l, int key);
void create_list_1(List *l);
void create_list_2(List *l);
int chain_len(Node* node1, Node* node2);
void print_list(Node* cur_node);
List *find_max_segment(List *l1, List *l2);

int main(){
    List l1, l2;
    l1.head = l2.head = NULL;

    create_list_1(&l1);
    create_list_2(&l2);

    print_list(find_max_segment(&l1,&l2)->head);

    return 0;
}
/*  copys n nodes starting at position pos and
 *  returns it as a new list
 * */
List *copy_part_of_list(Node *node, int n){
    int i;
    List *new_list = (List*) malloc (sizeof(List));
    new_list->head = NULL;

    for (i=0; i<n; i++, node = node->next) {
        add_node(new_list, node->key);
    }

    return new_list;
}


/*  returns longest chain of nodes that is a
 *  subset of l1 and of l2
 * */
List *find_max_segment(List *l1, List *l2){
    int max_chain_len = 0;
    int cur_chain_len;
    Node *max_chain_start_node = NULL;
    Node *cur_node_l1;
    Node *cur_node_l2;

    for (cur_node_l1=l1->head; cur_node_l1 != NULL; cur_node_l1=cur_node_l1->next) {
        for (cur_node_l2=l2->head; cur_node_l2 != NULL; cur_node_l2=cur_node_l2->next) {
            cur_chain_len = chain_len(cur_node_l1, cur_node_l2);
            if (cur_chain_len > max_chain_len) {
                max_chain_len = cur_chain_len;
                max_chain_start_node = cur_node_l1;
            }
        }
    }
    if (cur_chain_len > max_chain_len) {
        cur_chain_len = cur_chain_len;
        max_chain_start_node = cur_node_l1;
    }
    return copy_part_of_list(max_chain_start_node, max_chain_len);
}

/*
 *  returns length of similar nodes starting from node1 and node2
 * */
int chain_len(Node* node1, Node* node2){
    int count = 0;
    while (node1 && node2 && (node1->key == node2->key)) {
        count++;
        node1 = node1->next;
        node2 = node2->next;
    }
    return count;
}

/*
 *  compares two given lists
 * */
int listCompare(List *l1, List *l2, Node* pos1, Node* pos2, int n){
}

void create_list_2(List *l) {
    add_node(l,5);
    add_node(l,4);
    add_node(l,4);
    add_node(l,8);
    add_node(l,9);
    add_node(l,5);
    add_node(l,6);
    add_node(l,3);
    add_node(l,6);

}

void create_list_1(List *l) {
    add_node(l,1);
    add_node(l,5);
    add_node(l,6);
    add_node(l,3);
    add_node(l,4);
    add_node(l,8);
    add_node(l,9);
    add_node(l,5);
    add_node(l,4);
    add_node(l,3);
    add_node(l,6);
    add_node(l,7);
}

/*  adds node to end of list
 * */
void add_node(List *l, int key){
    Node *new_node = (Node*) malloc (sizeof(Node));
    Node *cur_node = l->head;

    new_node->key = key;
    new_node->next = NULL;

    if (!cur_node){
        l->head = new_node;
        return;
    }

    while (cur_node->next){
        cur_node = cur_node->next;
    }
    cur_node->next = new_node;
}

void print_list(Node* cur_node){
    if (!cur_node){
        putchar('\n');
        return;
    }
    printf("%d\t",cur_node->key);
    print_list(cur_node->next);
}
