#ifndef LITERALEXPRESSION_H
#define LITERALEXPRESSION_H

#include "Expression.h"

namespace Compilers_Scanners
{
	class LiteralExpression:public Expression
	{
	public:
		LiteralExpression(string& str):m_str(str){m_type = StringLiteral;}
	public:
		string m_str;
	public:
		virtual string GetString(){return m_str;}
	};
}

#endif