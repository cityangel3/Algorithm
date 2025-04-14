#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

int m, n;
vector<int> res;
bool check[8] = {false, };

void perm(int d){
    if(d == m){
        for (int i=0; i<m; i++)
            printf("%d ", res[i]);
        printf("\n");
        return;
    }

    for (int i=1; i<=n; i++){
        if(check[i] == true)
            continue;
        else{
            // res.push_back(i);
            res[d] = i;
            check[i] = true;
            perm(d+1);
            check[i] = false;
            // res.erase(res.begin() + res.size() - 1);
            // res.pop_back(); // 굳이 마지막 pop 할 필요 없이 overwrite 하면된다.
        }
    }
}

int main(){
    scanf("%d %d", &n, &m); 
    // res.resize(m+1);
    res.reserve(m+1); //faster
    perm(0);

    return 0;
}
