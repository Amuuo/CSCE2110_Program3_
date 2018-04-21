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

	void  addNode      (Node*&, Node*&);
	void  search       (Node*&, int   );
	void  getLines     (Node*&        );
	int   getDepth     (              );
	void  print        (              );
	void  initVecs     (              );
	void  importData   (              );
	void  searchPrompt (              );
	void  printMenu    (              );
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

	int searchWeight = 0;
	std::map<std::string, vertex> vertexes;
	void importData();
	void print();
	void search(std::string, std::string);
	void searchPrompt();
	void printMenu();
};

int menu();

// =========================================================================
//                  >>>>>>>>>>  M  A  I  N   <<<<<<<<<<<
// =========================================================================
int main() {
	
	// loop until user chooses to exit
	while (1) {

		int menuChoice = menu();

		switch (menuChoice) {

			case 1: {
				system("clear");
				Graph * graph = new Graph;
				graph->printMenu();
				delete graph;
				break;
			}
			case 2: {
				system("clear");
				Tree * tree = new Tree;
				tree->printMenu();
				delete tree;
				break;
			}
			case 3: exit(0);
			default: break;
		}
		system("clear");
	}
	return 0;
}
// =========================================================================
// =========================================================================

// takes in tree's head node and the search value
void Tree::search(Node* &root, int val) {

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
		vertexes[tmpName2].neighborList.insert(std::make_pair(&vertexes[tmpName], tmpWeight));

	}
}
// =========================================================================
void Graph::print() {
	char tmp;
	for (auto v : vertexes)
		v.second.printVertexInfo();
	std::cout << "\nPress any key to return to Graph Menu"; 
	std::cin >> tmp;
}
void Graph::search(std::string s, std::string e)
{
	for (auto v : vertexes[s].neighborList) {
		if (v.first->name == e) {
			searchWeight += v.second;
			std::cout << s << "-" << e << ", weight: " << searchWeight;
			return;
		}
	}
	for (auto v : vertexes[s].neighborList) {
		search(v.first->name, e);
	}
	std::cout << "\nNo search function yet";
}
void Graph::searchPrompt()
{
	std::string start, end, r;
	do {
		std::cout << "\n\nGRAPH SEARCH";
		std::cout << "\n\nSearch From: "; std::cin >> start;
		std::cout << "Search To: "; std::cin >> end;

		search(start, end);
		std::cout << "\n\nAnother Search (Y/N): ";
		std::cin >> r;
	} while (r == "y" || r == "Y");
	return;
}
void Graph::printMenu()
{
	int choice;
	int sChoice;

	//loop menu until choice is 4
	while (1) {

		std::cout << "\n\nGRAPH MENU";
		std::cout << "\n\n\t1. Import file for graph";
		std::cout << "\n\t2. Search Graph";
		std::cout << "\n\t3. Print Graph";
		std::cout << "\n\t4. Main Menu";

		std::cout << "\n\nSelection: "; std::cin >> choice;

		switch (choice) {

		case 1:	system("clear"); importData();   break;
		case 2: system("clear"); searchPrompt(); break;
		case 3: system("clear"); print();        break;
		case 4: system("clear"); return;         break;
		default:                                 break;
		}
		system("clear");
	}
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

void Tree::searchPrompt()
{
	int searchValue;
	char response;
	do {
		std::cout << "\nEnter search value: ";
		std::cin >> searchValue;
		std::cout << "\n";

		search(headNode, searchValue);

		std::cout << "\n\nAnother Search? (Y/N): ";
		std::cin >> response;

	} while (response == 'y' || response == 'Y');
}

void Tree::printMenu()
{
	int choice;
	int sChoice;

	//loop menu until choice is 4
	while (1) {

		std::cout << "\n\nTREE MENU";
		std::cout << "\n\n\t1. Import file for tree";
		std::cout << "\n\t2. Search Tree";
		std::cout << "\n\t3. Print Tree";
		std::cout << "\n\t4. Main Menu";

		std::cout << "\n\nSelection: "; std::cin >> choice;

		switch (choice) {

		case 1:	system("clear"); importData();   break;
		case 2: system("clear"); searchPrompt(); break;
		case 3: system("clear"); print();        break;
		case 4: system("clear"); return;         break;
			default:                break;
		}
		system("clear");
	}
}

int menu()
{
	int selection;
	std::cout << "\n\nMAIN MENU";
	std::cout << "\n\n\t1. Graph";
	std::cout << "\n\t2. Tree";
	std::cout << "\n\t3. Exit";

	std::cout << "\n\nSelection: "; 
	std::cin >> selection;

	return selection;
}
