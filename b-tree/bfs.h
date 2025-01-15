#define MAX_QUEUE_SIZE 1001

// bfs를 위한 queue 정의
typedef struct {
    int front, rear;
    int data[MAX_QUEUE_SIZE];
} q;

bool visited[1001];


void bfs(int start){
    visited[start] = true;
    q.push(start);
    int now;
    while(!q.empty()){
        now = q.front(); q.pop();
        cout << now << " ";
        for(int i = 0; i < edge[now].size(); i++){
            if(!visited[edge[now][i]]){
                visited[edge[now][i]] = true;
                q.push(edge[now][i]);
            }
        }
    }
}