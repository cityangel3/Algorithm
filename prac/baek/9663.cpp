#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>

using namespace std;

int n, cnt = 0;
int chess[15] = {0,};

int line_check(int row, int col){
    for(int i=0; i<row; i++){
        int bc = chess[i];
        int rdist = abs(row-i);
        int cdist = abs(col-bc);
        if(col == bc) // straight 
            return 1;
        if(rdist == cdist) // diagonal
            return 1;
    }
    return 0; 

}

void ans(int row){
    if(row == n){
        cnt++;
        return;
    }
    for(int c=0; c<n; c++){
        if(line_check(row, c))
            continue;
        
        chess[row] = c;
        ans(row+1);
    }
}

int main(void){
    scanf("%d", &n);
    ans(0);
    printf("%d\n", cnt);
    return 0;
}