stack = ["자","료","구",None,None]
top=2

print("-------스택 상태-------")
for i in range(len(stack)-1,-1,-1):
    print(stack[i])

print("---------------------")
data=stack[top]
stack[top]=None
top -=1
print("pop-->",data)          #1차 추출

data = stack[top]
stack[top]=None
top -=1
print("pop-->",data)          #2차 추출

data = stack[top]
stack[top]=None
top-=1
print("pop-->",data)          #3차 추출
print("---------------------")

print("-------스택 상태-------")
for i in range(len(stack)-1,-1,-1):
    print(stack[i])