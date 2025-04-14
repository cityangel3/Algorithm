#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
#include<vector>
#include<queue>
#include<algorithm> // max_element, min_element O(n)
// #include<unordered_set>

using namespace std;

string solution(vector<vector<int> > scores){
    string answer = "";
    int size = scores.size();


    for(int j=0; j<size; j++){
        vector<int> score;
        for(int i=0; i<size; i++){
            if(i == j) continue;
            score.push_back(scores[i][j]);
        }
        int mmax = *max_element(score.begin(), score.end());
        int mmin = *min_element(score.begin(), score.end());
        if((scores[j][j] <= mmax) && (scores[j][j] >= mmin))
            score.push_back(scores[j][j]);
        int m = score.size();
        int sum=0;
        for(int s=0; s<m; s++)
            sum += score[s];
        sum /= m;
        printf("%d\n",sum);
        if(90 <= sum) answer += 'A';
        else if(80 <= sum) answer += 'B';
        else if(70 <= sum) answer += 'C';
        else if(50 <= sum) answer += 'D';
        else answer += 'F';
    }
    return answer;
}

string solution2(vector<vector<int> > scores){
    string answer = "";
    int size = scores.size();
    priority_queue<int> maxh;
    priority_queue<int, vector<int>, greater<int> > minh;

    for(int j=0; j<size; j++){

        for(int i=0; i<size; i++){
            if(i == j) continue;
            maxh.push(scores[i][j]);
            minh.push(scores[i][j]);
        }
    
        if((scores[j][j] <= maxh.top()) && (scores[j][j] >= minh.top())){
            maxh.push(scores[j][j]);
            minh.push(scores[j][j]);
        }

        int m = maxh.size();
        int sum=0;
        for(int s=0; s<m; s++){
            int elem = maxh.top();
            sum += elem;
            maxh.pop();
            minh.pop();
        }
        sum /= m;
        printf("%d\n",sum);
        if(90 <= sum) answer += 'A';
        else if(80 <= sum) answer += 'B';
        else if(70 <= sum) answer += 'C';
        else if(50 <= sum) answer += 'D';
        else answer += 'F';
    }
    return answer;
}

int main(void){
    int n;
    vector<vector<int> > arr;
    scanf("%d", &n);
    arr.resize(n, vector<int>(n, 0));
    printf("%d x %d\n",arr.size(), arr[0].size());
    for(int i=0; i<arr.size(); i++){
        for(int j=0; j<arr[i].size(); j++){
            int elem;
            scanf(" %d", &elem);
            arr[i][j] = elem;
        }
    }
    for(int i=0; i<arr.size(); i++){
        for(int j=0; j<arr[i].size(); j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------\n");
    string ans = solution2(arr);
    for(char c : ans){
        printf("%c ",c);
    }
    printf("\n");
}