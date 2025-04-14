#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#define MAX 310

int N,M,R;
int arr[MAX][MAX] = {0, };
int dirx[4] = {1, 0, -1, 0};
int diry[4] = {0, 1, 0, -1};

void rotate(int start, int rots){
    for(int i=0; i<rots; i++){
        int x = start;
        int y = start;
        int orig = arr[start][start];

        int k = 0;
        while(k < 4){
            int nx = x + dirx[k];
            int ny = y + diry[k];
            if(nx == start && ny == start)
                break;
            else if((start <= ny && ny < N-start) && (start <= nx && nx < M-start)){
                arr[y][x] = arr[ny][nx];
                y = ny; x = nx;
            }
            else    
                k++;
        }
        arr[start+1][start] = orig;
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
    for(int r=0; r<ring; r++){ // ring 마다 R 번 회전
        int rot = R % ((N - 1 - 2*r + M - 1 -2*r) * 2); // modular
        rotate(r, rot);
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
