/* 교훈 */
/* 
 * 항상 필요한 자료구조(etc.좌표그룹) 구하고서 맞게 구한건지 꼭 체크하자.
 * if 문 조건 및 loop 종료 조건 항상 생각하고 주의해서 코너 케이스 발생 안하도록 하자.
    테스트를 많이 해보면서 찾자!
*/
/* 스킬 */
/*
 * 나선형 구조에서 빈칸 뒤로 빼기 (중력 구현과 비슷)
    하지만, dest 좌표 이동이 단순 직선이 아니기 때문에
    dest 좌표 이동하는 부분에서, 추가적으로 dist, mov(cnt), dir 구현해줘야함.
 * 나선형에서 한 번 순회로 필요한 연속적인 그룹 구하기 : 기준 value를 잡고 다른 값이 됐을때 그룹에 추가.
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

#define DEBUG 0
#define EMPTY 0
#define SHARK 7

int n, m;
int dx[4] = {0, 1, 0, -1}; // w, s, e, n
int dy[4] = {-1, 0, 1, 0};
int dix[4] = {-1, 1, 0, 0}; // n, s, w, e
int diy[4] = {0, 0, -1, 1};
int score[4] = {0, }; // record exploded # of bead

typedef struct info{ int di, si; }info;
typedef struct coord{ int x, y; }coord;

vector<vector<int> > board;
vector<info> blizards;
vector<vector<pair<int ,int>> > bomb;
vector<vector<pair<int ,int>> > groups;
vector<int> dest_dists;

#if DEBUG
void print_vector(vector<vector<int> > arr);
#endif

vector<vector<int> > add_new(vector<vector<pair<int ,int>> > gi){
    int r = n;
    int c = n;
    int x = r/2, y = c/2;
    int dist_idx = 0;
    int dir = 0;
    int mov = 0;
    bool flag = false;
    vector<vector<int> > res(r, vector<int>(c, 0));
    res[x][y] = SHARK;

    for(auto gp : gi){ 
        int val[2];
        val[0] = gp.size(); // size
        val[1] = board[gp[0].first][gp[0].second]; // value
        for(int i=0; i<2; i++){
            x += dx[dir];
            y += dy[dir];
            if((x < 0) || (x >= n) || (y < 0) || (y >= n)){ 
                flag = true;
                break;
            }
            res[x][y] = val[i];
            mov += 1;
            if(mov >= dest_dists[dist_idx]){
                mov = 0;
                dist_idx += 1;
                dir = (dir + 1) % 4;
            }
        }
        if(flag)
            break;
    }

    return res;
}

void bomb_board(vector<vector<pair<int ,int>> > bi){
    // explode continuous over 4 beads
    for(auto bp : bi){
        for(auto p : bp){
            score[board[p.first][p.second]] += 1;
            board[p.first][p.second] = EMPTY; // count exploded bead
        }
    }
}

vector<vector<pair<int ,int>> > find_groups(int sx, int sy, int size){
    vector<vector<pair<int, int>> > res;
    vector<pair<int, int> > group;
    int x = sx, y = sy;
    int dist = 1;
    int dir = 0;
    bool flag = false;

    int gval = SHARK;

    while((x != 0) || (y != 0)){
        for(int cnt=0; cnt<2; cnt++){
            for(int d=0; d<dist; d++){
                if((board[x][y] != SHARK)){
                    if(gval != board[x][y]){ // not first
                        if(group.size() >= size)
                            res.push_back(group);
                        group.clear();
                        gval = board[x][y];
                    }
                    if(board[x][y] == EMPTY){
                        flag = true;
                        break;
                    }
                    group.push_back(make_pair(x, y));
                }
                if((x == 0) && (y == 0)){
                    flag = true;
                    break;
                }
                x += dx[dir];
                y += dy[dir];
            }
            if(flag)
                break;
            dir = (dir + 1) % 4;
        }
        if(flag)
            break;
        dist += 1;
    }

    return res;
}

void renew_board(int sx, int sy){
    // remove empty slot, after blizard & bomb
    int x = sx, y = sy;
    int dist = 1;
    int dir = 0;
    int dest_dir = 0;
    int dest_mov = 0;
    int dest_dist_idx = 0;
    bool flag = false;
    coord dest;
    dest.x = sx; dest.y = sy;

    while((x != 0) || (y != 0)){
        for(int cnt=0; cnt<2; cnt++){
            for(int d=0; d<dist; d++){
                if(board[x][y] != EMPTY){
                    board[dest.x][dest.y] = board[x][y];
                    if((dest.x != x) || (dest.y != y)){ // there's empty in the middle
                        board[x][y] = EMPTY;
                    }
                    dest.x += dx[dest_dir];
                    dest.y += dy[dest_dir];
                    dest_mov += 1;
                    if(dest_mov >= dest_dists[dest_dist_idx]){
                        dest_mov = 0;
                        dest_dist_idx += 1;
                        dest_dir = (dest_dir + 1) % 4;
                    }
                }
                if((x == 0) && (y == 0)){
                    flag = true;
                    break;
                }
                x += dx[dir];
                y += dy[dir];
            }
            if(flag)
                break;
            dir = (dir + 1) % 4;
        }
        dist += 1;
    }
}

void blizard(int sx, int sy, int dir, int size){
    // execute blizard
    int x = sx, y = sy;
    for(int s=0; s<size; s++){
        int nx = x + dix[dir];
        int ny = y + diy[dir];
        if((nx < 0 ) || (nx >= n) || (ny < 0) || (ny >= n))
            continue;
        board[nx][ny] = EMPTY;
        x += dix[dir];
        y += diy[dir];
    }
}

int main(void){
#if DEBUG
    freopen("input.txt","r",stdin);
#endif
    int sx, sy;
    scanf("%d %d", &n, &m);
    board.resize(n, vector<int>(n, 0));
    sx = n/2; sy = n/2;

    for(int i=0; i<n; i++){ // board
        for(int j=0; j<n; j++){
            scanf(" %d", &board[i][j]);
        }
    }
    board[sx][sy] = SHARK; 

    for(int i=0; i<m; i++){ // blizards
        int di, si;
        scanf(" %d %d", &di, &si);
        blizards.push_back({di-1, si});
    }

    for(int i=1; i<=n; i++){
        dest_dists.push_back(i);
        dest_dists.push_back(i);
    }

#if DEBUG
    // print_vector(board);
    // printf("blizard size : %ld\n",blizards.size());
    // printf("-----------------------\n");
#endif
    
    for(info ii : blizards){
        int di = ii.di;
        int si = ii.si;

        blizard(sx, sy, di, si); // execute blizard
        
        #if DEBUG
            // print_vector(board);
            // printf("-----------------------\n");
        #endif 

        renew_board(sx, sy); // remove empty slots

        #if DEBUG
            // print_vector(board);
            // printf("-----------------------\n");
        #endif

        while(1){ // while no bomb
            bomb = find_groups(sx, sy, 4);

            #if DEBUG
                // printf("[bombs]\n");   
                // for(auto b : bomb){
                //     for(auto bb : b)
                //         printf("(%d, %d) ", bb.first, bb.second);
                //     printf("\n");
                // }
            #endif

            if(bomb.empty()) 
                break;
            bomb_board(bomb); // get over 4 group
            renew_board(sx, sy); // remove empty slots
        }

        #if DEBUG
            // printf("bombed board.\n");
            // print_vector(board);
            // printf("-----------------------\n");
        #endif
        groups = find_groups(sx, sy, 1); // get over 1 group

        #if DEBUG
            // printf("[groups]\n");   
            // for(auto g : groups){
            //     for(auto gg : g)
            //         printf("(%d, %d) ", gg.first, gg.second);
            //     printf("\n");
            // }
        #endif

        board = add_new(groups);
        
        #if DEBUG
            print_vector(board);
            printf("-----------------------\n");
        #endif

        bomb.clear();
        groups.clear();
    }
    int sum=0;
    for(int i=0; i<4; i++)
        sum += (i * score[i]);
    printf("%d\n", sum);
    return 0;
}

#if DEBUG
void print_vector(vector<vector<int> > arr){
    for(int i=0; i<arr.size(); i++){
        for(int j=0; j<arr[0].size(); j++)
            printf("%2d ", arr[i][j]);
        printf("\n");
    }
}
#endif
