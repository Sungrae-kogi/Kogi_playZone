import sys
input = sys.stdin.readline
INF = int(1e9)

def bf(start):
    #start node 초기화
    dist[start]=0
    #전체 n번의 라운드를 반복
    for i in range(n):
        #매 반복마다 모든간선을 확인해야 한다.
        for j in range(m):
            cur = edges[j][0]
            next_node = edges[j][1]
            cost = edges[j][2]
            #현재간선을 거쳐 다른 노드로 이동하는 거리가 더 짧은 경우
            if dist[cur] != INF and dist[next_node] > dist[cur]+cost:
                dist[next_node] = dist[cur]+cost
                #n 번째 라운드에서도 값이 갱신된다면 음수 순환이 존재하는거다
                if i==n-1:
                    return True
    return False

#n = 노드의 갯수, m = 간선의 갯수
n,m = map(int, input().split())

#모든 간선에 대한 정보를 담을 리스트
edges=[]
#최단 거리 테이블을 INF로 초기화
dist = [INF]*(n+1)

#모든 간선 정보 입력받기
for _ in range(m):
    a,b,c=map(int, input().split())
    edges.append((a,b,c))

#벨만 포드 알고리즘 실행
negative_cycle = bf(1)

if negative_cycle:
    print("-1")
else:
    #시작점인 1번노드를 제외한 다른 모든 노드로 가기 위한 최단 거리 출력
    for i in range(2, n+1):
        #도달 불가능한 경우 -1
        if dist[i] == INF:
            print("-1")
        else:
            print(dist[i])
