#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;
using ull = unsigned long long;
#define MAX 6
int n;
int **C;
unsigned long long A[MAX][MAX], res[MAX][MAX];

void print_mat(unsigned long long arr[MAX][MAX]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%llu ",(arr[i][j] % 1000));
        }
        printf("\n");
    }
}
void matmul(unsigned long long B[MAX][MAX]){
    ull C[MAX][MAX] = {0,};
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                C[i][j] += (A[i][k] * B[k][j]) % 1000;
                C[i][j] %= 1000;
            }
        }
    }
    for(int i=0; i<n; i++)
        memcpy(B[i], C[i], sizeof(unsigned long long)*n);
}

void div_mult(unsigned long long exp){
    // 결국 지수가 홀수인 횟수는 역으로 나누면서 가도 같으니까
    // 그냥 역으로 진행하면서 곱해줘도 무방
    exp -= 1;
    while(exp > 0){
        if((exp % 2) == 1)
            matmul(res);
        matmul(A);
        exp /= 2;
    }
}

int main(void){
    // 분할 정복을 (특히 흐름이 선형적일 때에는) 굳이 재귀호출로 처리할 필요는 없다.
    freopen("input.txt","r",stdin);
    unsigned long long p;
    scanf("%d %llu",&n,&p);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf(" %llu",&A[i][j]);
        }
    }

    for(int i=0; i<n; i++)
        memcpy(res[i], A[i], sizeof(unsigned long long)*n);

    div_mult(p);
    print_mat(res);
    return 0;
}
