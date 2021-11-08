class Node() :
    def __init__ (self) :
        self.data = None
        self.link = None

node1 = Node()
node1.data = "a"
node1.link = node1

node2 = Node()
node2.data = "b"
node1.link = node2
node2.link = node1

node3 = Node()
node3.data = "c"
node2.link = node3
node3.link = node1

node4 = Node()
node4.data = "d"
node3.link = node4
node4.link = node1

node5 = Node()
node5.data = "e"
node4.link = node5
node5.link = node1

current = node1
print(current.data, end = ' ')
while current.link != node1:
    current = current.link
    print(current.data, end= ' ')