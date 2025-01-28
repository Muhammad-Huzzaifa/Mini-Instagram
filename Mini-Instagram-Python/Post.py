from copy import deepcopy
from datetime import datetime
from Stack import Stack


class PostNode:
    def __init__(self, content, timestamp):
        self.content = content
        self.timestamp = timestamp

    def __eq__(self, other):
        return self.timestamp == other.timestamp
    
    def __lt__(self, other):
        return self.timestamp < other.timestamp
    
    def __gt__(self, other):
        return self.timestamp > other.timestamp
    

class Post:
    def __init__(self):
        self.posts = Stack()
    
    def addPost(self, content, now):
        self.posts.push(PostNode(content, now))

    def deleteRecentPost(self):
        self.posts.pop()

    def deleteAllPosts(self):
        self.posts.makeNull()

    def getPosts(self):
        return self.posts
    
    def viewPosts(self):
        temp = deepcopy(self.posts)
        print("<-------------------->")
        while not temp.isEmpty():
            post = temp.topValue()
            temp.pop()
            print(f"Content: {post.content}")
            timestamp = post.timestamp
            time = datetime.fromtimestamp(timestamp)
            print("Timestamp: ", time.strftime("%Y-%m-%dT%H:%M:%S"))
            print("<-------------------->")