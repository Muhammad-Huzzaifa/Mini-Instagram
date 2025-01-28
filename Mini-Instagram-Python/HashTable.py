class Pair:
    def __init__(self, username, password, next):
        self.username = username
        self.password = password
        self.next = next
    

class HashTable:
    def __init__(self):
        self.size = 50
        self.indexesFilled = 0
        self.arr = [None] * self.size
    
    def __hashFunction(self, username):
        hash = 0
        for char in username:
            hash += ord(char)
        return hash % self.size

    def __resize(self):
        tempSize = self.size
        self.size *= 2
        newArr = [None] * self.size
        for i in range(tempSize):
            current = self.arr[i]
            while current:
                next = current.next
                index = self.__hashFunction(current.username)
                current.next = newArr[index]
                newArr[index] = current
                current = next
        self.arr = newArr

    def insertPair(self, username, password):
        index = self.__hashFunction(username)
        if self.arr[index] == None:
            self.indexesFilled += 1
        current = self.arr[index]
        while current:
            if current.username == username:
                return
            current = current.next
        self.arr[index] = Pair(username, password, self.arr[index])
        if self.indexesFilled > (self.size * 0.8):
            self.__resize()

    def existUsername(self, username):
        index = self.__hashFunction(username)
        current = self.arr[index]
        while current:
            if current.username == username:
                return True
            current = current.next
        return False

    def getPassword(self, username):
        index = self.__hashFunction(username)
        current = self.arr[index]
        while current:
            if current.username == username:
                return current.password
            current = current.next
        return None