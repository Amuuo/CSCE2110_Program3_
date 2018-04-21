#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<deque>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<utility>

// =========================================================================
struct Node {

	Node  (            );
	Node  (int v       );
	Node  (int v, int d);

	int    value;
	int    depth;
	Node*  left ;
	Node*  right;
};

// =========================================================================
struct Tree {

	Tree();

	std::vector<std::set<int>>  vecs;
	Node*                       headNode;
	int                         depth;

	void  addNode     (Node*&, Node*&);
	void  search      (Node*&, int&  );
	void  getLines    (Node*&        );
	int   getDepth    (              );
	void  print       (              );
	void initVecs     (              );
	void importData   (              );
};

// =========================================================================
struct vertex {

	std::string name;
	std::set<std::pair<vertex*, int>> neighborList;

	//constructor
	vertex();
	vertex(std::string);
	vertex(vertex* next, int weight);
	void printVertexInfo();
};

// =========================================================================
struct Graph {

	std::map<std::string, vertex> vertexes;
	void importData();
	void printGraph();
};
// =========================================================================
// =========================================================================
int main()
{
	
	
	char response;

	Tree* tree = new Tree;
	tree->importData();

	int searchValue;

	do {
		std::cout << "\nEnter search value: ";
		std::cin  >> searchValue;
		std::cout << "\n";

		tree->search(tree->headNode, searchValue);

		std::cout << "\n\nAnother Search? (Y/N): ";
		std::cin  >> response;

	} while (response == 'y' || response == 'Y');

	tree->print();

   system("PAUSE");
	delete tree;

	return 0;
}
// =========================================================================
// =========================================================================

// takes in tree's head node and the search value
void Tree::search(Node* &root, int& val) {

	if (root == nullptr) {
		std::cout << "NULL\n\nCould not find " << val;
		return;
	}
	else if(root != nullptr && root->value != val)
		std::cout << root->value << "(Depth:" << root->depth << ")" << " -> ";
	if(val == root->value)
		std::cout << root->value << "\nFOUND!";
	else if(val < root->value)
		search(root->left, val);
	else if(val > root->value)
		search(root->right, val);
}
// =========================================================================
void Tree::addNode(Node* &newNode, Node* &currentNode) {

	if(currentNode == nullptr)
		currentNode = newNode;

	else if (newNode->value < currentNode->value) {
		++newNode->depth;
		depth = depth < newNode->depth ? newNode->depth : depth;
		addNode(newNode, currentNode->left);		
	}
	else if (newNode->value > currentNode->value) {
		++newNode->depth;
		depth = depth < newNode->depth ? newNode->depth : depth;
		addNode(newNode, currentNode->right);
	}
	else if(newNode->value == currentNode->value) {
		std::cout << "\n...deleting duplicate: " << newNode->value;
		delete newNode;
	}
}
// =========================================================================
int Tree::getDepth() {
	int    depth;
	return depth;
}
// =========================================================================
Node::Node() {
	depth = 0;
	left  = nullptr;
	right = nullptr;
}
// =========================================================================
Node::Node(int v) {
	depth = 0;
	value = v;
	left  = nullptr;
	right = nullptr;
}
// =========================================================================
Node::Node(int v, int d) {
	value = v;
	depth = d;
	left  = nullptr;
	right = nullptr;
}
// =========================================================================
Tree::Tree() {
	depth    = 0;
	headNode = nullptr;
}
// =========================================================================
void Tree::getLines(Node* &head){
		
	if (head)
		vecs[head->depth].insert(head->value);
	if (head->left)
		getLines(head->left);
	if (head->right)
		getLines(head->right);
	
}
// =========================================================================
void Tree::print() {

	int vecSize = vecs.size();
	auto white = [](int h) {
		std::string s = "";
		for (int i = 0; i < h; ++i)
			s += " ";
		return s;
	};
	for(int j = 1; j < vecSize+1; ++j){
		std::cout << white((vecSize+1 - j)*2);
		for (auto k : vecs[j-1]) {
			std::cout << white((vecSize+1 - j)+vecSize-2) << k;
		}
		std::cout << std::endl;
	}
}
// =========================================================================

//initializes vectors that hold node values, left-to-right, at every level
void Tree::initVecs() {
	for (int i = 0; i < depth+1; ++i) {
		std::set<int> nVec;
		vecs.push_back(nVec);
	}
}
// =========================================================================
vertex::vertex() {}
// =========================================================================
vertex::vertex(std::string n) {
	name = n;
}
// =========================================================================
vertex::vertex(vertex* next, int weight) {
	std::pair<vertex*, int> neighbor = std::make_pair(next, weight);
	neighborList.insert(neighbor);
}

// =========================================================================
void vertex::printVertexInfo() {

	std::cout << "\nVertex '" << name << "'";
	for (auto n : neighborList) 
		std::cout << "\n\t" << n.first->name << ", weight: " << n.second;	
}
// =========================================================================
void Graph::importData() {

	std::ifstream  in;
	std::string    filename;
	std::string    tmpName;
	std::string    tmpName2;
	int            tmpWeight;


	std::cout << "\nEnter filename for graph data: ";
	std::cin  >> filename;

	in.open(filename);

	//import file
	while (in.good()) {
		// import vertexes until blank line
		while(std::getline(in, tmpName) && !tmpName.empty()) {

			vertex* tmpVert = new vertex(tmpName);
			vertexes[tmpName] = *tmpVert;
		}
		// add vertex edges to vertex objects
		in >> tmpName >> tmpName2 >> tmpWeight;
		vertexes[tmpName].neighborList.insert(std::make_pair(&vertexes[tmpName2], tmpWeight));
	}
}
// =========================================================================
void Graph::printGraph() {

	for (auto v : vertexes)
		v.second.printVertexInfo();
}
// =========================================================================
void Tree::importData()
{
	std::string filename;  // string for tree-data filename
	std::ifstream in;      // input stream for data
	int  tmp;              // temp int for inputting file data

	// retrieve tree-data filename from user
	std::cout << "\nEnter filename containing the data for BST: ";
	std::cin >> filename;
	// open data file and import head node
	in.open(filename);
	in >> tmp;

	// allocate data for tree and head node

	headNode = new Node(tmp, 0);
	Node* newNode;

	// import remainder of list into tree
	while (in.good()) {
		in >> tmp;
		newNode = new Node(tmp);
		addNode(newNode, headNode);
	}
	in.close();
	initVecs();
	getLines(headNode);
	std::cout << "\nTree Depth: " << depth;

	return;
}

