#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"

namespace Compilers_Scanners
{
	class Token
	{
	public:
		Token():m_type(), m_value(-1){}
		Token(TokenType& type, int value):m_type(type), m_value(value){}
	public:
		TokenType m_type;
		int m_value;
	};
};

#endif