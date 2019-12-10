#include"Huffman.h"

int main()
{
	ifstream inFile;
	ofstream outFile;
	string temp = "";
	ifstream in;
	in.open("output.txt", ios::binary);
	ofstream out;
	long sizeCode;


	Encode(inFile, outFile);

	Decode(in, out);
	
	
	system("pause");
	return 0;
}
