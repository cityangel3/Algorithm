#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

#define MAX 30 //크기 넉넉히 가져가자. 딱 맞추지 말고

int n;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int map[MAX][MAX] = {0, };
bool visited[MAX][MAX] = {false, };
vector<int> houses;

void bfs(int x, int y){
    int count = 1;
    queue<pair<int, int> > q;

    q.push(make_pair(x, y));
    visited[x][y] = true;

    while(!q.empty()){
        int qx = q.front().first;
        int qy = q.front().second;

        q.pop();

        for(int i=0; i<4; i++){
            int nx = qx + dx[i];
            int ny = qy + dy[i];
            if((!visited[nx][ny]) && (map[nx][ny] == 1)){
                q.push(make_pair(nx, ny));
                count += 1;
                visited[nx][ny] = true;
            }
        }
    }
    houses.push_back(count);
}

int main(void){
    freopen("input.txt","r",stdin);
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf(" %1d", &map[i][j]);
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if((!visited[i][j]) && (map[i][j] == 1))
                bfs(i, j);
        }
    }
    sort(houses.begin(), houses.end());
    printf("%lu\n", houses.size());
    for(int num : houses)
        printf("%d\n", num);
    return 0;
}