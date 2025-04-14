#include <iostream>
#include <cstdio>
#include <string>
#include <queue>

using namespace std;
#define MAX 80
#define BIAS 3
#define RLOW 1
#define CLOW 1

int R, C, K;
int ans = 0;
int forest[MAX][MAX] = {0, };

int dirx[4] = {1, 0, -1, 0}; // E, S, W, N
int diry[4] = {0, 1, 0, -1};
int dirx_cw[4] = {1, -1, -1, 1}; // index 0 ~ 3 : N, E, S, W
int diry_cw[4] = {1, 1, -1, -1};
int dirx_ccw[4] = {-1, -1, 1, 1};
int diry_ccw[4] = {1, -1, -1, 1};

int check_south(int col, int row){
    if(forest[row+2][col] == 1) // start point
        return 0;
    else if(forest[row+1][col-1] == 1 || forest[row+1][col+1] == 1) // moved more than 1 row
        return 0;

    return 1;
}
int check_west(int col, int row){
    if(col-2 < CLOW)
            return 0;
    if(forest[row+2][col-1] == 1) // start point
            return 0;
    else if((row >= RLOW+2) && (forest[row+1][col-1] == 1 || forest[row+1][col-2] == 1)) // moved 1 row
        return 0;
    else if((row >= RLOW+BIAS) && (forest[row][col-2] == 1)) // moved 2 rows
        return 0;
    else((row >= RLOW+BIAS+1) && (forest[row-1][col-1] == 1)) // moved more than 3 rows
        return 0;

    return 1;
}
int check_east(int col, int row){
    if(C < col+2)
        return 0;
    if(forest[row+2][col+1] == 1) // start point
            return 0;
    else if((row >= RLOW+2) && (forest[row+1][col+1] == 1 || forest[row+1][col+2] == 1)) // moved 1 row
        return 0;
    else if((row >= RLOW+BIAS) && (forest[row][col+2] == 1)) // moved 2 rows
        return 0;
    else((row >= RLOW+BIAS+1) && (forest[row+1][col+1] == 1)) // moved more than 3 rows
        return 0;

    return 1;
}

int enter(int row, int col, int exit_dir){
    while(row <= RLOW+1+BIAS){
        if(check_south(col, row)){

        }
        else if(check_west(col, row)){

        }
        else if(check_east(col, row)){

        }
    }
}

void move(int row, int col, int exit_dir){
    if(!enter(row, col, exit_dir)){
        for(int i=RLOW+BIAS; i<=R+BIAS; i++){
            for(int j=CLOW; j<=C; j++){
                forest[i][j] = 0;
            }
        }
    }

}
int main() {
    freopen("input.txt","r",stdin);

    scanf("%d %d %d", &R, &C, &K);
    for(int i=0; i<K; i++){
        int col, d;
        scanf(" %d %d", &col, &d);
        move(RLOW, col, d);
    }

    return 0;
}