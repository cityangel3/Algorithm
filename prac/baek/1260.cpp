#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

#define MAXN 1000
#define MAXM 10000

int n, m, v;
vector<vector<int> > graph;
bool visited[MAXN] = {false, };
typedef struct st{
    int v;
}ST;

void dfs(int v){
    printf("%d ", v);
    visited[v] = true;

    for(int i=0; i<graph[v].size(); i++){
        int next = graph[v][i];
        if(!visited[next])
            dfs(next);
    }
}

void bfs(int v){
    queue<ST> q;

    q.push({v});
    visited[v] = true;
    
    while(!q.empty()){
        ST st = q.front();
        int cur = st.v;
        printf("%d ",cur);
        q.pop();

        for(int i=0; i<graph[cur].size(); i++){
            int next = graph[cur][i];
            if(visited[next] == true)
                continue;
            q.push({next});
            visited[next] = true;
        }
    }
}

int main(void){
    scanf("%d %d %d", &n, &m, &v);
    graph.resize(n+1);
    
    for(int i=0; i<m; i++){
        int v1, v2;
        scanf(" %d %d", &v1, &v2);
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    for(int i=1; i<=n; i++)
        sort(graph[i].begin(), graph[i].end());

    dfs(v);
    printf("\n");
    memset(visited, false, sizeof(visited));
    bfs(v);
    printf("\n");
    // for(int i=1; i<=n; i++){
    //     if(!graph[i].size())
    //         continue;
    //     printf("[%d] ", i);
    //     for(int j=0; j<graph[i].size(); j++)
    //         printf("%d ", graph[i][j]);
    //     printf("\n");
    // }
    return 0;
}