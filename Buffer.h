#include <stack>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

class Buffer
{
private:
////PRIVATE ATTRIBUTES
	stack <char> *LeftStack;
	stack <char> *RightStack;
////PRIVATE METHODS
	void setStacks(string s){
		int i=0,j;		
		if(s[0] != '|')
		{
			LeftStack->push(s[0]);
			for(i=1;!(s[i]=='|' && s[i-1]!='\\');i++)
				LeftStack->push(s[i]);
		}
			for(j=s.length()-1;j>i;j--)
				RightStack->push(s[j]);

	}

	string toString()
	{
		string out = "|";
		while(!RightStack->empty())
		{	
			out = out + RightStack->top();
			RightStack->pop();
		}

		while(!LeftStack->empty())
		{
			out = LeftStack->top() + out;		
			LeftStack->pop();
		}
		return out;
	}
public:
////CONSTRUCTOR
	Buffer()
	{
		LeftStack  = new stack <char>();
		RightStack = new stack <char>();
	}
////DESTRUCTOR
	~Buffer()
	{
		delete LeftStack;
		delete RightStack;
	}
////PUBLIC METHODS
	void addChar(char c)
	{
		LeftStack->push(c);
	}

	void deleteChar()
	{
		if(!LeftStack->empty())
		{
			LeftStack->pop();
			shiftLeft();
		}
	}
	void shiftRight()
	{
		if(!RightStack->empty())
		{		
			LeftStack->push(RightStack->top());
			RightStack->pop();
		}
	}

	void shiftLeft()
	{
		if(!LeftStack->empty())
		{
			RightStack->push(LeftStack->top());
			LeftStack->pop();
		}
	}
	
	string print()
	{
		system("clear");
		string out = toString();
		setStacks(out);
		return out;
	}
	
	void openFile(const char *filename)
	{
		ifstream inFile(filename);
		string fileString = "";
		if(!inFile)
		{
			string createFile = "touch ";
			createFile.append(filename);
			system(createFile.c_str());
			inFile.open(filename);		

		}
		while(!inFile.eof())
			fileString += inFile.get();
		
		fileString = fileString.substr(0,fileString.length()-1);
		fileString += '|';
		setStacks(fileString);
		cout<<print();
		inFile.close();
		
	}
	void saveFile(const char *filename)
	{
		ofstream outFile(filename);
		if(!outFile)
		{
			string createFile = "touch ";
			createFile.append(filename);
			system(createFile.c_str());		
			outFile.open(filename);		
		}
		string out = "";
		while(!RightStack->empty())
		{	
			out = out + RightStack->top();
			RightStack->pop();
		}

		while(!LeftStack->empty())
		{
			out = LeftStack->top() + out;		
			LeftStack->pop();
		}
		outFile << out;
		outFile.close();

	}
};
