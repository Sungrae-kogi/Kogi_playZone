#include <iostream>
using namespace std;

const int number = 4;
const int INF = 100000000;	//INT_MAX 쓰면 밑에 판별부분에서 덧셈을 하면서 오버플로우가발생해버린다. 21억의 절반보다 약간 낮은값을 써야함

int a[4][4] = {
	{0,5,INF,8},
	{7,0,9,INF},
	{2,INF,0,4},
	{INF,INF,3,0}
};

void floydWarshall() {
	int d[number][number];

	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			d[i][j] = a[i][j];
		}
	}

	//k=거쳐가는 노드		floyd알고리즘에서는 거쳐가는  노드가 중심이다.
	for (int k = 0; k < number; k++) {
		//i= 출발 노드
		for (int i = 0; i < number; i++) {
			//j=도착 노드
			for (int j = 0; j < number; j++) {
				if (d[i][k] + d[k][j] < d[i][j])	//k를 거쳐서 j로 가는 값보다 바로 j로가는값이 더 크다면
					d[i][j] = d[i][k] + d[k][j];	//더 적은 비용인것으로 갱신
			}
		}
	}

	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}
}

int main() {
	floydWarshall();

	return 0;
}