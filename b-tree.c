#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define order 3

struct node {
    int n_keys;
    int keys[order]; // �ӽ÷� Ű ������ ���� + 1
    struct node* children[order+1]; // �ӽ÷� �ڽ� ��� ������ ���� + 1
    bool is_leaf;
};

struct node* b_tree = NULL;

// ���ο� ��� ���� �Լ�
struct node* create_node(bool is_leaf);

// Ű�� �����ϰ� Ű��, �����Ͱ� ��ĭ�� �ڷ� �̵�, n_keys++
void insert_value(struct node* insert, int index, int key); 

// Ű �� ���� �� ������ ��ġ�� �ش��ϴ� �ε��� ��ȣ ����
int find_index(struct node* search, int key); 

// ���� �Լ�
void split(struct node* split_node, struct node* parent);

// ���� �Լ� ��ü
void insert_node(int key, struct node* search, struct node* parent);

// tree ��� �Լ�
void print_tree(struct node* search);

int main() {
    b_tree = create_node(true);

    while(1) {
        char command;

        command = getchar();
        getchar();
        // scanf("%c", &command);
        
        // printf("command: %c\n", command);
        
        int key;
        switch (command) {
            case 'i':
                // printf("command: %c\n", command);
                scanf("%d", &key);
                getchar();
                // printf("command: %c\n", command);
                // printf("key: %d\n", key);
                insert_node(key, b_tree, NULL);
                break;
            // case 'd':
            //     scanf("%d", &key);
            //     getchar();
            //     delete_node(key);
            //     break;
            // case 'f':
            //     scanf("%d", &key);
            //     getchar();
            //     if (find_node(key)) {
            //         printf("Key found\n");
            //     } else {
            //         printf("Key not found\n");
            //     }
            //     break;
            case 'p':
                print_tree(b_tree);
                break;
            case 'q':
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid command\n");
                break;
        }
    }

    return 0;
}


struct node* create_node(bool is_leaf) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->n_keys = 0;
    new_node->is_leaf = is_leaf;

    for (int i = 0; i < order; i++) {
        new_node->keys[i] = 0;
    }
    for (int i = 0; i < (order+1); i++) {
        new_node->children[i] = NULL;
    }
    return new_node;
}
// void scan(int a, int b) {} a,b ���� �� ���
// 
void insert_value(struct node* insert, int index, int key){
    int n_keys = insert->n_keys;

    for (int i = (n_keys-1); i >= index; i--){
        insert->keys[i+1] = insert->keys[i];
    }
    for (int i = n_keys; i >= index; i--){
        insert->children[i+1] = insert->children[i];
    }
    insert->keys[index] = key;
    insert->n_keys++;
}

int find_index(struct node* search, int key){
    int index = 0;
    int n_keys = search->n_keys;

    for (int i = 0; i <= (n_keys-1); i++){
        if ((key < search->keys[i])){
            index = i;
            break;
        }
        index = i + 1;
    }
    return index;
}

void split(struct node* split_node, struct node* parent){
    int n_keys = split_node->n_keys;

    int mid_index = n_keys/2;
    if (n_keys%2 == 0) mid_index--;
    int mid_value = split_node->keys[mid_index];

    struct node* new_node = create_node(split_node->is_leaf);

    for (int i = 0; i < (n_keys - mid_index - 1); i++){
        new_node->keys[i] = split_node->keys[mid_index+1 +i];
    }
    for (int i = 0; i < (n_keys - mid_index); i++){
        new_node->children[i] = split_node->children[mid_index+1 +i];
    }
    split_node->n_keys = mid_index;
    new_node->n_keys = n_keys - mid_index - 1;

    int index = 0;
    if (parent == NULL){
        parent = create_node(false), index = 0;
        parent->keys[index] = mid_value, parent->n_keys++;
        b_tree = parent;
    }
    else {
        index = find_index(parent, mid_value);
        insert_value(parent, index, mid_value);
    }

    parent->children[index] = split_node;
    parent->children[index+1] = new_node;
}


void insert_node(int key, struct node* search, struct node* parent) {

    int n_keys = search->n_keys; // ���� Ž�� ��� Ű ���� ����
    int index = find_index(search, key); // Ű �� ������ ��ġ �ʱ�ȭ

    // ���� Ű �� ������ ��ġ�� �ڽ� ��尡 �����ϸ�
    // ���� Ž�� ��带 �ڽ� ���� ����
    if (search->children[index] != NULL){
        insert_node(key, search->children[index], search);
    }
    else {
        insert_value(search, index, key);
        if (search->n_keys == order) split(search, parent);
        return;
    }

    if (search->n_keys == order) split(search, parent);   
}


void delete_node(int key) {

}

int find_node(int key) {
    return 0;
}


void print_tree(struct node* search) {

    for(int i = 0; i < search->n_keys; i++){
        printf("%d  ", search->keys[i]);
    }
    printf("\n");

    for(int i = 0; i <= search->n_keys; i++){
        if (search->children[i] != NULL){
            print_tree(search->children[i]);
        }
    }
}

