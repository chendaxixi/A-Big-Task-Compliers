#include "SymbolExpression.h"

using namespace Compilers_Scanners;

Expression* Expression::Symbol(char c)
{
	return new SymbolExpression(c);
}