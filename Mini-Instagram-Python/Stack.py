class StackNode:
    def __init__(self, data, bottom):
        self.data = data
        self.bottom = bottom


class Stack:
    def __init__(self):
        self.top = None

    def find(self, data):
        current = self.top
        while current:
            if current.data == data:
                return current
            current = current.bottom
        return None

    def isEmpty(self):
        return self.top == None
    
    def push(self, data):
        self.top = StackNode(data, self.top)

    def pop(self):
        if self.isEmpty():
            return False
        self.top = self.top.bottom
        return True

    def topValue(self):
        return self.top.data
    
    def makeNull(self):
        self.top = None