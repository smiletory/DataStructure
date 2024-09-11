#include <iostream>
using namespace std;

class priority_queue {
private:
    int size;
    int heap[10001];

public:
    priority_queue() {
        size = 0;
    }

    void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    void push(int n) {
        // Heap의 마지막에 새로운 노드를 추가
        // 마지막 노드 번호 /2한 인덱스가 부모노드
        // 부모노드랑 비교해서 새로운노드가 크면 위치 변경, 아니면 그대로 두고 종료
        // 위치를 변경했으면 변경된 위치에서 다시 부모노드 비교
        // 1이 되면 종료

        size++;
        heap[size] = n;
        int cur_n = size;
        int pn;

        while (true) {
            if (cur_n == 1) break;
            pn = cur_n / 2;
            if (heap[pn] < heap[cur_n]) {
                swap(&heap[pn], &heap[cur_n]);
                cur_n = pn;
            }
            else break;
        }
    }
        
    void pop() {
        // 루트 노드 값을 마지막 노드 값으로 변경
        // 1번 인덱스 요소 *2, *2+1 한 인덱스 요소들 중 큰 값의 인덱스로 swap 함수 실행
        // swap된 인덱스에서 또다시 반복
        // 만약 *2한 인덱스 위치가 heap의 사이즈를 넘어갈 경우 자식 노드가 없는 것이므로 종료

        if (empty()){
            cout << "no elements in queue" << '\n';
            return;
        }
        heap[1] = heap[size];
        size--;

        int cur_n = 1;
        int left;
        int right;
        int cp;
        int cpn;

        while (true) {
            left = cur_n * 2;
            right = (cur_n * 2) + 1;

            if (left > size) break;

            // heap[cn1], heap[cn2] 중 큰거랑 heap[cur_n] 비교
            cpn = left;
            if((right <= size) && (heap[left] < heap[right])) cpn = right;
            cp = heap[cpn];

            if (heap[cur_n] < cp) {
                swap(&heap[cur_n], &heap[cpn]);
                cur_n = cpn;
            }
            else break;
        }
    }

    int top() {
        // 루트 노드 반환
        // heap[1] return
        
        return heap[1];
    }

    bool empty() {
        // Heap의 크기가 0이면 true 반환
        // size = 0 이면 return true;
        if (size == 0) return true;
        else return false;
    }

    void cout_queue(){
        if (empty()){
            cout << "no elements in queue" << '\n';
            return;
        }
        for(int i = 1; i <= size; i++){
            cout << heap[i] << ' ';
        }
        cout << '\n';
    }
};

int main() {
    priority_queue pq;

    pq.push(40);
    pq.push(26);
    pq.push(32);
    pq.cout_queue();

    pq.pop();
    pq.cout_queue();
    cout << pq.top() << "\n";

    pq.push(1);
    pq.push(2);
    pq.push(11);
    pq.cout_queue();

    pq.pop();
    pq.cout_queue();

    return 0;
}