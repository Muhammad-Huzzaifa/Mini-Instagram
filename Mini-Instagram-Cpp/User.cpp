#include "User.h"

bool UserNode::operator==(const UserNode& other) const {
	return name == other.name;
}

bool UserNode::operator<(const UserNode& other) const {
	return name < other.name;
}

bool UserNode::operator>(const UserNode& other) const {
	return name > other.name;
}

User::User(UserNode* user, Tree<UserNode>* users, Friend* friends, List<Message>* messages)
	: user{ user }, users{ users }, friends{ friends }, messages{ messages } {
}

User::~User() {}

void User::sendFriendRequest(const string& to) {
	if (user->name == to) {
		cout << "YOU CAN'T SEND FRIEND REQUEST TO YOURSELF\n";
		return;
	}

	if (friends->getFriends().findNode(to) != nullptr) {

		if (friends->haveNoRelation(user->name, to)) {
			friends->sendFriendRequest(user->name, to);
			cout << "FRIEND REQUEST IS SENDED SUCCESSFULLY\n";

			sendNotification(to, "Friend request");
		}

		else {
			cout << "YOU ALREADY HAVE A RELATION " << to << endl;
		}
	}

	else {
		cout << "THERE IS NO USER NAMED " << to << endl;
	}
}

void User::acceptFriendRequest(const string& to) {

	if (friends->havePendingRelation(user->name, to)) {
		friends->acceptFriendRequest(user->name, to);
		cout << "FRIEND REQUEST FROM " << to << " IS ACCESPTED SUCCESSFULLY\n";
	}

	else {
		cout << "THERE IS NO ANY PENDING REQUEST FROM " << to << endl;
	}
}

void User::blockActiveFriend(const string& to) {

	if (!friends->haveNoRelation(user->name, to)) {
		friends->blockActiveFriend(user->name, to);
		cout << "NOW " << to << " AND YOU ARE NOT FRIENDS\n";
	}

	else {
		cout << to << " IS ALREADY NOT IN A FRIEND RELATION\n";
	}
}

void User::viewFriends() {
	friends->viewFriends(user->name);
}

void User::viewFriendSugesstions() {
	Tree<string> suggesstion{ friends->sugestFriends(user->name) };

	if (!suggesstion.isEmpty()) {
		cout << "HERE ARE SOME FRIEND SUGGESSTIONS FOR YOU\n";
		cout << "<-------------------->\n";
		void traverseSuggestionTree(TreeNode<string>*);
		traverseSuggestionTree(suggesstion.getRoot());
	}
	else {
		cout << "NO ANY FRIEND SUGGESSTION FOR YOU\n";
		cout << "<-------------------->\n";
	}
}

void traverseSuggestionTree(TreeNode<string>* root) {
	if (root != nullptr) {
		traverseSuggestionTree(root->left);

		cout << "# " << root->data << endl;
		cout << "<-------------------->\n";

		traverseSuggestionTree(root->right);
	}
}

void User::addPost(const string& content) {
	time_t now{ time(nullptr) };
	user->posts.addPost(content, now);

	List<Edge<string>> friendList{ friends->getFriendList(user->name) };
	ListNode<Edge<string>>* current{ friendList.getHead() };

	while (current != nullptr) {

		if (current->data.weight == "active") {
			sendNotification(current->data.data, "Post");
		}

		current = current->next;
	}

	cout << "<-------------------->\n";
	cout << "POST IS ADDED SUCCESSFULLY\n";
	cout << "<-------------------->\n";
}

void User::deleteRecentPost() {
	if (!user->posts.getPosts().isEmpty()) {
		user->posts.deleteRecentPost();
		cout << "RECENT POST IS DELETED SUCCESSFULLY\n";
		cout << "<-------------------->\n";
	}

	else {
		cout << "NO ANY POST TO DELETE\n";
		cout << "<-------------------->\n";
	}
}

void User::deleteAllPosts() {
	if (!user->posts.getPosts().isEmpty()) {
		user->posts.deleteAllPosts();
		cout << "ALL POSTS DELETED SUCCESSFULLY\n";
		cout << "<-------------------->\n";
	}

	else {
		cout << "NO ANY POST TO DELETE\n";
		cout << "<-------------------->\n";
	}
}

void User::viewPosts() const {
	if (!user->posts.getPosts().isEmpty()) {
		cout << user->name << "\'s POSTS:\n";
		user->posts.viewPosts();
	}

	else {
		cout << "NO ANY POST TO VIEW\n";
		cout << "<-------------------->\n";
	}
}

void User::viewFriendsPosts() const {
	Tree<PostNode> friendsPosts;

	List<Edge<string>> friendList{ friends->getFriendList(user->name) };
	ListNode<Edge<string>>* current{ friendList.getHead() };

	while (current != nullptr) {

		if (current->data.weight == "active") {

			UserNode username{ UserNode() };
			username.name = current->data.data;

			TreeNode<UserNode>* tempUser{ users->find(username) };
			Stack<PostNode> friendPosts{ tempUser->data.posts.getPosts() };

			while (!friendPosts.isEmpty()) {
				PostNode tempPost{ friendPosts.topValue() };
				friendPosts.pop();

				tempPost.content = tempPost.content + " (" + current->data.data + ")";
				friendsPosts.insert(tempPost);
			}
		}

		current = current->next;
	}

	if (!friendsPosts.isEmpty()) {
		void traversePostTree(TreeNode<PostNode>*);
		traversePostTree(friendsPosts.getRoot());
	}

	else {
		cout << "NO ANY POST FROM FRIENDS\n";
		cout << "<-------------------->\n";
	}
}

void traversePostTree(TreeNode<PostNode>* root) {
	if (root != nullptr) {
		traversePostTree(root->right);

		cout << root->data.content << endl;
		tm* time{ localtime(&root->data.timestamp) };
		cout << "TIMESTAMP: " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;
		cout << "<-------------------->\n";

		traversePostTree(root->left);
	}
}

void User::sendMessage(const string& to, const string& content) {
	ListNode<GraphNode<string>>* tempUser{ friends->getFriends().findNode(to) };
	if (tempUser == nullptr) {
		cout << "NO USER NAMED " << to << " EXIST\n";
		return;
	}

	ListNode<Message>* tempMessage{ messages->find(Message(user->name, to)) };

	if (tempMessage != nullptr) {
		time_t now{ time(nullptr) };
		tempMessage->data.sendMessage(user->name, content, now);
		cout << "MESSAGE IS SUCCESSFULLY SENDED TO " << to << endl;
		sendNotification(to, "Message");
	}

	else {
		if (friends->haveActiveRelation(user->name, to)) {
			Message newMessageObj{ Message(user->name, to) };
			time_t now{ time(nullptr) };
			newMessageObj.sendMessage(user->name, content, now);

			messages->insert(newMessageObj);
			cout << "MESSAGE IS SUCCESSFULLY SENDED TO " << to << endl;
			sendNotification(to, "Message");
		}

		else {
			cout << "YOU HAVE NO FRIEND NAMED " << to << endl;
		}
	}
}

void User::deleteRecentMessage(const string& user2) {
	ListNode<GraphNode<string>>* tempUser{ friends->getFriends().findNode(user2) };

	if (tempUser == nullptr) {
		cout << "NO USER NAMED " << user2 << "EXIST\n";
		return;
	}

	ListNode<Message>* tempMessage{ messages->find(Message(user->name, user2)) };

	if (tempMessage != nullptr) {
		tempMessage->data.deleteRecentMessage();

		if (tempMessage->data.getMessages().isEmpty()) {
			messages->remove(Message(user->name, user2));
		}

		cout << "RECENT MESSAGE IS DELETED SUCCESSFULLY\n";
	}

	else {
		cout << "THERE IS NO ANY MESSAGE BETWEEN " << user->name << " AND " << user2 << endl;
	}
}

void User::deleteAllMessages(const string& user2) {
	ListNode<GraphNode<string>>* tempUser{ friends->getFriends().findNode(user2) };
	if (tempUser == nullptr) {
		cout << "NO USER NAMED " << user2 << "EXIST\n";
		return;
	}

	ListNode<Message>* tempMessage{ messages->find(Message(user->name, user2)) };

	if (tempMessage != nullptr) {
		tempMessage->data.deleteAllMessages();
		messages->remove(Message(user->name, user2));
		cout << "ALL MESSAGES ARE DELETED SUCCESSFULLY\n";
	}

	else {
		cout << "THERE IS NO ANY MESSAGE BETWEEN " << user->name << " AND " << user2 << endl;
	}
}

void User::viewCoversation(const string& user2) {
	ListNode<GraphNode<string>>* tempUser{ friends->getFriends().findNode(user2) };
	if (tempUser == nullptr) {
		cout << "NO USER NAMED " << user2 << "EXIST\n";
		cout << "<-------------------->\n";
		return;
	}

	ListNode<Message>* tempMessage{ messages->find(Message(user->name, user2)) };

	if (tempMessage != nullptr) {
		cout << "\nCONVERSATION BETWEEN " << user->name << " AND " << user2 << endl;
		tempMessage->data.viewMessages();
	}

	else {
		cout << "<-------------------->\n";
		cout << "THERE IS NO ANY MESSAGE BETWEEN " << user->name << " AND " << user2 << endl;
		cout << "<-------------------->\n";
	}
}

void User::sendNotification(const string& to, const string& about, const time_t& now) {

	UserNode username{ UserNode() };
	username.name = to;

	TreeNode<UserNode>* tempUser{ users->find(username) };
	tempUser->data.notifications.sendNotification(user->name, about, now);
}

NotificationNode User::processNotification() {
	if (!user->notifications.getNotifications().isEmpty()) {
		return user->notifications.processNotification();
	}

	cout << "THERE IS NO ANY NOTIFICATION TO PROCESS\n";
	return NotificationNode({ "","",0 });
}

void User::clearAllNotifications() {
	if (!user->notifications.getNotifications().isEmpty()) {
		user->notifications.clearAllNotifications();
		cout << "NOTIFICATIONS ARE CLEARED SUCCESSFULLY\n";
	}

	else {
		cout << "THERE IS NO ANY NOTIFICATION TO CLEAR\n";
	}
}

void User::viewNotifications() const {
	if (!user->notifications.getNotifications().isEmpty()) {
		cout << user->name << "\'s NOTIFICATIONS:\n";
		user->notifications.viewNotifications();
	}

	else {
		cout << "<-------------------->\n";
		cout << "THERE IS NO ANY NOTIFICATION FOR YOU\n";
		cout << "<-------------------->\n";
	}
}