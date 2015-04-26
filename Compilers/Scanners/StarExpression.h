#ifndef STAREXPRESSION_H
#define STAREXPRESSION_H

#include "Expression.h"

namespace Compilers_Scanners
{
	class StarExpression:public Expression
	{
	public:
		StarExpression(Expression* e):m_exp(e){m_type = KleeneStar;}
		~StarExpression()
		{
			if (m_exp != NULL) delete m_exp;
		}
	public:
		Expression* m_exp;
	public:
		virtual Expression* GetStarExp(){return m_exp;}
	};
}

#endif