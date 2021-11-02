##클래스와 한수 선언 부분
class Node():
    def __init__ (self):
        self.data = None
        self.data = None

def printNodes(start):
    current = start
    if current == None:
        return
    print(current.data, end=' ')
    while current.link != None :
        current = current.link
        print(current.data, end=' ')
    print()

##전역 변수 선언 부분
memory = []
head, current, pre =None,None,None
dataArray = ["a","b","c","d","e"]

##메인 코드 부분
if __name__=="__main__":

    node = Node()
    node.data = dataArray[0]
    head = node
    memory.append(node)

    for data in dataArray[1:]:
        pre = node
        node = Node()
        node.data= data
        pre.link=node
        memory.append(node)

    printNodes(head)