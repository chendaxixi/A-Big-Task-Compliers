#ifndef SYMBOLEXPRESSION_H
#define SYMBOLEXPRESSION_H

#include "Expression.h"

namespace Compilers_Scanners
{
	class SymbolExpression:public Expression
	{
	public:
		SymbolExpression(char c)
		{
			m_type = ExpressionType::Symbol;
			m_symbol = c;
		}
	public:
		char m_symbol;
	public:
		virtual char GetSymbol(){return m_symbol;}
	};
}

#endif