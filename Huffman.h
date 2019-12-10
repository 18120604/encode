#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
//#include <cstdlib>
using namespace std;

struct Node
{
	char c;
	string code;
	long freq;
	Node* left;
	Node* right;
};
struct MinHeap
{
	long size; //kich thuoc cua minheap
	long capacity; //suc chua cua minheap
	Node** arr;
};

void create_node_array(Node* arrayNode[256]);
vector<Node*> create(ifstream& inFile);
Node* createNode(char c, long freq);
MinHeap* createMinHeap(long capacity);
void swapMinHeapNode(Node** a, Node** b);
void minHeapify(MinHeap* minHeap, long index);
long isSizeOne(MinHeap* minHeap);
Node* minNode(MinHeap* minHeap);
void insertMinHeap(MinHeap* minHeap, Node* p);
void buildMinHeap(MinHeap* minHeap);
void printArr(long arr[], long n);
long isLeaf(Node* root);
MinHeap* createAndBuildMinHeap(vector<Node*> node, long size);
Node* buildHuffmanTree(vector<Node*> node, long size);
void traverse(vector<Node*>& findcode, Node* node, string code);
void huffmanCodes(vector<Node*>& node, long size);
long binary_to_decimal(string& in);
string decimal_to_binary(long in);
void Encode(ifstream& inFile, ofstream& outFile);
void ReadFile(ifstream& inFile, string& temp, vector<Node*>& node, long& sizeCode,long& size);
void Decode(ifstream& inFile, ofstream& outFile);
