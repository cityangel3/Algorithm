#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<queue>
#include<set>

using namespace std;
#define MAX 1010

int n, m;
int tmap[MAX][MAX] = {0, };
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0 ,-1, 0};
bool visited[MAX][MAX] = {false, };

queue<pair<int, int> > ripen;
set<pair<int, int> > unripe;
int unriped=0;

int sol(){
    int days = 1;
    
    while(!ripen.empty()){
        pair<int, int> p = ripen.front();
        int qx = p.first;
        int qy = p.second;

        ripen.pop();

        for(int i=0; i<4; i++){
            int nx = qx + dx[i];
            int ny = qy + dy[i];
            if((nx < 0) || (nx >= n) || (ny < 0) || (ny >= m))
                continue;
            else if(tmap[nx][ny] == 0){
                tmap[nx][ny] = tmap[qx][qy] + 1;
                days = max(days, tmap[nx][ny]);
                // unripe.erase(unripe.find({nx, ny})); 
                // O(log n) 추가 되고 안되고 7배 차이 ... 616ms (n max 10^6)
                unriped -= 1;
                ripen.push({nx, ny});
            }
        }
    }
    // if(unripe.size())
    if(unriped)
        return 0;
    else 
        return days;
}

int main(void){
    freopen("input.txt","r",stdin);
    scanf("%d %d", &m, &n);

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int status;
            scanf(" %d", &status);
            if(status == 0){
                // unripe.insert({i, j});
                unriped += 1;
            }
            else if(status == 1){
                ripen.push({i, j});
                // visited[i][j] = true;
            }
            tmap[i][j] = status;
        }
    }
    printf("%d\n", sol()-1);
    return 0;
}