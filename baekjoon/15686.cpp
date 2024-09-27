#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

#define NMAX 60
#define DEBUG 0

int n,m;
// vector<int> ck_comb; -> vector reserve 조심해서 사용...
int ck_comb[NMAX];
vector<pair<int, int> > ck;
vector<pair<int, int> > hm;
vector<vector<int> > ck_hm;
priority_queue<int, vector<int>, greater<int> > res, ck_min;

void cal_min(){
    int sum=0;
    for(int i=0; i<hm.size(); i++){
        for(int j=0; j<m; j++){
            int idx = ck_comb[j];
            int dist = ck_hm[i][idx];
            ck_min.push(dist);         
        }

        sum += ck_min.top();
        ck_min = priority_queue<int, vector<int>, greater<int> >();
    }
    res.push(sum);
#if DEBUG
    // printf("cal_min : %d\n",sum);
#endif
}

void comb(int depth, int next, int csize){
    if(depth == m){
        cal_min();
    }
    for(int i=next; i<csize; i++){
        ck_comb[depth] = i;
        comb(depth + 1, i + 1, csize);
    }
}

void cal_dist(int csize, int hsize){
    for(int i=0; i<hsize; i++){
        int hx = hm[i].first;
        int hy = hm[i].second;
        for(int j=0; j<csize; j++){
            int cx = ck[j].first;
            int cy = ck[j].second;
            ck_hm[i][j] = abs(hx-cx) + abs(hy-cy);
        }
    }
}

int main(void){
    /* 배열이나 객체 크기 할당할 때 항상 여분있게 해두는거 염두! */
    freopen("input.txt","r",stdin);
    int ck_size, hm_size;

    scanf("%d %d",&n, &m);
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            int num;
            scanf(" %d",&num);
            if(num == 1)
                hm.push_back({i,j});
                // hm.emplace_back(make_pair(i,j)); // ck.emplace_back({i,j}); <- 컴파일 에러.
            else if(num == 2)
                ck.push_back({i,j});
                // ck.emplace_back(make_pair(i,j));
        }
    }
    ck_size = ck.size();
    hm_size = hm.size();
    
    ck_hm.reserve(hm_size * 2); 
    for(int i=0; i<hm_size; i++)
        ck_hm[i].reserve(ck_size * 2);

    cal_dist(ck_size, hm_size);

#if DEBUG
    for(int i=0;i<hm.size();i++)
        printf("(%d, %d) ",hm[i].first, hm[i].second);
    printf("\n");
    for(int i=0;i<ck.size();i++)
        printf("(%d, %d) ",ck[i].first, ck[i].second);
    printf("\n");
    for(int i=0; i<hm_size; i++){
        for(int j=0; j<ck_size; j++){
            printf("%d ",ck_hm[i][j]);
        }
        printf("\n");
    }
#endif
    // nCm 중에 최소거리 가장 좋은 것으로.
    // ck_comb.reserve(m);
    comb(0, 0, ck_size);
    
    printf("%d\n",res.top());
#if DEBUG
    for(int i=0; i<hm_size; i++){
        for(int j=0; j<ck_size; j++){
            printf("%d ",ck_hm[i][j]);
        }
        printf("\n");
    }
#endif
    return 0;
}