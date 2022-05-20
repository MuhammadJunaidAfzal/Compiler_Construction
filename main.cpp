#include <iostream>
#include "parser.h"
using namespace std;

int main(int argc, char* argv[])
{
	argc = 2;
	//asking for file name as command line arguments
	if (argc == 2)
	{
		parser p("sample_code0.mc");
		cout << endl << endl << p.start() << endl << endl;
		
		//lexer _lexer("sample_code0.mc");
		//token t;
		//t = _lexer.getNextToken();
		//while (t.tokenType != TokenType::END_OF_FILE)
		//{
		//	t.Print();
		//	t = _lexer.getNextToken();
		//}
		
	}
	else if (argc > 2)
	{ //argument limit exceeds
		cout << "Too many arguments" << endl;
	}
	else //if file name is'nt given
	{
		cout << "Please provide a file name" << endl;
	}
	return 0;
	system("pause");
}
