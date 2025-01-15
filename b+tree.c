#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define order 4 // 최대 자식 노드 개수

// b+tree 노드 기본 구조
struct node {
    int n_keys;
    int keys[order]; // 최대 키값 개수(order -1) + 분할 시 임시로 키 저장할 공간(1)
    struct node* children[order+1]; // 최대 자식 노드 개수(order) + 분할 시 임시로 자식 노드 포인터 저장할 공간(1)
    bool is_leaf; // 리프 노드 체크
};

// 루트 노드 가리키는 구조체 포인터
struct node* b_tree = NULL;

// 새로운 노드 생성 함수
struct node* create_node(bool is_leaf);

// 키 값 삽입할 인덱스 위치에 따라 기존의 키값, 포인터값 이동 후 새로운 키 값 삽입
void insert_value(struct node* insert, int index, int key); 

// 키 값 삽입 시 적절한 위치에 해당하는 인덱스 리턴
int find_index(struct node* search, int key); 

// 분할 함수
void split(struct node* split_node, struct node* parent);

// 삽입 함수 전체
void insert_node(int key, struct node* search, struct node* parent);

// tree 출력 함수
void print_tree(struct node* search);

// scan 함수 -> 트리에서 a이상 b이하 범위 내에 있는 수 모두 출력
void scan(int a, int b , struct node* search);


int main()
{
    b_tree = create_node(true);

    while (1) {
        char command;

        command = getchar();
        getchar();
        
        int key;
        int a, b;

        switch (command) {
            case 'i':
                scanf("%d", &key);
                getchar();
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
            case 's':
                printf("a = ");
                scanf("%d", &a);
                getchar();
                printf("b = ");
                scanf("%d", &b);
                getchar();

                scan(a, b, b_tree);
                printf("\n");
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


// 새로운 노드 생성 함수
struct node* create_node(bool is_leaf)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->n_keys = 0;

    for (int i = 0; i < order; i++) {
        new_node->keys[i] = 0;
    }
    for (int i = 0; i < (order+1); i++) {
        new_node->children[i] = NULL;
    }
    new_node->is_leaf = is_leaf;

    return new_node;
}

// 키 값 삽입할 인덱스 위치에 따라 기존의 키값, 포인터값 이동 후 새로운 키 값 삽입
void insert_value(struct node* insert, int index, int key)
{
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

// 키 값 삽입 시 적절한 위치에 해당하는 인덱스 리턴
int find_index(struct node* search, int key)
{
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

// 분할 함수
void split(struct node* split_node, struct node* parent)
{
    int n_keys = split_node->n_keys;
    int mid_index = n_keys/2;
    int mid_value = split_node->keys[mid_index];
    bool is_leaf = split_node->is_leaf;

    struct node* new_node;

    // 분할 할 노드가 리프 노드인 경우
    if (is_leaf){
        new_node = create_node(true);
        
        for (int i = 0; i < (n_keys - mid_index); i++){
            new_node->keys[i] = split_node->keys[mid_index + i];
        }
        for (int i = 0; i < (n_keys - mid_index + 1); i++){
            new_node->children[i] = split_node->children[mid_index + i];
        }
        split_node->n_keys = mid_index;
        new_node->n_keys = n_keys - mid_index;

        split_node->children[mid_index] = new_node;
    }
    // 분할 할 노드가 리프 노드가 아닌 경우 -> btree 분할과 동일
    else {
        new_node = create_node(false);

        for (int i = 0; i < (n_keys - mid_index - 1); i++){
            new_node->keys[i] = split_node->keys[mid_index+1 + i];
        }
        for (int i = 0; i < (n_keys - mid_index); i++){
            new_node->children[i] = split_node->children[mid_index+1 + i];
        }
        split_node->n_keys = mid_index;
        new_node->n_keys = n_keys - mid_index - 1;
    }

    // 부모 노드로 중간값 삽입
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

// 삽입 함수 전체
void insert_node(int key, struct node* search, struct node* parent) 
{
    // 현재 노드 키 값 개수 저장
    int n_keys = search->n_keys;
    // 현재 노드에서 키 값 삽입할 위치 찾기
    int index = find_index(search, key);

    // 만약 index에 자식 노드가 존재하면 현재 탐색 노드를 자식 노드로 변경
    if (search->children[index] != NULL){
        insert_node(key, search->children[index], search);
    }
    // index에 연결된 자식 노드가 없다면 키 값 삽입
    else {
        insert_value(search, index, key);
        // 키 값 삽입 후 최대 키 값 개수 초과하면 분할 시행
        if (search->n_keys == order) split(search, parent);

        return;
    }
    // 아래 if 문에서 최대 키 값 개수를 초과한다면 분할로 인해 
    // 중간값이 올라와 키 값 개수가 늘어난 것이므로 다시 분할 시행
    if (search->n_keys == order) split(search, parent);   
}

void delete_node(int key) 
{

}

int find_node(int key)
{
    return 0;
}

// 트리 출력 함수
void print_tree(struct node* search) 
{
    printf("RESULT\n");

    // 최하단 맨왼쪽 리프 노드로 이동(트리에서 가장 작은 수)
    while (search->children[0] != NULL) {
        search = search->children[0];
    }

    // 왼쪽부터 오른쪽 끝까지 이동하면서 키 값 순서대로 출력
    while (true){
        for (int i = 0; i < search->n_keys; i++){
            printf("%d ", search->keys[i]);
        }
        printf("\n");
        search = search->children[search->n_keys];
        
        if (search == NULL) break;
    }
}

// scan 함수 -> 트리에서 a이상 b이하 범위 내에 있는 수 모두 출력
void scan(int a, int b, struct node* search)
{
    for(int i = 0; i < search->n_keys; i++){
        if ((search->keys[i] >= a) && (search->keys[i] <= b)){
            printf("%d  ", search->keys[i]);
        }
    }

    for(int i = 0; i <= search->n_keys; i++){
        if (search->children[i] != NULL){
            scan(a, b, search->children[i]);
        }
    }
}

