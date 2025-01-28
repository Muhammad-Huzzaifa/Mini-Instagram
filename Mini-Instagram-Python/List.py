class ListNode:
    def __init__(self, data, next):
        self.data = data
        self.next = next


class List:
    def __init__(self):
        self.head = None

    def getHead(self):
        return self.head

    def find(self, data):
        current = self.head
        while current:
            if current.data == data:
                return current
            current = current.next
        return None

    def isEmpty(self):
        return self.head == None

    def insert(self, data):
        self.head = ListNode(data, self.head)

    def remove(self, data):
        if self.head == None:
            return False
        if self.head.data == data:
            self.head = self.head.next
        previous = None
        current = self.head
        while current:
            if current.data == data:
                if previous:
                    previous.next = current.next
                else:
                    self.head = current.next
                return True
            previous = current
            current = current.next
        return False

    def makeNull(self):
        self.head = None