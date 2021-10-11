###자동 로또 번호 생성기
#1~45 숫자 중에서 6개를 고르는 로또 번호를 자동으로 만들어 주는 프로그램을 작성하자. 사용자가 입력한 개수만큼 번호 쌍을 생성해 주는 기능을 한다.
import random

##전역 변수 선언 ##
total =[]
lotto =[]
pickNum = 0
count =0


print("**로또 번호 생성 시작 **")
count = int(input('몇 번을 뽑을까요?'))

for _ in range(count):
    lotto =[]
    while True:
        pickNum = random.randint(1,45)
        if pickNum not in lotto :
            lotto.append(pickNum)
        if len(lotto) >=6:
            break
    total.append(lotto)
for lotto in total:
    lotto.sort()
    print('자동번호--> ',end='')
    for i in range(0,6):
        print("%2d"%lotto[i], end='')
        print()