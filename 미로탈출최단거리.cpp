#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <algorithm>
#include <climits>

using namespace std;

int n, m;
int graph[201][201];

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

int bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x,y });

	//queue�� �������� �ݺ�
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		//4 ���������� Ȯ��
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			//���� �Ѿ�°��� ����
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)
				continue;
			//���̾ ����
			if (graph[nx][ny] == 0)
				continue;
			//�ش� ��带 ó�� �湮�ϴ� ��쿡�� �ִ� ��ΰŸ� ���
			if (graph[nx][ny] == 1) {
				graph[nx][ny] = graph[x][y] + 1;
				q.push({ nx,ny });		//�߰��� ������带 queue�� push
			}
		}
	}

	return graph[n - 1][m - 1];	//0���� �����ϴϱ� ������������ �����ǾƷ��� �ǹ�
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> graph[i][j];
		}
	}
	cout << bfs(0, 0) << endl;

	return 0;
}