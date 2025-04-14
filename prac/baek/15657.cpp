#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

int n, m;
int arr[8] = {0, };
vector<int> res;

void rcomb(int d, int cur){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }

    for(int i=cur; i<n; i++){
        res[d] = arr[i];
        rcomb(d+1, i);
    }
}

int main(void){
    scanf("%d %d", &n, &m);
    res.reserve(m);
    for(int i=0; i<n; i++)
        scanf(" %d", arr + i);
    sort(arr, arr+n);
    rcomb(0, 0);
    return 0;
}