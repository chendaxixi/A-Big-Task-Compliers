#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "ExpressionType.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using std::string;
using std::vector;
using std::set;
using namespace std;

namespace Compilers_Scanners
{
	class Expression
	{
	public:
		Expression():m_type(ExpressionType::Empty){}
		Expression(ExpressionType type):m_type(type){}
	public:
		ExpressionType m_type;
	public:
		static Expression* Empty();
		static Expression* Symbol(char c);
		static Expression* Literal(string str);
		Expression* Concat(Expression* follow);
		Expression* Union(Expression* follow);
		Expression* Many();
		Expression* Many1()
		{
			return this->Concat(this->Many());
		}
		static Expression* CharArray(vector<char>& charArray);
		static Expression* Range(char startC, char endC)
		{
			vector<char> charArray;
			for (int c = startC;c <= endC;c++)
				charArray.push_back(c);
			return CharArray(charArray);
		}
		Expression* Optional()
		{
			return this->Union(Empty());
		}
		Expression* operator |(Expression* right)
		{
			return this->Union(right);
		}
		Expression* operator *(Expression* right)
		{
			return this->Concat(right);
		}
		Expression* operator ^(int)
		{
			return this->Many();
		}
		virtual char GetSymbol(){return 0;}
		virtual string GetString(){string str;return str;}
		virtual vector<char> GetCharArray(){vector<char> c;return c;}
		virtual Expression* GetLeft(){return NULL;}
		virtual Expression* GetRight(){return NULL;}
		virtual Expression* GetStarExp(){return NULL;}
	};
}

#endif