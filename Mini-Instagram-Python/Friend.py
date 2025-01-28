from Graph import Graph
from Tree import Tree


class Friend:
    def __init__(self):
        self.friends = Graph()

    def haveActiveRelation(self, user1, user2):
        user1Node = self.friends.findNode(user1)
        user1RelationUser2 = self.friends.findEdge(user1, user2)
        if user1Node and user1RelationUser2 and user1RelationUser2.weight == "active":
            return True
        return False
    
    def havePendingRelation(self, user1, user2):
        user1Node = self.friends.findNode(user1)
        user1RelationUser2 = self.friends.findEdge(user1, user2)
        if user1Node and user1RelationUser2 and user1RelationUser2.weight == "pending":
            return True
        return False
    
    def haveNoRelation(self, user1, user2):
        user1Node = self.friends.findNode(user1)
        user1RelationUser2 = self.friends.findEdge(user1, user2)
        if user1Node == None or user1RelationUser2 == None:
            return True
        return False
    
    def addUser(self, user):
        self.friends.addNode(user)
    
    def removeUser(self, user):
        self.friends.removeNode(user)

    def sendFriendRequest(self, fromNode, toNode):
        self.friends.addEdge(fromNode, toNode, "pending")
    
    def acceptFriendRequest(self, fromNode, toNode):
        self.friends.changeEdgeWeight(fromNode, toNode, "active")

    def blockActiveFriend(self, fromNode, toNode):
        self.friends.removeEdge(fromNode, toNode)

    def sugestFriends(self, user):
        userFriendList = self.getFriendList(user)
        userFriends = userFriendList.getHead()
        suggestions = Tree()
        while userFriends:
            friendFriendList = self.getFriendList(userFriends.data.data)
            friendFriends = friendFriendList.getHead()
            while friendFriends:
                if user != friendFriends.data.data and self.haveNoRelation(user, friendFriends.data.data):
                    suggestions.insert(friendFriends.data.data)
                friendFriends = friendFriends.next
            userFriends = userFriends.next
        return suggestions

    def getFriends(self):
        return self.friends

    def getFriendList(self, user):
        return self.friends.findNode(user).data.adjacencyList

    def viewFriends(self, user):
        current = self.findNode(user).data.adjacencyList.getHead()
        if current:
            print("<-------------------->")
            while current:
                print(f"Name: {current.data.data}, Status: {current.data.weight}")
                print("<-------------------->")
                current = current.next
        else:
            print("<-------------------->")
            print(f"{user} has no any friend.")
            print("<-------------------->")