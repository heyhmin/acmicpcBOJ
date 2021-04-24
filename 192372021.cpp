#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

using namespace std;
int res, n, m, k;
//              0  up dn lf rt
int xmove[5] = {0, 0, 0, -1, 1};
int ymove[5] = {0, -1, 1, 0, 0};
pair<int, int> mapInfo[21][21]; // sharkNum, sharkSec
typedef struct{
  int heading;
  int x, y;
  int priority[5][4];
  bool out;
}_shark;
_shark shark[401];

void run(int sec, int remain){
  // for(int i = 0; i < n; i++){
  //   for(int j = 0; j < n; j++){
  //     cout << mapInfo[j][i].first << mapInfo[j][i].second << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;

  if( remain == 1 ) {
    res = sec - 1;
    return;
  }
  if( sec > 1000 ){
    res = -1;
    return;
  }

  // 이동, 방향 변경
  for(int i = 1; i <= m; i++){ // sharkNum
    _shark &tmp = shark[i];
    if(tmp.out) continue;
    bool moved = false;
    for(int j = 0; j < 4; j++){ // find empty, heading
      int next = tmp.priority[tmp.heading][j];
      int tx = tmp.x + xmove[next];
      int ty = tmp.y + ymove[next];
      if(tx < 0 || ty < 0 || tx >= n || ty >= n) continue;
      if(mapInfo[tx][ty].first == 0){ // empty
        tmp.heading = next;
        tmp.x = tx;
        tmp.y = ty;
        moved = true;
        break;
      }
    }
    if(!moved){ // all full - find self
      for(int j = 0; j < 4; j++){ // heading
        int next = tmp.priority[tmp.heading][j];
        int tx = tmp.x + xmove[next];
        int ty = tmp.y + ymove[next];
        if(tx < 0 || ty < 0 || tx >= n || ty >= n) continue;
        if(mapInfo[tx][ty].first == i){ // self
          tmp.heading = next;
          tmp.x = tx;
          tmp.y = ty;
          moved = true;
          break;
        }
      }
    }
  }
  // 상어 out
  for(int i = 1; i < m; i++){
    _shark strong = shark[i];
    if(strong.out) continue;
    for(int j = i + 1; j <= m; j++){
      _shark &weak = shark[j];
      if( !weak.out && (strong.x == weak.x) && (strong.y == weak.y) ){
        // cout << "out: " << j << endl;
        weak.out = true;
        remain--;
      }
    }
  }
  // 냄새 - mapInfo
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      // decrease
      if(mapInfo[i][j].first != 0){
        mapInfo[i][j].second--;
        if(mapInfo[i][j].second < 1)
          mapInfo[i][j].first = 0;
      }
    }
  }
  for(int i = 1; i <= m; i++){
    // new
    _shark tmp = shark[i];
    if(tmp.out) continue;
    mapInfo[tmp.x][tmp.y].first = i;
    mapInfo[tmp.x][tmp.y].second = k;
  }

  run(sec + 1, remain);
}

int main() {
	// assert(freopen("input.txt", "r", stdin));
	// assert(freopen("output.txt", "w", stdout));
	ios_base::sync_with_stdio(false);

  // 입력
  cin >> n >> m >> k; // n x m -> n rows x m columns
  int sharkNum;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> sharkNum;
      if(sharkNum != 0){
        shark[sharkNum].x = j;
        shark[sharkNum].y = i;
        mapInfo[j][i] = make_pair(sharkNum, k);
      }
    }
  }
  for(int i = 1; i <= m; i++){
    cin >> shark[i].heading;
  }
  for(int i = 1; i <= m; i++){
    _shark &tmp = shark[i];
    for(int j = 1; j <= 4; j++){
      cin >> tmp.priority[j][0] >> tmp.priority[j][1] >> tmp.priority[j][2] >> tmp.priority[j][3];
    }
  }

  run(1, m);
  // 출력
	cout << res << endl;

	return 0;
}
