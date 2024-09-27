#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

vector<int> v;
int N;

priority_queue<int> max_heap;
priority_queue<int, vector<int>, greater<int> > min_heap;

int mid_number(int size){
    int idx = size / 2;;
    int *arr = v.data();

    if(size % 2 == 0){
        return min(arr[idx], arr[idx-1]);
    }
    else{
        // return v[idx];
        return arr[idx];
    }
}
void wrong_ans(){
    scanf("%d",&N);
    v.reserve(N);

    for(int i=0;i<N;i++){
        int num;
        scanf("%d",&num);
        v.push_back(num);
        // 매 반복마다 sort하는 건 필요하지만, 
        // 아래와 같이 naive 한 방법은 불가능... -> 문제 시간 제약 조건
        sort(v.begin(),v.end());
        printf("%d\n",mid_number(v.size()));
    }
}
int main(void){
    // clock_t start, end;
    freopen("input.txt","r",stdin);
    // start = clock();

    /* 빠른 정렬 : priority queue(max,min heap) 떠올리자!*/ 
    // heap 구조를 사용한 정렬이 필요 -> c++ 의 priority queue 사용
    // 외에도 nlogn 은 quick, merge가 있음
    int num, cnt=0;
    scanf("%d",&N);

    for(int i=0;i<N;i++){
        int mxt, mnt;
        scanf(" %d",&num);
        if(cnt % 2 == 0) // 0부터 시작이라 max heap 먼저 채움
            max_heap.push(num);
        else
            min_heap.push(num);

        if(min_heap.empty()){
            printf("%d\n",max_heap.top());
            cnt++;
            continue;
        }

        mxt = max_heap.top();
        mnt = min_heap.top();
        if(mxt > mnt){
            max_heap.pop();
            min_heap.pop();
            max_heap.push(mnt);
            min_heap.push(mxt);
        }

        cnt++;
        printf("%d\n",max_heap.top());
    }

    // end = clock();
    // printf("%lf\n",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}