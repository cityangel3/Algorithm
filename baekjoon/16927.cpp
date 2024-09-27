#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

#define MAX 330
int ncol,nrow,rot;
int arr[MAX][MAX] = {0,};
int dirx[4] = {0, 1, 0, -1};
int diry[4] = {1, 0, -1, 0};

void traversal(int start, int rotate){
    for(int r=0; r<rotate; r++){
        int x = start, y = start;
        int orig = arr[start][start];

        int k = 0;
        while(k < 4){
            int curx = x + dirx[k];
            int cury = y + diry[k];

            if(curx == start && cury == start)
                break;
            else if((start <= curx && curx < nrow-start) && (start <= cury && cury < ncol-start)){
                arr[x][y] = arr[curx][cury];
                x = curx ; y = cury;
            }
            else
                k++;
        }
        arr[start+1][start] = orig;
    }
}
int main(void){
    freopen("input.txt","r",stdin);

    scanf("%d %d %d",&nrow, &ncol, &rot);
    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncol; j++){
            scanf(" %d",&arr[i][j]);
        }
    }
        
    int nring = min(nrow,ncol) / 2;
    // ring 마다 원래 위치로 오는 주기가 다름
    // int realrot = rot % ((nrow - 1 + ncol - 1) * 2); // only for outer ring
    int realrot;

    for(int i=0; i<nring; i++){ // ring 마다 돌리는 코드로 변경함.
        realrot = rot % ((nrow - 2*i - 1 + ncol - 2*i - 1) * 2);
        traversal(i,realrot); 
    }

    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncol; j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}