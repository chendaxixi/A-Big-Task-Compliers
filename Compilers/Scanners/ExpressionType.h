#ifndef EXPRESSIONTYPE_H
#define EXPRESSIONTYPE_H

namespace Compilers_Scanners
{
	enum ExpressionType
	{
		Empty,
		Symbol,
		Alternation,
		Concatenation,
		KleeneStar,
		AlternationCharArray,
		StringLiteral
	};
}

#endif