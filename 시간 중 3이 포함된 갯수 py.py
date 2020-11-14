#N시 분 초 중에서 3이 들어가 있는 횟수 Brute force 접근

h = int(input())

count = 0
for i in range(h+1):
    for j in range(60):
        for k in range(60):
            if '3' in str(i)+str(j)+str(k):
                count +=1

print(count)
            
