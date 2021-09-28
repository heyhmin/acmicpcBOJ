#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#define endl '\n'
#define prt(x) #x << ' ' << x << ' '
#define REP(i,a,b) for (auto i = (a); i <= (b); ++i) // vector.end() - 1
#define false 0
#define true 1

using namespace std;
vector<vector<int>> map(22, vector<int>(22, -3));
vector<vector<bool>> visited_map(22, vector<bool>(22, false));
int res, T, t, n, m;
typedef struct _group {
	int size = 0;
	int rainbowSize = 0;
	int base_r = 0;
	int base_c = 0;
	vector<pair<int, int>> blocks;
	bool operator < (const _group g) const {
		if (this->size == g.size) {
			if (this->rainbowSize == g.rainbowSize) {
				if (this->base_r == g.base_r) {
					return this->base_c < g.base_c;
				}
				return this->base_r < g.base_r;
			}
			return this->rainbowSize < g.rainbowSize;
		}
		return this->size < g.size;
	}
}group;
group tmp;

void printMap() {
	REP(i, 1, n) {
		REP(j, 1, n) {
			cout << " ";
			if (map[i][j] == -2) cout << "_";
			else if (map[i][j] == -1) cout << "X";
			else cout << map[i][j];
		}
		cout << endl;
	}
}

void init() {
	res = 0;
	map.clear();
	map.resize(22, vector<int>(22, -3));
	visited_map.clear();
	visited_map.resize(22, vector<bool>(22, false));
}

void findGroup(int r, int c, int color) {
	int rr = r - 1;
	if (1 < r && r <= n && !visited_map[rr][c] && (map[rr][c] == color || map[rr][c] == 0) ) {
		tmp.blocks.push_back(make_pair(rr, c));
		tmp.size++;
		if (map[rr][c] == 0) tmp.rainbowSize++;
		visited_map[rr][c] = true;
		findGroup(rr, c, color);
	}
	rr = r + 1;
	if (0 < r && r < n && !visited_map[rr][c] && (map[rr][c] == color || map[rr][c] == 0)) {
		tmp.blocks.push_back(make_pair(rr, c));
		tmp.size++;
		if (map[rr][c] == 0) tmp.rainbowSize++;
		visited_map[rr][c] = true;
		findGroup(rr, c, color);
	}
	int cc = c - 1;
	if (1 < c && c <= n && !visited_map[r][cc] && (map[r][cc] == color || map[r][cc] == 0)) {
		tmp.blocks.push_back(make_pair(r, cc));
		tmp.size++;
		if (map[r][cc] == 0) tmp.rainbowSize++;
		visited_map[r][cc] = true;
		findGroup(r, cc, color);
	}
	cc = c + 1;
	if (0 < c && c < n && !visited_map[r][cc] && (map[r][cc] == color || map[r][cc] == 0)) {
		tmp.blocks.push_back(make_pair(r, cc));
		tmp.size++;
		if (map[r][cc] == 0) tmp.rainbowSize++;
		visited_map[r][cc] = true;
		findGroup(r, cc, color);
	}
}

void gravity() {
	for (int i = n - 1; i > 0; --i) {
		REP(j, 1, n) {
			if (map[i][j] < 0) continue;
			// block down
			int block = map[i][j];
			int rr = i + 1;
			while (rr <= n) {
				if (map[rr][j] == -1) break;
				if (map[rr][j] == -2) {
					map[rr - 1][j] = -2;
					map[rr][j] = block;
				}
				++rr;
			}
		}
	}
}

int main() {
	assert(freopen("input.txt", "r", stdin));
	assert(freopen("output.txt", "w", stdout));

	cin >> T;
	t = 0;

	while (t < T) {
		// 초기화 & 입력
		t++;
		init();
		cin >> n >> m;

		REP(i, 1, n) {
			REP(j, 1, n) {
				cin >> map[i][j];
				if (map[i][j] == -1) visited_map[i][j] = true; // black, empty은 방문한 것으로 표시
			}
		}

		// 입력 끝
		while (true) {
			// pq로 size가 큰 그룹 찾기
			priority_queue<group> pq;
			// 1, 1부터 시작, visited_map에 방문 표시, 무지개 false // black, empty은 true
			REP(i, 1, n) {
				REP(j, 1, n) {
					// base block
					if (map[i][j] < 1 || visited_map[i][j]) continue;
					tmp.base_r = i;
					tmp.base_c = j;
					tmp.blocks.clear();
					tmp.blocks.push_back(make_pair(i, j));
					tmp.size = 1;
					if (map[i][j] == 0) tmp.rainbowSize = 1;
					else tmp.rainbowSize = 0;
					visited_map[i][j] = true;
					findGroup(i, j, map[i][j]);
					if (tmp.size < 2) continue;
					// rainbowBlock not visited
					REP(x, 1, n)
						REP(y, 1, n)
							if (map[x][y] == 0) visited_map[x][y] = false;
					pq.push(tmp);
				}
			}
			// 점수 획득
			if (pq.empty()) break;
			int s = pq.top().size;
			res += s * s;
			vector<pair<int, int>> bgroups = pq.top().blocks;
			REP(i, bgroups.begin(), bgroups.end() - 1) {
				map[i->first][i->second] = -2;
			}
			// 중력, 회전, 중력
			gravity();
			vector<vector<int>> tmp_map(22, vector<int>(22, -3));
			REP(i, 1, n)
				REP(j, 1, n)
					tmp_map[i][j] = map[j][n + 1 - i];
			map = tmp_map;
			gravity();
			// visited 초기화
			visited_map.clear();
			visited_map.resize(22, vector<bool>(22, false));
			REP(i, 1, n)
				REP(j, 1, n)
				if (map[i][j] < 0) visited_map[i][j] = true;
		}

		cout << "test " << t << " : " << res << endl;
	}

	return 0;
}
