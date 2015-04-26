#include "Scanner.h"

using namespace Compilers_Scanners;

//vector<string> Scanner::strList;

Token Scanner::Read()
{
	int temp = -1;
	if (buffer[nowward] == 0) return Token(TokenType("error", NULL, ERROR), -1);
	Token token;
	while(true)
	{
		temp = -1;
		for (int i = 0;i < m_lexicon.num;i++)
			if (Succeed(m_lexicon.DFAList[i]))
			{
				temp = i;
				break;
			}
		if (temp == -1)
			return Token(TokenType("error", NULL, ERROR), -1);
		token = AfterFind(m_lexicon.tokenList[temp]);
		if (token.m_value != -1)
			return token;
	}
}

bool Scanner::Succeed(DFAConvert& DFA)
{
	int state = 0;
	int oldState = 0;
	char c;
	while(state > -1)
	{
		forward++;
		c = buffer[forward];
		oldState = state;
		state = DFA.DTran[c][state];
	}
	if (DFA.DStates[oldState].find(DFA.size - 1) == DFA.DStates[oldState].end())
	{
		forward = nowward-1;
		return false;
	}
	else
		return true;
	
}

Token Scanner::AfterFind(TokenType& type)
{
	int n = 0;
	switch (type.m_type)
	{
	case BK:
		nowward = forward;
		forward = nowward - 1;
		return Token();
	default:
		nowward = forward;
		forward = nowward - 1;
		return Token(type, 0);
		break;
	}
}

void Scanner::InitLexicon()
{
	Expression* e = Expression::Range(0, '\n'-1)->Union(Expression::Range('\n'+1, 127));
	Expression* e2 = Expression::Range(0, '*'-1)->Union(Expression::Range('*'+1, '/'-1))->Union(Expression::Range('/'+1,127));
	Expression* e1 = Expression::Symbol('/')->Many()->Union(Expression::Symbol('*')->Many())
		->Concat(e2);
	m_lexicon.DefineToken("BK", 
		Expression::Symbol(' ')->Union(Expression::Symbol('\t'))->Union(Expression::Symbol('\n'))->Many1()
		->Union( Expression::Literal("//")->Concat(e->Many())
		->Concat(Expression::Symbol('\n')) )
		->Union( Expression::Literal("/*")->Concat(e1->Many())->Concat(Expression::Symbol('/')->Many())
		->Concat(Expression::Symbol('*')->Many1())->Concat(Expression::Symbol('/')) ), BK);
	m_lexicon.DefineToken("class", Expression::Literal("class"), K_CLASS);
//	m_lexicon.DefineToken("static", Expression::Literal("static"), K_STATIC);
//	m_lexicon.DefineToken("void", Expression::Literal("void"), K_VOID);
	m_lexicon.DefineToken("main", Expression::Literal("main"), K_MAIN);
//	m_lexicon.DefineToken("string", Expression::Literal("string"), K_STRING);
	m_lexicon.DefineToken("return", Expression::Literal("return"), K_RETURN);
	m_lexicon.DefineToken("int", Expression::Literal("int"), K_INT);
	m_lexicon.DefineToken("bool", Expression::Literal("bool"), K_BOOL);
	m_lexicon.DefineToken("if", Expression::Literal("if"), K_IF);
	m_lexicon.DefineToken("else", Expression::Literal("else"), K_ELSE);
	m_lexicon.DefineToken("while", Expression::Literal("while"), K_WHILE);
	m_lexicon.DefineToken("cout", Expression::Literal("cout"), K_COUT);
	m_lexicon.DefineToken("true", Expression::Literal("true"), K_TRUE);
	m_lexicon.DefineToken("false", Expression::Literal("false"), K_FALSE);
	m_lexicon.DefineToken("this", Expression::Literal("this"), K_THIS);
	m_lexicon.DefineToken("new", Expression::Literal("new"), K_NEW);
	m_lexicon.DefineToken("id", Expression::Range('a','z')->Union(Expression::Range('A','Z'))->
		Concat(Expression::Range('a','z')->Union(Expression::Range('A','Z'))->Union(Expression::Range('0','9'))->Many()), ID);
	m_lexicon.DefineToken("num", Expression::Range('0', '9')->Many1(), NUM);
	m_lexicon.DefineToken("&&", Expression::Literal("&&"), LOGICAL_AND);
	m_lexicon.DefineToken("||", Expression::Literal("||"), LOGICAL_OR);
	m_lexicon.DefineToken("!", Expression::Symbol('!'), LOGICAL_NOT);
	m_lexicon.DefineToken("<<", Expression::Literal("<<"), OUT_LESS);
	m_lexicon.DefineToken("<", Expression::Symbol('<'), LESS);
	m_lexicon.DefineToken(">", Expression::Symbol('>'), GREATER);
	m_lexicon.DefineToken("==", Expression::Literal("=="), EQUAL);
	m_lexicon.DefineToken("=", Expression::Symbol('='), ASSIGN);
	m_lexicon.DefineToken("+", Expression::Symbol('+'), PLUS);
	m_lexicon.DefineToken("-", Expression::Symbol('-'), MINUS);
	m_lexicon.DefineToken("*", Expression::Symbol('*'), MULTIPLY);
	m_lexicon.DefineToken("/", Expression::Symbol('/'), DIVIDE);
	m_lexicon.DefineToken("(", Expression::Symbol('('), LEFT_PH);
	m_lexicon.DefineToken("{", Expression::Symbol('{'), LEFT_BR);
	m_lexicon.DefineToken("[", Expression::Symbol('['), LEFT_BK);
	m_lexicon.DefineToken(")", Expression::Symbol(')'), RIGHT_PH);
	m_lexicon.DefineToken("}", Expression::Symbol('}'), RIGHT_BR);
	m_lexicon.DefineToken("]", Expression::Symbol(']'), RIGHT_BK);
	m_lexicon.DefineToken(",", Expression::Symbol(','), COMMA);
	m_lexicon.DefineToken(":", Expression::Symbol(':'), COLON);
	m_lexicon.DefineToken(";", Expression::Symbol(';'), SEMICOLON);
	m_lexicon.DefineToken(".", Expression::Symbol('.'), DOT);
}

//int Scanner::Insert()
//{
//	string str(buffer+nowward, forward-nowward);
//	int n = strList.size();
//	for (int i = 0;i < n;i++)
//		if (str == strList[i])
//			return i;
//	strList.push_back(str);
//	kindList.push_back(0);
//	return n;
//}
