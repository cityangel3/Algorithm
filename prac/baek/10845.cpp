#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>

using namespace std;

int main(void){
    int n, item;
    char cmd[20];
    queue<int> q;
    freopen("input.txt","r",stdin);
    scanf("%d", &n);
    while(n--){
        string s;
        scanf(" %s %d", cmd, &item);
        s = cmd;
        if(!s.compare("push"))
            q.push(item);
        else if(!s.compare("pop")){
            if(q.empty())
                printf("-1\n");
            else{
                printf("%d\n", q.front());
                q.pop();
            }
        }
        else if(!s.compare("size"))
            printf("%lu\n",q.size());
        else if(!s.compare("empty"))
            printf("%d\n", q.empty());
        else if(!s.compare("front")){
            if(q.empty())
                printf("-1\n");
            else
                printf("%d\n",q.front());
        }
        else if(!s.compare("back")){
            if(q.empty())
                printf("-1\n");
            else
                printf("%d\n",q.back());
        }
        else{
            printf("command error.\n");
        }
    }
}
