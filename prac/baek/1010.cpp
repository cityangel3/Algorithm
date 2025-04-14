#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>

using namespace std;

#define MAX 30

int dp[MAX][MAX] = {0,};
int t;

// combination with dynamic programming

int comb(int n, int r){
    if(dp[n][r] > 0)
        return dp[n][r];
    
    if(r == 0 || r == n){
        dp[n][r] = 1;
        return dp[n][r];
    }

    return dp[n][r] = comb(n-1, r-1) + comb(n-1, r);
}

int main(void){
    vector<int> res;
    scanf("%d", &t);
    res.resize(t);
    for(int i=0; i<t; i++){
        int n, m;
        scanf(" %d %d", &n, &m);
        // res.push_back(comb(m, n)); // ?? why size is 6?
        // 앞이 이미 0으로 3개 초기화 됨.
        res[i] = comb(m, n);
    }
    // printf("res size : %d\n", res.size());
    for(int i=0; i<res.size(); i++)
        printf("%d\n", res[i]);

    return 0;
}