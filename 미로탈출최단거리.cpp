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

	//queue가 빌때까지 반복
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		//4 방향으로의 확인
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			//맵을 넘어가는경우는 무시
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)
				continue;
			//벽이어도 무시
			if (graph[nx][ny] == 0)
				continue;
			//해당 노드를 처음 방문하는 경우에만 최단 경로거리 기록
			if (graph[nx][ny] == 1) {
				graph[nx][ny] = graph[x][y] + 1;
				q.push({ nx,ny });		//발견한 다음노드를 queue에 push
			}
		}
	}

	return graph[n - 1][m - 1];	//0부터 시작하니까 최종도착지점 우측맨아래를 의미
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