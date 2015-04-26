#include "AlternationExpression.h"

using namespace Compilers_Scanners;

Expression* Expression::Union(Expression* follow)
{
	return new AlternationExpression(this, follow);
}