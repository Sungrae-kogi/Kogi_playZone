#include <iostream>
#include <vector>
using namespace std;

//우선 테이블을 만들어서 일치하는부분을 생성 표기
vector<int> makeTable(string pattern) {
	int patternSize = pattern.size();
	vector<int> table(patternSize, 0);	//patternSize만큼 0으로 초기화
	int j = 0;
	for (int i = 1; i < patternSize; i++) {
		while (j > 0 && pattern[i] != pattern[j]) {	//pattern string을 탐색하며 글자의 같음을 비교
			j = table[j - 1];
		}
		if (pattern[i] == pattern[j]) {
			table[i] = ++j;
		}
	}
	return table;
}

void KMP(string parent, string pattern) {
	vector<int> table = makeTable(pattern);
	int parentSize = parent.size();
	int patternSize = pattern.size();
	int j = 0;
	for (int i = 0; i < parentSize; i++) {	//i index는 앞으로 나아가기만 하면됨
		while (j > 0 && parent[i] != pattern[j]) {
			j = table[j - 1];
		}
		if (parent[i] == pattern[j]) {
			if (j == patternSize - 1) {
				printf("%d번째에서 탐색 성공.\n", i - patternSize+2);
				j = table[j];
			}
			else {
				j++;
			}
		}
	}
}

int main() {
	string parent = "ababacabacaabacaaba";
	string pattern = "abacaaba";
	KMP(parent, pattern);
	vector<int> table = makeTable(pattern);
	for (int i = 0; i < table.size(); i++) {
		printf("%d ", table[i]);
	}

	return 0;
}