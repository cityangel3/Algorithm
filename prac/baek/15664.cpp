#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>

using namespace std;

#define MAXMN 8
#define MAXNUM 10010

int n, m;
int visited[MAXMN] = {0, };
int avail[MAXNUM] = {0, };
int asize;

vector<int> arr, comb;

void ans(int d, int cur){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", comb[i]);
        printf("\n");
        return;
    }
    for(int i=cur; i<asize; i++){
        if(visited[i] >= avail[arr[i]])
            continue;
        visited[i] += 1;
        comb[d] = arr[i];
        ans(d+1, i);
        visited[i] -= 1;
    }
}

int main(void){
    scanf("%d %d", &n, &m);

    for(int i=0; i<n; i++){
        int elem;
        scanf(" %d", &elem);
        if(avail[elem] == 0)
            arr.push_back(elem);
        avail[elem] += 1;
    }
    sort(arr.begin(), arr.end());
    asize = arr.size();
    comb.reserve(m);
    ans(0, 0);

    // for(int i=0; i<asize; i++)
    //     printf("(%d, %d) ", arr[i], avail[arr[i]]);
    // printf("\n");

    return 0;
}