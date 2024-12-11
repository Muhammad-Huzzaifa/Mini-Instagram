#include "App.h"

App::App()
	: logedInUser{ nullptr } {
}

App::~App() {}

void App::run() {
	system("cls");
	bool exit{ false };

	while (!exit) {
		cout << "<---WELCOME TO MINI-INSTAGRAM--->\n";
		cout << "1# SIGN UP\n2# LOGIN\n3# EXIT\nENTER YOUR CHOICE: ";
		int choice;
		cin >> choice;

		cin.ignore();
		cout << "<-------------------->\n\n";

		if (choice == 1) {
			signup();
		}
		else if (choice == 2) {
			login();
		}
		else if (choice == 3) {
			cout << "EXITING...\n";
			cout << "<-------------------->\n";
			exit = true;
			break;
		}
		else {
			cout << "INVALID CHOICE...\n";
			cout << "<-------------------->\n";
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("pause");
		system("cls");
	}
}

void App::signup() {
	UserNode user{ UserNode() };

	cout << "<-------------------->\n";
	cout << "ENTER YOUR NAME: ";
	getline(cin, user.name);
	while (!isValidName(user.name) || users.find(user) != nullptr) {
		cout << "INVALID OR ALREADY TAKEN! ENTER AGAIN (Alphabets / Space): ";
		getline(cin, user.name);
	}

	cout << "ENTER YOUR PASSWORD: ";
	getline(cin, user.password);
	while (!isValidPassword(user.password)) {
		cout << "INVALID PASSWORD! ENTER AGAIN (No Space/ No , /At least 8): ";
		getline(cin, user.password);
	}

	cout << "ENTER YOUR CITY: ";
	getline(cin, user.city);
	while (!isValidName(user.city)) {
		cout << "INVALID CITY! ENTER AGAIN (Alphabets / Space): ";
		getline(cin, user.city);
	}

	user.lastLoginTime = 0;

	users.insert(user);
	friends.addUser(user.name);
	loginHash.insertPair(user.name, user.password);

	cout << "<-------------------->\n";
	cout << "ACCOUNT CREATED SUCCESSFULLY\n";
	cout << "<-------------------->\n";
}

void App::login() {
	string name, password;

	cout << "<-------------------->\n";
	cout << "ENTER YOUR NAME: ";
	getline(cin, name);
	while (!isValidName(name)) {
		cout << "INVALID NAME! ENTER AGAIN (Alphabets / Space): ";
		getline(cin, name);
	}

	cout << "ENTER YOUR PASSWORD: ";
	getline(cin, password);
	while (!isValidPassword(password)) {
		cout << "INVALID PASSWORD! ENTER AGAIN (No Space/ No , /At least 8): ";
		getline(cin, password);
	}
	cout << "<-------------------->\n";

	if (loginHash.getPassword(name) == password) {
		cout << "YOU ARE LOGGED IN SUCCESSFULLY\n";
		cout << "<-------------------->\n";

		UserNode tempUser{ UserNode() };
		tempUser.name = name;
		logedInUser = &users.find(tempUser)->data;

		time_t now{ time(nullptr) };
		logedInUser->lastLoginTime = now;

		User user(logedInUser, &users, &friends, &messages);

		system("pause");
		system("cls");

		bool logedOut{ false };
		while (!logedOut) {
			cout << "<---WELCOME " << name << "--->\n";
			cout << " 1# ADD POST\n 2# DELETE RECENT POST\n 3# DELETE ALL POSTS\n 4# VIEW OWN POSTS\n 5# VIEW FRIENDS POSTS\n 6# SEARCH USER\n 7# VIEW FRIEND SUGGESTIONS\n 8# SEND FRIEND REQUEST\n 9# VIEW OWN FRIENDS\n10# BLOCK FRIEND\n11# SEND MESSAGE\n12# VIEW CONVERSATION\n13# DELETE RECENT MESSAGE\n14# DELETE ALL MESSAGES\n15# SHOW NOTIFICATIONS\n16# PROCESS NOTIFICATION\n17# ACCEPT FRIEND REQUEST\n18# LOGOUT\nENTER YOUR CHOICE: ";
			int ichoice;
			cin >> ichoice;

			cin.ignore();
			cout << "<-------------------->\n\n";

			if (ichoice == 1) {
				string content;
				cout << "ENETR CONTENT: ";
				getline(cin, content);
				user.addPost(content);
			}
			else if (ichoice == 2) {
				user.deleteRecentPost();
			}
			else if (ichoice == 3) {
				user.deleteAllPosts();
			}
			else if (ichoice == 4) {
				user.viewPosts();
			}
			else if (ichoice == 5) {
				user.viewFriendsPosts();
			}
			else if (ichoice == 6) {
				search();
			}
			else if (ichoice == 7) {
				user.viewFriendSugesstions();
			}
			else if (ichoice == 8) {
				string username;
				cout << "ENTER USERNAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.sendFriendRequest(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 9) {
				cout << name << "\'s FRIEND LIST:\n";
				user.viewFriends();
			}
			else if (ichoice == 10) {
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.blockActiveFriend(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 11) {
				string username, content;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);
				cout << "ENTER MESSAGE: ";
				getline(cin, content);

				cout << "<-------------------->\n";
				user.sendMessage(username, content);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 12) {
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.viewCoversation(username);
			}
			else if (ichoice == 13) {
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.deleteRecentMessage(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 14) {
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.deleteAllMessages(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 15) {
				user.viewNotifications();
			}
			else if (ichoice == 16) {
				processNotification(user);
			}
			else if (ichoice == 17) {
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.acceptFriendRequest(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 18) {
				cout << "LOGGING OUT...\n";
				cout << "<-------------------->\n";
				logedInUser = nullptr;
				logedOut = true;
				break;
			}
			else {
				cout << "INVALID CHOICE...\n";
				cout << "<-------------------->\n";
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			system("pause");
			system("cls");
		}
	}
	else {
		cout << "INCORRECT NAME OR PASSWORD...\n";
		cout << "<-------------------->\n";
	}
}

void App::search() {
	List<string> searchedUsers;

	string lowerCase(const string&);
	void searchUsers(TreeNode<UserNode>*, const string&, List<string>&);

	string tosearch;
	cout << "ENTER YOUR SEARCH: ";
	getline(cin, tosearch);
	cout << "<-------------------->\n\n";

	searchUsers(users.getRoot(), lowerCase(tosearch), searchedUsers);
	if (!searchedUsers.isEmpty()) {
		cout << "USERS FOUND IN SEARCH:\n";
		cout << "<-------------------->\n";
		ListNode<string>* current{ searchedUsers.getHead() };
		while (current != nullptr) {
			if (current->data != logedInUser->name) {
				cout << "# " << current->data << endl;
				cout << "<-------------------->\n";
			}
			else {
				cout << "# YOU" << endl;
				cout << "<-------------------->\n";
			}
			current = current->next;
		}
	}
	else {
		cout << "NO ANY USER MACHES YOUR SEARCH\n";
		cout << "<-------------------->\n";
	}
}

string lowerCase(const string& original) {
	string lower{ original };
	transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
	return lower;
}

void searchUsers(TreeNode<UserNode>* root, const string& lower, List<string>& searchedUsers) {
	if (root != nullptr) {
		searchUsers(root->right, lower, searchedUsers);

		if (lowerCase(root->data.name).find(lower) != string::npos) {
			searchedUsers.insert(root->data.name);
		}

		searchUsers(root->left, lower, searchedUsers);
	}
}

void App::processNotification(User& user) {
	NotificationNode earliest{ user.processNotification() };

	if (earliest.about == "Friend request") {
		tm* time{ localtime(&earliest.timestamp) };
		cout << "FRIEND REQUEST FROM " << earliest.sender << " AT " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

		cout << "1# ACCEPT FRIEND REQUEST\n2# REJECT FRIEND REQUEST\n3# REMAIN UNSEEN\nENTER YOUR CHOICE: ";
		int rchoice;
		cin >> rchoice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (rchoice != 1 && rchoice != 2 && rchoice != 3) {
			cin >> rchoice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (rchoice == 1) {
			cout << "<-------------------->\n";
			user.acceptFriendRequest(earliest.sender);
			cout << "<-------------------->\n";
		}
		else if (rchoice == 2) {
			cout << "<-------------------->\n";
			user.blockActiveFriend(earliest.sender);
			cout << "<-------------------->\n";
		}
		else if (rchoice == 3) {
			logedInUser->notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp);
			cout << "<-------------------->\n";
		}
	}
	else if (earliest.about == "Message") {
		tm* time{ localtime(&earliest.timestamp) };
		cout << "MESSAGE FROM " << earliest.sender << " AT " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

		cout << "1# VIEW CONVERSATION\n2# MARK AS READ AND GO\n3# REMAIN UNSEEN\nENTER YOUR CHOICE: ";
		int rchoice;
		cin >> rchoice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (rchoice != 1 && rchoice != 2 && rchoice != 3) {
			cin >> rchoice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (rchoice == 1) {
			cout << "<-------------------->\n";
			user.viewCoversation(earliest.sender);
		}
		else if (rchoice == 2) {
			cout << "<-------------------->\n";
		}
		else if (rchoice == 3) {
			logedInUser->notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp);
			cout << "<-------------------->\n";
		}
	}
	else if (earliest.about == "Post") {
		tm* time{ localtime(&earliest.timestamp) };
		cout << "POST FROM " << earliest.sender << " AT " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

		cout << "1# SEE FRIENDS POSTS\n2# MARK AS READ AND GO\n3# REMAIN UNSEEN\nENTER YOUR CHOICE: ";
		int rchoice;
		cin >> rchoice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (rchoice != 1 && rchoice != 2 && rchoice != 3) {
			cin >> rchoice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (rchoice == 1) {
			cout << "<-------------------->\n";
			user.viewFriendsPosts();
		}
		else if (rchoice == 2) {
			cout << "<-------------------->\n";
		}
		else if (rchoice == 3) {
			logedInUser->notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp);
			cout << "<-------------------->\n";
		}
	}
}

void App::loadUsers() {

}

void App::loadFriends() {

}

void App::loadMessages() {

}

void App::saveUsers() {

}

void App::saveFriends() {

}

void App::saveMessages() {

}

bool App::isValidName(const std::string& name) {
	for (char ch : name) {
		if (!isalpha(ch) && !isspace(ch)) {
			return false;
		}
	}
	return !name.empty();
}

bool App::isValidPassword(const std::string& password) {
	if (password.length() < 8) {
		return false;
	}

	for (char ch : password) {
		if (isspace(ch) || ch == ',') {
			return false;
		}
	}
	return true;
}