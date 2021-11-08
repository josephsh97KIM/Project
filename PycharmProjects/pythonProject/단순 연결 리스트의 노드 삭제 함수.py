##클래스와 함수 선언
class Node() :
    def __init__ (self):
        self.data = None
        self.link = None

def printNodes(start) :
    current = start
    if current == None:
        return
    print(current.data, end=' ')
    while current.link != None:
        current = current.link
        print(current.data, end=' ')
    print()

def deleteNode(deleteData) :
    global memory, head, current, pre

    if head.data == deleteData:
        current = head
        head = head.link
        del(current)
        return

    current = head
    while current.link !=None :
        pre = current
        current = current.link
        if current.data == deleteData:
            pre.link = current.link
            del(current)
            return

##전역 변수 선언 부분
memory = []
head, current, pre =None,None,None
dataArray = ["a","b","c","d","e"]
if __name__=="__main__" :

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

    deleteNode("a")
    printNodes(head)

    deleteNode("c")
    printNodes(head)

    deleteNode("e")
    printNodes(head)

    deleteNode("1")
    printNodes(head)