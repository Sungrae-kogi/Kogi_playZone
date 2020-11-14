# 상하좌우 문제, 첫째 줄에 공간의 크기인 N이 주어짐 (1<=N<=100)
# 둘째 줄에 A가 이동할 계획서 내용이 주어짐 방향을 지칭하는 알파벳으로
# 시작지점은 (1,1)
# 시뮬레이션 유형, 명령에 따라 개체를 차례대로 이동한다

n = int(input())
x,y = 1,1
nx,ny = 1,1
plans = input().split()

# L, R, U, D에 따른 이동 방햐
dx = [0,0,-1,1]
dy = [-1,1,0,0]
move_types = ['L','R','U','D']

# 이동 계획을 하나씩 꺼낸다
for plan in plans:
    for i in range(len(move_types)):
        if plan == move_types[i]:
            nx = x + dx[i]
            ny = y + dy[i]
        #공간을 벗어나는 것은 무시
        if nx<1 or ny<1 or nx>n or ny>n:
            continue
        #이동
        x,y = nx,ny


print(x,y)
    
