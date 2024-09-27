#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

#define MAXN 310
#define MAXM 310

int nrow, ncol, rot;
int arr[MAXN][MAXM]={0,};
// right, down, left, up -> clockwise
int dx[4] = {0,1,0,-1}; 
int dy[4] = {1,0,-1,0};

void traversal(int ring){
    for(int r=0; r<ring; r++){
        int x = r, y = r; // start from orig of each ring.
        int orig = arr[r][r]; // for last move.

        int k = 0;
        while(k < 4){
            int curx = x + dx[k];
            int cury = y + dy[k];
            if( curx == x && cury == y)
                break; // returned to orig.
            else if( (r <= curx && curx < nrow-r) && (r <= cury && cury < ncol-r)){
                arr[x][y] = arr[curx][cury];
                x = curx; y = cury;
            }
            else
                k++;
        }
        arr[r+1][r] = orig;
    }
}
int main(void){
    freopen("input.txt","r",stdin);
    /* 시계 반대 방향으로 돌려야 하니, 한칸씩 당길때는 그 반대 방향으로 순회해야 하는 구나 */
    int nring=0;
    scanf("%d %d %d",&nrow, &ncol, &rot);
    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncol; j++){
            scanf(" %d",&arr[i][j]);
        }
    }

    nring = min(nrow, ncol) / 2; // # of rings is the key.
    for(int i=0; i<rot; i++)
        traversal(nring);

    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncol; j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}