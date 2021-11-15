stack = [None,None,None,None,None]
top = -1 #데이터가 비어있는 상태일때 top은 -1값이다.

top += 1
stack[top]="자"
top += 1
stack[top]="료"
top += 1
stack[top]="구"

print("#####스텍 상태#####")
for i in range(len(stack)-1,-1,-1):
    print(stack[i])