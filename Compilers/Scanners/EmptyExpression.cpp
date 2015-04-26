#include "EmptyExpression.h"

using namespace Compilers_Scanners;

Expression* Expression::Empty()
{
	return new EmptyExpression;
}