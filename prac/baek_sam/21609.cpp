/* 교훈 */
/* 
 * 2차원 배열 안에서 그룹 단위로 bfs를 통해 찾을 때, 공통되는 요소는 vector로 모아뒀다가 
    따로 free 해주는 방법이 있다.
 * memset, memcpy 할 때, MAX로 초기화해놓고, 그보다 작은 n*n*sizeof()로 하면 초기화 안된다!
    그냥 sizeof(arr)로 하자.
 * 추가 자료구조(vector) 쓰는 것에 거부감을 가지지 말자. 즉, 여러개의 자료구조 변수를 활용하자.
    하나로 통합하는 것을 고민할 시간에, 그냥 추가로 써서 부분 부분 적용하는것이 더 효율적이다.
*/
/* 스킬 */
/*
 * 2차원 배열 돌리기
 * 중력 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;
#define MAX 30
#define DEBUG 0
#define EMPTY 7

int n, m;
unsigned long long score=0;
bool visited[MAX][MAX] = {false, };
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

typedef struct info{int x, y, rb, size;}info;

vector<vector<int> > board;//(MAX, vector<int>(MAX, 7));
vector<vector<pair<int, int>> > big_coords;
vector<pair<int, int> > gtemp;

info find_group(int x, int y, int value){
    queue<pair<int, int> > q;
    vector<pair<int, int> > zeros;
    info g;
    int mx = x, my = y;
    int rainbow=0;
    int num=1;

    gtemp.clear(); // renew

    q.push(make_pair(x, y));
    gtemp.push_back(make_pair(x, y)); // for delete 
    visited[x][y] = true;

    while(!q.empty()){
        int qx = q.front().first;
        int qy = q.front().second;

        q.pop();
        for(int i=0; i<4; i++){
            int nx = qx + dx[i];
            int ny = qy + dy[i];
            if((nx < 0) || (nx >= n) || (ny < 0) || (ny >= n))
                continue;
            if((board[nx][ny] == value || board[nx][ny] == 0) && (!visited[nx][ny])){
                visited[nx][ny] = true;
                q.push(make_pair(nx, ny));
                gtemp.push_back(make_pair(nx, ny)); // for delete
                num += 1;
                if(board[nx][ny] == 0){ // rainbow block
                    zeros.push_back(make_pair(nx, ny)); // 0 is shared element
                    rainbow += 1;
                }
                else{ // normal block, find standard
                    if(nx < mx){ 
                        mx = nx; my = ny; 
                    }
                    else if((nx == mx) && (ny < my)){ 
                        mx = nx; my = ny; 
                    }
                }
            }
        }
    }
    g.rb = rainbow; g.size = num;
    g.x = mx; g.y = my;
    for(auto p : zeros) // free zero coords
        visited[p.first][p.second] = false;
    return g;
}

unsigned long long find_big_and_delete(vector<info> g){
    info big = g[0];
    int idx = 0;
    for(int i=0; i<g.size(); i++){
        if(big.size < g[i].size){
            big = g[i]; idx = i;
            continue;
        }
        else if(big.size == g[i].size){
            if(big.rb < g[i].rb){
                big = g[i]; idx = i;
                continue;
            }
            else if(big.rb == g[i].rb){
                if(big.x < g[i].x){
                    big = g[i]; idx = i;
                    continue;
                }
                else if(big.x == g[i].x){
                    if(big.y < g[i].y)
                        big = g[i]; idx = i;
                    continue;
                }
            }
        }
    }
#if DEBUG
    printf("big : (%d, %d) size(%d)\n",big.x,big.y,big.size);
    printf("idx : %d\n", idx);
    printf("coords size(%lu)\n", big_coords[idx].size());
#endif
    // delete biggest group
    for(auto p : big_coords[idx]){
        board[p.first][p.second] = EMPTY;
    }

    return (big.size) * (big.size);
}

void gravity(){
    int row = n; 
    int col = n;

    for(int c=0; c<col; c++){
        int dest = n-1;
        for(int r=row-1; r>=0; r--){
            if(board[r][c] != EMPTY){
                if(board[r][c] == -1){
                    dest = r-1;
                    continue;
                }
                if(dest < 0) break;
                board[dest][c] = board[r][c];
                if(dest != r){
                    board[r][c] = EMPTY;
                }
                dest -= 1;
            }
        }
        // for(int r=row; r>=0; r--)
        //     board[r][c] = EMPTY;
    }
}

vector<vector<int> > rotate90_ccw(vector<vector<int> > arr){
    int r = arr.size();
    int c = arr[0].size();
    vector<vector<int> > res(c, vector<int>(r, 0));
    for(int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            res[c-1-j][i] = arr[i][j];
        }
    }
    return res;
}

#if DEBUG
void print_vector(vector<vector<int> > v,int r,int c);
void print_group(vector<info> group);
#endif

int main(void){
#if DEBUG
    freopen("input.txt","r",stdin);
#endif
    int blocks=1;
    scanf("%d %d", &n, &m);
    board.resize(n, vector<int>(n, EMPTY));

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf(" %d", &board[i][j]);
        }
    }

    while(1){
        vector<info> group;
        info ii;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if((!visited[i][j]) && (1 <= board[i][j]) && (board[i][j] <= m)){
                    ii = find_group(i, j, board[i][j]);
                    if(ii.size < 2)
                        continue;
                    group.push_back(ii);
                    big_coords.push_back(gtemp);
                }
                
            }
        }
        if(!group.size())
            break;
        #if DEBUG
            print_group(group);
        #endif
        score += find_big_and_delete(group);
        #if DEBUG
            print_vector(board, n, n);
        #endif
        gravity();
        #if DEBUG
            print_vector(board, n, n);
        #endif
        board = rotate90_ccw(board);
        #if DEBUG
            print_vector(board, n, n);
        #endif
        gravity();
        #if DEBUG
            print_vector(board, n, n);
        #endif
        memset(visited, false, sizeof(visited));
        big_coords.clear();
    #if DEBUG
        printf("current score : %llu\n",score);
        printf("------------------------------\n");
    #endif
    }
    printf("%llu\n", score);
    return 0;
}

#if DEBUG
void print_vector(vector<vector<int> > v,int r,int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++)
            printf("%2d ", v[i][j]);
        printf("\n");
    }
    printf("\n");
}
void print_group(vector<info> group){
    int idx=0;
    for(auto gi : group){
        printf("[%d] (%d, %d) size(%d) rb(%d)\n", idx, gi.x, gi.y, gi.size, gi.rb);
        idx += 1; 
    }
}
#endif