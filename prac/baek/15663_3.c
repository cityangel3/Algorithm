#include <stdio.h>
int arr[8],ans[8],check[8]={0,};
void go(int n,int m,int index){
    if(index == m){
        for(int i =0;i<m;i++)
            printf("%d ",ans[i]);
        printf("\n");
        return;
    }
    int rep=0;
    for(int i =0;i<n;i++){
        /* 이렇게 하면 직전이 중복이면서 포함된 경우, rep=0이여서 자동으로 허용.
            직전이 중복이면서 포함되지 않은 경우 불허하게 됨. */
        if(!check[i] && rep != arr[i]){ 
            check[i] = 1;
            ans[index] = arr[i];
            rep = ans[index];
            go(n,m,index+1);
            check[i] = 0;
        }
    }
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i =0;i<n;i++)
        scanf("%d",arr+i);
    for(int i=1;i<n;i++){
        int j = i - 1;
        int key = arr[i];
        while(j>=0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    go(n,m,0);
}