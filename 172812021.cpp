#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

using namespace std;
int n = 0;
int playerRes[50][9];
int playOrder[9];
int res = 0;
bool isInOrder[9];
unsigned int position = 0;
// 0명 0 / 1루 1 / 2루 2 / 3루 4 /
// 1-2루 3 / 1-3루 5 / 2-3루 6 / 1 2 3루 7 /

void baseball(){
  int curScore = 0;
  int curPlayer = 0;
  int outCount = 0;
  int inCount = 0;
  int now = -1;

  while(inCount < n){
    curPlayer %= 9;
    // 현재 이닝의 해당 순서의 선수의 기록
    now = playerRes[inCount][playOrder[curPlayer++]];
    switch (now) {
      case 0: outCount++; break;
      case 1: if(position & 4) curScore++;
              position = position << 1;
              position |= 1;
              break;
      case 2: if(position & 4) curScore++;
              if(position & 2) curScore++;
              position = position << 2;
              position |= 2;
              break;
      case 3: if(position & 4) curScore++;
              if(position & 2) curScore++;
              if(position & 1) curScore++;
              position = 0;
              position |= 4;
              break;
      case 4: if(position & 4) curScore++;
              if(position & 2) curScore++;
              if(position & 1) curScore++;
              curScore++;
              position = 0;
              break;
      default: cout << "default" << endl;
    }
    if(outCount == 3){
      inCount++; // 이닝 종료;
      outCount = 0; // 아웃 초기화;
      position = 0; // position 초기화
    }
  }

  res = max(curScore, res);
}

void setOrder(int index){
  if(index == 9){
    // 초과, 없는 index
    baseball();
    return;
  }
  if(index == 3) index++; // 4번 타자는 정해짐
  for(int i = 1; i < 9; i++){
    if(isInOrder[i]) continue;
    isInOrder[i] = true; // 같은 번호를 중복 선택하지 않도록 한다.
    // 1 ~ 8의 숫자를 012, 45678 index에 넣는다.
    playOrder[index] = i;
    setOrder(index + 1);
    // 함수 호출 이후에는 원래대로 바꾼다.
    isInOrder[i] = false;
  }
}

int main() {
	// assert(freopen("input.txt", "r", stdin));
	// assert(freopen("output.txt", "w", stdout));
	ios_base::sync_with_stdio(false);

  cin >> n;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < 9; j++){
      cin >> playerRes[i][j];
    }
  }

  playOrder[3] = 0; // 1번 선수는 4번 타자

  setOrder(0);

	cout << res << endl;

	return 0;
}
