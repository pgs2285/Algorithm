# 게임 프로그래밍 공부 - 1단계 알고리즘 공부

- [1. 프로젝트 준비(미로 생성 및 오른손의 법칙)](#프로젝트-준비)
  - [1 - 1. 오른손의 법칙](#1-오른손의-법칙)
- [2. 선형 자료 기초](#2-선형자료-기초)
  - [ 2 - 1. 동적 배열 구현](#2-1동적배열-구현하기)
  - [ 2 - 2. 양방향 연결리스트 구현](#2-2-연결리스트-구현하기양방향)
  - [ 2 - 3. 스택 구현](#2-3-스택-구현하기)
  - [ 2 - 4. 큐 구현](#2-4-큐-구현하기)
  - [ 2 - 5. 오른손의 법칙 개선하기](#2-5-오른손의-법칙-개선하기)
- [3.그래프의 기초](#그래프-기초)
  - [ 3 - 1. 그래프 이론 및 코드로 구현하는법 알아보기](#그래프-기초)  
    - -[ 3 - 1 - a. 그래프 구현 {통째로 구현하기}](#통째로-관리하는-방법)  
    - -[ 3 - 1 - b. 그래프 구현 {연결된 목록을 따로 관리하기}](#연결된-목록을-따로-관리하는-방법)  
    - -[ 3 - 1 - c. 그래프 구현 {행렬을 이용해 관리하기}](#행렬을-이용해-관리하는-방법)  
    - -[ 3 - 1 - d. 그래프 구현 {가중치가 있는그래프}](#가중치가-있는그래프)  
  - [ 3 - 2. DFS(깊이 우선 탐색, Depth First Search) 구현하기](#3-2-dfs깊이-우선-탐색-depth-first-search-구현하기)
  - [ 3 - 3. BFS(너비 우선 탐색, Breath First Search) 구현하기](#3-3-bfs너비-우선-탐색-breath-first-search-구현하기)
  - [ 3 - 4. BFS를 이용한 길찾기](#3-4-bfs를-이용한-길찾기-구현)  
  - [ 3 - 5. 다익스트라 구현하기](#3-5-다익스트라-알고리즘)
- [4.힙과 우선순위 큐](#4힙과-우선순위-큐)
  - [4 -1 트리 기초](#4--1-트리-기초)
    - [4-1-2 트리생성](#4-1-1-트리-생성)
    - [4-2-2 트리호출](#4-1-2-트리-출력)
  - [4 - 3. 우선순위 큐 구하기](#4-3-우선순위-큐-구현하기)
  - [4 - 4. A* 구현하기](#4-4-A*-구현하기)

-[햇갈릴 만한것 Review](#햇갈릴-만한것-review)

- [1. 전위/후위 연산자 오버로딩](#1-전위후위연산자-오버로딩)
- [2. vector의 resize vs reserve](#2-vector의-resize-vs-reserve)
- [3. shared_ptr](#3-shared_ptr)

## 1.프로젝트 준비

_여기서 생성한 미로는 당장은 아니고, 추후 길찾기 알고리즘을 위해 미리 생성_

- ConsoleHelper.h, ConsoleHelper.cpp : 콘솔의 커서 조정 및 색을 입혀주기 위한 클래스로 굳이 외울필요는 없다. 한번 세팅하면 다시 안돌아봄.

- Board.h, Board.cpp : 길찾기 알고리즘을 위해서 미로를 만들어 줘야하는데, 미로를 만드는 코드들이다. 미로는 Binary Tree 미로생성 알고리즘을 통해 제작한다.
  
  - 바이너리 트리 미로 생성: (x % 2 == 0) || (y % 2 == 0) 을 통해 벽을 설정해주면 대부분이 벽으로 막혀있는데 열려있는 점들을 순회하며 위, 아래로 랜덤하게 길을 뚫어주는것.

- pch.h : 미리 컴파일된 헤더로, 컴파일 시간을 단축하기 위해서 사용한다. 추후 좌표값 계산을 편하게 하기위한 연산자 오버라이딩도 구현되어있다.

- Player.h, Player.cpp : 캐릭터 이동관련. 실질적인 길찾기 알고리즘은 player클래스의 Update문에서 담당할것이다.
  
  ### 1. 오른손의 법칙
  
  알고리즘이라 하긴 뭐하지만 미로탈출중 가장 대표적인 방법이다.

로직

1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인한다
   1-1. 참일시, 오른쪽 방향으로 90도 회전 후 한 보전진
   1-2. 거짓일시 2번으로.
2. 현재 바라보는 방향 기준으로 전진할 수 있는지 확인.
   2-1. 참일시 앞으로 한보 전진.
   2-2. 거짓일시 3번으로.
3. 왼쪽으로 90도 회전,
4. 이후 무한 루프.

구현된 코드는 [./Maze/Player.cpp](./Maze/Player.cpp) 의 RightHandOnWall함수에서 확인 할 수 있으며 결과는 다음과 같다.  
<img src="./GitHubImage/RightHandOnWall.gif" title="" alt="오른손법칙" data-align="center">

## 2. 선형자료 기초

Chapter2 에서 구현한 대부분의 자료구조는 [./Algorithm/Selfmodule](./Algorithm/Selfmodule)에 저장된다.  
구현에만 집중하고 헤더파일 분리는 나중에 시간나면 제대루,,,

### 특징

대표적으로 배열, 동적배열, 연결리스트가 있음
대표적인 특징만 알아보자면

- 배열 : 배열은 정해진 크기에서 축소, 확대할 수 없음. 연속되어있다는 것은 장점이 될수 있지만, 아무래도 확대, 축소가 불가능한것은 단점이 된다.

- 동적 배열 : 동적배열은 사용할 배열의 크기를 유동적으로 조절이 가능하다. 연속된 방을 사용하는것은 똑같지만, 가득 찰경우 아예 다른 주소에서 연속된 값을 가져온다.
  또한 가득 차서 이동시 capacity에 여유분을 준다. (보통 capacity + capacity / 2) 로 추후 가면 안정적으로 사용 가능. 중간 삽입 삭제시 이전에 값을 당겨야하는 경우가 있어,
  중간 삽입 삭제에 비효율 적이다.

- 연결 리스트 : 연속되지 않은 형태, 한 노드가 다른노드를 지정하는 식이라 간 삽입 삭제에 이점을 보이지만 임의접근 Random Access가 불가능하다.
  
  #### 2-1.동적배열 구현하기.
  
  동적배열은 기존에 vector로 구현이 되어있지만, 연습 겸 구현해 보았다.  
  구현된 벡터 클래스는 **[여기](./Algorithm/SelfModule/Vector.h)** 를 클릭하면 볼 수 있다.  
  capacity는 배열의 잦은 이주를 방지하기 위해 미리 공간을 선점해 두는 것으로 이전 크기의 \* 1.5 를 채택했다.  
  그밖에 reserve, size, clear, push_back 등 기존에 있던 vector클래스와 같이 구현했다.  
  아래 이미지는 기존에 vector와 구현한 Vector클래스의 비교이다.  
  ![vector](./GitHubImage/Vector.png)

#### 2-2. 연결리스트 구현하기.(양방향)

연결리스트는 기존에 list로 구현이 되어있지만, 연습 겸 구현해 보았다.
구현된 리스트 클래스는 **[여기](./Algorithm/SelfModule/List.h)** 를 클릭하면 볼 수 있다.  
리스트 내부의 하나하나 요소를 구성하는 Node와,  
추후 배회할때 필요한 Iterator,  
Node들을 전체로 포함하는 List 클래스들로 구성을 했다.
아래 이미지는 기존에 list와 구현한 List클래스의 비교이다.  
![List](./GitHubImage/List.png)

#### 2-3. 스택 구현하기

스택은 LIFO(Last In First Out) 형태의 자료구조로, 웹페이지 뒤로가기, ctrl+z 등과 같이 여러군대에 쓰이는 자료구조이다.  
구현된 스택 클래스는 **[여기](./Algorithm/SelfModule/Stack.h)** 를 클릭하면 볼 수 있다.  
사실 스택은 여러가지 형태로 구현할 수 있다. 배열, 동적배열, 연결리스트 등 다양하지만 여기선 Node에 전에 들어온 주소값을 넣어 관리하는  
연결리스트 형태로 구현하였다.  
아래 이미지는 기존 스택과 구현한 Stack클래스의 비교이다.
![Stack](./GitHubImage/Stack.png)

#### 2-4. 큐 구현하기

큐는 FIFO(First In First Out), 즉 선입선출의 방식으로 작동한다. Stack보다 활용도가 높은 알고리즘으로 대표적으로 대기열에서 사용한다.  
단방향인 그냥 Queue 와 양방향인 deque 가 있다. 일단 여기선 단방향인 queue를 구현한다.  
구현된 큐 클래스는 **[여기](./Algorithm/SelfModule/Queue.h)** 를 클릭하면 볼 수 있다.
큐 또한 여러가지 방법으로 구현 가능하지만, 배열을 이용해 순환구조를 만들어 구현해본다. 즉 시작과 끝을 알고있어 index를 조정해가며 구현하는 queue이다.  
기존에 동적배열은 이미 구현해봤으므로, vector함수를 사용해 구현했다. 이런식으로 구현하면 동적배열의 단점이었던 중간 삽입삭제 시 O(n)의 시간복잡도를 갖는다는
문제를 해결 할 수 있다.  
아래 이미지는 기존 큐와 구현한 Queue클래스의 비교이다.  
<img src="./GitHubImage/Queue.png" title="" alt="Stack" data-align="center">

#### 2-5. 오른손의 법칙 개선하기

위에서 배운 stack으로 오른손의 법칙을 개선할 수 있다. 기존에 진행 할 경로를 \_path에 저장해 두었는데, 이를 순회하며 반복되는 경로가 있을시
pop을 해주면 결과적으로는 바로 출구쪽으로 직행하게 될것이다.개선된 코드는 **[여기](./Maze/Player.cpp)**의 RightHandOnWall함수에서 볼 수 있다.

```cpp
//...(생략)
stack<Pos> s;
for (int i = 0; i < _path.size() - 1; i++)
{
    if (s.empty() == false && s.top() == _path[i + 1])
    {
        s.pop();
    }
    else s.push(_path[i]);
}
```

이렇게 pop 될떄마다 stack의 top이 _path[i+1]와 맞물려(즉 현재 기준으로 전후이니, pop될시 이 _path[i-n] & _path[i+n] 끼리 비교하는것과 다름없다.) 겹친경로는 다 사라지게 된다.
결과는 아래와 같다. 확실히 개선이 된것을 볼 수 있다.  
<img src="./GitHubImage/RightHandOnWallRevise.gif" title="" alt="revise" data-align="center">

## 그래프 기초

### 3 - 1. 그래프 특징 및 구현

그래프는 현실 세계의 사물이나 추상적인 개념간의 연결관계를 표현한다.

- 정점(Vertex) : 데이터를 표현(사물, 개념 등)

- 간선(Edge) : 정점들을 연결하는데 사용.

도로망, 소셜 네트워크 관계도, 지하철 노선도 등에서 사용한다.

그래프에는 각 간선에 가중치를 부여한 **가중치 그래프**, 간선에 방향이 있는 **방향그래프** 가 있다.

다음 그래프를 코드로 4가지 방법으로 구현해보자.(방향그래프)

1. 통째로 관리
2. 연결된 목록을 따로 관리
3. 행렬을 이용해 관리
4. 가중치가 있는 그래프

<img src="./GitHubImage/question1.png" title="" alt="Graph" data-align="center">

##### 통째로 관리하는 방법

```cpp
struct Vertex
{
    vector<Vectex*> edges;
    int data;
}
vector<Vertex> v;
v.resize(6);
v[0].edges.push_back(&v[1])
v[0].edges.push_back(&v[3])
v[1].edges.push_back(&v[0])
v[1].edges.push_back(&v[2])
v[1].edges.push_back(&v[3])
v[3].edges.push_back(&v[4])
v[5].edges.push_back(&v[4])
```

##### 연결된 목록을 따로 관리하는 방법

```cpp
vector<vector<int>> adjacent(6);
adjacent[0] = {1,3};
adjacent[1] = {1,3};
adjacent[3] = {4};
adjacent[5] = {4};
```

간선들이 비교적 적은 문제에서 많이 사용하는 방법이다.

##### 행렬을 이용해 관리하는 방법

adjacant[from][to] 로 읽으면 된다. 즉 adjacent[0][1] 면 0 -> 1

```cpp
vector<vector<bool>> adjacent(6, vector<bool>(6,false));
adjacent[0][1] = true;
adjacent[0][3] = true;
adjacent[1][0] = true;
adjacent[1][2] = true;
adjacent[1][3] = true;
adjacent[3][4] = true;
adjacent[5][4] = true;
```

행렬을 이용한 2차원 그래프 표현이다. 메모리 소모가 심하지만, 빠른 접근이 가능하다.(간선이 많은경우 이점이 있다.)

##### 가중치가 있는그래프

크게 다르지 않다. 당장에 2번 방식에 int 대신 pair을 써서 표현해도 되고(adjacent[0] = {std::pair(1,50)}같이), 3번에선 bool대신 int를 받아서 써도된다.  
간단하게 아래같이도 표현가능하다.

```cpp
vector<vector<int>> adjacent =
{
  vector<int> {-1,10,-1,50,-1,-1},
  vector<int> {15, -1, 5, 10, -1, -1},
  .......
}
```

같이 표현도 가능하다.  

### 3-2. DFS(깊이 우선 탐색, Depth First Search) 구현하기

입구에서 깊은것부터 탐색하는 방법이다.   
구현한 DFS 해더파일 선언부는 **[여기(DFS.h)](./Algorithm/SelfModule/DFS.h)**를 클릭하면 볼 수 있고,   
DFS의 구현부는 **[여기(DFS.cpp)](/Algorithm/SelfModule/DFS.cpp)**를 클릭하면 볼 수 있다.  
연결된 목록을 따로 adjacent에서 관리해 재귀함수로 구현하였다.  
DFS 헤더파일 선언 후 **dfs.visit(시작노드)**를 지정하면 해당 노드부터 DFS를 진행하게 제작했다.  
만약 노드가 동떨어져 있으면(시작점에서 타고가도 연결되어 있지 않으면) DfsEtc를 호출하면 나머지 노드들을 찾아서 DFS를 진행한다.  
결과는 아래와 같다.   
<img src="./GitHubImage/DFS-1.png" width="40%" height="30%" title="px(픽셀) 크기 설정" alt="dfs"></img>  

### 3-3. BFS(너비 우선 탐색, Breath First Search) 구현하기

DFS와는 다르게 가까운 노드부터 방문한다는게 특징이다.  
구현한 DFS 해더파일 선언부는 **[여기(BFS.h)](./Algorithm/SelfModule/BFS.h)**를 클릭하면 볼 수 있고,   
DFS의 구현부는 **[여기(BFS.cpp)](/Algorithm/SelfModule/BFS.cpp)**를 클릭하면 볼 수 있다.  
연결된 정점들은 무한루프를 통해서 탐색한다.  
BFS 헤더파일 선언후  **bfs.visit(시작노드)**를 지정하면 해당 노드부터 BFS를 진행하게 제작했다.  
만약 노드가 동떨어져 있으면(시작점에서 타고가도 연결되어 있지 않으면) discoverAll를 호출하면 나머지 노드들을 찾아서 BFS를 진행한다.  
결과는 아래와 같다.  
<img title="px(픽셀) 크기 설정" src="./GitHubImage/bfs.png" alt="dfs" width="" height="" data-align="center">  

### 3-4. BFS를 이용한 길찾기 구현.

위에서 했던 우수법(오른손의 법칙)은 길을 찾긴 하진만 최단경로를 보장하지 못할 뿐더러, 미로가 복잡할 경우 길을 찾지 못하는 경우도 있다.  
BFS를 사용하면 최단경로가 보장이 된다. 또한 방금 학습했던 BFS는 인접노드와, 정점들의 정보를 따로 입력해줘야했지만, 미로에서는 맵의 구조를 안다면 그래프로 표현이 가능하다.  
구현 알고리즘은 다음과 같다.   

>     bfs
>     1. 처음 방문한 곳을 큐에 넣어주고 발견 check,
>     2. 무한 루프를 돌면서 순회한다. 상하좌우 갈 수 있나 체크 
>     2-1. 갈 수 없으면 continue.
>     2-2. 이미 발견한 지역이면 continue.
>     3. bfs순회 후 도착했으면 break 하고 parent를 역참조 하여 간다.  
> 
> 구현된 코드는 [./Maze/Player.cpp](./Maze/Player.cpp) 의 Bfs함수에서 확인 할 수 있으며 결과는 다음과 같다.  
> <img title="px(픽셀) 크기 설정" src="./GitHubImage/bfsPathFinding.gif" alt="bfs" width="" height="" data-align="center">   

### 3-5. 다익스트라 알고리즘

위에서 BFS는 길찾기를 사용할때 각 간선들이 동일한 비용을 갖고 있다고 가정해 만드는데 큰 문제는 없었다.  
아래 이미지처럼 간선마다 비용(가중치, 거리)들이 붙기 시작한다면 다른 알고리즘을 알아봐야한다.  
<img title="px(픽셀) 크기 설정" src="./GitHubImage/costGraph.png" alt="dfs" width="" height="" data-align="center">  
이 이미지에서 가장 0번에서 4번까지 가는 가장 저코스트의 경로는 0->1->3->4 이다.  

1. 출발노드 설정후 최소비용 저장.
2. 이동하고 그 다음 노드까지 이동하는 비용과, 이전에 있던 cost값 비교 후 작은값을 넣어준다.(갱신)
3. 반복
   위와같은 순서대로 구현해줄 것이다.   

구현한 다익스트라 해더파일 선언부는 **[여기(Dijkstra.h)](./Algorithm/SelfModule/Dijkstra.h)**를 클릭하면 볼 수 있고,  
다익스트라의 구현부는 **[여기(Dijkstra.cpp)](/Algorithm/SelfModule/Dijkstra.cpp)**를 클릭하면 볼 수 있다.  
구현된 결과는 다음과 같다.  
<img title="px(픽셀) 크기 설정" src="./GitHubImage/dijkstra.png" alt="dfs" data-align="center" width="411">

## 4.힙과 우선순위 큐

### 4 -1 트리 기초

트리란 계층적 구조를 갖는 데이터를 표현하기 위한 자료구조이다

- 노드(Node): 데이터를 표현

- 간선(Edge): 노드의 계층구조를 표현하기 위해 사용

#### 4-1-1 트리 생성

트리는 아래와 같이 생성 할 수 있다.

```cpp
using NodeRef = std::shared_ptr<struct Node>;
struct Node
{
    Node(const string& data) : data(data) {}

    string data;
    vector<NodeRef> children;
};

NodeRef CreateTree()
{
    NodeRef root = make_shared<Node>("루트");
    {
        NodeRef node = make_shared<Node>("요소 1");
        root->children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("리프1");
            node->children.push_back(leaf);
        }
....(생략)
}
```

#### 4-1-2 트리 출력

호출은 재귀함수를 이용하면 된다.   

```cpp
void PrintTree(NodeRef root, int depth)
{
    for (int i = 0; i < depth; i++) cout << "-";
    cout << root->data << endl;
    for (NodeRef& child : root->children)
        PrintTree(child,depth + 1);
}
```

Tree에 대한 예시코드는 [여기(TreeExam.cpp)](./Algorithm/SelfModule/TreeExam.cpp)를 클릭하면 되고, 결과는 아래같이 나온다.  

<img title="px(픽셀) 크기 설정" src="./GitHubImage/Tree.png" alt="dfs" data-align="center" width="395">  

### 4-2 힙트리 이론

#### 이진트리(이진검색트리)란?

이진트리는 각 노드가 최대 두개의 자식을 가지는 트리이다.  
이진검색트리는 왼쪽은 현재값보다 작고, 오른쪽은 현재값보다 무조건 큰 트리의 구조를 의미한다. 이진트리를 효율적으로 구현하기 위해서는 이진트리의 균형을 맞추어주어야 하는데, 이를위해 AVL,Red-Black을 사용한다.  

#### 힙트리 란?

힙트리는 완전이진트리의 일종으로 우선순위 큐를 구현하기 위한 트리이다. 다만 느슨한 정렬을 이루게된다.(상위노드가 하위노드보다 크다는 정도만)힙트리는 다음과 같은 법칙을 따른다.  

- [부모 노드]가 가진값은 항상 [자식노드] 보다 크다.

- 노드의 개수를 알면 트리 구조는 무조건 확정할 수 있다. (마지막 레벨을 제외한 모든 레벨은 채워져 있어야한다. 채울때는 왼쪽부터 채워야한다.) 이는 배열을 이용해서 힙 구조를 바로 표현할 수 있다는 것을 의미한다.  
  (루트는 A[0], i번 노드의 왼쪽자식은 [(2*i) + 1], i번 노드의 오른쪽 자식은 [(2*i) + 2], i 번 노드의 부모는  [(i-1)/2] 이다.)    



### 4-3 우선순위 큐 구현하기.

우선순위 큐는 template 형태로 구현했으며 총 3개의 인자까지 받을 수 있다.  
Priority_queue<자료형, Container, Predicate> 형식으로 넣어줄 수 있으며 Predicate는 정렬방식을 넣어준다 (std::greater, std::less)  
간단하게 알고리즘을 설명하자면 push할땐 맨 밑에 넣어주고 (i - 1) / 2 와 크기를 계속비교해주고 Predicate 조건에 맞으면 멈춘다.
pop은 A[0]를 삭제하고 끝노드를 올린후, 좌측과비교, 우측과 비교후 Predicate조건에 맞으면 멈춘다.
Priority_queue 에 대한 예시코드는 [여기(Priority_queue)](./Algorithm/SelfModule/Priority_queue.h)를 클릭하면 되고, 결과는 아래같이 나온다.  
<img title="px(픽셀) 크기 설정" src="./GitHubImage/priority_queue.png" alt="pq" data-align="center" width="395">      

### 4-4 A* 알고리즘 구현하기

A*알고리즘은 최종점수(F)를 기준으로 가장빠른 경로를 찾는 알고리즘이다.   

**F=G+H** 를 기반으로 최단거리를 찾는데, **G** 는 **시작점에서 해당좌표까지 이동하는데 드는 비용**이고, **H**는 **목적지에 얼마나 가까운지 나타내는 것이다**  

즉 보통 F값이  작을수록 좋은것이며, 이를 구현하기 위해 priority_queue를 사용한다(보통predicate를 greater로 둬서 오름차순으로 정렬).   이를 제외하면 전체적인 알고리즘은 다익스트라와 똑같다. 구현한 코드는 [여기(Player.cpp)](./Maze/Player.cpp) 에 AStar() ,함수에 있으며 구현 결과는 아래와 같다  

![dfs](./GitHubImage/AStar.gif "px(픽셀) 크기 설정")

### 햇갈릴 만한것 Review

### 1. (전위/후위)연산자 오버로딩.

연산자 오버로딩에서 ++의 위치에 따라 오버로딩하는 함수의 모양이 달라진다. 아래는 연결리스트를 구현하던 코드의 일부이다.

```cpp
++it
Iterator operator--()
{
    _node = _node->_prev;
    return *this;
}
// it ++
Iterator& operator--(int)
{
    _node = _node->_prev;
    return *this;
}
```

이런식으로 참조기호와 매개변수에 구분을 두어 전위와 후위연산자를 구분한다.

### 2. vector의 resize vs reserve

같은 기능을 하는 함수는 아니지만, 초기 배열 크기를 할당할때 두가지 모두 사용해도 되므로, 그 상황에서 차이점을 서술한다.  
resize는 할당후 초기화 한다. 즉 size를 호출했을때 변경 후 사이즈가 출력되고, []로 바로 접근할 수도 있다.
reserve는 메모리에 할당만 하고 초기화는 하지 않는다. 즉 capacity()를 호출 하면 크기를 볼 순 있지만, size()호출시 이전과 같은값이 호출될것이다.  
크기를 미리 할당한다는 면에서만 비추어 보면 reserve가 resize보다 빠를수 밖에 없다.  

### 3. shared_ptr

c++ 11에서 추가된 스마트포인터 클래스중 하나이다.

포인터를 더 사용하지 않는경우 메모리를 자동으로 해제해주는 특징이 있어 memory leak 문제를 방지할 수 있다.

```cpp
std::shared_ptr<int> p1 = new int(); // 컴파일 에러
std::shared_ptr<int> p1 = std::make_shared<int>(); //성공
```

위 예제에서 확인하듯이 shared_ptr객체에 포인터를 바로 대입하면 컴파일시 에러가 발생한다. 왜냐하면 shared_ptr 생성자의 아규먼트는 명시적이여햐 하기떄문이다.
