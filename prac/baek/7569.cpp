#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;
#define MAX 110

int m, n, h;
int unripen = 0;
int tmap[MAX][MAX][MAX] = {0, };
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int dz[2] = {1,-1};

typedef struct info{
    int x, y, z;
}info;

queue<info> ripen;

int sol(){
    int days = 1;

    while(!ripen.empty()){
        info coord = ripen.front();
        int x = coord.x;
        int y = coord.y;
        int z = coord.z;

        ripen.pop();

        for(int i=0; i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if((nx < 0) || (nx >= n) || (ny < 0) || (ny >= m))
                continue;
            else if(tmap[z][nx][ny] == 0){
                unripen -= 1;
                ripen.push({nx, ny, z});
                tmap[z][nx][ny] = tmap[z][x][y] + 1;
                days = max(days, tmap[z][nx][ny]);
            }
        }
        for(int i=0; i<2; i++){
            int nz = z + dz[i];
            if((nz < 0) || (nz >= h))
                continue;
            else if(tmap[nz][x][y] == 0){
                unripen -= 1;
                ripen.push({x, y, nz});
                tmap[nz][x][y] = tmap[z][x][y] + 1;
                days = max(days, tmap[nz][x][y]);
            }
        }

        // for(int z=0; z<h; z++){
        //     for(int i=0; i<n; i++){
        //         for(int j=0; j<m; j++){
        //             printf("%d ", tmap[z][i][j]);
        //         }
        //         printf("\n");
        //     }
        // }
        // printf("----------------------\n");
    }
    if(unripen)
        return 0;
    else 
        return days;
}

int main(void){
    freopen("input.txt","r",stdin);
    scanf("%d %d %d", &m, &n, &h);
    for(int z=0; z<h; z++){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int status;
                scanf(" %d", &status);
                if(status == 0)
                    unripen += 1;
                else if(status == 1)
                    ripen.push({i, j, z});
                tmap[z][i][j] = status;
            }
        }
    }

    printf("%d\n", sol() - 1);
    
    return 0;
}