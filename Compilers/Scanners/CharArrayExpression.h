#ifndef CHARARRAYEXPRESSION_H
#define CHARARRAYEXPRESSION_H

#include "Expression.h"

namespace Compilers_Scanners
{
	class CharArrayExpression:public Expression
	{
	public:
		CharArrayExpression(vector<char>& charArray):m_charArray(charArray)
		{
			m_type = AlternationCharArray;
		}
	public:
		vector<char> m_charArray;
	public:
		virtual vector<char> GetCharArray(){return m_charArray;}
	};
}

#endif