#include <stdio.h>
#include <stdlib.h>

// 3차 B-tree -> 최대 키 개수: 2개, 최대 자식 노드 개수: 3개
#define order 3 

// 노드 기본 형식
struct node
{
    int n_keys; // 현재 키 개수
    int keys[order - 1]; // 키 값 저장할 배열 (키 최대 개수는 order-1)
    struct node* children[order]; // 자식 노드 포인터
};

// 삽입 삭제 시 순회를 위한 포인터
struct node* b_tree = NULL;

struct node* create_node()
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    // 새로운 노드 초기화
    new_node->n_keys = 0; 
    for (int i = 0; i < order - 1; i++) {
        new_node->keys[i] = 0;
    }
    for (int i = 0; i < order; i++) {
        new_node->children[i] = NULL;
    }
    // 새로운 노드를 만들고 그 시작 주소값 반환
    return new_node;
}

void insert_node(int key)
{
    // b_tree 포인터는 늘 트리의 시작점을 가리킴
    // while 연결된 포인터가 없을 때까지 반복
    //  for 키 값 개수만큼
    //  만약 현재 키값보다 크고, 다음 키값보다 작으면 현재 키값에 해당하는
    //  자식 노드로 이동한 뒤 거기서 다시 비교
    
    // 1. 노드 접근 들어있는 키 값 개수만큼 탐색 시작
    // 2. 탐색하다가 적절한 위치를 찾았는데 거기에 연결된 자식노드가 있다?
    // 3. 그럼 그 자식 노드로 이동해서 다시 탐색 시작
    // 4. 만약 적절한 위치를 찾았는데 거기에 연결된 자식노드가 없다?
    // 5. 두 가지 경우로 삽입
    // 6. 최대 키 값 개수를 초과하지 않을 경우 그 위치에 삽입
    // 7. 최대 키 값 개수를 초과할 경우 분할 수행 후 다시 탐색

    // 키 값 개수 초과로 인한 분할은 나중에 구현하기

    // 삽입 함수
    // 키 값 순회 함수
    // 분할 함수
    
    struct node* node = b_tree;

    while(true){
        if(node == NULL) break;
        int result = 0;

        for(int i = 0; i < node -> n_keys; i++){
            if(node -> keys[i] == 0){
                if(node -> children[i] != NULL){
                    // 자식노드로 이동하여 또다시 비교 수행
                    node = node -> children[i];
                    result =1;
                }
                else
            }
            if(key < node -> keys[i]){
                // 자식노드가 있는 경우
                if(node -> children[i] != NULL){
                    // 자식노드로 이동하여 또다시 비교 수행
                    node = node -> children[i];
                }
                // 자식노드가 없는 경우
                else{
                    // 키 값 개수 초과할 경우 분할 수행
                    if(node -> n_keys == (order - 1))
                    // 키 값 개수 초과하지 않을 경우 한 칸 밀어서 삽입
                    else {
                        node -> keys[i+1] = node -> keys[i];
                        node -> keys[i] = key;
                    }
                } 
            }
        }
        if(result == 0){
            if(node -> children[node -> n_keys] == NULL){
                node -> keys[node -> n_keys] = key;
                node -> n_keys++;
                break;
            }
            else {
                node = node -> children[node -> n_keys];
            }
        }
        
            
    }
    
}

void delete_node(int key) {

}

int find_node(int key) {
    return 0;
}

void print_tree() {

}

int main() {
    b_tree = create_node();

    while(1) {
        char command;
        scanf("%c", &command);
        getchar();

        int key;
        switch (command) {
            case 'i':
                scanf("%d", &key);
                insert_node(key);
                break;
            case 'd':
                scanf("%d", &key);
                delete_node(key);
                break;
            case 'f':
                scanf("%d", &key);
                if (find_node(key)) {
                    printf("Key found\n");
                } else {
                    printf("Key not found\n");
                }
                break;
            case 'p':
                print_tree();
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