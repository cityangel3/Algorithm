#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define MAX 110
#define WMAX 100010

int n, k;
int v[MAX] = {0, };
int w[MAX] = {0, };
int ans[MAX][WMAX] = {0,};

int main(void){
    freopen("input.txt","r",stdin);

    scanf("%d %d",&n, &k);
    for(int i=1; i<=n; i++){
        scanf("%d %d", &w[i], &v[i]);
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=k; j++){ // 버틸 수 있는 무게까지 증가시켜가며 (j : 가방 용량)
            if(w[i] <= j){ // 더 넣을 수 있는 상태
                ans[i][j] = max(ans[i-1][j], ans[i-1][j-w[i]] + v[i]);
                // ans[i-1][j] 는 현재 무게합에서 이전까지의 물건 가치 최대
                // ans[i-1][j-w[i]] 는 지금 물건이 들어가지 않은 무게에서 지금 물건을 넣은 가치를 보기 위함
            }
            else{ // 더 넣을 수 없는 상태
                ans[i][j] = ans[i-1][j]; // 같은 무게 이전 선택 이어감
            }
        }
    }
    printf("%d\n",ans[n][k]);
    return 0;
}