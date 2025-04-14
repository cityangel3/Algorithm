#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

int n, m;
vector<int> res;

void rperm(int d){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }

    for(int i=1; i<=n; i++){
        res[d] = i;
        rperm(d+1);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    res.reserve(m);
    rperm(0);
    return 0;
}