#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

#define MAXN 8
#define MAXM 8

int map[MAXN][MAXM] = {0, };
int map_tp[MAXN][MAXM] = {0, };
int dirx[4] = {0, 1, 0, -1};
int diry[4] = {1, 0, -1, 0};
int selected[3] = {0, };
int n, m, vsize, rsize;
int safe=0, safe_tp;

vector<pair<int, int> > virus;
vector<pair<int, int> > room;

void prints(){
    for(int i=0; i<3; i++)
        printf("%d ", selected[i]);
    printf("\n");
}

void print_map(){
    // printf("virus size : %d, room size : %d\n", vsize, rsize);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d ", map_tp[i][j]);
        }
        printf("\n");
    };
}

void dfs(int x, int y){       
    for(int j=0; j<4; j++){
        int nx = x + dirx[j];
        int ny = y + diry[j];
        if((nx < 0) || (nx >= n) || (ny < 0) || (ny >= m)) // oob
            continue;
        else if(map_tp[nx][ny]) // wall or virus
            continue;
        else{
            map_tp[nx][ny] = 2;
            safe_tp -= 1;
            if(safe_tp <= safe)
                return;
            dfs(nx, ny);
        }   
    }
}

void comb(int d, int cur){
    if(d == 3){
        memcpy(map_tp, map, sizeof(map));
        safe_tp = rsize - 3;
        for(int i=0; i<3; i++){ // set new wall
            int idx = selected[i];
            int x = room[idx].first;
            int y = room[idx].second;
            map_tp[x][y] = 1;
        }
        for(int i=0; i<vsize; i++){
            int vx = virus[i].first;
            int vy = virus[i].second;
            dfs(vx ,vy);
        }
        if(safe < safe_tp){
            safe = safe_tp;
            // printf("safe : %d\n", safe);    
            // print_map();
            // for(int i=0; i<3; i++){ // set new wall
            //     int idx = selected[i];
            //     int x = room[idx].first;
            //     int y = room[idx].second;
            //     printf("(%d, %d) ", x, y);
            // }
            // printf("\n");
        }
        return;
    }
    for(int i=cur; i<rsize; i++){
        selected[d] = i;
        comb(d+1, i+1);
    }
}

int main(void){
    freopen("input.txt","r",stdin);
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int val;
            scanf(" %d", &val);
            map[i][j] = val;
            if(val == 2) // virus coord
                virus.push_back(make_pair(i, j));
            else if(val == 0)  // room coord
                room.push_back(make_pair(i, j));
        }
    }
    vsize = virus.size();
    rsize = room.size();
    comb(0, 0);
    printf("%d\n", safe);
    return 0;   
}