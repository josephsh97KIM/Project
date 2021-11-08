##클래스와 함수 선언 부분
class Node():
    def __init__(self):
        self.data = None
        self.link = None

def printNodes(start):
    current = start
    if current == None :
        return
    print(current.data, end = ' ')
    while current.link != None:
        current = current.link
        print(current.data, end = ' ')
    print()

def findNode(findData):
    global memory, head, current, pre

    current = head
    if current.data == findData:
        return current
    while current.link != None :
        current = current.link
        if current.data == findData:
            return current
    return Node()

#전역 변수 선언 부분
memory = []
head, current, pre = None, None, None
dataArray = ["a","b","c","d","e"]

##메인 코드
if __name__ == "__main__" :

    node = Node()
    node.data = dataArray[0]
    head = node
    memory.append(node)

    for data in dataArray[1:]:
        pre = node
        node = Node()
        node.data = data
        pre.link = node
        memory.append(node)

    printNodes(head)

    fNode = findNode("a")
    print(fNode.data)

    fNode = findNode("c")
    print(fNode.data)

    fNode = findNode("1")
    print(fNode.data)