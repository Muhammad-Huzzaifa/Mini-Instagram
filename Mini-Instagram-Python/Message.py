from copy import deepcopy
from datetime import datetime
from Stack import Stack


class MessageNode:
    def __init__(self, sender, content, timestamp):
        self.sender = sender
        self.content = content
        self.timestamp = timestamp


class Message:
    def __init__(self, user1, user2):
        self.user1 = user1
        self.user2 = user2
        self.messages = Stack()

    def sendMessage(self, sender, content, now):
        self.messages.push(MessageNode(sender, content, now))
    
    def deleteRecentMessage(self):
        self.messages.pop()

    def deleteAllMessages(self):
        self.messages.makeNull()
    
    def getUsers(self):
        return self.user1, self.user2
    
    def getMessages(self):
        return self.messages
    
    def viewMessages(self):
        temp = deepcopy(self.messages)
        if not temp.isEmpty():
            print("<-------------------->")
            while not temp.isEmpty():
                message = temp.topValue()
                temp.pop()
                print(f"{message.sender}: {message.content}")
                timestamp = message.timestamp
                time = datetime.fromtimestamp(timestamp)
                print("Timestamp: ", time.strftime("%Y-%m-%dT%H:%M:%S"))
                print("<-------------------->")
        else:
            print("<-------------------->")
            print(f"There is no any message between {self.user1} and {self.user2}")
            print("<-------------------->")
    
    def __eq__(self, other):
        return (
            self.user1 == other.user1 and self.user2 == other.user2 or
            self.user1 == other.user2 and self.user2 == other.user1
        )