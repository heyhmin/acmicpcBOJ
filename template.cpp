#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <queue> // push pop front back empty size
#include <stack> // push pop top empty size

using namespace std;
int res=987654321, n, m, k;
//              0  up dn lf rt
int xmove[5] = {0, 0, 0, -1, 1};
int ymove[5] = {0, -1, 1, 0, 0};
vector<vector<int>> arr;
vector<vector<int>> rotSet;
vector<int> rotIdx;
pair<int, int> mapInfo[21][21]; // sharkNum, sharkSec
typedef struct{
  int heading;
  int x, y;
  int priority[5][4];
  bool out;
}_shark;
_shark shark[401];
unsigned int position;

void run(int sec, int remain){
  if( remain == 1 ) {
    res = sec - 1;
    return;
  }
  if( sec > 1000 ){
    res = -1;
    return;
  }
  if(position & 4) curScore++; // 100으로 끝나면 true
  position = position << 1; // 왼쪽으로 밀기
  position |= 1; // 켜기
  run(sec + 1, remain);
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

void opCalculator(int opidx, int resTmp){
  if(opidx > (len-1)/2){
    res = max(resTmp, res);
    return;
  }
  if(opidx + 1 < (len+1)/2){
    // 다음 op를 괄호로 계산, 현재 op를 일반 계산, 다다음 op로 넘어감
    int parentheses = calculator(numarr[opidx], numarr[opidx+1], oparr[opidx+1]);
    opCalculator(opidx + 2, calculator(resTmp, parentheses, oparr[opidx]));
  }
  // 현재 op를 일반 계산, 다음 op로 넘어감.
  opCalculator(opidx + 1, calculator(resTmp, numarr[opidx], oparr[opidx]));
}

int main() {
	assert(freopen("input.txt", "r", stdin));
	assert(freopen("output.txt", "w", stdout));
	ios_base::sync_with_stdio(false);

  // 입력
  cin >> n >> m >> k; // n x m -> n rows x m columns
  arr.resize(n+1, vector<int>(m+1, 0));
  vector<int> tmp = {r, c, s};
  rotSet.push_back(tmp);
  rotIdx.push_back(i);
  int sharkNum;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> sharkNum;
      if(sharkNum != 0){
        shark[sharkNum].x = j;
        shark[sharkNum].y = i;
        mapInfo[j][i] = make_pair(sharkNum, k); // input 이후에는 x, y 순서대로
      }
    }
  }
  for(int i = 1; i <= m; i++){
    _shark &tmp = shark[i]; // &를 사용해서 값 바꾸기
    for(int j = 1; j <= 4; j++){
      cin >> tmp.priority[j][0] >> tmp.priority[j][1] >> tmp.priority[j][2] >> tmp.priority[j][3];
    }
  }
  string str; cin >> str;
  char carr[len+1];
  strcpy(carr, str.c_str()); // str -> char array
  numarr[0] = carr[0] - '0'; // char -> int

  // next_permutation(vec.begin(), vec.end());
  // 시작 위치, 끝 위치를 넘겨주면 해당 범위를 기준으로 다음 순열로 정렬한 후 true를 리턴한다.
  do{
    vector<vector<int>> tempv = arr;
    rotate(tempv, 0);
  }while(next_permutation(rotIdx.begin(), rotIdx.end()));
	cout << res << endl;
	return 0;
}
