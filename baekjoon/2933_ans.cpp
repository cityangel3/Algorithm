#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
int r,c,n;
const int max_rcn = 101;
 
char map[max_rcn][max_rcn];
bool visited[max_rcn][max_rcn];
bool flag;
 
int order[max_rcn];
vector<pair<int,int>> cluster;
 
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
 
void print_map(){
    for(int i=r;i>=1;i--){
        for(int j=1;j<=c;j++){
            cout << map[i][j];
        }
        cout << '\n';
    }
 
    return;
}
 
void Input(){
    cin >> r >> c;
    for(int i=r;i>=1;i--){
        for(int j=1;j<=c;j++){
            cin >> map[i][j];
        }
    }
 
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> order[i];
    }
 
    return;
}
 
 
void DFS(int x, int y){
    if(x == 1) {
        flag = true;
        return;
    }
 
    for(int i=0;i<4;i++){
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if(nx<1 || nx>r || ny<1 || ny>c || visited[nx][ny]) continue;
        if(map[nx][ny]=='.') continue;
        visited[nx][ny] = true;
        cluster.push_back({nx,ny});
        DFS(nx,ny);
    }
}
 
void find_cluster(int x, int y){
    if(x<1 || y<1 || x>r || y>c) return;
    if(map[x][y]=='.') return;
 
    //초기화 (모든 좌표 기록을 벡터)
    cluster.clear();
    flag = false;
    memset(visited, false, sizeof(visited));
 
    cluster.push_back({x,y});
    visited[x][y]= true;
    DFS(x,y);
 
    //바닥과 붙어있는 클러스터라면 이동하지 않는다.
    if(flag) return;
 
    //이동이 필요한 경우
    int size = cluster.size();
    //이동 전 위치 '.' 으로 변경
    for(int i=0;i<size;i++){
        int x = cluster[i].first;
        int y = cluster[i].second;
        map[x][y] = '.';
    }
    
    int md = 0; //move_distance
    bool next_md=true;
    while(next_md){
        for(int i=0;i<size;i++){
            int x = cluster[i].first;
            int y = cluster[i].second;
            int next_h = x-md-1;
            if(next_h <=0 || map[next_h][y]=='x') {
                next_md = false;
            }
        }
 
        if(next_md) md ++;
    }
    
    for(int i=0;i<size;i++){
        int x = cluster[i].first;
        int y = cluster[i].second;
        map[x-md][y] = 'x';
    }
    return;
}
 
 
void shoot(int r, int left_right){
    int point;
    if(left_right % 2 == 1){
        for(int i=1;i<=c;i++){
            if(map[r][i]=='x'){
                point = i;
                map[r][i] = '.';
                break;
            }
        }
        //왼쪽에서 날아와서 부딪혔다 -> 오른쪽, 위, 아래 확인
        find_cluster(r,point+1);
        find_cluster(r+1,point);
        find_cluster(r-1,point);
    }
    else{
        for(int i=c;i>=1;i--){
            if(map[r][i]=='x'){
                point = i;
                map[r][i] = '.';
                break;
            }
        }
        //오른쪽에서 날아와서 부딪혔다 -> 왼쪽, 위, 아래 확인
        find_cluster(r,point-1);
        find_cluster(r+1,point);
        find_cluster(r-1,point);
    }
    return;
}
 
void solve(){
    for(int i=1;i<=n;i++){
        shoot(order[i],i);
    }
    print_map();
}
 
 
int main(){
    Input();
    solve();
    return 0;
}