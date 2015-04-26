#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include "Expression.h"

namespace Compilers_Scanners
{
	enum tokenType
	{
		BK,
		K_CLASS,
//		K_STATIC,
//		K_VOID,
		K_MAIN,
//		K_STRING,
		K_RETURN,
		K_INT,
		K_BOOL,
		K_IF,
		K_ELSE,
		K_WHILE,
		K_COUT,
		K_TRUE,
		K_FALSE,
		K_THIS,
		K_NEW,
		ID,
		NUM,
		LOGICAL_AND,
		LOGICAL_OR,
		LOGICAL_NOT,
		OUT_LESS,
		LESS,
		GREATER,
		EQUAL,
		ASSIGN,
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,
		LEFT_PH,
		RIGHT_PH,
		LEFT_BK,
		RIGHT_BK,
		LEFT_BR,
		RIGHT_BR,
		COMMA,
		COLON,
		SEMICOLON,
		DOT,
		ERROR
	};
	class TokenType
	{
	public:
		TokenType():m_str(), m_exp(NULL), m_type(ERROR), m_id(0){}
		TokenType(string str, Expression* exp, tokenType type):m_str(str), m_exp(exp), m_type(type), m_id(0){}
	public:
		string m_str;
		Expression* m_exp;
		tokenType m_type;
		int m_id;
	};
};

#endif