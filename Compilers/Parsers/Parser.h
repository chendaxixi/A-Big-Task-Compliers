#ifndef PARSERS_H
#define PARSERS_H

#include "..\\Scanners\\Scanner.h"

using namespace Compilers_Scanners;

namespace Compilers_Parsers
{
	class Parser
	{
	public:
		Parser():scan(){}
	public:
		Scanner scan;
	//	bool fail;
	public:
		bool Program();
		bool Define();
		bool Decl();
		bool MainMethodDecl();
		bool ClassDefine();
		bool MethodDefine();
		bool MethodDecl();
		bool FieldDecl();
		bool FieldDefine();
		bool FormalList();
		bool Type();
		bool FormalRest();
		bool StateMent();
		bool Exp();
		bool ExpP();
		bool ExpList();
		bool ExpRest();
	};
};

#endif