#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
#define MAX 110
#define DEBUG 0
#define SWAP(a,b) {char temp = *a; *a = *b; *b = temp;}

int R,C,N;
char cave[MAX][MAX];
bool visited[MAX][MAX];
bool cflag, stop;

int info[MAX];
int dirx[4] = {1,0,-1,0};
int diry[4] = {0,1,0,-1};

vector<pair<int, int> > cluster;

void push_cluster(int x, int y);
int check(int x, int y);
void print_cave();

void push_down(){
    int size = cluster.size();
    stop = false;
    // for(int i=0;i<cluster.size();i++)
    //     printf("(%d, %d)",cluster[i].first,cluster[i].second);
    // printf("\n");
    while(1){
        int i,l = cluster[0].first;
        int cnt = 0;
        for(i=0; i<size; i++){
            int cy = cluster[i].first;
            int cx = cluster[i].second;
            if(l > cy){
                for(int j=i-cnt; j<i; j++){
                    int bx = cluster[j].second;
                    SWAP(&cave[l][bx], &cave[l+1][bx]);
                    cluster[i].first += 1;
                }
                l = cy; cnt = 0;
            }
            if((cave[cy+1][cx] == 'x') || (cy == R)){
                stop = true;
                break;
            }
            // SWAP(&cave[cy][cx], &cave[cy+1][cx]);
            // cluster[i].first += 1;
            cnt++;
            // print_cave();
            // printf("\n");
        }
        if(i == size){
            for(int j=i-cnt; j<i; j++){
                int bx = cluster[j].second;
                SWAP(&cave[l][bx], &cave[l+1][bx]);
            }
        }
        if(stop) break;
    }
}
void gather(int x, int y){
    cluster.push_back(make_pair(y,x));
    visited[y][x] = true;

    for(int i=0; i<4; i++){
        int ax = x + dirx[i];
        int ay = y + diry[i];
        if(ax > C || ay > R || ax < 1 || ay < 1) continue;
        if((cave[ay][ax] == 'x') && (visited[ay][ax] == false)){
            gather(ax, ay);
        }
    }
}
void dfs(int x, int y){
    visited[y][x] = true;
    if(y == R)
        cflag = true;
    
    for(int i=0; i<4; i++){
        int ax = x + dirx[i];
        int ay = y + diry[i];
        if(ax > C || ay > R || ax < 1 || ay < 1) continue;
        if((cave[ay][ax] == 'x') && (visited[ay][ax] == false)){
            dfs(ax, ay);
        }
    }
}
void visit_clear(){
    for(int j=1; j<=R; j++)
        memset(visited + j, false, C * sizeof(bool));
}
void update_cave(int h, int dir){
    int unit, start, end;
    int x = 0,y = R-h+1;
    char *line = cave[y];
    // 미네랄 만나는 좌표 찾기.
    if(dir == 1){  unit = 1; start = 1; end = C+1;  }
    else{   unit = -1; start = C; end = 0;  }
    for(int i=start; i != end; i+=unit){
        if(line[i] == 'x'){
            x = i;
            break;
        }
    }
    if(x == 0)
        return;
    // 미네랄 파괴.
    cave[y][x] = '.';
#if DEBUG
    printf("mineral : %d, %d\n",R-y+1,x);
#endif
     // 인접한 미네랄들 클러스터 단위로 쭉 따라갔을때 동굴의 바닥(=R)에 닿아야함.
    for(int i=0; i<4; i++){
        int ax = dirx[i] + x;
        int ay = diry[i] + y;
        if(cave[ay][ax] == 'x'){
            cflag = false;
            dfs(ax,ay);
            memset(visited, false, sizeof(visited));
            // visit_clear();
            
#if DEBUG
            printf("start : %d, %d // res : %d\n",R-ay+1,ax,cflag);
#endif
             // 바닥에 도달 못한 클러스터는 쭉 내려야함.
            if(!cflag){
                gather(ax,ay);
                sort(cluster.begin(), cluster.end(), greater<>());
                push_down();
                cluster.clear();
                memset(visited, false, sizeof(visited));
                // visit_clear();
            }
        }
    }
    // 공중에 뜬 클러스터들 쭉 내리기 -> 좌표단위로 ? 

}

int main(void){
    freopen("input.txt","r",stdin);
    
    scanf(" %d %d",&R,&C);
    for(int i=1; i<=R; i++){
        for(int j=1; j<=C; j++){
            scanf(" %c",&cave[i][j]);
        }
    }

    scanf(" %d",&N);
    for(int i=0; i<N; i++){
        scanf("%d",info+i);
    }

    for(int i=0; i<N; i++){
        if(i % 2 == 0)
            update_cave(info[i],1);
        else
            update_cave(info[i],-1);
        // print_cave();
        // printf("\n");
    }

    print_cave();
    return 0;
}
void print_cave(){
    for(int i=1; i<=R; i++){
        for(int j=1; j<=C; j++){
            printf("%c",cave[i][j]);
        }
        printf("\n");
    }
}
/*
queue<pair<int, int> > q_check;
queue<pair<int, int> > q_cluster;
priority_queue<pair<int, int> > bpq, apq;
void push_cluster(int x, int y){
    // 테트리스 블록 내리기인데...
    // cluster의 가장 바닥 줄에 대한 정보 찾기. 
    // 1. priority queue에 y 기준으로 내림차순 정보 모으기.
    // 2. pop 하면서 y 축 방향 +1이 0 인지 확인..?
    
    int size;
    q_cluster.push(make_pair(y,x));
    visited[y][x] = true;

    while(!q_cluster.empty()){
        int qy = q_cluster.front().first;
        int qx = q_cluster.front().second;

        bpq.push(q_cluster.front());
        q_cluster.pop();

        for(int i=0;i<4;i++){
            int ax = qx + dirx[i];
            int ay = qy + diry[i];
            if((cave[ay][ax] == 'x') && (visited[ay][ax] == false)){
                q_cluster.push(make_pair(ay,ax));
                visited[ay][ax] = true;
            }
        }
    }

    size = bpq.size();
    // 그 바닥 중에 x를 만날때까지 내리기.
    while(1){
        int flag = 0;
        while(!bpq.empty()){
            int pqy = bpq.top().first;
            int pqx = bpq.top().second;
            int by = pqy + 1, bx = pqx;
            bpq.pop();
            if((by > R) || (cave[by][bx] == 'x')){
                flag = 1;
                break;
            }
            SWAP(&cave[pqy][pqx] , &cave[by][bx]);
            apq.push(make_pair(by,bx));
            // roll back 되도록 바꿔야함. 
            // 근데 이미 메모리 초과인데..
        }
        if(flag)
            break;
        while(!apq.empty()){
            bpq.push(apq.top());
            apq.pop();
        }
    }
}
int check(int x, int y){
    // 클러스터별로 쭉 따라가기 -> dfs, "bfs"
    visited[y][x] = true;
    q_check.push(make_pair(x,y));
    while(!q_check.empty()){
        int qx = q_check.front().first;
        int qy = q_check.front().second;
        if(qy == R){
            return 1;
        }

        q_check.pop();

        for(int i=0;i<4;i++){
            int ax = qx + dirx[i];
            int ay = qy + diry[i];
            if((cave[ay][ax] == 'x') && (visited[ay][ax] == false)){
                q_check.push(make_pair(ax,ay));
                visited[qy][qx] = true;
            }
        }
    }
    return 0;
}
*/