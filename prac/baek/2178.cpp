#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<queue>

using namespace std;

#define MAX 110

int map[MAX][MAX] = {0, };
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int n, m;
bool visited[MAX][MAX] = {false, };

typedef struct info{int x,y,d;}Info;

int bfs(int x, int y){
    queue<Info> q;
    q.push({x, y, 1});
    visited[x][y] = true;

    while(!q.empty()){
        Info qi = q.front();
        int qx = qi.x;
        int qy = qi.y;
        int qd = qi.d;
        if((qx == n-1) && (qy == m-1))
            return qd;

        q.pop();

        for(int i=0; i<4; i++){
            int nx = qx + dx[i];
            int ny = qy + dy[i];
            if((!visited[nx][ny]) && (map[nx][ny])){
                q.push({nx, ny, qd+1});
                visited[nx][ny] = true;
            }
        }
    }
    return -1;
}

int main(void){
    freopen("input.txt","r",stdin);
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf(" %1d", &map[i][j]);
        }
    }
    printf("%d\n", bfs(0, 0));
    return 0;
}