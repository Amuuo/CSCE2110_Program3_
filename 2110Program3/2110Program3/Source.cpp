#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>

//tree

struct Node {

	Node  (            );
	Node  (int v       );
	Node  (int v, int d);

	int    value;
	int    depth;
	Node*  left;
	Node*  right;
};

struct Tree {

	Tree();

	Node*  headNode;
	int    depth;

	void  addNode     (Node*& newNode);
	void  addNode     (Node*&, Node*&);
	void  search      (              );
	void  search      (Node*&, int&  );
	void  printDepth  (              );
	void  printTree   (              );
	int   getDepth    (              );
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
		tree->addNode(newNode, tree->headNode);
	}
	in.close();

	//tree->printDepth();

	int searchValue;

	do {
		std::cout << "\nEnter search value: ";
		std::cin >> searchValue;
		std::cout << "\n";
		tree->search(tree->headNode, searchValue);
		std::cout << "\n\nAnother Search? (Y/N): ";
		std::cin >> response;

	} while (response == 'y' || response == 'Y');

	delete tree;

	return 0;
}

// takes in tree's head node and the search value
void Tree::search(Node* &root, int& val) {

	if (root == nullptr)
		std::cout << "NULL\n\nCould not find " << val;
	else if (root != nullptr && root->value != val)
		std::cout << root->value << " -> ";
	if (val == root->value)
		std::cout << root->value << "\nFOUND!";
	else if (val < root->value)
		search(root->left, val);
	else if (val > root->value)
		search(root->right, val);
}

void Tree::addNode(Node* &newNode, Node* &currentNode) {

	if (currentNode == nullptr)
		currentNode = newNode;
	else if (newNode->value < currentNode->value)
		addNode(newNode, currentNode->left);
	else if (newNode->value > currentNode->value)
		addNode(newNode, currentNode->right);
	else if (newNode->value == currentNode->value) {
		std::cout << "\n...deleting duplicate: " << newNode->value;
		delete newNode;
	}
}

int Tree::getDepth() {
	int depth;
	return depth;
}

/*void Tree::printTree() {
int currLevel = 1;
int level = depth - currLevel;
int edges = level > 0 ? pow(2, level) : 1;
int leadSpace = pow(2, level) - 1;
int btwSpace = pow(2, level + 1) - 1;
}*/

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

