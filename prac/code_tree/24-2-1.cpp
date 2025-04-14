//미지의 공간 탈출, 2024 하반기 오전 1번
// 59' + 55'
// 7:26 - 9:55 = 2:29// 물론 딴짓하며 풀긴했지만...
/* 교훈 */
/*
 * bfs에서 종료 조건을 map 값으로 하는 경우가 있으니, 그냥 visit쓰는쪽으로 생각하고 웬만하면 map 값 바꾸지 말자.
 * 문제에서 말하는 조건 경우(e.g.탈출 불가한 경우 -1)를 자세히 읽고 요건에 맞게 출력 주의하자.
 * 배열에 인덱스 접근할 때, 그리고 인덱스가 변하는 상황에선 "경계 검사" 꼭!! 유의하자.
*/
/* 스킬 */
/*
 * 2차원 배열 돌리기
 * 3차원 배열을 3*M 크기의 정사각 2차원 배열로 확장시켜 bfs : 인접 좌표 이동시 적절히 점프 시켜줘야 하는 경우 고려해야 했음
 * 1초마다 일정 방향으로 크기가 증가하는 함정 : map에 기록하면 되돌아갈 수 없으므로(이전 시간 검사 시), 
    최대 확장하는 좌표들을 기록해 두고 bfs 하면서 시간에 따른 함정 좌표를 확인해, 예외처리를 해줬음.
 * 3차원 배열과 2차원 배열 공간의 인접점 구하기 : 좌표 특성 및 방향(동,서,남,북)에 따라서 어떤식으로 구할 수 있는지 고민.
 * 디버깅시에 bfs 경로 구하기 : (nx,ny) 에 대해서 vector<vector<pair<int, int>>> 를 선언해 parent를 기록.
    이후, 도착점부터 역으로 시작점까지 while 돌면서 경로를 찾음.
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

#define MAXN 30
#define MAXM 20
#define DEBUG 0

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int dirx[4] = {0, 0, 1, -1};
int diry[4] = {1, -1, 0, 0};
bool outvisit[MAXN][MAXN] = {false, };
bool innervisit[MAXM*3][MAXM*3] = {false, };
int n, m, f;

typedef struct info{int x,y,d,v;}info;
typedef struct coord{int x,y,t;}coord;
vector<info> strange;
vector<vector<coord> > stranges;
vector<vector<int> > outmap(MAXN, vector<int>(MAXN, 0));
vector<vector<int> > innermap(MAXM*3, vector<int>(MAXM*3, 7));
pair<int, int> inner_start, outer_start, outer_dest, inner_dest;
#if DEBUG == 1
    vector<vector<pair<int, int> > > debug_parent(MAXM*3, vector<pair<int, int> >(MAXM*3, {-1,-1})); 
#endif
vector<vector<int> > rotate90_cw(vector<vector<int> > &arr){
    int r = arr.size();
    int c = arr[0].size();
    vector<vector<int> > res(c, vector<int>(r, 0));
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            res[j][r-1-i] = arr[i][j];
        }
    }
    return res;
}

vector<vector<int> > rotate90_ccw(vector<vector<int> > &arr){
    int r = arr.size();
    int c = arr[0].size();
    vector<vector<int> > res(c, vector<int>(r, 0));
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            res[c-1-j][i] = arr[i][j];
        }
    }
    return res;
}

vector<vector<int> > rotate180(vector<vector<int> > &arr){
    int r = arr.size();
    int c = arr[0].size();
    vector<vector<int> > res(r, vector<int>(c, 0));
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            res[r-1-i][c-1-j] = arr[i][j];
        }
    }
    return res;
}

void make_innermap(vector<vector<int> > arr, int dir){
    int xs,ys;
    if(dir == 0){ // e
        xs = m; ys = 2*m;
    }
    else if(dir == 1){  // w
        xs = m; ys = 0;
    }
    else if(dir == 2){ // s
        xs = 2*m; ys = m;
    }
    else if (dir == 3){ // n
        xs = 0; ys = m;
    }
    else{ // a
        xs = m; ys = m;
    }
    for(int x=xs; x<xs+m; x++){
        for(int y=ys; y<ys+m; y++){
            innermap[x][y] = arr[x-xs][y-ys];
        }
    }
}

pair<int, int> find_inner_dest(int x, int y){
    queue<pair<int, int> > q;
    pair<int, int> p = {-1, -1};
    bool flag = false;
    outvisit[x][y] = true;
    q.push(make_pair(x,y));

    while(!q.empty()){
        int qx = q.front().first;
        int qy = q.front().second;

        q.pop();

        for(int i=0; i<4; i++){
            int nx = qx+dx[i];
            int ny = qy+dy[i];
            if((nx < 0) || (nx >= n) || (ny < 0) || (ny >= n))
                continue;
            else if(outmap[nx][ny] == 0){
                p.first = nx; p.second = ny;
                flag = true;
            }
            else if((outmap[nx][ny] == 3) && (!outvisit[nx][ny]))
            {
                outvisit[nx][ny] = true;
                q.push(make_pair(nx, ny));
            }
        }
        if(flag)
            break;
    }
    // calculate inner_dest
    if(p.first < x){ // n 
        inner_dest.first = 0;
        inner_dest.second = m + abs(y - p.second); // using col
    }
    else if(p.first >= x+m){ // s
        inner_dest.first = 3*m-1;
        inner_dest.second = m + abs(y - p.second); // using col
    } 
    else if(p.second < y){ // w
        inner_dest.second = 0;
        inner_dest.first = m + abs(p.first - x); // using row
    }
    else if(p.second >= y+m){ // e
        inner_dest.second = 3*m-1;
        inner_dest.first = m + abs(p.first - x); // using row
    }
    memset(outvisit, false, sizeof(outvisit)); // init
    return p; // return outer_start
}

int inner_bfs(){
    // innermap
    queue<coord> q;
    q.push({inner_start.first, inner_start.second, 0});
    innervisit[inner_start.first][inner_start.second] = true;

    while(!q.empty()){
        int qx = q.front().x;
        int qy = q.front().y;
        int qt = q.front().t;
        if((qx == inner_dest.first) && (qy == inner_dest.second))
            return qt;
        q.pop();
        for(int i=0; i<4; i++){
            int nx = qx+dx[i];
            int ny = qy+dy[i];
            if((nx < 0) || (nx >= 3*m) || (ny < 0) || (ny >= 3*m))
                continue;
            
            if(innermap[nx][ny] == 7){
                if((nx < m && ny < m) || (nx >= 2*m && ny >= 2*m)){ // case 1, 4
                    nx = qy; ny = qx;
                }
                else if((nx < m) && (ny >= 2*m)){ // case 2
                    if(i == 0){
                        nx = qy - (m - 1);
                        ny = (3*m - 1) - qx;
                    }
                    else if(i == 3){
                        ny = qx + (m - 1);
                        nx = (3*m - 1) - qy;
                    }
                    else printf("inner dir error! (%d, %d)\n",qx,qy);
                }
                else if((nx >= 2*m) && (ny < m)){ // case 3
                    if(i == 1){
                        ny = qx - (m - 1);
                        nx = (3*m - 1) - qy;
                    }
                    else if(i == 2){
                        nx = qy + (m - 1);
                        ny = (3*m - 1) - qx;
                    }
                    else printf("inner dir error! (%d, %d)\n",qx,qy);
                }
                else printf("inner dir error!\n");

                // printf("(%d, %d) -> modified nx, ny = (%d, %d)\n", x, y, nx, ny);
            }
            
            if((!innervisit[nx][ny]) && (innermap[nx][ny] == 0)){
                innervisit[nx][ny] = true;
                q.push({nx, ny, qt+1});
                #if DEBUG == 1
                    debug_parent[nx][ny] = {qx, qy};
                #endif
            }
        }
    }
    return 0;
}

int out_bfs(int v){
    // outmap
    queue<coord> q;
    int time = v;

    outvisit[outer_start.first][outer_start.second] = true;
    q.push({outer_start.first, outer_start.second, v});

    while(!q.empty()){
        int qx = q.front().x;
        int qy = q.front().y;
        int qt = q.front().t;

        q.pop();

        for(int i=0; i<4; i++){
            int nx = qx + dx[i];
            int ny = qy + dy[i];
            bool sflag = false;
            if((nx < 0) || (nx >= n) || (ny < 0) || (ny >= n))
                continue;
            if(outmap[nx][ny] == 4)
                return (qt + 1);
            for(auto ss : stranges){
                for(auto s : ss){
                    if((qt+1) < s.t)
                        break;
                    else if((nx == s.x) && (ny == s.y)){
                        sflag = true; break;
                    }
                }
                if(sflag) break;
            }
            if(sflag) continue;
        
            if((!outvisit[nx][ny]) && (outmap[nx][ny] == 0)){
                outvisit[nx][ny] = true;
                q.push({nx, ny, qt+1});
                #if DEBUG == 1
                    outmap[nx][ny] = (-1)*(qt+1);
                #endif
            }
        }
    }

    return 0;
}

#if DEBUG == 1
void print_vector(vector<vector<int> > arr, int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++)
            printf("%3d ",arr[i][j]);
        printf("\n");
    }
    printf("\n");
}

void print_debug(pair<int, int> start, pair<int, int> dest){
    int cx = dest.first;
    int cy = dest.second;
    while((cx != start.first) || (cy != start.second)){
        printf("(%d, %d)->", cx, cy);
        auto p = debug_parent[cx][cy];
        cx = p.first;
        cy = p.second;
    }
    printf("(%d, %d)\n",cx, cy);
}
#endif

int main(void){
    vector<vector<int> > arr;
    pair<int, int> thr_start;
    bool inner_flag=false;
#if DEBUG == 1
    freopen("input.txt","r",stdin);
#endif
    scanf("%d %d %d", &n, &m, &f);

    arr.resize(m, vector<int>(m, 0));

    for(int i=0; i<n; i++){ // get outer map
        for(int j=0; j<n; j++){
            scanf(" %d", &outmap[i][j]);
            if((outmap[i][j] == 3) && (!inner_flag)){ // to find inner_dest
                thr_start.first = i; thr_start.second = j;
                inner_flag = true;
            }
            else if(outmap[i][j] == 4){ // outer_dest
                outer_dest.first = i; outer_dest.second = j;
            }
        }
    }

    for(int i=0; i<5; i++){ // get inner map info
        for(int x=0; x<m; x++){
            for(int y=0; y<m; y++){
                scanf(" %d", &arr[x][y]);
                if((i == 4) && (arr[x][y] == 2)){ // inner_start
                    inner_start.first = x+m; inner_start.second = y+m;
                }
            }
        }
        if(i == 0) // e, ccw 90'
            arr = rotate90_ccw(arr);
        else if(i ==1) // w, cw 90'
            arr = rotate90_cw(arr);
        else if (i == 3) // n, 180'
            arr = rotate180(arr);
        // s & above, 0'
        make_innermap(arr, i); // make inner_map
    }

    for(int i=0; i<f; i++){ // get strange info
        int x, y, d, v;
        scanf("%d %d %d %d", &x, &y, &d, &v);
        strange.push_back({x, y, d, v});
    }

     // find inner_dest 
    outer_start = find_inner_dest(thr_start.first, thr_start.second);
    if(outer_start.first == -1){
        printf("-1\n"); return 0;
    }
#if DEBUG == 1
    printf("-------------------------\n");
    printf("inner_start(%d, %d)\n",inner_start.first,inner_start.second);
    printf("inner_dest(%d, %d)\n",inner_dest.first,inner_dest.second);
    print_vector(innermap, 3*m, 3*m);
    printf("-------------------------\n");
    printf("outer_start(%d, %d)\n", outer_start.first,outer_start.second);
    printf("outer_dest(%d, %d)\n", outer_dest.first,outer_dest.second);
    print_vector(outmap, n, n);
#endif

    for(info ii : strange){
        int x, y, t;
        vector<coord> ss;
        x = ii.x; y = ii.y; t = 0;
        ss.push_back({x, y, t});
        while(outmap[x][y] == 0){
            x += dirx[ii.d];
            y += diry[ii.d];
            t += ii.v;
            if((x < 0) || (x >= n) || (y < 0) || (y >= n))
                break;
            if(outmap[x][y] != 0) 
                break;
            ss.push_back({x, y, t});
        }
        stranges.push_back(ss);
    }
#if DEBUG == 1    
    printf("-------------------------\n");
    for(auto ss : stranges){
        for(auto s : ss)
            printf("(%d, %d(%d)) ",s.x,s.y,s.t);
        printf("\n");
    }
#endif
    // get time from inner_start to inner_dest
    int inner_time=0, out_time=0;
    inner_time = inner_bfs();
    if(inner_time == 0){
        printf("-1\n"); return 0;
    }
#if DEBUG == 1
    printf("-------------------------\n");
    print_debug(inner_start, inner_dest);
#endif
    out_time = out_bfs(inner_time+1);
#if DEBUG == 1
    printf("-------------------------\n");
    printf("inner_time : %d\n",inner_time);
    print_vector(outmap, n, n);
#endif
    
    if(out_time == 0){
        printf("-1\n"); return 0;
    }
    printf("%d\n",out_time);
    
    return 0;   
}

