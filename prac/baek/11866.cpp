#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

int main(void){
    int n, k;
    vector<int> table;
    vector<int> res;
    vector<int>::iterator iter;

    scanf("%d %d", &n, &k);

    for(int i=1; i<=n; i++)
        table.push_back(i);
    iter = table.begin() + k - 1;
    k -= 1;
    while(table.size()){
        res.push_back(*iter);
        iter = table.erase(iter);
        for(int i=0; i<k; i++){ // iter가 증가한 직후에서 경계 검사를 해야 한다.
            if(iter == table.end())
                iter = table.begin();
            iter++;
        }
        if(iter == table.end()) // iter가 증가한 직후에서 경계 검사를 해야 한다.
                iter = table.begin();
    }
    printf("<");
    for(int i=0; i<res.size()-1; i++)
        printf("%d, ", res[i]);
    printf("%d>\n", *(res.rbegin()));
    return 0;
}