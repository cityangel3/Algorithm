#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX 8
int n, m;
vector<int> res;
int arr[MAX] = {0, };
bool check[MAX] = {false, };

void perm(int d){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }

    for(int i=0; i<n; i++){
        if(check[i] == true)
            continue;
        else{
            res[d] = arr[i];
            check[i] = true;
            perm(d+1);
            check[i] = false;
        }
    }
}

int main(void){
    scanf("%d %d", &n, &m);
    res.reserve(m);
    for(int i=0; i<n; i++)
        scanf(" %d", arr + i);
    sort(arr, arr+n);
    perm(0);
    return 0;
}