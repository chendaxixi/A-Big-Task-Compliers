#include "..\\Parsers\\Parser.h"
#include <iostream>

using namespace std;
using namespace Compilers_Scanners;
using namespace Compilers_Parsers;

int main(int argc, char* args[])
{
	Parser p;
	p.scan.Open("test.txt");
	if (p.Program()) 
		cout << "该源代码符合miniC++的词法和语法";
	else
		cout << "该源代码不符合miniC++的词法和语法";
	system("pause");
	return 0;
}