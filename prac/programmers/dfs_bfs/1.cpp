#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

vector<int> chose;

void rperm(int d, int m, int *arr, int *ans, vector<int> num, int target){
    if(d == m){
        int sum;
        if(chose[0] == 1)
            sum = num[0];
        else if(chose[0] == 2)
            sum = (-1)*(num[0]);
        else 
            printf("error.\n");

        for(int i=1; i<m; i++){
            if(chose[i] == 1)
                sum += num[i];
            else if(chose[i] == 2)
                sum -= num[i];
            else 
                printf("error.\n");
        }
        if(sum == target)
            *ans += 1;
        return;
    }
    for(int i=0; i<2; i++){
        chose[d] = arr[i];
        rperm(d+1, m, arr, ans, num, target);
    }
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int size = numbers.size();
    int arr[2] = {1, 2};

    chose.reserve(size);
    rperm(0, size, arr, &answer, numbers, target);
    
    return answer;
}

int main(void){
    int n, target;
    vector<int> arr;

    scanf("%d %d", &n, &target);
    for(int i=0; i<n; i++){
        int elem;
        scanf(" %d", &elem);
        arr.push_back(elem);
    }
    
    printf("%d\n",solution(arr, target));
    return 0;
}