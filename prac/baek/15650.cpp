#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

int n, m;
vector<int> res;

void comb(int d, int cur){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }

    for(int i=cur; i<=n; i++){
        res[d] = i;
        comb(d+1, i+1);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    res.reserve(m+1);
    comb(0, 1);
    return 0;
}
