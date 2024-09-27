# C++ library 
## Tip
1. 전역변수 혹은 동적할당 사용 (stack 메모리 많이 안줘서.)
    * 메모리는 500*500이 필요하다면 510*510으로 선언
2. 변수 초기화
    * 수십개의 케이스를 다뤄야 하는 문제들이 나와서 변수 초기화 문제가 생기기 쉬워요.개인적으로 삼성 문제 풀땐 항상 void init() 함수 만들어서 이 함수에서 모든 전역변수 초기화하는 코드를 작성.
3. freopen
    * freopen으로 입력시간 줄이고, 출력문도 편하게 볼 수 있으니 꼭 사용법 익혀갑시다.
```c++
    freopen("input.txt", "r", stdin);  
    freopen("output.txt", "w", stdout);  
```
## 실수 조심
1. index 자료구조에 사용될 때 1부터인지 0부터인지에 따라서 초기화 및 for문 접근 주의
2. ++ 보다는 +1 로 명시적으로 사용하기
## 기본
```c++
    #include <iostream> // cout, cin etc ...
    #include <cstdio> // printf, fprintf, fopen etc ...
    using namespace std;
    #include <bits/stdc++.h> // all 
    #include <cstring> // memeset, memcpy
    using pp = pair<int, int> // using 을 통해 type alias 가능
    abs -> <cstdlib>
    fabs -> <cmath>
    min, max -> <algorithm>
```
```c++
    /* c++, c 표준 스트림 동기화 끄기 */
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    /* 그냥 cstdio로 printf, scanf 쓰는게 더 빠름 */
    printf("%s\n",line.c_str()); // string 도 이게 더 빠름
    string line;
    getline(cin,line,'1'); // 1입력까지 받음
    getline(cin,line);
    cout << line << '\n';
```
```c++
    // 초기화 방식
    int x(0);		// 초기치를 괄호로 감싼 예
    int y = 0;		// 초기치를 "=" 다음에 지정한 예
    int z{ 0 };		// 초기치를 중괄호로 감싼 예
    int t = { 0 };		// "="와 중괄호로 초기치를 지정한 예
    // 중괄호를 쓰면 초기화 모두 통일 가능
    int a{ 0 };
    Knight k{ k2 };
    vector<int> v{ 1, 2, 3, 4 };
    // 하지만 오버플로우 방지 기능으로, 
    // 아래처럼 casting에서 다른 "=,()" 초기화처럼 자유롭지 않다.
    int x = 0;
    double y{ x }; //에러. 반대도.
```
## 할당
```c++
    int count = 10;
    int * arr = new int[count];
    int * arr = new int[5] {0,0,0,0,0}; // 초기화 동시에
    delete 없앨메모리포인터;   // 포인터
    delete []없앨메모리포인터; // 배열
    /* Vector 사용 */
    /* 1차원 */
	cin >> N; //테스트케이스 N
	vector<int> v; //벡터 정의
	for (int i = 0; i < N; i++) { //벡터에 입력값 추가
    	int a;
        cin>>a;
		v.push_back(a);
	}
    /* 2차원 */
    vector<vector<int> > v2; //2차원벡터 정의
    vector<int> v;
    // m x n
    for (int i = 0; i < n; i++)  //2차원벡터에 추가할 1차원벡터
		v.push_back(0);
	for (int i = 0; i < m; i++)  //2차원벡터에 벡터 추가
		v2.push_back(v);
	/* Pair */
    vector<pair<int, int>> v; //pair vector 정의
	for (int i = 0; i < N; i++)  //pair형식으로 요소 추가
		v.push_back(make_pair(i,i));
	for (int i = 0; i < N; i++)  //pair형식으로 요소 출력
		cout << v[i].first << " " << v[i].second; 
	

```
## 입출력
```c++
    /* 길이 알고 있을 때, 한글자씩 받기 */
    int a[7];
    for(int i=0;i<7;i++)
	    scanf("%1d",&a[i]); 
    /* 길이 모를 대, 한글자씩 받기 */
    string a;
	cin >> a;
	for (int i = 0; i < a.size(); i++) {
		temp += a[i] - '0'; //string -> 정수값으로
	}
    /* 공백포함 입력받기 */
    string name;
    getline(cin,name);
    /* 띄어쓰기 기준으로 입력 - 길이 알 때 */
    for (int i = 0; i < 100; i++) 
        scanf(" %d", &a); //앞에 공백 넣기 ~ 개행문자 무시
    /* 띄어쓰기 기준으로 입력 - 길이 모를 때 */
    string a;
    getline(cin, a); //버퍼로부터 '\n'을 기준으로 끊어서 읽어들여 str에 저장
                     // ‘\n’을 버퍼에 남기지 않는다. 그냥 무시할뿐!
    //cin.getline(str, size,char delim) delim 디폴트는 '\n'
    
    char* str_buff = new char[1000]; 
    strcpy(str_buff, a.c_str());
    char* tok = strtok(str_buff, " "); 
    //tok을 살피며 끝이 아니라면 계속 진행한다.
    while (tok != nullptr) {
    
    	//str_arr에 값을 추가한다.
        str_arr[str_cnt++] = string(tok); 
        
        //띄어쓰기를 기준으로 나누어 다음 문자를 tok에 저장한다.
        tok = strtok(nullptr, " ");
    }
```
## 자료구조
* pair, vector, queue, stack, set, map, priority queue
    * 빠른 정렬 : priority queue(max,min heap) 떠올리자!

    * DFS : vector = stack & BFS = queue
    ``` 
        단순히 모든 정점을 방문하는 것이 중요한 문제의 경우 DFS, BFS 두 가지 방법 중 어느 것을 사용하셔도 상관없다.
        => 단, dfs에서 return을 잘못 쓸 경우 전체 순회 안될 수 있으니 주의.
            => 전체 순회하려면 return 하면 안됨.
        * 경로의 특징을 저장해둬야 하는 문제, 
        1. 예를 들면 각 정점에 숫자가 적혀있고 a부터 b까지 가는 경로를 구하는데 
        경로에 같은 숫자가 있으면 안 된다는 문제 등, 각각의 경로마다 특징을 저장해둬야 할 때는 DFS를 사용한다. 
        2. 검색 대상 그래프가 정말 크다면 DFS를 고려
        3. 메모리 초과 우려시 dfs 사용
        (BFS는 경로의 특징을 가지지 못함)

        * 최단거리 구해야 하는 문제
        1. 미로 찾기 등 최단거리를 구해야 할 경우, BFS가 유리하다.
        2. 검색대상의 규모가 크지 않고, 검색 시작 지점으로부터 원하는 대상이 별로 멀지 않다면 BFS를 고려하는 것이 좋다.
    ```
## Queue
```c++
        // 최근에는
        typedef struct{int x,y,z}st;
        queue<st> q;
        q.push({a,b,c});
        st c = q.pop();
        // 이런식으로 했습니다 => tuple과 구조체 비슷.
        // 더 편한거 쓰면 될듯.

        //그런데 아래방식이 가능합니다
        queue<tuple<int,int,int>> q; 
        //tuple<string,float,char> 도 가능
        q.push(a,b,c);
        auto c = q.pop();
        get<0>(c);
        get<1>(c);
        get<2>(c)

        //#include<utility>
        //pair를 tuple과 함께 사용하게 될 경우에는 반드시 include를 해줘야 한다.

        //#include<tuple>
        // tuple을 사용할 수도 있다고 한다. 
        queue<tuple<int,int,int>> q;
        // 둘다가능.
        q.push(a,b,c);
        q.push({a,b,c});
        int a, b, c;
        tie(a, b, c) = q.front();
```
## Priority Queue
```c++
        priority_queue<int> max_heap;
        priority_queue<int, vector<int>, greater<int> > min_heap;
        priority_queue<pair<int , int>> pq;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        q = queue<int>() // queue 초기화.
        queue<int, vector<int>> q4(v); // vector 이용해 초기화
        // vector의 clear가 queue에는 없기때문에 아래처럼.
        q = queue<int>(); // 재선언
```
## Deque
```c++
    dq.front();
    dq.push_front();
    dq.pop_front();
    dq.back();
    dq.push_back();
    dq.pop_back();
    dq.resize();
    dq.swap(deque);
    dq.insert(1,2,3); // 1번째 위치에 2개의 3 삽입
    dq.insert(3,4); // 3번째 위치에 4 삽입
    dq.erase(iter);
    dq.clear();
```
## Vector
```c++
    //emplace_back() ->코테용으론 이게 맞다.
    //C++11 에서 도입된 함수, 
    //emplace_back은 벡터에 메모리 할당을 하는 동시에 값을 삽입하는 것이 가능.
    vt.emplace_back("abc",1,234);
    vector<vector<int>> vec;
    vec.push_back(2); //불가능
    vec.emplace_back(2); //가능
    // 2차원 벡터에서 행의 길이는 불변, 열의 길이는 가변일때 emplace_back 가능.
    vec.emplace_back({1,0}); //불가능
    // 단, 위처럼 배열 자체를 넣어주는건 불가능
```
```c++
    vector<int> v;	// int타입을 요소로 가지는 벡터 v선언
    v.push_back(a)	// 벡터 v의 맨뒤에 a추가
    v.pop_back()	// 벡터 v의 맨뒤 요소 삭제
    v[i]	        // 벡터 v의 i번째 요소 참조
    v[i] = a	    // 벡터 v의 i번째 요소를 a로 변경(에러 가능성 O)
    v.size()	    // 벡터 v의 크기 반환 
    v.begin()	    // v의 첫번째 요소의 주소
    v.end()	        // v의 마지막 요소의 주소
    v.erase(v.begin() + i); // 특정 원소 제거
    vector<vector<int> > arr(n, vector<int>(k, 0)); //n by k 0 으로 초기화.
    vector<pair<int, int> > info; // pair 활용

    v.reserve(); v.resize(); // 해두고 
    int* arr = v.data(); // 읽어서 접근하는게 더 빠름
    // vector 활용 찾기
        int num = 3;
        auto it = find(v.begin(), v.end(), num);
        if (it == v.end()) 
            cout << num << "은 찾을 수 없습니다.\n";
        else 
            cout << num << "는 존재하며 인덱스는 " << it - v.begin() << " 입니다.\n";

    // 정렬
    bool cmp(pair<int, int> a, pair<int, int> b){
    // return a.second < b.second; // 오름차순
    return a.second > b.second; // 내림차순
    }
    sort(info.begin(), info.end()); // 오름차순
    sort(info.begin(), info.end(), greater<>()); // 내림차순 정렬
    sort(info.begin(), info.end(), cmp); // 사용자 정의
```
## String
```c++
    #include <string>
    using namespace std;
    string s;
    getline
    // string 찾기
    if(str.find("asdf") == string::npos) {
    // cant find
    }
```
## Map
```typescript
    C++에서 map 타입을 사용할 때 보통 키는 String을 사용한다. (int쓸거면 array를 쓰면되니까)
    
    map<string, vector<x>> mapdata;
        로 사용하면 하나의 key 안에 여러개 데이터를 담을 수 있다.
        예를들면
    map<string, vector<int>> score;
    scorel"jwy"] = vector<int>{100,99,98};
    scorel"hgd"] = vector<int>{0,0}
        이런식으로 사용이 가능.
        (부를때는 score"iwy"1[2]을 호출하면 98이 나옴)
        
        만약 여러타입을 value로 가질 수 있도록 하려면 구조체를 사용하거나 tuple을 사용한다.
    map<string, tuple<int,double,string> score:로 선언된다면
    score["jwy"] = make_tuple(100, 90.5, "FA"): 등으로 입력 가능하다.
```