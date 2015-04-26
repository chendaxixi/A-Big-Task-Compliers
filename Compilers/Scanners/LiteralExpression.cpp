#include "LiteralExpression.h"

using namespace Compilers_Scanners;

Expression* Expression::Literal(string str)
{
	return new LiteralExpression(str);
}