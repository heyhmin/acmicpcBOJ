#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

using namespace std;
int numarr[10];
char oparr[10];
int res, len;

int calculator(int num1, int num2, char op){
  switch (op) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    default: return 0;
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

	cin >> len;
  string str; cin >> str;
  char carr[len+1];
  strcpy(carr, str.c_str());

  numarr[0] = carr[0] - '0';
  oparr[0] = '.';
  res = numarr[0];

  for(int i = 1; i < (len+1)/2; i++){
    numarr[i] = carr[i*2] - '0';
    oparr[i] = carr[i*2-1];
  }

  for(int i = 1; i < (len+1)/2; i++){
    res = calculator(res, numarr[i], oparr[i]);
  }

  if(len > 1) opCalculator(1, numarr[0]);

	cout << res << endl;

	return 0;
}
