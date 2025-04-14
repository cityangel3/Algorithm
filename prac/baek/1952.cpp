#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int> > snail;

int main(void){
    int m, n;
    scanf("%d %d",&m, &n);
    snail.resize(m, vector<int>(n, 0));
    int top, bottom, right, left;
    int num = 0;
    int ans = 0;
    int bf;
    top = 0; bottom = m-1;
    left = 0; right = n-1;

    while((left <= right) && (top <= bottom)){
        bf = num;
        for(int i=left; i<=right; i++)
            snail[top][i] = num++;
        if(bf < num)
            ans += 1;
        top += 1;
        
        bf = num;
        for(int i=top; i<=bottom; i++)
            snail[i][right] = num++;
        if(bf < num)
            ans += 1;
        right -= 1;

        if(top <= bottom){
            bf = num;
            for(int i=right; i>=left; i--)
                snail[bottom][i] = num++;
            if(bf < num)
                ans += 1;
            bottom -= 1;
        }

        if(left <= right){
            bf = num;
            for(int i=bottom; i>=top; i--)
                snail[i][left] = num++;
            if(bf < num)
                ans += 1;
            left += 1;
        }
    }
    /*
    이미 top, right가 줄어든 상태에서 bottom, left에 접근하려는 것이기 때문에
    중복 접근이나 경계를 넘는 경우가 생길 수 있어요.

    예를 들어, 홀수 크기 배열에서는 마지막에 left == right && top == bottom인 중앙에 도달하게 되는데,
    이후에도 bottom이나 left를 기준으로 한 반복문이 돌면 같은 칸을 다시 방문하거나, 오버플로우될 수 있어요
    */

    // for(int i=0; i<m; i++){
    //     for(int j=0; j<n; j++){
    //         printf("%d ",snail[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d\n",ans-1);
    return 0;
}