#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define MAX 1010
int n, m, v;
bool visited[MAX] = {false, };
vector<int> graph[MAX];

void dfs(int num){
    int size = graph[num].size();

    printf("%d ",num);
    visited[num] = true;

    for(int i=0; i<size; i++){
        int next = graph[num][i];
        if(visited[next] == false){
            dfs(next);
        }
    }
}

void bfs(int num){
    queue<int> q;

    visited[num] = true;
    q.push(num);

    while(!q.empty()){
        int elem = q.front();
        q.pop();
        int size = graph[elem].size();
        printf("%d ",elem);

        for(int i=0; i<size; i++){
            int next = graph[elem][i];
            if(visited[next] == false){
                q.push(next);
                visited[next] = true;
            }
        }

    }

}

int main(void){
    freopen("input.txt","r",stdin);

    scanf(" %d %d %d",&n, &m, &v);

    for(int i=0; i<m; i++){
        int s, d;
        scanf(" %d %d",&s, &d);
        graph[s].push_back(d);
        graph[d].push_back(s);
    }
    for(int i=1; i<=n; i++){ // 초기화 할 때 항상 시작이 어디인지 주의!!!
        sort(graph[i].begin(),graph[i].end());
    }
    dfs(v);
    printf("\n");
    memset(visited, false, sizeof(visited));
    bfs(v);
    printf("\n");
    return 0;
}
