#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

#define MAXMN 8
#define MAXNUM 10010

int n, m;
int asize;
int avail[MAXNUM] = {0, };
vector<int> arr, res;

void ans(int d, int cur){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }
    for(int i=cur; i<asize; i++){
        res[d] = arr[i];
        ans(d+1, i);
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
    res.reserve(m);
    ans(0, 0);
}