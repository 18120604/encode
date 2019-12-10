#include"Huffman.h"

void create_node_array(Node* arrayNode[256])
{
	for (long i = 0; i < 256; i++)
	{
		arrayNode[i] = new Node;
		arrayNode[i]->c = i;
		arrayNode[i]->freq = 0;
	}
}
vector<Node*> create(ifstream& inFile)
{
	vector<Node*>x;
	Node* arrayNode[256];
	create_node_array(arrayNode);
	inFile.open("input.txt", ios::binary);
	if (inFile.fail())
	{
		cout << "could not open file!";
	}
	char c;
	/*inFile.get(c);
	while (!inFile.eof())
	{
		arrayNode[c]->freq++;
		inFile.get(c);
	}*/
	while (inFile)
	{
		inFile.get(c);
		if (inFile.eof())
			break;
		arrayNode[(unsigned char)c]->freq++;
	}
	inFile.close();
	for (long i = 0; i < 256; i++)
	{
		if (arrayNode[i]->freq)
		{
			//cout << (char)i << "-" << arrayNode[i]->freq << endl;
			x.push_back(arrayNode[i]);
		}
	}
	return x;
}
Node* createNode(char c, long freq) //tao node voi ki tu va tan suat
{
	Node* p = new Node;
	p->c = c;
	p->freq = freq;
	p->left = NULL;
	p->right = NULL;
	return p;
}
MinHeap* createMinHeap(long capacity) //tao cay  voi suc chua
{
	MinHeap* minHeap = new MinHeap;
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->arr = (Node**)malloc(minHeap->capacity * sizeof(MinHeap));
	return minHeap;
}
void swapMinHeapNode(Node** a, Node** b) //hoan vi 2 node voi nhau
{
	Node* t = *a;
	*a = *b;
	*b = t;
}
void minHeapify(MinHeap* minHeap, long index) //hieu chinh minHeap tai node thu i
{
	long min = index;
	long left = 2 * index + 1;
	long right = 2 * index + 2;
	if (left < minHeap->size && minHeap->arr[left]->freq < minHeap->arr[min]->freq)
	{
		min = left;
	}
	if (right < minHeap->size && minHeap->arr[right]->freq < minHeap->arr[min]->freq)
	{
		min = right;
	}
	if (min != index)
	{
		swapMinHeapNode(&minHeap->arr[min], &minHeap->arr[index]);
		minHeapify(minHeap, min);
	}
}
long isSizeOne(MinHeap* minHeap) //kiem tra kich thuoc cua minheap co bang 1
{
	if (minHeap->size == 1)
	{
		return 1;
	}
	return 0;
}
Node* minNode(MinHeap* minHeap) //lay ra node co tan suat nho nhat
{
	Node* temp = minHeap->arr[0];
	minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}
void insertMinHeap(MinHeap* minHeap, Node* p) //chen node vao cay
{
	++minHeap->size;
	long i = minHeap->size - 1;
	while (i && p->freq < minHeap->arr[(i - 1) / 2]->freq)
	{
		minHeap->arr[i] = minHeap->arr[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->arr[i] = p;
}
void buildMinHeap(MinHeap* minHeap) //tao cay
{
	long n = minHeap->size - 1;
	for (long i = (n - 1) / 2; i >= 0; i--)
	{
		minHeapify(minHeap, i);
	}
}
void printArr(long arr[], long n) //in mang
{
	for (long i = 0; i < n; i++)
	{
		cout << arr[i];
	}
	cout << endl;
}
long isLeaf(Node* root) //kiem tra node la
{
	return !(root->left) && !(root->right);
}

MinHeap* createAndBuildMinHeap(vector<Node*> node, long size) //tao va xay dung cay
{
	MinHeap* minHeap = createMinHeap(size);
	for (long i = 0; i < size; i++)
	{
		minHeap->arr[i] = createNode(node[i]->c, node[i]->freq);
	}
	minHeap->size = size;
	buildMinHeap(minHeap);
	return minHeap;
}
Node* buildHuffmanTree(vector<Node*> node, long size) //tao cay huffman
{
	Node* left;
	Node* right;
	Node* top;
	MinHeap* minHeap = createAndBuildMinHeap(node, size);
	while (!isSizeOne(minHeap))
	{

		left = minNode(minHeap);
		right = minNode(minHeap);
		top = createNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}
	return minNode(minHeap);
}

void traverse(vector<Node*>& findcode, Node* node, string code)
{
	if (node->left == NULL && node->right == NULL)
	{
		node->code = code;
		findcode.push_back(node);
	}
	else
	{
		traverse(findcode, node->left, code + '0');
		traverse(findcode, node->right, code + '1');
	}


}

void printCode(vector<Node*> findcode, Node* node, string code)//in bang code ung voi ki tu
{
	traverse(findcode, node, code);
	string s = "";
	for (long i = 0; i < findcode.size(); i++)
	{
		if (findcode[i]->code != "")
		{
			cout << findcode[i]->c << "=" << findcode[i]->code << endl;
		}
	}
}
void huffmanCodes(vector<Node*>& node, long size)
{
	Node* root = buildHuffmanTree(node, size);
	string code;

	traverse(node, root, code);
}

long binary_to_decimal(string& in)
{
	long result = 0;
	for (long i = 0; i < in.size(); i++)
		result = result * 2 + in[i] - '0';
	return result;
}

string decimal_to_binary(long in)
{
	if (in < 0)
		in += 256;
	string temp = "";
	string result = "";
	while (in)
	{
		temp += ('0' + in % 2);
		in /= 2;
	}
	result.append(8 - temp.size(), '0');
	for (long i = temp.size() - 1; i >= 0; i--)
	{
		result += temp[i];

	}
	return result;
}

void Encode(ifstream& inFile, ofstream& outFile)//nen du lieu
{
	vector<Node*>x = create(inFile);
	vector<Node*>node;
	inFile.open("input.txt",ios::binary);//
	outFile.open("output.txt",ios::binary);//
	long size = x.size();
	huffmanCodes(x, x.size());
	for (int i = 0; i < x.size(); i++)
		node.push_back(x[i]);
	string in = "";
	string s = "";
	string s1 = "";
	char c;
	//inFile.get(c);
	while (inFile)
	{
		inFile.get(c);
		if (inFile.eof())
			break;
		for (long i = 0; i < node.size(); i++)
		{
			if (node[i]->c == c)
			{
				s += node[i]->code;
				s1 += node[i]->code;
			}
		}
		while (s.size() > 8)
		{
			string temptemp = s.substr(0, 8);
			in += (char)binary_to_decimal(temptemp);
			s = s.substr(8);
		}

	}

	outFile << size << ' ' << s1.size() << endl;
	for (long i = 0; i < size; i++)
	{
		outFile << node[i]->c << node[i]->freq << ' ';
	}
	outFile << endl;
	long count = 8 - s.size();
	if (s.size() < 8)
	{
		s.append(count, '0');
	}
	in += (char)binary_to_decimal(s);
	for (int i = 0; i < in.size(); i++)
		outFile << in[i];
	inFile.close();
	outFile.close();
}

void ReadFile(ifstream& inFile, string& temp, vector<Node*>& node, long& sizeCode,long& size)
{

	long tanSo;
	char c;
	char tmp;
	inFile >> size;
	inFile.get(tmp);//' '
	inFile >> sizeCode;
	inFile.get(tmp);//\n
	int j = 0;
	while (inFile)
	{
		inFile.get(c);
		if (inFile.eof())
			break;
		else if (j < size)
		{
			inFile >> tanSo;
			Node*b = createNode(c, tanSo);
			{
				node.push_back(b); 
			}
			inFile.get(tmp);//' '
			if(j==size-1)
				inFile.get(tmp);//' '
		}
		else 
		{
			temp += decimal_to_binary(unsigned char(c));
		}
		j++;
	}
	
}

void Decode(ifstream& inFile, ofstream& outFile)//giai nen du lieu
{
	vector<Node*> node;
	string temp = "";
	long sizeCode;
	
	long size = 0;
	ReadFile(inFile, temp, node, sizeCode,size);
	
	outFile.open("decode.txt", ios::binary);
	Node* root = buildHuffmanTree(node,size);
	Node* current = root;
	string ans = "";
	for (long j = 0; j < sizeCode; j++)
	{
		if (temp[j] == '0')
			current = current->left;
		else
			current = current->right;
		if (!current->left && !current->right)
		{
			ans+= current->c;
			current = root;
		}
	}
	outFile << ans;
	
}


