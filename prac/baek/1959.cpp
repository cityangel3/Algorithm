#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>

using namespace std;

// 시간 제한 및 for loop 도는 횟수 꼭 확인

int main(void){
    unsigned long long m, n;

    scanf("%llu %llu", &m, &n);

    pair<long long, long long> p;
    long long top, bottom, left, right, num=0, x, y;
    long long ans=0, i, j;

    top = 0; bottom = m-1; left = 0; right = n-1;
    x = top; y = left;
    while((top <= bottom) && (left <= right)){
        num = (right - left + 1);
        if(0 < num){
            ans += 1;
            y = right;
        }
        top += 1;

        num = (bottom - top + 1);
        if(0 < num){
            ans += 1;
            x = bottom;
        }
        right -= 1;

        if(top <= bottom){
            num = (right - left + 1);
            if(0 < num){
                ans += 1;
                y = left;
            }
            bottom -= 1;
        }

        if(left <= right){
            num = (bottom - top + 1);
            if(0 < num){
                ans += 1;
                x = top;
            }
            left += 1;
        }
        // printf("t:%d b:%d l:%d r:%d",top,bottom,left,right);
    }
    printf("%lld\n%lld %lld\n",ans-1, x+1, y+1);
    return 0;
}