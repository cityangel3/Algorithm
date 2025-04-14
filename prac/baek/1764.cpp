#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<string>
#include<algorithm>
#include<set>

using namespace std;

#define MAX 20;

char name[20];

int main(void){
    int n, m;
    int res=0;
    string name;
    multiset<string> s;
    set<string> ss;

    vector<string> vv;
    vector<string> vs;
    // freopen("input.txt", "r", stdin);

    scanf("%d %d", &n, &m);
    scanf("%*c");
    for(int i=0; i<n; i++){
        getline(cin, name);//, '\n'); // enter problem?
        // printf("%s\n",name.c_str());
        // s.insert(name);
        vv.push_back(name); // O(1)
    }
    sort(vv.begin(), vv.end()); //O(nlogn)
    for(int i=0; i<m; i++){
        getline(cin, name);//, '\n'); // enter problem?
        // printf("%s\n",name.c_str());
        // if(binary_search(s.begin(), s.end(), name)){
        if(binary_search(vv.begin(), vv.end(), name)){
            res++;
            // ss.insert(name);
            vs.push_back(name);
        }
    }
    sort(vs.begin(), vs.end()); //O(nlogn)
    printf("%d\n",res);
    // for(string n : ss){
    for(string n : vs){
        printf("%s\n",n.c_str());
    }
    return 0;
}