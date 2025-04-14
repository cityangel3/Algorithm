#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

int n, m;
vector<int> res;

void rcomb(int d, int cur){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }

    for(int i=cur; i<=n; i++){
        res[d] = i;
        rcomb(d+1, i);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    res.reserve(m);
    rcomb(0, 1);
    return 0;
}