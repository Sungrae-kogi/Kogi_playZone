data = input()
result = []
value =0

#문자를 하나씩 확인
for x in data:
    #알파벳이면 결과 리스트에 삽입
    if x.isalpha():
        result.append(x)
    #숫자는 따로 더해둔다.
    else:
        value += int(x)


result.sort()
if value != 0:
    result.append(str(value))

print(' '.join(result))
