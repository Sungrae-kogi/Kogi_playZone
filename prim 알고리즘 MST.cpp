#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#define MAX_VERTICES 7
#define TRUE 1
#define FALSE 0
/*
	Prim Algorithm 은 정점 선택을 기반으로 나아간다
	시작 정점을 spanning tree에 넣어준다
	spanning tree집합에 인접한 정점들 중에서 최소 간선으로 연결될 수 있는 정점을 spanning tree집합에 넣어주고
	이때 간선은 spanning tree의 간선이 된다
	이 과정을 간선이 n-1개가 될때까지 반복
*/

int weight[MAX_VERTICES][MAX_VERTICES] = {// 신장트리의 거리와 모양을 배열로 표현, INF는 바로갈 수 있는 경로가 없음을 뜻한다.
  {0,29,INT_MAX,INT_MAX,INT_MAX,10,INT_MAX},
  {29,0,16,INT_MAX,INT_MAX,INT_MAX,15},
  {INT_MAX,16,0,12,INT_MAX,INT_MAX,INT_MAX},
  {INT_MAX,INT_MAX,12,0,22,INT_MAX,18},
  {INT_MAX,INT_MAX,INT_MAX,22,0,27,25},
  {10,INT_MAX,INT_MAX,INT_MAX,27,0,INT_MAX},
  {INT_MAX,15,INT_MAX,18,25,INT_MAX,0}
};

int selected[MAX_VERTICES];
int dist[MAX_VERTICES]; //최소거리정보를 담는 배열

int get_min_vertex(int n) {
    int v, i;
    for (i = 0; i < n; i++) {
        if (selected[i] == FALSE) {
            v = i;
            break;
        }
    }

    //선택되지않은 정점번호 v를 과연 v가 최소거리를 지닌 정점인지
    for (i = 0; i < n; i++) {
        if (selected[i] == FALSE && (dist[i] < dist[v])) {   //미방문정점에다가, v보다 거리가더작은게있다면
            v = i;  //더 작은거를가진 정점의 번호로 바꿔준다
        }
    }

    //탐색 끝
    return v;
}


//s는 시작 정점
void prim(int s, int n) {
    int v, u;
    
    //함수 호출하면 우선 사용할 배열을 초기화시켜준다,
    for (int u = 0; u < n; u++) {
        dist[u] = INT_MAX;
        selected[u] = FALSE;
    }

    //첫 시작 정점은 dist를 0으로 초기화해준다, 자기자신에서 자기자신까지의 거리는 0이지
    dist[s] = 0;

    for (int i = 0; i < n; i++) {
        u = get_min_vertex(n);  //우선순위큐를 사용한다면 이 함수가필요없을수있다,
        selected[u] = TRUE;

        //dist[u] == INT_MAX 란 의미가 무엇일까에 대해 생각해보자
        //정점들중 dist값이 제일 작은 번호가 get_min_vertex 함수로 선택되어진상태이다 그게 MAX값이란건
        //경로가 없다는의미
        if (dist[u] == INT_MAX)
            return;
        
        cout << u << " ";

        for (v = 0; v < n; v++) {
            /*
            직접적인 경로가 발견되어 dist값이 MAX_INT에서 상수로 갱신되거나 기존의 값보다 작은 값이 발견되어
            최소값으로 갱신해주는 과정이 포함되어있다.
            */
            if (weight[u][v] != INT_MAX) {  //정점 u와 연결이 되어있는 정점까지의 거리를 각각 비교
                //INT_MAX가 아니란건 u와 연결되어있는정점이란거고 그 위치 v가 FALSE 즉, 미선택상태이고 더 값이작다면
                if (selected[v] == FALSE && weight[u][v] < dist[v]) {
                    dist[v] = weight[u][v];
                }
            }
        }
    }
}

void main() {
    prim(0, MAX_VERTICES);  //정점 갯수가 7개인 그래프
}