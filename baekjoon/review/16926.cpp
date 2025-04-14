#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#define MAX 310

int N,M,R;
int arr[MAX][MAX] = {0, };
int dirx[4] = {1, 0, -1, 0};
int diry[4] = {0, 1, 0, -1};

void rotate(int rings){
    for(int r=0; r<rings; r++){
        int x = r;
        int y = r;
        int orig = arr[r][r];
        int k=0;
        while(k < 4){
            int nx = x + dirx[k]; // 커서가 이동해야 하니까 
            int ny = y + diry[k];
            if(nx == r && ny == r)
                break;
            else if((r <= ny && ny < N-r) && (r <= nx && nx < M-r)){ // 같은 축에서 이동이 있으니까 최소 경계는 같거나 큰걸로
                arr[y][x] = arr[ny][nx];
                y = ny; x = nx; // 계속 업데이트 돼야함
            }
            else
                k++;
        }
        arr[r+1][r] = orig;
    }
}
int main(void){
    freopen("input.txt","r",stdin);

    scanf("%d %d %d",&N, &M, &R);
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            scanf(" %d",&arr[i][j]);
        }
    }

    int ring = min(N, M) / 2;
    for(int i=0; i<R; i++){
        rotate(ring);
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}