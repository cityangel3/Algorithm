#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

int n, m;
int arr[8] = {0, };
bool check[8] = {false, };
vector<pair<int, int> > res;


void hybrid(int d, int before){
    if(d == m){
        for(int i=0; i<m; i++)
            printf("%d ", res[i].first);
        printf("\n");
        return;
    }

    for(int i=0; i<n; i++){
        if(check[i] == true)
            continue;
        if((i >= 1) && (arr[i] == arr[i-1])){
            /* 이건 직전이 중복되고 & "직전이 중복된 숫자이냐" */
            // if(res[d-1].second != i-1) 
            //     continue;
            /* 직전이 중복되고 & "직전이 포함되어 있냐" 여야 함 
                : 배열에는 순차적으로 저장되어 있지만, 순회하는것은 순차적이지 않을 수 있어서 */
            int flag = 0;
            for(int j=0; j<d; j++){
                if(res[j].second == i-1)
                    flag = 1;
            }
            if(!flag)
                continue;
        }

        //  res[d] = {arr[i], i};
        res[d] = make_pair(arr[i], i);
        check[i] = true;
        hybrid(d+1, res[d].first);
        check[i] = false;
    }
}

int main(void){
    int elem, temp;
    scanf("%d %d", &n, &m);
    res.reserve(m);
    for(int i=0; i<n; i++)
        scanf(" %d", arr + i);
    sort(arr, arr+n);
    // 중복 제거 , 중복되는 인덱스 
    hybrid(0, 0);
    return 0;   
}