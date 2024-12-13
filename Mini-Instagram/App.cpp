#include "App.h"

App::App()
	: logedInUser{nullptr}
{
	loadUsers();
	loadFriends();
	loadMessages();
}

App::~App()
{
	saveUsers();
	saveFriends();
	saveMessages();
}

void App::run()
{
	system("cls");
	bool exit{false};

	while (!exit)
	{
		cout << "<---WELCOME TO MINI-INSTAGRAM--->\n";
		cout << "1# SIGN UP\n2# LOGIN\n3# EXIT\nENTER YOUR CHOICE: ";
		int choice;
		cin >> choice;

		cin.ignore();
		cout << "<-------------------->\n\n";

		if (choice == 1)
		{
			signup();
		}
		else if (choice == 2)
		{
			login();
		}
		else if (choice == 3)
		{
			cout << "EXITING...\n";
			cout << "<-------------------->\n";
			exit = true;
			break;
		}
		else
		{
			cout << "INVALID CHOICE...\n";
			cout << "<-------------------->\n";
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("pause");
		system("cls");
	}
}

void App::signup()
{
	UserNode user{UserNode()};

	cout << "<-------------------->\n";
	cout << "ENTER YOUR NAME: ";
	getline(cin, user.name);
	while (!isValidName(user.name) || users.find(user) != nullptr)
	{
		cout << "INVALID OR ALREADY TAKEN! ENTER AGAIN (Alphabets / Space): ";
		getline(cin, user.name);
	}

	cout << "ENTER YOUR PASSWORD: ";
	getline(cin, user.password);
	while (!isValidPassword(user.password))
	{
		cout << "INVALID PASSWORD! ENTER AGAIN (No Space/ No , /At least 8): ";
		getline(cin, user.password);
	}

	cout << "ENTER YOUR CITY: ";
	getline(cin, user.city);
	while (!isValidName(user.city))
	{
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

void App::login()
{
	string name, password;

	cout << "<-------------------->\n";
	cout << "ENTER YOUR NAME: ";
	getline(cin, name);
	while (!isValidName(name))
	{
		cout << "INVALID NAME! ENTER AGAIN (Alphabets / Space): ";
		getline(cin, name);
	}

	cout << "ENTER YOUR PASSWORD: ";
	getline(cin, password);
	while (!isValidPassword(password))
	{
		cout << "INVALID PASSWORD! ENTER AGAIN (No Space/ No , /At least 8): ";
		getline(cin, password);
	}
	cout << "<-------------------->\n";

	if (loginHash.getPassword(name) == password)
	{
		cout << "YOU ARE LOGGED IN SUCCESSFULLY\n";
		cout << "<-------------------->\n";

		UserNode tempUser{UserNode()};
		tempUser.name = name;
		logedInUser = &users.find(tempUser)->data;

		time_t now{time(nullptr)};
		logedInUser->lastLoginTime = now;

		User user(logedInUser, &users, &friends, &messages);

		system("pause");
		system("cls");

		bool logedOut{false};
		while (!logedOut)
		{
			cout << "<---WELCOME " << name << "--->\n";
			cout << " 1# ADD POST\n 2# DELETE RECENT POST\n 3# DELETE ALL POSTS\n 4# VIEW OWN POSTS\n 5# VIEW FRIENDS POSTS\n 6# SEARCH USER\n 7# VIEW FRIEND SUGGESTIONS\n 8# SEND FRIEND REQUEST\n 9# VIEW OWN FRIENDS\n10# BLOCK FRIEND\n11# SEND MESSAGE\n12# VIEW CONVERSATION\n13# DELETE RECENT MESSAGE\n14# DELETE ALL MESSAGES\n15# SHOW NOTIFICATIONS\n16# PROCESS NOTIFICATION\n17# ACCEPT FRIEND REQUEST\n18# LOGOUT\nENTER YOUR CHOICE: ";
			int ichoice;
			cin >> ichoice;

			cin.ignore();
			cout << "<-------------------->\n\n";

			if (ichoice == 1)
			{
				string content;
				cout << "ENETR CONTENT: ";
				getline(cin, content);
				user.addPost(content);
			}
			else if (ichoice == 2)
			{
				user.deleteRecentPost();
			}
			else if (ichoice == 3)
			{
				user.deleteAllPosts();
			}
			else if (ichoice == 4)
			{
				user.viewPosts();
			}
			else if (ichoice == 5)
			{
				user.viewFriendsPosts();
			}
			else if (ichoice == 6)
			{
				search();
			}
			else if (ichoice == 7)
			{
				user.viewFriendSugesstions();
			}
			else if (ichoice == 8)
			{
				string username;
				cout << "ENTER USERNAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.sendFriendRequest(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 9)
			{
				cout << name << "\'s FRIEND LIST:\n";
				user.viewFriends();
			}
			else if (ichoice == 10)
			{
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.blockActiveFriend(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 11)
			{
				string username, content;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);
				cout << "ENTER MESSAGE: ";
				getline(cin, content);

				cout << "<-------------------->\n";
				user.sendMessage(username, content);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 12)
			{
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.viewCoversation(username);
			}
			else if (ichoice == 13)
			{
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.deleteRecentMessage(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 14)
			{
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.deleteAllMessages(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 15)
			{
				user.viewNotifications();
			}
			else if (ichoice == 16)
			{
				processNotification(user);
			}
			else if (ichoice == 17)
			{
				string username;
				cout << "ENTER FRIEND\'S NAME: ";
				getline(cin, username);

				cout << "<-------------------->\n";
				user.acceptFriendRequest(username);
				cout << "<-------------------->\n";
			}
			else if (ichoice == 18)
			{
				cout << "LOGGING OUT...\n";
				cout << "<-------------------->\n";
				logedInUser = nullptr;
				logedOut = true;
				break;
			}
			else
			{
				cout << "INVALID CHOICE...\n";
				cout << "<-------------------->\n";
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			system("pause");
			system("cls");
		}
	}
	else
	{
		cout << "INCORRECT NAME OR PASSWORD...\n";
		cout << "<-------------------->\n";
	}
}

void App::search()
{
	List<string> searchedUsers;

	string lowerCase(const string &);
	void searchUsers(TreeNode<UserNode> *, const string &, List<string> &);

	string tosearch;
	cout << "ENTER YOUR SEARCH: ";
	getline(cin, tosearch);
	cout << "<-------------------->\n\n";

	searchUsers(users.getRoot(), lowerCase(tosearch), searchedUsers);
	if (!searchedUsers.isEmpty())
	{
		cout << "USERS FOUND IN SEARCH:\n";
		cout << "<-------------------->\n";
		ListNode<string> *current{searchedUsers.getHead()};
		while (current != nullptr)
		{
			if (current->data != logedInUser->name)
			{
				cout << "# " << current->data << endl;
				cout << "<-------------------->\n";
			}
			else
			{
				cout << "# YOU" << endl;
				cout << "<-------------------->\n";
			}
			current = current->next;
		}
	}
	else
	{
		cout << "NO ANY USER MACHES YOUR SEARCH\n";
		cout << "<-------------------->\n";
	}
}

string lowerCase(const string &original)
{
	string lower{original};
	transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
	return lower;
}

void searchUsers(TreeNode<UserNode> *root, const string &lower, List<string> &searchedUsers)
{
	if (root != nullptr)
	{
		searchUsers(root->right, lower, searchedUsers);

		if (lowerCase(root->data.name).find(lower) != string::npos)
		{
			searchedUsers.insert(root->data.name);
		}

		searchUsers(root->left, lower, searchedUsers);
	}
}

void App::processNotification(User &user)
{
	NotificationNode earliest{user.processNotification()};

	if (earliest.about == "Friend request")
	{
		tm *time{localtime(&earliest.timestamp)};
		cout << "FRIEND REQUEST FROM " << earliest.sender << " AT " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

		cout << "1# ACCEPT FRIEND REQUEST\n2# REJECT FRIEND REQUEST\n3# REMAIN UNSEEN\nENTER YOUR CHOICE: ";
		int rchoice;
		cin >> rchoice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (rchoice != 1 && rchoice != 2 && rchoice != 3)
		{
			cin >> rchoice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (rchoice == 1)
		{
			cout << "<-------------------->\n";
			user.acceptFriendRequest(earliest.sender);
			cout << "<-------------------->\n";
		}
		else if (rchoice == 2)
		{
			cout << "<-------------------->\n";
			user.blockActiveFriend(earliest.sender);
			cout << "<-------------------->\n";
		}
		else if (rchoice == 3)
		{
			logedInUser->notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp);
			cout << "<-------------------->\n";
		}
	}
	else if (earliest.about == "Message")
	{
		tm *time{localtime(&earliest.timestamp)};
		cout << "MESSAGE FROM " << earliest.sender << " AT " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

		cout << "1# VIEW CONVERSATION\n2# MARK AS READ AND GO\n3# REMAIN UNSEEN\nENTER YOUR CHOICE: ";
		int rchoice;
		cin >> rchoice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (rchoice != 1 && rchoice != 2 && rchoice != 3)
		{
			cin >> rchoice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (rchoice == 1)
		{
			cout << "<-------------------->\n";
			user.viewCoversation(earliest.sender);
		}
		else if (rchoice == 2)
		{
			cout << "<-------------------->\n";
		}
		else if (rchoice == 3)
		{
			logedInUser->notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp);
			cout << "<-------------------->\n";
		}
	}
	else if (earliest.about == "Post")
	{
		tm *time{localtime(&earliest.timestamp)};
		cout << "POST FROM " << earliest.sender << " AT " << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

		cout << "1# SEE FRIENDS POSTS\n2# MARK AS READ AND GO\n3# REMAIN UNSEEN\nENTER YOUR CHOICE: ";
		int rchoice;
		cin >> rchoice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (rchoice != 1 && rchoice != 2 && rchoice != 3)
		{
			cin >> rchoice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (rchoice == 1)
		{
			cout << "<-------------------->\n";
			user.viewFriendsPosts();
		}
		else if (rchoice == 2)
		{
			cout << "<-------------------->\n";
		}
		else if (rchoice == 3)
		{
			logedInUser->notifications.sendNotification(earliest.sender, earliest.about, earliest.timestamp);
			cout << "<-------------------->\n";
		}
	}
}

void App::traverseForSaving(ofstream &ufile, ofstream &pfile, ofstream &nfile, TreeNode<UserNode> *root)
{
	if (root != nullptr) {
		traverseForSaving(ufile, pfile, nfile, root->left);

		UserNode user{ root->data };
		
		ufile << user.name << ',' << user.password << ',' << user.city << ',';

		time_t t{ user.lastLoginTime };
		tm* time{ localtime(&t) };
		ufile << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;
		
		Stack<PostNode> posts{ user.posts.getPosts() };
		Stack<PostNode> temp;

		while (!posts.isEmpty()) {
			temp.push(posts.topValue());
			posts.pop();
		}

		pfile << user.name << endl;
		while (!temp.isEmpty()) {
			pfile << temp.topValue().content << endl;

			t = temp.topValue().timestamp;
			time = localtime(&t);
			pfile << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

			temp.pop();
		}
		pfile << endl;


		Queue<NotificationNode> notifications{ user.notifications.getNotifications() };

		nfile << user.name << endl;
		while (!notifications.isEmpty()) {
			nfile << notifications.frontValue().sender << ',' << notifications.frontValue().about << ',';
			
			t = notifications.frontValue().timestamp;
			time = localtime(&t);
			nfile << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

			notifications.dequeue();
		}
		nfile << endl;

		traverseForSaving(ufile, pfile, nfile, root->right);
	}
}

void App::loadUsers()
{
	ifstream file{"userinfo.csv"};

	if (!file.is_open())
	{
		cout << "Error in opening userinfo.csv file.\n";
		return;
	}

	string line;
	while (getline(file, line))
	{

		while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
		{
			line.pop_back();
		}

		if (line.empty())
		{
			break;
		}

		stringstream ss{line};
		UserNode user;

		getline(ss, user.name, ',');
		getline(ss, user.password, ',');
		getline(ss, user.city, ',');

		tm tm = {};
		ss >> get_time(&tm, "%Y-%m-%dT%H:%M:%S");
		user.lastLoginTime = mktime(&tm);

		loginHash.insertPair(user.name, user.password);

		users.insert(user);
		friends.addUser(user.name);
	}

	file.close();

	file.open("posts.txt");

	if (!file.is_open())
	{
		cout << "Error in opening posts.txt file.\n";
		return;
	}

	while (getline(file, line))
	{

		while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
		{
			line.pop_back();
		}

		if (line.empty())
		{
			break;
		}

		UserNode usern;
		usern.name = line;
		TreeNode<UserNode> *user{users.find(usern)};

		string inner;
		while (getline(file, inner))
		{

			while (!inner.empty() && (inner.back() == '\n' || inner.back() == '\r'))
			{
				inner.pop_back();
			}

			if (inner.empty())
			{
				break;
			}

			string post{inner};

			string timestamp;
			getline(file, timestamp);
			while (!timestamp.empty() && (timestamp.back() == '\n' || timestamp.back() == '\r'))
			{
				timestamp.pop_back();
			}

			stringstream ss{timestamp};
			tm tm = {};
			ss >> get_time(&tm, "%Y-%m-%dT%H:%M:%S");

			user->data.posts.addPost(post, mktime(&tm));
		}
	}

	file.close();

	file.open("notifications.txt");

	if (!file.is_open())
	{
		cout << "Error in opening notifications.txt file.\n";
		return;
	}

	while (getline(file, line))
	{

		while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
		{
			line.pop_back();
		}

		if (line.empty())
		{
			break;
		}

		UserNode usern;
		usern.name = line;
		TreeNode<UserNode> *user{users.find(usern)};

		string inner;
		while (getline(file, inner))
		{

			while (!inner.empty() && (inner.back() == '\n' || inner.back() == '\r'))
			{
				inner.pop_back();
			}

			if (inner.empty())
			{
				break;
			}

			stringstream ss{inner};
			string sender, about;

			getline(ss, sender, ',');
			getline(ss, about, ',');

			tm tm = {};
			ss >> get_time(&tm, "%Y-%m-%dT%H:%M:%S");

			user->data.notifications.sendNotification(sender, about, mktime(&tm));
		}
	}

	file.close();
}

void App::loadFriends()
{
	ifstream file{"friends.csv"};

	if (!file.is_open())
	{
		cout << "Error in opening friends.csv file.\n";
		return;
	}

	string line;
	while (getline(file, line))
	{

		while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
		{
			line.pop_back();
		}

		if (line.empty())
		{
			break;
		}

		stringstream ss{line};

		string name;
		getline(ss, name, ',');

		string edge;
		while (getline(ss, edge, ','))
		{
			string status;
			string frinedName;

			stringstream sse{edge};

			getline(sse, status, ':');
			getline(sse, frinedName);

			if (status == "pending")
			{
				friends.sendFriendRequest(name, frinedName);
			}

			if (status == "active")
			{
				friends.sendFriendRequest(name, frinedName);
				friends.acceptFriendRequest(frinedName, name);
			}
		}
	}

	file.close();
}

void App::loadMessages()
{
	ifstream file{"messages.txt"};

	if (!file.is_open())
	{
		cout << "Error in opening messages.txt file.\n";
		return;
	}

	string line;
	while (getline(file, line))
	{

		while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
		{
			line.pop_back();
		}

		if (line.empty())
		{
			break;
		}

		string user1{line};
		string user2;

		getline(file, user2);
		while (!user2.empty() && (user2.back() == '\n' || user2.back() == '\r'))
		{
			user2.pop_back();
		}

		Message message(user1, user2);

		string inner;
		while (getline(file, inner))
		{

			while (!inner.empty() && (inner.back() == '\n' || inner.back() == '\r'))
			{
				inner.pop_back();
			}

			if (inner.empty())
			{
				break;
			}

			stringstream ss{inner};
			string sender, content;

			getline(ss, sender, ':');
			getline(ss, content);

			string timestamp;
			getline(file, timestamp);
			while (!timestamp.empty() && (timestamp.back() == '\n' || timestamp.back() == '\r'))
			{
				timestamp.pop_back();
			}

			stringstream sst{timestamp};
			tm tm = {};
			sst >> get_time(&tm, "%Y-%m-%dT%H:%M:%S");

			message.sendMessage(sender, content, mktime(&tm));
		}

		messages.insert(message);
	}

	file.close();
}

void App::saveUsers()
{
	ofstream ufile{"userinfo.csv"};
	ofstream pfile{"posts.txt"};
	ofstream nfile{"notifications.txt"};

	if (!ufile.is_open())
	{
		cout << "Error in opening userinfo.csv file.\n";
		return;
	}

	if (!pfile.is_open())
	{
		cout << "Error in opening posts.txt file.\n";
		return;
	}

	if (!nfile.is_open())
	{
		cout << "Error in opening notifications.txt file.\n";
		return;
	}

	traverseForSaving(ufile, pfile, nfile, users.getRoot());

	ufile.close();
	pfile.close();
	nfile.close();
}

void App::saveFriends()
{
	ofstream file{"friends.csv"};

	if (!file.is_open())
	{
		cout << "Error in opening friends.csv file.\n";
		return;
	}

	Graph<string> temp{friends.getFriends()};

	ListNode<GraphNode<string>> *current{temp.firstNode()};
	while (current != nullptr)
	{
		file << current->data.data << ',';

		ListNode<Edge<string>> *currEdge{current->data.adjacencyList.getHead()};
		while (currEdge != nullptr)
		{
			file << currEdge->data.weight << ':' << currEdge->data.data;

			if (currEdge->next != nullptr)
			{
				file << ',';
			}

			currEdge = currEdge->next;
		}
		file << endl;

		current = current->next;
	}

	file.close();
}


void App::saveMessages()
{
	ofstream file{"messages.txt"};

	if (!file.is_open())
	{
		cout << "Error in opening messaes.txt file.\n";
		return;
	}

	ListNode<Message> *current{messages.getHead()};
	while (current != nullptr)
	{
		file << current->data.getUsers().first << endl
			 << current->data.getUsers().second << endl;

		Stack<MessageNode> messageStack{current->data.getMessages()};
		Stack<MessageNode> temp;

		while (!messageStack.isEmpty())
		{
			temp.push(messageStack.topValue());
			messageStack.pop();
		}

		while (!temp.isEmpty())
		{
			file << temp.topValue().sender << ':' << temp.topValue().content << endl;

			time_t t{temp.topValue().timestamp};
			tm *time{localtime(&t)};
			file << put_time(time, "%Y-%m-%dT%H:%M:%S") << endl;

			temp.pop();
		}
		file << endl;

		current = current->next;
	}

	file.close();
}

bool App::isValidName(const std::string &name)
{
	for (char ch : name)
	{
		if (!isalpha(ch) && !isspace(ch))
		{
			return false;
		}
	}
	return !name.empty();
}

bool App::isValidPassword(const std::string &password)
{
	if (password.length() < 8)
	{
		return false;
	}

	for (char ch : password)
	{
		if (isspace(ch) || ch == ',')
		{
			return false;
		}
	}
	return true;
}