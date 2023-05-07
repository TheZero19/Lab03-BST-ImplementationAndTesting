#pragma once
#include "pch.h"

#include"BinarySearchTree.h"
#include<iostream>
#include<vector>
#include<tuple>

using namespace std;

int BinarySearchTree::size() {
	return sizeCount;
}

void BinarySearchTree::add(int key, std::string value) {
	//Expected only positive values of keys in the tree.
	Node* newNode = new Node(key, value);
	Node* temp = root;
	if (root == NULL) {
		root = newNode;
		sizeCount += 1;
	}
	else {
		sizeCount += 1;
		while (temp != nullptr) {
			if (key <= temp->key) {
				if (temp->left == nullptr) {
					temp->left = newNode;
					//cout << " " << temp->left->value;
					break;
				}
				temp = temp->left;
			}
			else {
				if (temp->right == nullptr) {
					temp->right = newNode;
					//cout << " " << temp->right->value;
					break;
				}
				temp = temp->right;
			}

		}
	}
	return;
}

//FOR RETURNING VALUE FOR A SPECIFIC KEY:
std::string BinarySearchTree::search(int key) {
	Node* temp = root;
	if (temp == nullptr) {
		std::cout << "TREE EMPTY!" << std::endl;
		return "False";
	}
	else {
		while (temp != nullptr) {
			if (key < temp->key) {
				temp = temp->left;
			}
			else if (key > temp->key) {
				temp = temp->right;
			}
			else {
				return temp->value;
			}
		}
		std::cout << "KEY OUT OF BOUND!" << std::endl;
		return "False";
	}
}


//tuple in c++ has to be pre-defined for what datatype will occur at given indices.
std::tuple<int, std::string> BinarySearchTree::smallest() {
	Node* temp = root;
	if (root == nullptr) {
		return make_tuple(-1, "TREE EMPTY!");
	}
	else {
		while (temp->left != nullptr) {
			temp = temp->left;
		}
		return make_tuple(temp->key, temp->value);
	}
}

std::tuple<int, std::string> BinarySearchTree::largest() {
	Node* temp = root;
	if (root == NULL) {
		return make_tuple(-1, "TREE EMPTY!");
	}
	else {
		while (temp->right != NULL) {
			temp = temp->right;
		}
		return make_tuple(temp->key, temp->value);
	}
}


//IN-ORDER WALK:
void recursiveInOrderWalk(Node* temp, std::vector<int>& inOrderTraversal) {

	if (temp == nullptr) {
		return;
	}
	else {
		recursiveInOrderWalk(temp->left, inOrderTraversal);
		inOrderTraversal.push_back(temp->key); //storing into the referenced variable the keys traversed.
		recursiveInOrderWalk(temp->right, inOrderTraversal);
	}
}

std::vector<int> BinarySearchTree::inorder_walk() {
	std::vector<int> traversal; //to store the keys that will be traversed
	recursiveInOrderWalk(root, traversal); //passing by reference
	return traversal;
}

//PRE-ORDER WALK:
void recursivePreOrderWalk(Node* temp, std::vector<int>& preOrderTraversal) {
	if (temp == nullptr) {
		return;
	}
	else {
		preOrderTraversal.push_back(temp->key);
		recursivePreOrderWalk(temp->left, preOrderTraversal);
		recursivePreOrderWalk(temp->right, preOrderTraversal);
	}
}

std::vector<int> BinarySearchTree::preorder_walk() {
	//similar implementation as of IN-ORDER-WALK.
	std::vector<int> traversal;
	recursivePreOrderWalk(root, traversal);
	return traversal;
}


//POST-ORDER WALK:
void recursivePostOrderWalk(Node* temp, std::vector<int>& postOrderTraversal) {
	if (temp == nullptr) {
		return;
	}
	else {
		recursivePostOrderWalk(temp->left, postOrderTraversal);
		recursivePostOrderWalk(temp->right, postOrderTraversal);
		postOrderTraversal.push_back(temp->key);
	}
}


std::vector<int> BinarySearchTree::postorder_walk() {
	//similar implementation as of IN-ORDER-WALK.
	std::vector<int> traversal;
	recursivePostOrderWalk(root, traversal);
	return traversal;
}


std::string BinarySearchTree::remove(int key) {
	Node* temp = root;
	Node* parent = nullptr; //to keep track of current node's parent.
	if (temp == nullptr) {
		return "TREE EMPTY";
	}
	else {
		while (temp != nullptr) {
			if (key < temp->key) {
				parent = temp;
				temp = temp->left;
			}
			else if (key > temp->key) {
				parent = temp;
				temp = temp->right;
			}
			//else block: if the key is found
			else if (key == temp->key) {
				//for only right child
				if (temp->left == nullptr) {
					if (parent == nullptr) {
						temp = temp->right;
					}
					else if(parent->left == temp) {
						parent->left = temp->right;
					}
					else {
						parent->right = temp->right;
					}
				}
				//for only left child
				else if (temp->right == nullptr) {
					if (parent == nullptr) {
						temp = temp->left;
					}
					else if (parent->left == temp) {
						parent->left = temp->left;
					}
					else {
						parent->right = temp->left;
					}
					delete temp;
				}
				//case for both child
				else {
					Node* smallestNodeRightSubtree = temp->right;
					//navigate to the smallest key bearing node in the right sub-tree:
					while (smallestNodeRightSubtree->left != nullptr) {
						smallestNodeRightSubtree = smallestNodeRightSubtree->left;
					}
					//copy values to the root node
					temp->key = smallestNodeRightSubtree->key;
					temp->value = smallestNodeRightSubtree->value;

					if (temp->right == smallestNodeRightSubtree) {
						temp->right = smallestNodeRightSubtree->right;
					}
					else {
						parent = temp;
						Node* temp2 = smallestNodeRightSubtree->right;
						while (temp2 != nullptr && temp2 != smallestNodeRightSubtree) {
							parent = temp2;
							temp2 = temp2->left;
						}
						parent->left = smallestNodeRightSubtree->right;
					}

					//delete the least key bearing node in the right subtree
					delete smallestNodeRightSubtree;
					smallestNodeRightSubtree = nullptr;
				}
				sizeCount = sizeCount - 1;
				return ""; //returning nill string for keys found and deleted
			}

			else {
				//if the key is not found in the tree:
				return "False";
			}
		}

	}
}
