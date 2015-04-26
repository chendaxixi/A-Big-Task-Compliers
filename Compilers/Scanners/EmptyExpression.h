#ifndef EMPTYEXPRESSION_H
#define EMPTYEXPRESSION_H

#include "Expression.h"

namespace Compilers_Scanners
{
	class EmptyExpression:public Expression
	{
	public:
		EmptyExpression(){m_type = ExpressionType::Empty;}

	};
}

#endif