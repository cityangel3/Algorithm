#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

#define MAX 100010

priority_queue<int> max_heap;
priority_queue<int, vector<int>, greater<int> > min_heap;
int n;

void swap(){
    int xtemp = max_heap.top();
    int ntemp = min_heap.top();
    max_heap.pop();
    min_heap.pop();
    max_heap.push(ntemp);
    min_heap.push(xtemp);
}
int main(void){ 
    freopen("input.txt","r",stdin);
    // logic 상 max_heap의 top()이 항상 중간 값이어야 되니까 max_heap부터 채우는 것.
    scanf("%d",&n);

    for(int i=0; i<n; i++){
        int num;
        scanf(" %d", &num);
        if(i % 2)
            min_heap.push(num);
        else
            max_heap.push(num);
        
        if(!min_heap.empty())
            if(max_heap.top() > min_heap.top())
                swap();
        
        printf("%d\n",max_heap.top());
    }
    return 0;
}