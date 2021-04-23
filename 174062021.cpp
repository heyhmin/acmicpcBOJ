#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

using namespace std;
int n, m, k, sum, res = 987654321;
vector<vector<int>> arr;
vector<vector<int>> rotSet;
vector<int> rotIdx;

void rotate(vector<vector<int>> carr, int idx){
  if(idx == k){
    // res
    for(int i = 1; i <= n; i++){
      sum = 0;
      for(int j = 1; j <= m; j++){
        sum += carr[i][j];
      }
      res = min(res, sum);
    }
    return;
  }

  int r, c, _s;
  r = rotSet[rotIdx[idx]][0];
  c = rotSet[rotIdx[idx]][1];
  _s = rotSet[rotIdx[idx]][2];

  // 배열 회전 전 상태
  vector<vector<int>> copyarr = carr;

  // 배열 회전
  for(int s = 1; s <= _s; s++){
    // 위쪽 부분, 오른쪽으로 이동 ( column change )
    for(int i = -s + 1; i <= s; i++)
      carr[r - s][c + i] = copyarr[r - s][c + i - 1];
    // 오른쪽 부분, 아래로 이동 ( row change )
    for(int i = -s + 1; i <= s; i++)
      carr[r + i][c + s] = copyarr[r + i - 1][c + s];
    // 아래쪽 부분, 왼쪽으로 이동 ( column change )
    for(int i = s - 1; i >= -s; i--)
      carr[r + s][c + i] = copyarr[r + s][c + i + 1];
    // 왼쪽 부분, 위로 이동 ( row change )
    for(int i = s - 1; i >= -s; i--)
      carr[r + i][c - s] = copyarr[r + i + 1][c - s];
  }
  rotate(carr, idx+1);
}

int main() {
	// assert(freopen("input.txt", "r", stdin));
	// assert(freopen("output.txt", "w", stdout));
	ios_base::sync_with_stdio(false);
  // 입력
  cin >> n >> m >> k; // n x m -> n rows x m columns
  arr.resize(n+1, vector<int>(m+1, 0));
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      cin >> arr[i][j];
    }
  }

  int r, c, s;
  for(int i = 0; i < k; i++){
    cin >> r >> c >> s;
    vector<int> tmp = {r, c, s};
    rotSet.push_back(tmp);
    rotIdx.push_back(i);
  }

  // next_permutation(vec.begin(), vec.end());
  // 시작 위치, 끝 위치를 넘겨주면 해당 범위를 기준으로 다음 순열로 정렬한 후 true를 리턴한다.
  do{
    vector<vector<int>> tempv = arr;
    rotate(tempv, 0);
  }while(next_permutation(rotIdx.begin(), rotIdx.end()));
  // 출력
	cout << res << endl;

	return 0;
}
