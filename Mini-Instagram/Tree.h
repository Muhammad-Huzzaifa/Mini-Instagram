#pragma once
#include <algorithm>
using namespace std;

template <typename T>
struct TreeNode {
	T data;
	TreeNode<T>* left, * right;
	TreeNode(const T&);
};

template <typename T>
class Tree {
public:
	Tree();
	Tree(const Tree<T>&);
	~Tree();

	Tree<T>& operator=(const Tree<T>&);

	TreeNode<T>* getRoot() const;

	TreeNode<T>* find(const T&) const;
	bool isEmpty() const;

	bool insert(const T&);
	bool remove(const T&);

	void makeNull();

public:
	TreeNode<T>* root;

	void copyTreeHelper(TreeNode<T>*);
	void deleteTreeHelper(TreeNode<T>*&);
	TreeNode<T>* findHelper(TreeNode<T>*, const T&) const;
	bool insertHelper(TreeNode<T>*&, const T&);
	bool removeHelper(TreeNode<T>*&, const T&);

	void rotateRight(TreeNode<T>*&);
	void rotateLeft(TreeNode<T>*&);
	int height(TreeNode<T>*);
	int balanceFactor(TreeNode<T>*);
};

template <typename T>
TreeNode<T>::TreeNode(const T& data)
	: data{ data }, left{ nullptr }, right{ nullptr } {
}

template <typename T>
Tree<T>::Tree()
	: root{ nullptr } {
}

template <typename T>
Tree<T>::Tree(const Tree<T>& other) {
	root = nullptr;
	if (other.root != nullptr) {
		copyTreeHelper(other.root);
	}
}

template <typename T>
Tree<T>::~Tree() {
	makeNull();
}

template <typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other) {
	if (this != &other) {
		makeNull();
		if (other.root != nullptr) {
			copyTreeHelper(other.root);
		}
	}
	return this;
}

template <typename T>
TreeNode<T>* Tree<T>::getRoot() const {
	return root;
}

template <typename T>
TreeNode<T>* Tree<T>::find(const T& data) const {
	return findHelper(root, data);
}

template <typename T>
bool Tree<T>::isEmpty() const {
	return root == nullptr;
}

template <typename T>
bool Tree<T>::insert(const T& data) {
	return insertHelper(root, data);
}

template <typename T>
bool Tree<T>::remove(const T& data) {
	return removeHelper(root, data);
}

template <typename T>
void Tree<T>::makeNull() {
	deleteTreeHelper(root);
}

template <typename T>
void Tree<T>::copyTreeHelper(TreeNode<T>* node) {
	if (node == nullptr) {
		return;
	}
	insert(node->data);
	copyTreeHelper(node->left);
	copyTreeHelper(node->right);
}

template <typename T>
void Tree<T>::deleteTreeHelper(TreeNode<T>*& temp) {
	if (temp != nullptr) {
		deleteTreeHelper(temp->left);
		deleteTreeHelper(temp->right);
		delete temp;
		temp = nullptr;
	}
}

template <typename T>
TreeNode<T>* Tree<T>::findHelper(TreeNode<T>* temp, const T& data) const {
	if (temp == nullptr) {
		return nullptr;
	}

	if (data < temp->data) {
		return findHelper(temp->left, data);
	}
	else if (data > temp->data) {
		return findHelper(temp->right, data);
	}
	else {
		return temp;
	}
}

template <typename T>
bool Tree<T>::insertHelper(TreeNode<T>*& temp, const T& data) {
	if (temp == nullptr) {
		temp = new TreeNode<T>(data);
		return true;
	}

	if (data < temp->data) {
		insertHelper(temp->left, data);
	}
	else if (data > temp->data) {
		insertHelper(temp->right, data);
	}
	else {
		return false;
	}

	if (balanceFactor(temp) > 1) {
		if (data < temp->left->data) {
			rotateRight(temp);
		}
		else {
			rotateLeft(temp->left);
			rotateRight(temp);
		}
	}
	else if (balanceFactor(temp) < -1) {
		if (data > temp->right->data) {
			rotateLeft(temp);
		}
		else {
			rotateRight(temp->right);
			rotateLeft(temp);
		}
	}

	return true;
}

template <typename T>
bool Tree<T>::removeHelper(TreeNode<T>*& temp, const T& data) {
	if (temp == nullptr) {
		return false;
	}

	if (data < temp->data) {
		removeHelper(temp->left, data);
	}
	else if (data > temp->data) {
		removeHelper(temp->right, data);
	}
	else {
		if (temp->left == nullptr && temp->right == nullptr) {
			delete temp;
			temp = nullptr;
		}
		else if (temp->left != nullptr && temp->right == nullptr) {
			TreeNode<T>* to_delete{ temp };
			temp = temp->left;
			delete to_delete;
			to_delete = nullptr;
		}
		else if (temp->left == nullptr && temp->right != nullptr) {
			TreeNode<T>* to_delete{ temp };
			temp = temp->right;
			delete to_delete;
			to_delete = nullptr;
		}
		else {
			TreeNode<T>* predecessor{ temp->left };
			while (predecessor->right != nullptr) {
				predecessor = predecessor->right;
			}

			temp->data = predecessor->data;

			removeHelper(temp->left, predecessor->data);
		}
	}

	if (temp == nullptr) {
		return true;
	}

	if (balanceFactor(temp) > 1) {
		if (balanceFactor(temp->left) >= 0) {
			rotateRight(temp);
		}
		else {
			rotateLeft(temp->left);
			rotateRight(temp);
		}
	}
	else if (balanceFactor(temp) < -1) {
		if (balanceFactor(temp->right) <= 0) {
			rotateLeft(temp);
		}
		else {
			rotateRight(temp->right);
			rotateLeft(temp);
		}
	}
	return true;
}

template <typename T>
void Tree<T>::rotateRight(TreeNode<T>*& temp) {
	TreeNode<T>* leftChild{ temp->left };

	temp->left = leftChild->right;
	leftChild->right = temp;

	temp = leftChild;
}

template <typename T>
void Tree<T>::rotateLeft(TreeNode<T>*& temp) {
	TreeNode<T>* rightChild{ temp->right };

	temp->right = rightChild->left;
	rightChild->left = temp;

	temp = rightChild;
}

template <typename T>
int Tree<T>::height(TreeNode<T>* temp) {
	if (temp == nullptr) {
		return -1;
	}

	return 1 + max(height(temp->left), height(temp->right));
}

template <typename T>
int Tree<T>::balanceFactor(TreeNode<T>* temp) {
	return height(temp->left) - height(temp->right);
}