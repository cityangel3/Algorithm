#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;
#define MAX 130

int nrow,ncol,r;
int ansr,ansc;
int arr[MAX][MAX] = {0,};
int ans[MAX][MAX] = {0,};
void print_arr(int n,int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }
}
void swap_rc(){
    int temp = ansr;
    ansr = ansc;
    ansc = temp;
}
void cal_one(){
    for(int i=0; i<ansr; i++){
        for(int j=0; j<ansc; j++){
            ans[ansr-1-i][j] = arr[i][j];
        }
    }
}
void cal_two(){
    for(int i=0; i<ansr; i++){
        for(int j=0; j<ansc; j++){
            ans[i][ansc-1-j] = arr[i][j];
        }
    }
}
void cal_three(){
    for(int i=0; i<ansr; i++){
        for(int j=0; j<ansc; j++){
            ans[j][ansr-1-i] = arr[i][j];
        }
    }
    swap_rc();
}
void cal_four(){
    for(int i=0; i<ansr; i++){
        for(int j=0; j<ansc; j++){
            ans[ansc-1-j][i] = arr[i][j];
        }
    }
    swap_rc();
}
void cal_five(){
    int halfr = ansr/2;
    int halfc = ansc/2;
    for(int i=0; i<halfr; i++){
        for(int j=0; j<halfc; j++){
            ans[i][j+halfc] = arr[i][j];
        }
    }
    for(int i=0; i<halfr; i++){
        for(int j=halfc; j<ansc; j++){
            ans[i+halfr][j] = arr[i][j];
        }
    }
    for(int i=halfr; i<ansr; i++){
        for(int j=halfc; j<ansc; j++){
            ans[i][j-halfc] = arr[i][j];
        }
    }
    for(int i=halfr; i<ansr; i++){
        for(int j=0; j<halfc; j++){
            ans[i-halfr][j] = arr[i][j];
        }
    }
}
void cal_six(){
    int halfr = ansr/2;
    int halfc = ansc/2;
    for(int i=0; i<halfr; i++){
        for(int j=0; j<halfc; j++){
            ans[i+halfr][j] = arr[i][j];
        }
    }
    for(int i=0; i<halfr; i++){
        for(int j=halfc; j<ansc; j++){
            ans[i][j-halfc] = arr[i][j];
        }
    }
    for(int i=halfr; i<ansr; i++){
        for(int j=halfc; j<ansc; j++){
            ans[i-halfr][j] = arr[i][j];
        }
    }
    for(int i=halfr; i<ansr; i++){
        for(int j=0; j<halfc; j++){
            ans[i][j+halfc] = arr[i][j];
        }
    }
}
int main(void){
    freopen("input.txt","r",stdin);
    int num;
    scanf("%d %d %d",&nrow,&ncol,&r);
    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncol; j++){
            scanf(" %d",&arr[i][j]);
        }
    }
    ansr = nrow; ansc = ncol;
    for(int i=0; i<r; i++){
    scanf(" %d",&num);

        switch(num){
            case 1:
                cal_one();
                break;
            case 2:
                cal_two();
                break;
            case 3:
                cal_three();
                break;
            case 4:
                cal_four();
                break;
            case 5:
                cal_five();
                break;
            case 6:
                cal_six();
                break;
            default:
                printf("input error\n");
                break;
        }
    memcpy(arr,ans,sizeof(ans));
    }
    print_arr(ansr,ansc);
    return 0;
}