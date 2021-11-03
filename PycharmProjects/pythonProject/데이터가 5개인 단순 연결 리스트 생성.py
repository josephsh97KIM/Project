class Node():      #Node 클래스 정의
     def __init__ (self):
         self.data = None
         self.link = None

node1 = Node()
node1.data = "A"

node2 = Node()
node2.data = "B"
node1.link = node2 #첫번째 노드의 링크에 두번째 노드의 이름을 입력하여 두 노드를 연결

node3 = Node()
node3.data = "C"
node2.link = node3

node4 = Node()
node4.data= "D"
node3.link = node4

node5 = Node()
node5.data = "E"
node4.link = node5

# print(node1.data, end = ' ')
# print(node1.link.data, end = ' ')
# print(node1.link.link.data, end = ' ')
# print(node1.link.link.link.data, end = ' ')
# print(node1.link.link.link.link.data, end = ' ')

current = node1   #첫번째 노드를 current노드로 지정하고 데이터를 출력
print(current.data, end = ' ')
while current.link !=None :  #현재노드의 링크가 비어있지 않는 동안 반복
    current = current.link
    print(current.data,end = ' ')