#pragma once
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "Stack.h"
using namespace std;

struct PostNode {
	string content;
	time_t timestamp;

	bool operator==(const PostNode&) const;
	bool operator<(const PostNode&) const;
	bool operator>(const PostNode&) const;
};

class Post {
public:
	Post();
	~Post();

	void addPost(const string&, const time_t&);
	void deleteRecentPost();
	void deleteAllPosts();

	Stack<PostNode> getPosts() const;
	void viewPosts() const;

public:
	Stack<PostNode> posts;
};