#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;
#define MAX 1010

int N,M,V;
vector<int> graph[MAX];
bool visited[MAX] = {false, };
bool visited2[MAX] = {false, };

void dfs(int v){
    visited[v] = true;
    printf("%d ",v);
    vector<int> edge = graph[v];
    int size = edge.size();
    for(int i=0; i<size; i++){
        int next = edge[i];
        if(!visited[next])
            dfs(next);
    }
}
void bfs(int v){
    queue<int> q;
    q.push(v);
    visited2[v] = true;

    while(!q.empty()){
        int num = q.front();
        vector<int> edge = graph[num];
        int size = edge.size();

        q.pop();
        printf("%d ",num);

        for(int i=0; i<size; i++){
            int next = edge[i];

            if(!visited2[next]){
                q.push(next);
                visited2[next] = true;
            }
        }
    }
}

int main(void){
    freopen("input.txt","r",stdin);

    scanf("%d %d %d",&N,&M,&V);

    for(int i=0; i<M; i++){
        int v1,v2;
        scanf("%d %d",&v1,&v2);
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }   
    for(int i=1; i<=N; i++)
        sort(graph[i].begin(), graph[i].end());

    dfs(V);
    printf("\n");
    bfs(V);
    printf("\n");

    return 0;
}