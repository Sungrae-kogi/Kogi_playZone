#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <climits>

using namespace std;

//�������������� �ڵ����� 0���� �ʱ�ȭ
int n, m;

int graph[1001][1001];

//dfs�� Ư�� ��带 �湮�ϰ�, �׿� ������ �������� �� ��嵵 �湮 > ��ó���� ���ȣ���
bool dfs(int x, int y) {
	if (x <= -1 || x >= n || y <= -1 || y >= m) {
		return false;
	}

	//�̹湮 ���¶��
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
			if (dfs(i, j)) {	//graph[i][j]�� 0 ��, �̹湮�����̸� �� ������ �� �湮ó���ҰŴϱ� 1�ø���
				result += 1;
			}
		}
	}

	cout << result << endl;
	return 0;
}
