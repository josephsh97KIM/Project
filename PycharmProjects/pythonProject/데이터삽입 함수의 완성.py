data =  ["a","b","c","d","e"]

def insert_data(position,plus):

    if position <0 or position >len(data):
        print("데이터를 삽입할 범위를 벗어났습니다.")
        return

    data.append(None)    #빈칸 추가
    kLen = len(data)     #배열 크기

    for i in range(kLen-1, position, -1):
        data[i] = data[i-1]
        data[i-1] = None

    data[position]= plus #지정위치 알파벳 추가

insert_data(2, 'f')
print(data)
insert_data(6,'g')
print(data)
