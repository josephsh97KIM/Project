##함수 선언 부분##
def printPoly(p_x):
    term = len(p_x) - 1      #최고차항 숫자 = 배열 길이 - 1
    polyStr = "P(x)= "

    # for i in range(len(px)) :
    #     coef = p_x[i]         #계수

    ##2차원 배열로 표현하기##
    for i in range(len(p_x[0])):
        term = p_x[0][i]    #항 차수
        coef = p_x[1][i]    #계수
    ##---------------------------##

        if coef ==0:  #계수가 0이면 생략
            term -= 1
            continue
        if (coef>=0 and i !=0 ) : # 최고차항 앞의 +는 출력하지 않도록 함
            polyStr += "+"
        polyStr += str(coef) + "x^" + str(term) + " "
        term -= 1

    return polyStr

def calcPoly(xVal, p_x):
    retValue = 0

    # term = len(p_x) - 1
    #
    # for i in range(len(px)):
    #     coef = p_x[i]
    #     retValue += coef * xValue ** term
    #     term -= 1                         #= 7x^3 -4x^2 +0x^1 +5x^0

    ##2차원 배열시 ##
    for i in range(len(p_x[0])):
        term = p_x[0][i] #항 차수
        coef = p_x[1][i] #계수
        retValue += coef * xValue ** term
        term -=1

    return retValue

##전역 변수 선언 부분##
px= [7, -4, 0, 5]
###2차원 배열시 전역 변수 선언 부분##
px = [[300,20,0],[7,-4,5]]

##메인코드 부분##
if __name__ == "__main__":

    pStr = printPoly(px)
    print(pStr)

    xValue = int (input("x값-->"))

    pxValue = calcPoly(xValue,px)
    print(pxValue)