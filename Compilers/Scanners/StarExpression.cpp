#include "StarExpression.h"

using namespace Compilers_Scanners;

Expression* Expression::Many()
{
	return new StarExpression(this);
}