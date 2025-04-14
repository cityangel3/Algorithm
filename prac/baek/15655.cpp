#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

#define MAX 8

int n, m;
int arr[MAX] = {0, };
vector<int> res;

void comb(int d, int cur){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }

    for(int i=cur; i<n; i++){
        res[d] = arr[i];
        comb(d+1, i+1);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    res.reserve(m);
    for(int i=0; i<n; i++)
        scanf(" %d", arr + i);
    sort(arr, arr+n);
    comb(0, 0);
    return 0;
}