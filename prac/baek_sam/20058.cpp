/* 교훈 */
/* 
 * 상대 좌표 다를 때, 예를 들어 순회할 때 시작점이 서로 다른 배열과 같은 경우 
    (i-istart) 같은거 괄호를 해주고 빼주는거 주의하자! => 괄호 안하면 더 큰 수를 빼는 것임.(oob) 
 * bfs 로 그룹 요소 갯수 셀 때, 시작은 1부터이다.
 * dx, dy 등으로 주변 좌표 둘러볼 때 경계 검사 무조건!!
 * 문제 조건 무조건 계속 확인하면서 구현하자. (이미 0 인 칸에는 적용안되는 등)
 * 10^6 규모 부터는 시간 복잡도 신경써야한다.
 * in-place 업데이트와 copy는 규모에 따라 다르지만, 여기선 17배나 차이난다
    => 생각보다 엄청난 차이 (copy의 무서움)
*/
/* 스킬 */
/*
 * 부분 회전
 * in-place 90도 회전 방식
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;
#define DEBUG 0
#define MAX 70

vector<vector<int> > board;
vector<int> magics;
int n, q;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int big = 0;
int sum = 0;
bool visited[MAX][MAX] = {false, };

#if DEBUG
void print_vector(vector<vector<int> > arr);
#endif

vector<vector<int> > rotate90_cw(vector<vector<int> > arr, int rs, int cs, int size){
    vector<vector<int> > res(size, vector<int>(size, 0));

    for(int i=rs; i<rs+size; i++){
        for(int j=cs; j<cs+size; j++){
            res[(j-cs)][size-1-(i-rs)] = arr[i][j];
        }
    }
    return res;
}

void rotate90_cw_inplace(vector<vector<int> > &arr, int rs, int cs, int size){
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            swap(arr[rs + i][cs + j], arr[rs + j][cs + i]);
        }
    }

    for(int i=0; i<size; i++)
        reverse(arr[rs+i].begin() + cs, arr[rs+i].begin() + cs + size);
}

// vector<vector<int> > 
void melting(vector<vector<int> > &arr){
    int r = arr.size();
    int c = arr[0].size();
    // vector<vector<int> > res(r, vector<int>(c, 0)); // copy
    // copy -> time over

    vector<pair<int, int> > v;

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            int zero=0;
            if(arr[i][j] == 0)
                continue;

            for(int d=0; d<4; d++){
                int nx = i + dx[d];
                int ny = j + dy[d];
                if((nx < 0) || (nx >= n) || (ny < 0) || (ny >= n)){
                    zero += 1;
                    continue;
                }
                if(arr[nx][ny] == 0)
                    zero += 1;
            }
            
            if(zero > 1)
                v.push_back({i, j});
                // res[i][j] = arr[i][j] - 1;
        }
    }

    for(auto p : v)
        arr[p.first][p.second] -= 1;
    // return res;
}

void renew_board(vector<vector<int> > arr, int rs, int cs, int size){
    for(int i=rs; i<rs+size; i++){
        for(int j=cs; j<cs+size; j++){
            board[i][j] = arr[i-rs][j-cs];
        }
    }
}

void bfs(int x, int y){
    queue<pair<int ,int> > q;
    int gsize=1;

    visited[x][y] = true;
    q.push(make_pair(x, y));
    sum += board[x][y];

    while(!q.empty()){
        int qx = q.front().first;
        int qy = q.front().second;

        q.pop();

        for(int i=0; i<4; i++){
            int nx = qx + dx[i];
            int ny = qy + dy[i];
            if((nx < 0) || ( nx >= n) || (ny < 0) || (ny >= n))
                continue;
            else if((!visited[nx][ny]) && (board[nx][ny])){
                q.push(make_pair(nx, ny));
                visited[nx][ny] = true;
                gsize += 1;
                sum += board[nx][ny];
            }
        }
    }
    big = max(big, gsize);
}

int main(void){
#if DEBUG
    freopen("input.txt","r",stdin);
#endif
    int size=1;
    scanf("%d %d", &n, &q);
    for(int i=0; i<n; i++)
        size *= 2;
    n = size;
    board.resize(n, vector<int>(n, 0));
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf(" %d", &board[i][j]);
        }
    }

    for(int i=0; i<q; i++){
        int l;
        scanf(" %d", &l);
        magics.push_back(l);
    }

    #if DEBUG
        printf("[origin]\n");
        print_vector(board);
        printf("------------------------\n");
    #endif

    vector<vector<int> > sb;
    for(int l : magics){ // firestorms
        int sl=1;
        for(int i=0; i<l; i++)
            sl *= 2;
        if(sl == 1){
            melting(board);
            continue;
        }
        sb.resize(sl, vector<int>(sl, 0));

        #if DEBUG
            printf("(n: %d, sl: %d)\n",n,sl);
        #endif

        for(int i=0; i<n; i+=sl){ // rotate board
            for(int j=0; j<n; j+=sl){
                /* copy */ 
                // sb = rotate90_cw(board, i, j, sl);
                // renew_board(sb, i, j, sl);

                /* in-place */
                rotate90_cw_inplace(board, i, j, sl); 
            }
        }
        #if DEBUG
            printf("[after rotate]\n");
            print_vector(board);
            printf("-----------------\n");
        #endif
        // board = 
        melting(board);

        #if DEBUG
            printf("[after melting]\n");
            print_vector(board);
        #endif
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if((!visited[i][j]) && (board[i][j]))
                bfs(i, j);
        }
    }
    printf("%d\n%d\n", sum, big);
    return 0;
}

#if DEBUG
void print_vector(vector<vector<int> > arr){
    for(int i=0; i<arr.size(); i++){
        for(int j=0; j<arr[0].size(); j++)
            printf("%2d ", arr[i][j]);
        printf("\n");
    }
}
#endif