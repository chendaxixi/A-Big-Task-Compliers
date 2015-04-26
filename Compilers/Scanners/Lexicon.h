#ifndef LEXICON_H
#define LEXICON_H

#include "TokenType.h"
#include "DFAConvert.h"

namespace Compilers_Scanners
{
	class Lexicon
	{
	public:
		Lexicon():tokenList(), DFAList(), num(0){}
		~Lexicon()
		{
			for (int i = 0;i < num;i++)
				delete tokenList[i].m_exp;
		}
	public:
		vector<TokenType> tokenList;
		vector<DFAConvert> DFAList;
		int num;
	public:
		tokenType DefineToken(string str, Expression* exp, tokenType type)
		{
			TokenType token(str, exp, type);
			token.m_id = num;
			DFAConvert DFA(token.m_exp->Concat(Expression::Symbol('#')));
			tokenList.push_back(token);
			DFAList.push_back(DFA);
			num++;
			return token.m_type;
		}
	};
};

#endif