#include "ConcatenationExpression.h"

using namespace Compilers_Scanners;

Expression* Expression::Concat(Expression* follow)
{
	return new ConcatenationExpression(this, follow);
}