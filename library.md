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
## 기본
```c++
    #include <iostream> // cout, cin etc ...
    #include <cstdio> // printf, fprintf, fopen etc ...
    using namespace std;
    #include <bits/stdc++.h> // all 
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

## Vector
```c++
    vector<int> v;	// int타입을 요소로 가지는 벡터 v선언
    v.push_back(a)	// 벡터 v의 맨뒤에 a추가
    v.pop_back()	// 벡터 v의 맨뒤 요소 삭제
    v[i]	        // 벡터 v의 i번째 요소 참조
    v[i] = a	    // 벡터 v의 i번째 요소를 a로 변경(에러 가능성 O)
    v.size()	    // 벡터 v의 크기 반환 
    v.begin()	    // v의 첫번째 요소의 주소
    v.end()	        // v의 마지막 요소의 주소
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
    sort(info.begin(), info.end(), cmp);
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