#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>

using namespace std;

#define MAXNM 7
#define MAXNUM 10010

int n, m;
int asize;
int visited[MAXNM] = {0, };
int avail[MAXNUM] = {0, };

vector<int> arr;
vector<int> comb;

void ans(int d){
    if(d == m){
        for(int i=0; i<m; i++){
            printf("%d ", comb[i]);
        }
        printf("\n");
        return;
    }
    for(int i=0; i<asize; i++){
        comb[d] = arr[i];
        ans(d+1);
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
    asize = arr.size();
    sort(arr.begin(), arr.end());
    comb.reserve(m);
    ans(0);
    // for(int i=0; i<asize; i++)
    //     printf("(%d %d) ", arr[i], avail[arr[i]]);
    // printf("\n");
    return 0;
}