# 입출력

# a = input()
# print(a, end=" ")
# print(type(a))
# print(a, type(a), sep=",")

# 정수 변환
# a = int(input())
# print(a, type(a))

# b = float(input())
# print(b, type(b))

# 정수 2개 입력
# 100
# 200
# a = int(input())
# b = int(input())
# print(a, b)

# 100 200
a = input().split()
print(a, type(a))

# map
# map(함수, List 객체)

# map
a, b, c = map(int, input().split())
print(a, b, c)

# list
a = list(map(int, input().split()))
print(a, type(a))