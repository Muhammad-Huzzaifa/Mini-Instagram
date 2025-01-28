from copy import deepcopy
from datetime import datetime
from Queue import Queue


class NotificationNode:
    def __init__(self, sender, about, timestamp):
        self.sender = sender
        self.about = about
        self.timestamp = timestamp


class Notification:
    def __init__(self):
        self.notifications = Queue()

    def sendNotification(self, sender, about, now):
        self.notifications.enqueue(NotificationNode(sender, about, now))

    def processNotification(self):
        recent = self.notifications.frontValue()
        self.notifications.dequeue()
        return recent
    
    def clearAllNotifications(self):
        self.notifications.makeNull()

    def getNotifications(self):
        return self.notifications
    
    def viewNotifications(self):
        temp = deepcopy(self.notifications)
        print("<-------------------->")
        while not temp.isEmpty():
            notification = temp.frontValue()
            temp.dequeue()
            print(f"{notification.about} from {notification.sender}")
            timestamp = notification.timestamp
            time = datetime.fromtimestamp(timestamp)
            print("Timestamp: ", time.strftime("%Y-%m-%dT%H:%M:%S"))
            print("<-------------------->")