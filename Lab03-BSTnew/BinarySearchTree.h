#pragma once

#include"pch.h"
#include<string>
#include<vector>
#include<tuple>

class Node {
public:

	int key;
	std::string value;
	Node* left;
	Node* right;

	Node(int key, std::string value) {
		this->key = key;
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
	}
};

class BinarySearchTree {
private:
	int sizeCount;

public:
	Node* root;

	BinarySearchTree() {
		this->sizeCount = 0;
		this->root = nullptr;
	}

	//required functions:
	int size();
	void add(int key, std::string value);
	std::string search(int key);
	std::tuple<int, std::string> smallest();
	std::tuple<int, std::string> largest();
	std::string remove(int key);

	//traversal
	//using vector for having mutable datatype similar to lists in python.
	std::vector<int> inorder_walk(); 
	std::vector<int> preorder_walk();
	std::vector<int> postorder_walk();

};