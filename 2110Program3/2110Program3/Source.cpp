#include<iostream>
#include<fstream>
#include<vector>
#include<conio.h>
#include<cmath>

//tree

struct Node {

	Node();
	Node(int v);
	Node(int v, int d);

	int    value;
	int    depth;
	Node*  left;
	Node*  right;
};

struct Tree {

	Tree();

	Node*  headNode;
	int    depth;

	void  addNode(Node*& newNode);
	void  search();
	void  printDepth();
	void  printTree();
};



int main()
{
	std::ifstream in;    // ifstream for data file
	int tmp;
	char response;

	// open data file and import head node
	in.open("tree1.txt");
	in >> tmp;
	// allocate data for tree and head node
	Tree* tree = new Tree;
	tree->headNode = new Node(tmp, 1);
	Node* newNode;
	// import remainder of list into tree
	while (in.good()) {
		in >> tmp;
		newNode = new Node(tmp);
		tree->addNode(newNode);
	}
	in.close();

	tree->printDepth();

	do {
		tree->search();
		std::cout << "\n\nAnother Search? (Y/N): ";
		response = _getch();

	} while (response == 'y' || response == 'Y');

	delete tree;

	return 0;
}

void Tree::printDepth() {
	std::cout << "\nTree depth: " << depth << std::endl;
}

// takes in tree's head node and the search value
void Tree::search()
{
	int searchValue;
	Node* currentNode = headNode;
	std::cout << "\nEnter search value: ";
	std::cin >> searchValue;

	while (searchValue != currentNode->value)
	{
		if (searchValue < currentNode->value && currentNode->left != nullptr) {
			if (currentNode->left->value == searchValue) {
				std::cout << currentNode->value << " -> " << searchValue;
				return;
			}
			else {
				std::cout << currentNode->value << " -> ";
				currentNode = currentNode->left;
			}
		}

		else if (searchValue > currentNode->value && currentNode->right != nullptr) {
			if (currentNode->right->value == searchValue) {
				std::cout << currentNode->value << " -> " << searchValue;
				return;
			}
			else {
				std::cout << currentNode->value << " -> ";
				currentNode = currentNode->right;
			}
		}
		else {
			std::cout << currentNode->value;
			std::cout << "\nNo " << searchValue << " was found...";
			return;
		}
	}
}

void Tree::addNode(Node*& newNode) {

	Node* currentNode = headNode;

	while (1)
	{
		// if the new value is a duplicate, delete the Node
		if (newNode->value == currentNode->value) {
			delete newNode; break;
		}
		// if new value is less than the currentNode, move down to the left
		if (newNode->value < currentNode->value) {
			// next Node is empty, fill spot and break, otherwise, step down
			if (currentNode->left == nullptr) {
				currentNode->left = newNode;
				newNode->depth++;
				if (depth < newNode->depth)
					depth = newNode->depth;
				break;
			}
			else {
				currentNode = currentNode->left;
				newNode->depth++;
				if (depth < newNode->depth)
					depth = newNode->depth;
			}
		}

		// if new value is greater than currentNode, move down to the right
		if (newNode->value > currentNode->value) {
			// next Node is empty, fill spot and break, otherwise, step down
			if (currentNode->right == nullptr) {
				currentNode->right = newNode;
				newNode->depth++;
				if (depth < newNode->depth)
					depth = newNode->depth;
				break;
			}
			else {
				currentNode = currentNode->right;
				newNode->depth++;
				if (depth < newNode->depth)
					depth = newNode->depth;
			}
		}
	}
}

void Tree::printTree() {
	int currLevel = 1;
	int level = depth - currLevel;
	int edges = level > 0 ? pow(2, level) : 1;
	int leadSpace = pow(2, level) - 1;
	int btwSpace = pow(2, level + 1) - 1;
}

Node::Node() {
	depth = 0;
	left = nullptr;
	right = nullptr;
}

Node::Node(int v) {
	depth = 0;
	value = v;
	left = nullptr;
	right = nullptr;
}

Node::Node(int v, int d) {
	value = v;
	depth = d;
	left = nullptr;
	right = nullptr;
}

Tree::Tree() {
	depth = 1;
	headNode = nullptr;
}
