#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int> > snail;

int n, number;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int main(void){
    scanf("%d", &n);
    scanf(" %d", &number);
    snail.resize(n, vector<int>(n, 0));
    int x, y;
    int dist = 1;
    int dir = 0;
    int num = 1;
    bool flag = false;
    pair<int, int> p;
    x = n/2; y = n/2;
    while((x != 0) || (y != 0)){
        for(int cnt=0; cnt<2; cnt++){
            for(int d=0; d<dist; d++){
                if(num == number){ p.first = x; p.second = y;}
                snail[x][y] = num++;
                x += dx[dir];
                y += dy[dir];
                if((x == 0) && (y == 0)){
                    flag = true; break;
                }
            }
            if(flag){
                if(num == number){ p.first = x; p.second = y;}
                snail[x][y] = num;
                break;
            }
            dir = (dir + 1) % 4;
        }
        dist += 1;
    }

    for(int i=0; i<snail.size(); i++){
        for(int j=0; j<snail[0].size(); j++){
            printf("%d ",snail[i][j]);
        }
        printf("\n");
    }
    printf("%d %d\n", p.first+1, p.second+1);
    return 0;
}