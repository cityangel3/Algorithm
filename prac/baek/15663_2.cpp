#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

int n, m;
int visited[8] = {0, };
int avail[10010] = {0, };
int arr[8] = {0, };
int res[8] = {0, };

void ans(int d){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }
    for(int i=0; i<n; i++){
        if(visited[i] >= avail[arr[i]])  
            continue;
        res[d] = arr[i];
        visited[i]++;
        ans(d+1);
        visited[i]--;
    }
}

int main(void){
    int elem, idx=0;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        scanf(" %d", &elem);
        if(avail[elem] == 0)
            arr[idx++] = elem;
        avail[elem]++;
    }

    n = idx;
    sort(arr, arr+n);
    ans(0);
    return 0;
}