/* 교훈 */
/*
 * 좌표 관련해서, 배열 oob 안되도록 종료 조건 및 경계 확인 잘하기.
 * 미리 디버깅 용으로 출력해놓는 습관.
 * unsigned를 loop 변수로 쓰면 --되다가 0 다음에 최댓값이 돼서 무한 loop 되는거 주의.
    -> 그냥 long long 만 쓰자.
*/
/* 스킬 */
/*
 * 나선형 이동(안->밖)
 * 주변에 영향을 준다 -> const 배열로, 고정 좌표 및 정보 넣어놓고 활용
 * int& 변수; 는 c의 포인터와 같다.
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>

using namespace std;
#define DEBUG 0

int n;
int dx[4] = {0, 1, 0, -1}; // ccw
int dy[4] = {-1, 0, 1, 0};

typedef struct info{ 
    int x, y; 
    float ptg;
}info;
const vector<vector<info> > spread = {
    {{-1, 0, 0.01}, {1, 0, 0.01}, {-1, -1, 0.07}, {1, -1, 0.07}, {-2, -1, 0.02}, {2, -1, 0.02}, {-1, -2, 0.1}, {1, -2, 0.1}, {0, -3, 0.05}, {0, -2, 0}}, // left
    {{0, -1, 0.01}, {0, 1, 0.01}, {1, -1, 0.07}, {1, 1, 0.07}, {1, -2, 0.02}, {1, 2, 0.02}, {2, -1, 0.1}, {2, 1, 0.1}, {3, 0, 0.05}, {2, 0, 0}}, // bottom
    {{-1 ,0, 0.01}, {1, 0, 0.01}, {-1, 1, 0.07}, {1, 1, 0.07}, {-2, 1, 0.02}, {2, 1, 0.02}, {-1, 2, 0.1}, {1, 2, 0.1}, {0, 3, 0.05}, {0, 2, 0}}, // right
    {{0, -1, 0.01}, {0, 1, 0.01}, {-1, 1, 0.07}, {-1, -1, 0.07}, {-1, 2, 0.02}, {-1, -2, 0.02}, {-2, 1, 0.1}, {-2, -1, 0.1}, {-3, 0, 0.05}, {-2, 0, 0}} // top
};
// const int spread[4][9][2] = { // 1%, 7%, 2%, 10%, 5%
//     {{-1, 0}, {1, 0}, {-1, -1}, {1, -1}, {-2, -1}, {2, -1}, {-1, -2}, {1, -2}, {0, -2}}, // left
//     {{0, -1}, {0, 1}, {1, -1}, {1, 1}, {1, -2}, {1, 2}, {2, -1}, {2, 1}, {2, 0}}, // bottom
//     {{-1 ,0}, {1, 0}, {-1, 1}, {1, 1}, {-2, 1}, {2, 1}, {-1, 2}, {1, 2}, {0, 2}}, // right
//     {{0, -1}, {0, 1}, {-1, 1}, {-1, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}, {-2, 0}} // top
// };

vector<vector<int> > smap;

#if DEBUG
void print_vector(vector<vector<int> > arr);
#endif

bool lineout(int x, int y){
    if((x < 0) || (x >= n) || (y < 0) || (y >= n))
        return true;
    return false;
}

unsigned long long moving(int sx, int sy){
    unsigned long long out=0;
    int x = sx, y = sy;
    int dist = 1;
    int dir = 0;
    bool flag = false;
    while((x != 0) || (y != 0)){ // end point: origin
        for(int cnt=0; cnt<2; cnt++){
            for(int d=0; d<dist; d++){
                float sand = (float)smap[x+dx[dir]][y+dy[dir]];
                float ssum = 0;
#if DEBUG
                    printf("[%d, %d] sand(%f)\n",x,y,sand);
#endif
                for(int sp=0; sp<10; sp++){
                    int px = x + spread[dir][sp].x;
                    int py = y + spread[dir][sp].y;
                    float ptg = spread[dir][sp].ptg;
                    int sand_mov;
                    if(sp == 9)
                        sand_mov = (int)(sand - ssum);
                    else
                        sand_mov = (int)(sand * ptg);

                    ssum += sand_mov;
                    if(lineout(px, py))
                        out += (unsigned long long)(sand_mov);
                    else   
                        smap[px][py] += sand_mov;
                }
                #if DEBUG
                    print_vector(smap);
                #endif
                x += dx[dir];
                y += dy[dir];
                smap[x][y] -= (int)ssum;
                if((x == 0) && (y == 0)){ // dist 다 이동하기 전에 도착 가능
                    flag = true; break; 
                }
            }
            if(flag) break;
            dir  = (dir + 1) % 4; // change direction
        }
        dist += 1 ;
    }
    #if DEBUG
        printf("----------------------\n");
    #endif  
    return out;
}

int main(void){
#if DEBUG
    freopen("input.txt","r",stdin);
#endif
    unsigned long long sands=0;
    scanf("%d", &n);
    smap.resize(n, vector<int>(n, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf(" %d", &smap[i][j]);
        }
    }

    sands = moving(n/2, n/2);
    printf("%llu\n",sands);
    return 0;
}

#if DEBUG
void print_vector(vector<vector<int> > arr){
    for(int i=0; i<arr.size(); i++){
        for(int j=0; j<arr[0].size(); j++)
            printf("%2d ",arr[i][j]);
        printf("\n");
    }
}
#endif