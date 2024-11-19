# Mini Instagram

Mini Instagram is a simplified version of Instagram built using custom data structures such as Linked Lists, Graphs, Stacks, Queues, and Binary Search Trees (BST). The system simulates a social media platform where users can interact with each other through friend requests, messaging, and posts. This project demonstrates the implementation of these data structures in a real-world context while adhering to object-oriented principles.

## Features

- **User Profile:**
  - Each user has a profile with attributes like name, password, city, posts, and last login timestamp.
  - Friend relationships are modeled as edges with attributes like status (active, blocked, pending).

- **Users and Relationships:**
  - Users are represented in a graph where each user is a node and friendships are edges.
  - Pending friend requests are managed using a queue, and login credentials are verified with hash lookup.

- **Messages:**
  - A stack is used to store messages between users, with the most recent message at the top.

- **Posts:**
  - Users can post content, which is stored in a stack, and followers see posts in their newsfeed.

- **Friend Request Management:**
  - Friend requests are handled using a queue, with the oldest request processed first.

- **Notifications:**
  - Notifications such as new friend requests, accepted requests, and messages are managed in a queue.

- **Real-Time Messaging:**
  - Messages are queued and dequeued to emulate real-time communication between users.

- **Search Users:**
  - Users are stored in a Binary Search Tree (BST), allowing efficient O(log n) search by username.

## Menu Functionalities

1. **Signup**:
   - Validates unique usernames and enforces password strength rules.
   
2. **Login**:
   - Password resets via security questions with history stored in a file.
   
3. **Logout**:
   - Allows users to log out from their account.

4. **Follow Request**:
   - Displays pending follow requests and allows bulk approvals.

5. **Cancel and Accept Requests**:
   - Notifies the user when a request is accepted.

6. **Posts**:
   - Displays posts from followers in a timeline.

7. **Notifications**:
   - Displays unread notifications in a queue.

8. **Messaging**:
   - Allows users to send messages to their followers.

9. **Search Users**:
   - Allows searching for users by name using a BST traversal.

10. **Followers List**:
    - Displays a list of a user's followers.

11. **Newsfeed**:
    - Displays a user's own posts.

## Data Structures Used

- **Graph**: To represent users and their relationships.
- **Queue**: To manage friend requests, notifications, and messages.
- **Stack**: For messages and posts, with the most recent message/post at the top.
- **Binary Search Tree (BST)**: For storing users in sorted order by username for efficient search.
- **HashMap**: For username and password lookup during login.

## Project Structure

The project is organized into three main files:

1. **UserProfile.h**: Contains classes for user profiles, managing user data, and relationships.
2. **NetworkManager.h**: Manages friend requests, messages, and notifications.
3. **Main.cpp**: The main driver program implementing the user interface and menu functionalities.

## How to Run

1. Clone the repository:
    ```bash
    git clone https://github.com/Muhammad-Huzzaifa/Mini-Instagram.git
    cd Mini-Instagram
    ```

2. Compile the project:
    ```bash
    g++ -o Mini_Instagram Main.cpp
    ```

3. Run the project:
    ```bash
    ./Mini_Instagram
    ```

## Example

Here’s an example of how to interact with the system:

1. **Signup**: Create a new user profile with a unique username, password, and city.
2. **Login**: Log in using your username and password.
3. **Send Friend Request**: Send a friend request to another user.
4. **Post**: Create a new post, which will appear in the newsfeed of your followers.
5. **Send Message**: Send messages to your friends.
6. **Check Notifications**: View pending notifications, such as new friend requests.



Happy coding! 🎉
