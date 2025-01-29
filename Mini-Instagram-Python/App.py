from os import system
from datetime import datetime
from csv import reader
from List import List
from Stack import Stack
from Tree import Tree
from Friend import Friend
from Message import Message
from User import User, UserNode
from HashTable import HashTable


class App:
    def __init__(self):
        self.logedInUser = None
        self.users = Tree()
        self.friends = Friend()
        self.messages = List()
        self.loginHash = HashTable()
        self.loadUsers()
        self.loadFriends()
        self.loadMessages()
    
    def __del__(self):
        self.saveUsers()
        self.saveFriends()
        self.saveMessages()
    
    def __isValidName(self, name):
        return all(ch.isalpha() or ch.isspace() for ch in name) and bool(name)

    def __isValidPassword(self, password):
        if len(password) < 8:
            return False
        if any(ch.isspace() or ch == ',' for ch in password):
            return False
        return True

    def run(self):
        system("cls")
        exit = False
        while not exit:
            print("<---WELCOME TO MINI-INSTAGRAM--->")
            choice = input("1# SIGN UP\n2# LOGIN\n3# EXIT\nENTER YOUR CHOICE: ")
            print("<-------------------->\n")
            if choice == '1':
                self.signup()
            elif choice == '2':
                self.login()
            elif choice == '3':
                print("EXITING...")
                print("<-------------------->")
                exit = True
                break
            else:
                print("INVALID CHOICE...")
                print("<-------------------->")
            input("Press Enter to continue...")
            system("cls")

    def signup(self):
        user = UserNode()
        print("<-------------------->")
        user.name = input("ENTER YOUR NAME: ")
        while not self.__isValidName(user.name) or self.users.find(user):
            user.name = input("INVALID OR ALREADY TAKEN! ENTER AGAIN (Alphabets / Space): ")
        user.password = input("ENTER YOUR PASSWORD: ")
        while not self.__isValidPassword(user.password):
            user.password = input("INVALID PASSWORD! ENTER AGAIN (No Space/ No , /At least 8): ")
        user.city = input("ENTER YOUR CITY: ")
        while not self.__isValidName(user.city):
            user.city = input("INVALID CITY! ENTER AGAIN (Alphabets / Space): ")
        user.lastLoginTime = 0
        self.users.insert(user)
        self.friends.addUser(user.name)
        self.loginHash.insertPair(user.name, user.password)
        print("<-------------------->")
        print("ACCOUNT CREATED SUCCESSFULLY")
        print("<-------------------->")

    def login(self):
        print("<-------------------->")
        name = input("ENTER YOUR NAME: ")
        while not self.__isValidName(name):
            name = input("INVALID NAME! ENTER AGAIN (Alphabets / Space): ")
        password = input("ENTER YOUR PASSWORD: ")
        while not self.__isValidPassword(password):
            password = input("INVALID PASSWORD! ENTER AGAIN (No Space/ No , /At least 8): ")
        print("<-------------------->")
        if self.loginHash.getPassword(name) == password:
            print("YOU ARE LOGGED IN SUCCESSFULLY")
            print("<-------------------->")
            tempUser = UserNode()
            tempUser.name = name
            self.logedInUser = self.users.find(tempUser).data
            now = datetime.now().timestamp()
            self.logedInUser.lastLoginTime = now
            user = User(self.logedInUser, self.users, self.friends, self.messages)
            input("Press Enter to continue...")
            system("cls")
            logedOut = False
            while not logedOut:
                print(f"<---WELCOME {name}--->")
                print(" 1# ADD POST\n 2# DELETE RECENT POST\n 3# DELETE ALL POSTS\n 4# VIEW OWN POSTS\n 5# VIEW FRIENDS POSTS\n 6# SEARCH USER\n 7# VIEW FRIEND SUGGESTIONS\n 8# SEND FRIEND REQUEST\n 9# VIEW OWN FRIENDS\n10# BLOCK FRIEND\n11# SEND MESSAGE\n12# VIEW CONVERSATION\n13# DELETE RECENT MESSAGE\n14# DELETE ALL MESSAGES\n15# SHOW NOTIFICATIONS\n16# PROCESS NOTIFICATION\n17# ACCEPT FRIEND REQUEST\n18# LOGOUT")
                ichoice = input("ENTER YOUR CHOICE: ")
                print("<-------------------->\n")
                if ichoice == '1':
                    content = input("ENTER CONTENT: ")
                    user.addPost(content)
                elif ichoice == '2':
                    user.deleteRecentPost()
                elif ichoice == '3':
                    user.deleteAllPosts()
                elif ichoice == '4':
                    user.viewPosts()
                elif ichoice == '5':
                    user.viewFriendsPosts()
                elif ichoice == '6':
                    self.search()
                elif ichoice == '7':
                    user.viewFriendSugesstions()
                elif ichoice == '8':
                    username = input("ENTER USERNAME: ")
                    print("<-------------------->")
                    user.sendFriendRequest(username)
                    print("<-------------------->")
                elif ichoice == '9':
                    print(f"{name}'s FRIEND LIST:")
                    user.viewFriends()
                elif ichoice == '10':
                    username = input("ENTER FRIEND'S NAME: ")
                    print("<-------------------->")
                    user.blockActiveFriend(username)
                    print("<-------------------->")
                elif ichoice == '11':
                    username = input("ENTER FRIEND'S NAME: ")
                    content = input("ENTER MESSAGE: ")
                    print("<-------------------->")
                    user.sendMessage(username, content)
                    print("<-------------------->")
                elif ichoice == '12':
                    username = input("ENTER FRIEND'S NAME: ")
                    print("<-------------------->")
                    user.viewCoversation(username)
                elif ichoice == '13':
                    username = input("ENTER FRIEND'S NAME: ")
                    print("<-------------------->")
                    user.deleteRecentMessage(username)
                    print("<-------------------->")
                elif ichoice == '14':
                    username = input("ENTER FRIEND'S NAME: ")
                    print("<-------------------->")
                    user.deleteAllMessages(username)
                    print("<-------------------->")
                elif ichoice == '15':
                    user.viewNotifications()
                elif ichoice == '16':
                    self.processNotification(user)
                elif ichoice == '17':
                    username = input("ENTER FRIEND'S NAME: ")
                    print("<-------------------->")
                    user.acceptFriendRequest(username)
                    print("<-------------------->")
                elif ichoice == '18':
                    print("LOGGING OUT...")
                    print("<-------------------->")
                    self.logedInUser = None
                    logedOut = True
                    break
                else:
                    print("INVALID CHOICE...")
                    print("<-------------------->")

                input("Press Enter to continue...")
                system("cls")
        else:
            print("INCORRECT NAME OR PASSWORD...")
            print("<-------------------->")

    def search(self):
        def searchUsers(root, name, searchedUsers):
            if root:
                searchUsers(root.left, name, searchedUsers)
                if name in root.data.name.lower():
                    searchedUsers.insert(root.data.name)
                searchUsers(root.right, name, searchedUsers)
        searchedUsers = List()
        tosearch = input("ENTER YOUR SEARCH: ")
        print("<-------------------->\n")
        searchUsers(self.users.root, tosearch.lower(), searchedUsers)
        if not searchedUsers.isEmpty():
            print("USERS FOUND IN SEARCH: ")
            print("<-------------------->")
            current = searchedUsers.getHead()
            while current:
                if current.data != self.logedInUser.name:
                    print(f"# {current.data}")
                    print("<-------------------->")
                else:
                    print("# YOU")
                    print("<-------------------->")
                current = current.next
        else:
            print("NO USERS FOUND IN SEARCH...")
            print("<-------------------->")

    def processNotification(self, user):
        earliest = user.processNotification()
        if earliest.about == "Friend request":
            time = datetime.fromtimestamp(earliest.timestamp)
            print(f"FRIEND REQUEST FROM {earliest.sender} AT {time.strftime('%Y-%m-%dT%H:%M:%S')}")
            print("1# ACCEPT FRIEND REQUEST\n2# REJECT FRIEND REQUEST\n3# REMAIN UNSEEN")
            rchoice = input("ENTER YOUR CHOICE: ")
            while rchoice not in ['1', '2', '3']:
                rchoice = input("INVALID CHOICE! ENTER AGAIN: ")
            if rchoice == '1':
                print("<-------------------->")
                user.acceptFriendRequest(earliest.sender)
                print("<-------------------->")
            elif rchoice == '2':
                print("<-------------------->")
                user.blockActiveFriend(earliest.sender)
                print("<-------------------->")
            else:
                self.logedInUser.notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp)
                print("<-------------------->")
        elif earliest.about == "Message":
            time = datetime.fromtimestamp(earliest.timestamp)
            print(f"MESSAGE FROM {earliest.sender} AT {time.strftime('%Y-%m-%dT%H:%M:%S')}")
            print("1# VIEW CONVERSATION\n2# MARK AS READ AND GO\n3# REMAIN UNSEEN")
            rchoice = input("ENTER YOUR CHOICE: ")
            while rchoice not in ['1', '2', '3']:
                rchoice = input("INVALID CHOICE! ENTER AGAIN: ")
            if rchoice == '1':
                print("<-------------------->")
                user.viewCoversation(earliest.sender)
            elif rchoice == '2':
                print("<-------------------->")
            else:
                self.logedInUser.notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp)
                print("<-------------------->")
        elif earliest.about == "Post":
            time = datetime.fromtimestamp(earliest.timestamp)
            print(f"POST FROM {earliest.sender} AT {time.strftime('%Y-%m-%dT%H:%M:%S')}")
            print("1# SEE FRIENDS POSTS\n2# MARK AS READ AND GO\n3# REMAIN UNSEEN")
            rchoice = input("ENTER YOUR CHOICE: ")
            while rchoice not in ['1', '2', '3']:
                rchoice = input("INVALID CHOICE! ENTER AGAIN: ")
            if rchoice == '1':
                print("<-------------------->")
                user.viewFriendsPosts()
            elif rchoice == '2':
                print("<-------------------->")
            else:
                self.logedInUser.notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp)
                print("<-------------------->")

    def loadUsers(self):
        try:
            with open("userinfo.csv", newline='') as file:
                read = reader(file)
                for row in read:
                    row = [col.strip() for col in row]
                    if not row:
                        continue
                    user = UserNode()
                    user.name, user.password, user.city = row[:3]
                    user.lastLoginTime = datetime.strptime(row[3], "%Y-%m-%dT%H:%M:%S").timestamp()
                    self.loginHash.insertPair(user.name, user.password)
                    self.users.insert(user)
                    self.friends.addUser(user.name)
        except FileNotFoundError:
            print("Error in opening userinfo.csv file.")
            return
        
        try:
            with open("posts.txt", newline='') as file:
                while True:
                    line = file.readline().strip()
                    if not line:
                        break
                    usern = UserNode()
                    usern.name = line
                    user = self.users.find(usern)
                    if not user:
                        continue

                    while True:
                        inner = file.readline().strip()
                        if not inner:
                            break
                        post = inner
                        timestamp = file.readline().strip()
                        if not timestamp:
                            continue
                        post_time = datetime.strptime(timestamp, "%Y-%m-%dT%H:%M:%S").timestamp()
                        user.data.posts.addPost(post, post_time)
        except FileNotFoundError:
            print("Error in opening posts.txt file.")
            return

        try:
            with open("notifications.txt", newline='') as file:
                while True:
                    line = file.readline().strip()
                    if not line:
                        break
                    usern = UserNode()
                    usern.name = line
                    user = self.users.find(usern)
                    if not user:
                        continue
                    while True:
                        inner = file.readline().strip()
                        if not inner:
                            break
                        sender, about, timestamp = inner.split(',')
                        notification_time = datetime.strptime(timestamp.strip(), "%Y-%m-%dT%H:%M:%S").timestamp()
                        user.data.notifications.sendNotification(sender.strip(), about.strip(), notification_time)
        except FileNotFoundError:
            print("Error in opening notifications.txt file.")
            return

    def loadFriends(self):
        try:
            with open("friends.csv", newline='') as file:
                for line in file:
                    line = line.strip()
                    if not line:
                        continue
                    parts = line.split(',')
                    name = parts[0].strip()
                    for edge in parts[1:]:
                        status, friendName = edge.split(':')
                        status = status.strip()
                        friendName = friendName.strip()
                        if status == "pending":
                            self.friends.sendFriendRequest(name, friendName)
                        elif status == "active":
                            self.friends.sendFriendRequest(name, friendName)
                            self.friends.acceptFriendRequest(friendName, name)
        except FileNotFoundError:
            print("Error in opening friends.csv file.")

    def loadMessages(self):
        try:
            with open("messages.txt", newline='') as file:
                while True:
                    line = file.readline().strip()
                    if not line:
                        break
                    user1 = line
                    user2 = file.readline().strip()
                    if not user2:
                        break
                    message = Message(user1, user2)
                    while True:
                        inner = file.readline().strip()
                        if not inner:
                            break
                        sender, content = inner.split(':', 1)
                        sender = sender.strip()
                        content = content.strip()
                        timestamp = file.readline().strip()
                        if not timestamp:
                            continue
                        message_time = datetime.strptime(timestamp, "%Y-%m-%dT%H:%M:%S").timestamp()
                        message.sendMessage(sender, content, message_time)
                    self.messages.insert(message)
        except FileNotFoundError:
            print("Error in opening messages.txt file.")

    def saveUsers(self):
        def traverseForSaving(ufile, pfile, nfile, root):
            if root:
                traverseForSaving(ufile, pfile, nfile, root.left)
                user = root.data
                ufile.write(f"{user.name},{user.password},{user.city},")
                ufile.write(f"{datetime.fromtimestamp(user.lastLoginTime).strftime('%Y-%m-%dT%H:%M:%S')}\n")
                posts = user.posts.getPosts()
                temp = Stack()
                while not posts.isEmpty():
                    temp.push(posts.topValue())
                    posts.pop()
                pfile.write(f"{user.name}\n")
                while not temp.isEmpty():
                    post = temp.topValue()
                    pfile.write(f"{post.content}\n")
                    pfile.write(f"{datetime.fromtimestamp(post.timestamp).strftime('%Y-%m-%dT%H:%M:%S')}\n")
                    temp.pop()
                pfile.write("\n")
                notifications = user.notifications.getNotifications()
                nfile.write(f"{user.name}\n")
                while not notifications.isEmpty():
                    notif = notifications.frontValue()
                    nfile.write(f"{notif.sender},{notif.about},")
                    nfile.write(f"{datetime.fromtimestamp(notif.timestamp).strftime('%Y-%m-%dT%H:%M:%S')}\n")
                    notifications.dequeue()
                nfile.write("\n")
                traverseForSaving(ufile, pfile, nfile, root.right)
        try:
            with open("userinfo.csv", "w") as ufile, open("posts.txt", "w") as pfile, open("notifications.txt", "w") as nfile:
                traverseForSaving(ufile, pfile, nfile, self.users.root)
        except IOError as e:
            print(f"Error in opening file: {e}")

    def saveFriends(self):
        try:
            with open("friends.csv", "w") as file:
                temp = self.friends.getFriends()
                current = temp.firstNode()
                while current:
                    file.write(f"{current.data.data},")
                    currEdge = current.data.adjacencyList.getHead()
                    edges = []
                    while currEdge:
                        edges.append(f"{currEdge.data.weight}:{currEdge.data.data}")
                        currEdge = currEdge.next
                    file.write(",".join(edges) + "\n")
                    current = current.next
        except IOError as e:
            print(f"Error in opening friends.csv file: {e}")

    def saveMessages(self):
        try:
            with open("messages.txt", "w") as file:
                current = self.messages.getHead()
                while current:
                    file.write(f"{current.data.getUsers().first}\n{current.data.getUsers().second}\n")
                    messageStack = current.data.getMessages()
                    temp = Stack()
                    while not messageStack.isEmpty():
                        temp.push(messageStack.topValue())
                        messageStack.pop()
                    while not temp.isEmpty():
                        file.write(f"{temp.topValue().sender}:{temp.topValue().content}\n")
                        file.write(f"{datetime.fromtimestamp(temp.topValue().timestamp).strftime('%Y-%m-%dT%H:%M:%S')}\n")
                        temp.pop()
                    file.write("\n")
                    current = current.next
        except IOError as e:
            print(f"Error in opening messages.txt file: {e}")