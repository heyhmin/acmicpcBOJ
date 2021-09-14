#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#define prt(x) #x << ' ' << x
#define ALL(x) (x).begin(), (x).end()
#define endl '\n'
#define SZ(x) (int)size(x)
#define REP(i,a,b) for (int i = (a); i <= (b); ++i)

using namespace std;
int T, t, n, m, limit, num1 = 0, num2 = 0, num3 = 0, m_cnt = 0;
vector<vector<int>> magic (105, vector<int>(2, 0));
int arr1[50] = { 7, 22, 45, 76, 115, 162, 217, 280, 351, 430, 517, 612, 715, 826, 945, 1072, 1207, 1350, 1501, 1660, 1827, 2002, 2185, 2376, 2575, 2782, 2997, 3220, 3451, 3690, 3937, 4192, 4455, 4726, 5005, 5292, 5587, 5890, 6201, 6520, 6847, 7182, 7525, 7876, 8235, 8602, 8977, 9360, 9751 };
int arr4[50] = { 5, 18, 39, 68, 105, 150, 203, 264, 333, 410, 495, 588, 689, 798, 915, 1040, 1173, 1314, 1463, 1620, 1785, 1958, 2139, 2328, 2525, 2730, 2943, 3164, 3393, 3630, 3875, 4128, 4389, 4658, 4935, 5220, 5513, 5814, 6123, 6440, 6765, 7098, 7439, 7788, 8145, 8510, 8883, 9264, 9653 };
int arr2[50] = { 3, 14, 33, 60, 95, 138, 189, 248, 315, 390, 473, 564, 663, 770, 885, 1008, 1139, 1278, 1425, 1580, 1743, 1914, 2093, 2280, 2475, 2678, 2889, 3108, 3335, 3570, 3813, 4064, 4323, 4590, 4865, 5148, 5439, 5738, 6045, 6360, 6683, 7014, 7353, 7700, 8055, 8418, 8789, 9168, 9555 };
int arr3[50] = { 1, 10, 27, 52, 85, 126, 175, 232, 297, 370, 451, 540, 637, 742, 855, 976, 1105, 1242, 1387, 1540, 1701, 1870, 2047, 2232, 2425, 2626, 2835, 3052, 3277, 3510, 3751, 4000, 4257, 4522, 4795, 5076, 5365, 5662, 5967, 6280, 6601, 6930, 7267, 7612, 7965, 8326, 8695, 9072, 9457 };

void init() {
	magic.clear();
	magic.resize(105, vector<int>(2, 0));
	num1 = 0;
	num2 = 0;
	num3 = 0;
	m_cnt = 0;
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

		cin >> n >> m;
		limit = n * n - 1;

		vector < vector<int> > map(50, vector<int>(50, 0));
		vector<int> map_1d;
		// 입력
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				cin >> map[i][j];

		for (int i = 1; i <= m; ++i)
			cin >> magic[i][0] >> magic[i][1];

		// 1d로 바꾸기
		int r, c, ss, cnt;
		int center = (n + 1) / 2;
		r = center;
		c = center;
		ss = 1;
		cnt = 0;
		while (cnt < (n - 1) / 2) {
			for (int i = 1; i <= ss; ++i) map_1d.push_back(map[r][c - i]);
			c -= ss;
			for (int i = 1; i <= ss; ++i) map_1d.push_back(map[r + i][c]);
			r += ss;
			++ss;
			for (int i = 1; i <= ss; ++i) map_1d.push_back(map[r][c + i]);
			c += ss;
			for (int i = 1; i <= ss; ++i) map_1d.push_back(map[r - i][c]);
			r -= ss;
			++ss;
			cnt++;
		}
		for (int i = n - 1; i > 0; i--) map_1d.push_back(map[1][i]);

		auto it = find(map_1d.begin(), map_1d.end(), 0);
		if (it != map_1d.end()) map_1d.resize( find(map_1d.begin(), map_1d.end(), 5) - map_1d.begin() );

		// 마법 시작
		while (m > m_cnt) {
			int strength = magic[++m_cnt][1];
			int mapSize = map_1d.size()-1;
			switch (magic[m_cnt][0])
			{
			case 1: for (int i = 0; i < strength; ++i) {
				if (arr1[i] - i >= mapSize) break;
				map_1d.erase(map_1d.begin() + arr1[i] - (i + 1));
				--mapSize;
				} break;
			case 2: for (int i = 0; i < strength; ++i) {
				if (arr2[i] - i >= mapSize) break;
				map_1d.erase(map_1d.begin() + arr2[i] - (i + 1));
				--mapSize;
				} break;
			case 3: for (int i = 0; i < strength; ++i) {
				if (arr3[i] - i >= mapSize) break;
				map_1d.erase(map_1d.begin() + arr3[i] - (i + 1));
				--mapSize;
				} break;
			case 4: for (int i = 0; i < strength; ++i) {
				if (arr4[i] - i >= mapSize) break;
				map_1d.erase(map_1d.begin() + arr4[i] - (i + 1));
				--mapSize;
				} break;
			default: break;
			}
			bool bombStop = false;
			map_1d.push_back(0);
			while (!bombStop) {
				// 구슬 [폭발]
				bombStop = true;
				int sameNum = *map_1d.begin();
				int sameCnt = 0;
				for (auto i = map_1d.begin(); i != map_1d.end(); ++i) {
					if (sameNum == *i) sameCnt++;
					else {
						if (sameCnt > 3) {
							bombStop = false;
							i = map_1d.erase(i - sameCnt,  i);
							switch (sameNum)
							{
							case 1: num1 += sameCnt; break;
							case 2: num2 += sameCnt; break;
							case 3: num3 += sameCnt; break;
							default:
								break;
							}
						}
						sameNum = *i;
						sameCnt = 1;
					}
				}
			}
			// 구슬 재배열
			int sameNum = *map_1d.begin();
			int sameCnt = 0;
			int newCnt = 0;
			vector<int> temp;
			for (auto i = map_1d.begin(); i != map_1d.end(); ++i) {
				if (sameNum == 0) break;
				if (sameNum == *i) sameCnt++;
				else {
					if (++newCnt > limit) break;
					temp.push_back(sameCnt);
					if (++newCnt > limit) break;
					temp.push_back(sameNum);
					
					sameNum = *i;
					sameCnt = 1;

				}
			}
			map_1d.clear();
			map_1d = temp;

			/*
			for (auto it = map_1d.begin(); it != map_1d.end(); ++it)
				cout << ' ' << *it;
			cout << "?" << endl; */
		}
		// 출력
		cout << t << " test : " << num1 + 2 * num2 + 3 * num3 << endl;
		//cout << num1 + 2 * num2 + 3 * num3 << endl;
	}
}
