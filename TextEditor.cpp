#include <iostream>
#include "Buffer.h"

using namespace std;

int main()
{
	Buffer editor;
	string input;
	string filename;

	system("clear");
	cout<<"WELCOME TO THE CONSOLE OPERATED DOCUMENT EDITOR (C.O.D.E.)"<<endl;
	cout<<">>DISPLAY NOTATIONS:"<<endl;
	cout<<">>\t|    --- Cursor"<<endl;
	cout<<">>\t'>>' --- Editor Output Line"<<endl;
	cout<<">>\t'<<' --- User Input Line"<<endl;
	cout<<">>COMMANDS:"<<endl;
	cout<<">>\t<  --- Shift left"<<endl;
	cout<<">>\t>  --- Shift Right"<<endl;
	cout<<">>\t\\  --- Any special character that follows this will not be cosidered as a command."<<endl;
	cout<<">>\t~  --- Delete a character to the left of the cursor."<<endl;
	cout<<">>\t'\\n' --- Next Line."<<endl;
	cout<<">>\t^  --- End of input "<<endl;

	cout<<"\n\n\n>>Enter the name of the file you want to edit."<<endl;
	getline(cin,filename);

	editor.openFile(filename.c_str());	
	while(true)
	{
		cout<<"\n<<";
		getline(cin,input);
		for(int i=0;i<input.length();i++)
		{
			switch(input[i])
			{
				case '^':
					cout<<">>"<<editor.print()<<endl;
					editor.saveFile(filename.c_str());
					system("clear");
					cout<<"THANK YOU FOR USING C.O.D.E."<<endl;
					return 0;
				case '~':
					editor.deleteChar();
					editor.shiftRight();
					break;
				case '<':
					editor.shiftLeft();
					break;
				case '>':
					editor.shiftRight();
					break;
				case '\\':
					if(i !=input.length()-1)
						if(input[++i] == 'n')
						{
							editor.addChar('\n');
							continue;
						}
				default:
					editor.addChar(input[i]);
			}
		}
		cout<<">>"<<editor.print()<<endl;

	}
return 0;
}
