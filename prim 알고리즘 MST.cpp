#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#define MAX_VERTICES 7
#define TRUE 1
#define FALSE 0
/*
	Prim Algorithm �� ���� ������ ������� ���ư���
	���� ������ spanning tree�� �־��ش�
	spanning tree���տ� ������ ������ �߿��� �ּ� �������� ����� �� �ִ� ������ spanning tree���տ� �־��ְ�
	�̶� ������ spanning tree�� ������ �ȴ�
	�� ������ ������ n-1���� �ɶ����� �ݺ�
*/

int weight[MAX_VERTICES][MAX_VERTICES] = {// ����Ʈ���� �Ÿ��� ����� �迭�� ǥ��, INF�� �ٷΰ� �� �ִ� ��ΰ� ������ ���Ѵ�.
  {0,29,INT_MAX,INT_MAX,INT_MAX,10,INT_MAX},
  {29,0,16,INT_MAX,INT_MAX,INT_MAX,15},
  {INT_MAX,16,0,12,INT_MAX,INT_MAX,INT_MAX},
  {INT_MAX,INT_MAX,12,0,22,INT_MAX,18},
  {INT_MAX,INT_MAX,INT_MAX,22,0,27,25},
  {10,INT_MAX,INT_MAX,INT_MAX,27,0,INT_MAX},
  {INT_MAX,15,INT_MAX,18,25,INT_MAX,0}
};

int selected[MAX_VERTICES];
int dist[MAX_VERTICES]; //�ּҰŸ������� ��� �迭

int get_min_vertex(int n) {
    int v, i;
    for (i = 0; i < n; i++) {
        if (selected[i] == FALSE) {
            v = i;
            break;
        }
    }

    //���õ������� ������ȣ v�� ���� v�� �ּҰŸ��� ���� ��������
    for (i = 0; i < n; i++) {
        if (selected[i] == FALSE && (dist[i] < dist[v])) {   //�̹湮�������ٰ�, v���� �Ÿ������������ִٸ�
            v = i;  //�� �����Ÿ����� ������ ��ȣ�� �ٲ��ش�
        }
    }

    //Ž�� ��
    return v;
}


//s�� ���� ����
void prim(int s, int n) {
    int v, u;
    
    //�Լ� ȣ���ϸ� �켱 ����� �迭�� �ʱ�ȭ�����ش�,
    for (int u = 0; u < n; u++) {
        dist[u] = INT_MAX;
        selected[u] = FALSE;
    }

    //ù ���� ������ dist�� 0���� �ʱ�ȭ���ش�, �ڱ��ڽſ��� �ڱ��ڽű����� �Ÿ��� 0����
    dist[s] = 0;

    for (int i = 0; i < n; i++) {
        u = get_min_vertex(n);  //�켱����ť�� ����Ѵٸ� �� �Լ����ʿ�������ִ�,
        selected[u] = TRUE;

        //dist[u] == INT_MAX �� �ǹ̰� �����ϱ ���� �����غ���
        //�������� dist���� ���� ���� ��ȣ�� get_min_vertex �Լ��� ���õǾ��������̴� �װ� MAX���̶���
        //��ΰ� ���ٴ��ǹ�
        if (dist[u] == INT_MAX)
            return;
        
        cout << u << " ";

        for (v = 0; v < n; v++) {
            /*
            �������� ��ΰ� �߰ߵǾ� dist���� MAX_INT���� ����� ���ŵǰų� ������ ������ ���� ���� �߰ߵǾ�
            �ּҰ����� �������ִ� ������ ���ԵǾ��ִ�.
            */
            if (weight[u][v] != INT_MAX) {  //���� u�� ������ �Ǿ��ִ� ���������� �Ÿ��� ���� ��
                //INT_MAX�� �ƴ϶��� u�� ����Ǿ��ִ������̶��Ű� �� ��ġ v�� FALSE ��, �̼��û����̰� �� �����۴ٸ�
                if (selected[v] == FALSE && weight[u][v] < dist[v]) {
                    dist[v] = weight[u][v];
                }
            }
        }
    }
}

void main() {
    prim(0, MAX_VERTICES);  //���� ������ 7���� �׷���
}