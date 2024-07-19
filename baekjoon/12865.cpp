#include <iostream>
#include <cstdio>
// #include <string>
// #include <cstring>
// #include <cmath>
// #include <cstdlib>
// #include <algorithm>
// #include <Vector>
// #include <utility>
// #include <deque>
// #include <list>
// #include <ctime>
// #include <limits>
// #include <climits>

using namespace std;
#define MAX 110
int k,n;
int DP[MAX][10010]={0,};
int W[MAX], V[MAX];


int main(void){
    freopen("input.txt", "r", stdin);  
    // freopen("output.txt", "W", stdout);  
    scanf("%d %d",&n,&k);

    for(int i=1;i<=n;i++){
        scanf(" %d %d", W+i, V+i);
    }
    // permutaion 으로 모든 경우를 봐야만 하는가? => Brute Force 시간 복잡도 O(2^n)...
    // => 정렬해서 큰 가치 순으로 더해주면 ... x (DP 문제는 sort로 풀 수 없다.)
    // Ans : DP 로 푸는 것 ~ max(물건 추가 x, 물건 빼고 새로 채우기)
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            if(W[i] <= j){ // 용량이 현재 무게를 포함할 수 있는 용량이 되면
                // DP[i][j] = max(DP[i-1][j], DP[i-1][j - W[i]] + V[i]);
                DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - W[i]] + V[i]);
                // 이번 무게를 제외한, 이전 최대합에서 현재 가치를 더한 것과 (현재 j 인덱스가 이미 무게가 더해진 상태) 
                // 현재 무게에 대한 이전 최대합과의 비교
            }
            else{
                DP[i][j] = DP[i-1][j]; // 용량이 0 ~ K 로 순회하므로 [n][k]에 최대값이 저장된다.
            }
        }
    }
    printf("%d\n",DP[n][k]);
    return 0;
}