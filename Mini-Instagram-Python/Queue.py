class QueueNode:
    def __init__(self, data, next):
        self.data = data
        self.next = next


class Queue:
    def __init__(self):
        self.front = None
        self.rear = None

    def find(self, data):
        current = self.front
        while current:
            if current.data == data:
                return current
            current = current.next
        return None
    
    def isEmpty(self):
        return self.front == None
    
    def enqueue(self, data):
        if self.isEmpty():
            self.front = self.rear = QueueNode(data, None)
        else:
            self.rear.next = QueueNode(data, None)
            self.rear = self.rear.next

    def dequeue(self):
        if self.isEmpty():
            return False
        if self.front == self.rear:
            self.front = self.rear = None
        else:
            self.front = self.front.next
        return True
    
    def frontValue(self):
        return self.front.data
    
    def makeNull(self):
        self.front = self.rear = None