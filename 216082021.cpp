#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#define endl '\n'
#define prt(x) #x << ' ' << x << ' '
#define REP(i,a,b) for (auto i = (a); i <= (b); ++i)

using namespace std;
int T, t, n, result = 0;
vector<vector<int>> map(405, vector<int>(405, -1));
vector<vector<int>> fourLike(405, vector<int>(7, 0));

typedef struct _block{
	int r = 0;
	int c = 0;
	int cntEmpty = 0;
	int cntLike = 0;
}block;
vector<block> blocks;

void init() {
	blocks.clear();
	map.clear();
	map.resize(405, vector<int>(405, -1));
	fourLike.clear();
	fourLike.resize(405, vector<int>(5, 0));
	result = 0;
}

int main() {
	assert(freopen("input.txt", "r", stdin));
	assert(freopen("output.txt", "w", stdout));

	cin >> T;
	t = 0;
	while (T > t) {
		// 초기화
		t++;

		init();

		// 입력
		cin >> n;
		int nn = n * n;
		int nnCnt = 0;

		REP(i, 1, nn){
			cin >> fourLike[i][0] >> fourLike[i][1] >> fourLike[i][2] >> fourLike[i][3] >> fourLike[i][4];
		}

		block tmpBlock;
		REP(i, 1, n) {
			REP(j, 1, n) {				
				tmpBlock.r = i;
				tmpBlock.c = j;
				blocks.push_back(tmpBlock);
				map[i][j] = 0;
			}
		}
		while (nn > nnCnt) {
			nnCnt++;
			int student = fourLike[nnCnt][0];
			// cntEmpty, cntLike 채우기
			REP(i, blocks.begin(), blocks.end() - 1) {
				int cntE = 0;
				int cntL = 0;
				int r = i->r;
				int c = i->c;
				if (r > 1 && map[r - 1][c] == 0) cntE++;
				if (c > 1 && map[r][c - 1] == 0) cntE++;
				if (r < n && map[r + 1][c] == 0) cntE++;
				if (c < n && map[r][c + 1] == 0) cntE++;
				i->cntEmpty = cntE;
				REP(j, 1, 4) {
					int tmpLike = fourLike[nnCnt][j];
					if (r > 1 && map[r - 1][c] == tmpLike) cntL++;
					if (c > 1 && map[r][c - 1] == tmpLike) cntL++;
					if (r < n && map[r + 1][c] == tmpLike) cntL++;
					if (c < n && map[r][c + 1] == tmpLike) cntL++;
				}
				i->cntLike = cntL;
			}
			// newBlockList sorted with cntEmpty
			vector<block> emptyBlocks;
			for (int i = 4; i >= 0; i--) {
				REP(j, blocks.begin(), blocks.end() - 1) {
					if (j->cntEmpty == i  && map[j->r][j->c] == 0) {
						tmpBlock.r = j->r;
						tmpBlock.c = j->c;
						tmpBlock.cntEmpty = j->cntEmpty;
						tmpBlock.cntLike = j->cntLike;
						emptyBlocks.push_back(tmpBlock);
					}
				}
			}
			
			// sort it by cntLike again
			vector<block> likeBlocks;
			for (int i = 4; i >= 0; i--) {
				REP(j, emptyBlocks.begin(), emptyBlocks.end() - 1) {
					if (j->cntLike == i) {
						tmpBlock.r = j->r;
						tmpBlock.c = j->c;
						tmpBlock.cntEmpty = j->cntEmpty;
						tmpBlock.cntLike = j->cntLike;
						likeBlocks.push_back(tmpBlock);
					}
				}
			}
			// 자리 배정
			REP(i, likeBlocks.begin(), likeBlocks.end() - 1) {
				if (map[likeBlocks.begin()->r][likeBlocks.begin()->c] == 0) {
					map[likeBlocks.begin()->r][likeBlocks.begin()->c] = student;
					break;
				}
			}
		}

		int stuCnt = 0;
		// 만족도 조사
		REP(i, 1, n) {
			REP(j, 1, n) {
				int cntL = 0;
				int stuOrder;
				REP(k, 1, nn) {
					if (map[i][j] == fourLike[k][0]) {
						stuOrder = k;
						break;
					}
				}
				REP(k, 1, 4) {
					int tmpLike = fourLike[stuOrder][k];
					if (i > 1 && map[i - 1][j] == tmpLike) { cntL++; continue; }
					if (j > 1 && map[i][j - 1] == tmpLike) { cntL++; continue; }
					if (i < n && map[i + 1][j] == tmpLike) { cntL++; continue; }
					if (j < n && map[i][j + 1] == tmpLike) { cntL++; continue; }
				}
				switch (cntL)
				{
				case 1: result += 1; break;
				case 2: result += 10; break;
				case 3: result += 100; break;
				case 4: result += 1000; break;
				default: break;
				}
			}
		}
		// 출력
		cout << t << " test : " << result << endl;
	}
}
