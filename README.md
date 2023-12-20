# 게임 프로그래밍 공부 - 1단계 알고리즘 공부   

- [1. 프로젝트 준비(미로 생성 및 오른손의 법칙)](#프로젝트-준비)
  - [1 - 1. 오른손의 법칙](#1-오른손의-법칙)
- [2. 선형 자료 기초](#2-선형자료-기초)
  - [ 2 - 1. 동적 배열 구현](#2-1동적배열-구현하기)


## 1.프로젝트 준비   
*여기서 생성한 미로는 당장은 아니고, 추후 길찾기 알고리즘을 위해 미리 생성*
- ConsoleHelper.h, ConsoleHelper.cpp : 콘솔의 커서 조정 및 색을 입혀주기 위한 클래스로 굳이 외울필요는 없다. 한번 세팅하면 다시 안돌아봄.  
- Board.h, Board.cpp : 길찾기 알고리즘을 위해서 미로를 만들어 줘야하는데, 미로를 만드는 코드들이다. 미로는 Binary Tree 미로생성 알고리즘을 통해 제작한다.  
    - 바이너리 트리 미로 생성:  (x % 2 == 0) || (y % 2 == 0) 을 통해 벽을 설정해주면 대부분이 벽으로 막혀있는데 열려있는 점들을 순회하며 위, 아래로 랜덤하게 길을 뚫어주는것.  
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
![오른손법칙](./GitHubImage/RightHandOnWall.gif)


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
capacity는 배열의 잦은 이주를 방지하기 위해 미리 공간을 선점해 두는 것으로 이전 크기의 * 1.5 를 채택했다.  
그밖에 reserve, size, clear, push_back 등 기존에 있던 vector클래스와 같이 구현했다.  
아래 이미지는 기존에 vector와 구현한 Vector클래스의 비교이다.  
![vector](./GitHubImage/Vector.png)   
#### 2-1.동적배열 구현하기.   
동적배열은 기존에 vector로 구현이 되어있지만, 연습 겸 구현해 보았다.   
구현된 벡터 클래스는 **[여기](./Algorithm/SelfModule/Vector.h)** 를 클릭하면 볼 수 있다.   
capacity는 배열의 잦은 이주를 방지하기 위해 미리 공간을 선점해 두는 것으로 이전 크기의 * 1.5 를 채택했다.  
그밖에 reserve, size, clear, push_back 등 기존에 있던 vector클래스와 같이 구현했다.  
아래 이미지는 기존에 vector와 구현한 Vector클래스의 비교이다.  
![vector](./GitHubImage/Vector)   
#### 2-2. 연결리스트 구현하기.(양방향)  
연결리스트는 기존에 list로 구현이 되어있지만, 연습 겸 구현해 보았다.
구현된 리스트 클래스는 ** [여기](./Algorithm/SelfModule/List.h)** 를 클릭하면 볼 수 있다.  
리스트 내부의 하나하나 요소를 구성하는 Node와,  
추후 배회할때 필요한 Iterator,  
Node들을 전체로 포함하는 List 클래스들로 구성을 했다.
아래 이미지는 기존에 list와 구현한 List클래스의 비교이다.  
![List](./GitHubImage/List.png)


## 햇갈릴 만한것 Review
### 1. (전위/후위)연산자 오버로딩. a++, ++a  
연산자 오버로딩에서 ++의 위치에 따라 오버로딩하는 함수의 모양이 달라진다.  아래는 연결리스트를 구현하던 코드의 일부이다.  
```cpp
++it
Iterator& operator--()
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
