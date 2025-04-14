#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

int main(void){
    int n, m;
    int answer=0;
    vector<int> arr;
    scanf("%d %d",&n, &m);
    arr.resize(n);
    for(int i=0; i<n; i++)
        scanf(" %d", &arr[i]);
    
    int left=0, right=0;
    int sum=arr[0];
    // int sum = 0;
    while(1){
        if(sum < m){
            right += 1;
            if(right >= n) break;
            sum += arr[right];
        }
        else if(sum == m){
            answer += 1;
            right += 1;
            if(right >= n) break;
            sum += arr[right];
        }
        else{
            sum -= arr[left];
            left += 1;
        }
        // printf("%d l:%d ,r:%d\n",sum,left,right);
    }
    printf("%d\n",answer);
    return 0;
}