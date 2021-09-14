#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#define endl '\n'
#define prt(x) #x << ' ' << x
#define REP(i,a,b) for (auto i = (a); i <= (b); ++i)

using namespace std;
int T, t, n, m, result, m_cnt;
vector < vector<int>> cloudMove (105, vector<int>(2, 0));
vector < vector<int>> map(55, vector<int>(55, -1));
vector < pair<int, int>> cloudPosition;

void init() {
	cloudMove.clear();
	cloudMove.resize(105, vector<int>(2, 0));
	map.clear();
	map.resize(55, vector<int>(55, -1));
	cloudPosition.clear();
	result = 0;
	m_cnt = 0;
}

int main() {
	init();
	// 입력
	cin >> n >> m;
	
	REP(i, 1, n)
		REP(j, 1, n)
			cin >> map[i][j];

    REP(i, 1, m)
		cin >> cloudMove[i][0] >> cloudMove[i][1];

    cloudPosition.push_back(make_pair(n, 1));
	cloudPosition.push_back(make_pair(n, 2));
	cloudPosition.push_back(make_pair(n - 1, 1));
	cloudPosition.push_back(make_pair(n - 1, 2));

	// 시작
	while (m > m_cnt) {
		m_cnt++;
		// 이동
		int posSize = cloudPosition.size();
		REP(i, 0, posSize - 1) {
			REP(j, 1, cloudMove[m_cnt][1]) { // second = c, x // first = r, y
				switch (cloudMove[m_cnt][0])
				{
				case 1:
					cloudPosition[i].second--;
					break;
				case 2:
					cloudPosition[i].second--;
        			cloudPosition[i].first--;
					break;
				case 3:
					cloudPosition[i].first--;
					break;
				case 4:
					cloudPosition[i].second++;
					cloudPosition[i].first--;
					break;
				case 5:
					cloudPosition[i].second++;
					break;
				case 6:
					cloudPosition[i].second++;
					cloudPosition[i].first++;
					break;
				case 7:
					cloudPosition[i].first++;
					break;
				case 8:
					cloudPosition[i].second--;
					cloudPosition[i].first++;
						break;
				default:break;
				}
				if (cloudPosition[i].first < 1) cloudPosition[i].first = n;
				if (cloudPosition[i].first > n) cloudPosition[i].first = 1;
				if (cloudPosition[i].second < 1) cloudPosition[i].second = n;
				if (cloudPosition[i].second > n) cloudPosition[i].second = 1;
			}
		}
		// 비 내림
		REP(i, 0, posSize - 1)
			map[cloudPosition[i].first][cloudPosition[i].second]++;
		// 대각선 물 복사
		REP(i, 0, posSize - 1) {
			int r = cloudPosition[i].first;
			int c = cloudPosition[i].second;
			int cnt = 0;
			if (map[r - 1][c - 1] > 0) cnt++;
			if (map[r - 1][c + 1] > 0) cnt++;
			if (map[r + 1][c - 1] > 0) cnt++;
			if (map[r + 1][c + 1] > 0) cnt++;
			map[r][c] += cnt;
		}
		vector < pair<int, int>> tmpNext;
		// 구름 생성, 이전 구름 사라짐
		REP(i, 1, n) {
			REP(j, 1, n) { 
				if (find(cloudPosition.begin(), cloudPosition.end(), make_pair(i, j)) != cloudPosition.end()) continue;
				if (map[i][j] > 1) {
				    tmpNext.push_back(make_pair(i, j));
					map[i][j] -= 2;
				}
			}
	    }
		cloudPosition.clear();
		cloudPosition = tmpNext;
	}
	
    REP(i, 1, n)
		REP(j, 1, n)
			if (map[i][j] > 0) result += map[i][j];
	// 출력
	cout << result << endl;
}
