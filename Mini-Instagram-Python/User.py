from copy import deepcopy
from datetime import datetime
from Post import Post
from Notification import Notification
from Friend import Friend
from Message import Message
from Tree import Tree


class UserNode:
    def __init__(self):
        self.name = None
        self.password = None
        self.city = None
        self.lastLoginTime = None
        self.posts = Post()
        self.notifications = Notification()

        def __eq__(self, other):
            return self.name == other.name
        
        def __lt__(self, other):
            return self.name < other.name
        
        def __gt__(self, other):
            return self.name > other.name


class User:
    def __init__(self, user, users, friends, messages):
        self.user = user
        self.users = users
        self.friends = friends
        self.messages = messages

    def sendFriendRequest(self, toNode):
        if self.user.name == toNode:
            print("YOU CAN'T SEND FRIEND REQUEST TO YOURSELF")
            return
        if self.friends.getFriends().findNode(toNode):
            if self.friends.haveNoRelation(self.user.name, toNode):
                self.friends.sendFriendRequest(self.user.name, toNode)
                print("FRIEND REQUEST IS SENDED SUCCESSFULLY")
                self.sendNotification(toNode, "Friend request")
            else:
                print(f"YOU ALREADY HAVE A RELATION WITH {toNode}")
        else:
            print(f"THERE IS NO USER NAMED {toNode}")

    def acceptFriendRequest(self, toNode):
        if self.friends.havePendingRelation(self.user.name, toNode):
            self.friends.acceptFriendRequest(self.user.name, toNode)
            print(f"FRIEND REQUEST FROM {toNode} IS ACCEPTED SUCCESSFULLY")
        else:
            print(f"THERE IS NO PENDING FRIEND REQUEST FROM {toNode}")

    def blockActiveFriend(self, toNode):
        if not self.friends.haveNoRelation(self.user.name, toNode):
            self.friends.blockActiveFriend(self.user.name, toNode)
            print(f"NOW {toNode} AND YOU ARE NOT FRIENDS")
        else:
            print(f"{toNode} IS ALREADY NOT IN A FRIEND RELATION")

    def viewFriends(self):
        self.friends.viewFriends(self.user.name)

    def viewFriendSugesstions(self):
        def traverseSuggestionTree(root):
            if root:
                traverseSuggestionTree(root.left)
                print(f"# {root.data}")
                print("<-------------------->")
                traverseSuggestionTree(root.right)
        suggesstions = self.friends.sugestFriends(self.user.name)
        if not suggesstions.isEmpty():
            print("HERE ARE SOME FRIEND SUGESSTIONS FOR YOU")
            print("<-------------------->")
            traverseSuggestionTree(suggesstions.getRoot())
        else:
            print("THERE IS NO FRIEND SUGESSTION FOR YOU")
            print("<-------------------->")
    
    def addPost(self, content):
        now = datetime.now().timestamp()
        self.user.posts.addPost(content, now)
        friendList = self.friends.getFriendList(self.user.name)
        current = friendList.getHead()
        while current:
            if current.data.weight == "active":
                self.sendNotification(current.data.data, "Post")
            current = current.next
        print("<-------------------->")
        print("POST IS ADDED SUCCESSFULLY")
        print("<-------------------->")

    def deleteRecentPost(self):
        if not self.user.posts.getPosts().isEmpty():
            self.user.posts.deleteRecentPost()
            print("RECENT POST IS DELETED SUCCESSFULLY")
            print("<-------------------->")
        else:
            print("THERE IS NO POST TO DELETE")
            print("<-------------------->")

    def deleteAllPosts(self):
        if not self.user.posts.getPosts().isEmpty():
            self.user.posts.deleteAllPosts()
            print("RECENT POST IS DELETED SUCCESSFULLY")
            print("<-------------------->")
        else:
            print("THERE IS NO POST TO DELETE")
            print("<-------------------->")

    def viewPosts(self):
        if not self.user.posts.getPosts().isEmpty():
            print(f"{self.user.name}'s POSTS:")
            self.user.posts.viewPosts()
        else:
            print("THERE IS NO POST TO SHOW")
            print("<-------------------->")

    def viewFriendsPosts(self):
        def traversePostTree(root):
            if root:
                traversePostTree(root.left)
                print(root.data.content)
                timestamp = root.data.timestamp
                time = datetime.fromtimestamp(timestamp)
                print("TIMESTAMP: ", time.strftime("%Y-%m-%dT%H:%M:%S"))
                print("<-------------------->")
                traversePostTree(root.right)
        friendsPosts = Tree()
        friendList = self.friends.getFriendList(self.user.name)
        current = friendList.getHead()
        while current:
            if current.data.weight == "active":
                username = UserNode()
                username.name = current.data.data
                tempUser = self.users.find(username)
                friendPosts = deepcopy(tempUser.data.posts.getPosts())
                while not friendPosts.isEmpty():
                    tempPost = friendPosts.topValue()
                    friendPosts.pop()
                    tempPost.content = f"{tempPost.content} ({current.data.data})"
                    friendsPosts.insert(tempPost)
            current = current.next
        if not friendsPosts.isEmpty():
            traversePostTree(friendsPosts.getRoot())
        else:
            print("THERE IS NO FRIEND POST TO SHOW")
            print("<-------------------->")

    def sendMessage(self, toNode, content):
        pass

    def deleteRecentMessage(self, user2):
        pass

    def deleteAllMessages(self, user2):
        pass

    def viewConversation(self, user2):
        pass

    def sendNotification(self, toNode, about, now):
        pass
    
    def processNotification(self):
        pass

    def clearAllNotifications(self):
        pass

    def viewNotifications(self):
        pass