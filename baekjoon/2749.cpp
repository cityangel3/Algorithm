#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

#define DIV 1000000


int fibo(int n){
    // if(n == 1) 
    //     return 1;
    // else if(n == 0)
    //     return 0;
    if(n <= 1)
        return n;
    return fibo(n-1) + fibo(n-2);
}

int fibo2(int n){
    int a = 0, b = 1;
    int res = a;
    while(n > 1){
        n -= 1;
        res = a + b;
        a = b;
        b = res;
    }
    return res;
}

int getPisanoPeriod(int m) {
    int previous = 0, current = 1;
    int period = 0;

    // 최대 m*m번 반복하면 피사노 주기가 반드시 나타난다는 특성이 있음.
    for (unsigned long long i = 0; i < m * m; i++) {
        int temp = current;
        current = (previous + current) % m;
        previous = temp;
        period++;

        // 피사노 주기의 시작은 항상 0, 1임.
        if (previous == 0 && current == 1)
            return period;
    }
    return period; // 이론적으로 도달하지 않음.
}

int main(){
    /* 입력되는 데이터 크기 주의하자 (llu, lld 항상 염두에 두기) */
    long long n, sum = 1, period;
    vector<long long> v;
    // const int period = DIV/10*15;
    // int v[period] = {0,1};

    scanf("%lld", &n);

    period = getPisanoPeriod(DIV);
    period = DIV/10*15;
    v.resize(period);

    v[0] = 0;
    v[1] = 1;

    for (int i=2; i<period; i++){
        v[i] = v[i-1] + v[i-2];
        v[i] %= DIV;
    }
    printf("%lld\n", v[n%period]);
}