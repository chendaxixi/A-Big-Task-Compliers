#ifndef CONCATENATIONEXPRESSION_H
#define CONCATENATIONEXPRESSION_H

#include "Expression.h"

namespace Compilers_Scanners
{
	class ConcatenationExpression:public Expression
	{
	public:
		ConcatenationExpression(Expression* left, Expression* right):m_left(left), m_right(right)
		{
			m_type = Concatenation;
		}
	public:
		~ConcatenationExpression()
		{
			if (m_left != NULL) delete m_left;
			if (m_right != NULL) delete m_right;
		}
	public:
		Expression* m_left;
		Expression* m_right;
	public:
		virtual Expression* GetLeft(){return m_left;}
		virtual Expression* GetRight(){return m_right;}
	};
}

#endif