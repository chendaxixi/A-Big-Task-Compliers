#include "CharArrayExpression.h"

using namespace Compilers_Scanners;

Expression* Expression::CharArray(vector<char>& charArray)
{
	return new CharArrayExpression(charArray);
}