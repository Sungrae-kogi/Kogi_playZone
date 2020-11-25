#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <climits>

using namespace std;

//전역변수선언은 자동으로 0으로 초기화
int n, m;

int graph[1001][1001];

//dfs로 특정 노드를 방문하고, 그와 인접한 동서남북 쪽 노드도 방문 > 그처리는 재귀호출로
bool dfs(int x, int y) {
	if (x <= -1 || x >= n || y <= -1 || y >= m) {
		return false;
	}

	//미방문 상태라면
	if (graph[x][y] == 0) {
		graph[x][y] = 1;
		dfs(x - 1, y);
		dfs(x, y - 1);
		dfs(x + 1, y);
		dfs(x, y + 1);
		return true;
	}
	return false;
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> graph[i][j];
		}
	}

	int result = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dfs(i, j)) {	//graph[i][j]가 0 즉, 미방문상태이며 그 영역을 다 방문처리할거니까 1늘린다
				result += 1;
			}
		}
	}

	cout << result << endl;
	return 0;
}
