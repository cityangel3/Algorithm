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

void rperm(int d){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }

    for(int i=0; i<n; i++){
        res[d] = arr[i];
        rperm(d+1);
    }
}

int main(void){
    scanf("%d %d", &n, &m);
    res.reserve(m);
    for(int i=0; i<n; i++)
        scanf(" %d", arr + i);
    sort(arr, arr+n);
    rperm(0);
    return 0;
}