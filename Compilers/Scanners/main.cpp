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
		cout << "��Դ�������miniC++�Ĵʷ����﷨";
	else
		cout << "��Դ���벻����miniC++�Ĵʷ����﷨";
	system("pause");
	return 0;
}