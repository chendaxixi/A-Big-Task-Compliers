#include "Parser.h"

using namespace Compilers_Parsers;

bool Parser::Program()	
{
	int oldward = scan.nowward;
	while (Define()){}
	if (!MainMethodDecl())
	{scan.Back(oldward);return false;}
	while(Decl()){}
	if (scan.Read().m_type.m_type == ERROR)
		if (scan.buffer[scan.nowward] == 0) 
			return true;
	{scan.Back(oldward);return false;}
}

bool Parser::Define()
{
	int oldward = scan.nowward;
	if(FieldDefine())return true;
	if(ClassDefine())return true;
	if(MethodDefine())return true;
	{scan.Back(oldward);return false;}
}

bool Parser::Decl()
{
	int oldward = scan.nowward;
	if (MethodDecl()) return true;
	if (FieldDecl()) return true;
	{scan.Back(oldward);return false;}
}

bool Parser::MainMethodDecl()
{
	int oldward = scan.nowward;
	if (scan.Read().m_type.m_type != K_INT){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != K_MAIN){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != LEFT_PH){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != RIGHT_PH){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != LEFT_BR){scan.Back(oldward);return false;}
	while(StateMent()){}
	if (scan.Read().m_type.m_type != K_RETURN){scan.Back(oldward);return false;}
	if(!Exp()){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != SEMICOLON){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != RIGHT_BR){scan.Back(oldward);return false;}
	return true;
}

bool Parser::ClassDefine()
{
	int oldward = scan.nowward;
	if (scan.Read().m_type.m_type != K_CLASS){scan.Back(oldward);return false;}
	Token token = scan.Read();
	if (token.m_type.m_type != ID){scan.Back(oldward);return false;}
	token = scan.Read();
	if (token.m_type.m_type == LEFT_BR)
	{
		while(FieldDefine()){}
		while(MethodDecl()){}
		if (scan.Read().m_type.m_type != RIGHT_BR){scan.Back(oldward);return false;}
	}
	else if (token.m_type.m_type == COLON)
	{
		token = scan.Read();
		if (token.m_type.m_type != ID){scan.Back(oldward);return false;}
		if (scan.Read().m_type.m_type != LEFT_BR){scan.Back(oldward);return false;}
		while(FieldDefine()){}
		while(MethodDecl()){}
		if (scan.Read().m_type.m_type != RIGHT_BR){scan.Back(oldward);return false;}
	}
	else {scan.Back(oldward);return false;}
	return true;
}

bool Parser::MethodDefine()
{
	int oldward = scan.nowward;
	if (!Type()){scan.Back(oldward);return false;}
	Token token = scan.Read();
	if (token.m_type.m_type != ID){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != LEFT_PH){scan.Back(oldward);return false;}
	if (!FormalList()){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != RIGHT_PH){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != SEMICOLON){scan.Back(oldward);return false;}
	return true;
}

bool Parser::MethodDecl()
{
	int oldward = scan.nowward;
	if (!Type()){scan.Back(oldward);return false;}
	Token token = scan.Read();
	if (token.m_type.m_type != ID){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != LEFT_PH){scan.Back(oldward);return false;}
	if (!FormalList()){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != RIGHT_PH){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != LEFT_BR){scan.Back(oldward);return false;}
	while(StateMent()){}
	if (scan.Read().m_type.m_type != K_RETURN){scan.Back(oldward);return false;}
	if (!Exp()){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != SEMICOLON){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != RIGHT_BR){scan.Back(oldward);return false;}
	return true;
}

bool Parser::FieldDefine()
{
	int oldward = scan.nowward;
	if(!Type()){scan.Back(oldward);return false;}
	Token token = scan.Read();
	if (token.m_type.m_type != ID){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != SEMICOLON){scan.Back(oldward);return false;}
	return true;
}

bool Parser::FieldDecl()
{
	int oldward = scan.nowward;
	if (!Type()){scan.Back(oldward);return false;}
	Token token = scan.Read();
	if (token.m_type.m_type != ID){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != ASSIGN){scan.Back(oldward);return false;}
	if(!Exp()){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != SEMICOLON){scan.Back(oldward);return false;}
	return true;
}

bool Parser::FormalList()
{
	int oldward = scan.nowward;
	if (!Type()){scan.Back(oldward);return true;}
	Token token = scan.Read();
	if (token.m_type.m_type != ID){scan.Back(oldward);return true;}
	while(FormalRest()){}
	return true;
}

bool Parser::FormalRest()
{
	int oldward = scan.nowward;
	if (scan.Read().m_type.m_type != COMMA){scan.Back(oldward);return false;}
	if (!Type()){scan.Back(oldward);return false;}
	if (scan.Read().m_type.m_type != ID){scan.Back(oldward);return false;}
	return true;
}

bool Parser::Type()
{
	int oldward = scan.nowward;
	if (scan.Read().m_type.m_type == K_INT)
	{
		oldward = scan.nowward;
		if (scan.Read().m_type.m_type == LEFT_BK)
		{
			if (scan.Read().m_type.m_type == RIGHT_BK)
				return true;
			else
			{
				scan.Back(oldward);return true;
			}
		}
		else 
		{
			scan.Back(oldward);return true;
		}
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == K_BOOL)
		return true;
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == ID)
		return true;
	scan.Back(oldward);
	{scan.Back(oldward);return false;}
}

bool Parser::StateMent()
{
	int oldward = scan.nowward;
	if (scan.Read().m_type.m_type == LEFT_BR)
	{
		while(StateMent()){}
		if(scan.Read().m_type.m_type == RIGHT_BR) return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == K_IF)
	{
		if (scan.Read().m_type.m_type == LEFT_PH)
			if(Exp())
				if (scan.Read().m_type.m_type == RIGHT_PH)
					if(StateMent())
						if (scan.Read().m_type.m_type == K_ELSE)
							if(StateMent())
								return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == K_WHILE)
	{
		if (scan.Read().m_type.m_type == LEFT_PH)
			if(Exp())
				if (scan.Read().m_type.m_type == RIGHT_PH)
					if(StateMent())
						return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == K_COUT)
	{
		if (scan.Read().m_type.m_type == OUT_LESS)
			if(Exp())
				if (scan.Read().m_type.m_type == SEMICOLON)
					return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == ID)
	{
		if (scan.Read().m_type.m_type == ASSIGN)
			if(Exp()) 
				if (scan.Read().m_type.m_type == SEMICOLON)
					return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == ID)
	{
		if (scan.Read().m_type.m_type == LEFT_BK)
			if(Exp())
				if (scan.Read().m_type.m_type == RIGHT_BK)
					if (scan.Read().m_type.m_type == ASSIGN)
						if(Exp())
							if (scan.Read().m_type.m_type == SEMICOLON)
								return true;
	}
	scan.Back(oldward);
	if(FieldDefine()) return true;
	if(FieldDecl()) return true;
	{scan.Back(oldward);return false;}
}

bool Parser::Exp()
{
	int oldward = scan.nowward;
	if (scan.Read().m_type.m_type == NUM)
	{
		if(ExpP())
			return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == K_TRUE)
	{
		if(ExpP())
			return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == K_FALSE)
	{
		if(ExpP())
			return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == ID)
	{
		if(ExpP())
			return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == K_THIS)
	{
		if(ExpP())
			return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == K_NEW)
	{
		if (scan.Read().m_type.m_type == K_INT)
			if (scan.Read().m_type.m_type == LEFT_BK)
				if(Exp())
					if (scan.Read().m_type.m_type == RIGHT_BK)
						if(ExpP())
							return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == K_NEW)
	{
		if (scan.Read().m_type.m_type == ID)
			if (scan.Read().m_type.m_type == LEFT_PH)
				if(ExpList())
					if (scan.Read().m_type.m_type == RIGHT_PH)
						if(ExpP())
							return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == LOGICAL_NOT)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == LEFT_PH)
	{
		if(Exp())
			if (scan.Read().m_type.m_type == RIGHT_PH)
				if(ExpP())
					return true;
	}
	scan.Back(oldward);
	{scan.Back(oldward);return false;}
}

bool Parser::ExpP()
{
	int oldward = scan.nowward;
	if (scan.Read().m_type.m_type == PLUS)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == MINUS)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == MULTIPLY)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == DIVIDE)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == LESS)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == GREATER)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == EQUAL)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == LOGICAL_AND)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == LOGICAL_OR)
	{
		if(Exp())
			if(ExpP())
				return true;
	}
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == LEFT_BK)
	{
		if(Exp())
			if (scan.Read().m_type.m_type == RIGHT_BK)
				if(ExpP())
					return true;
	}	
	scan.Back(oldward);
	if (scan.Read().m_type.m_type == DOT)
	{
		if (scan.Read().m_type.m_type == ID)
			if (scan.Read().m_type.m_type == LEFT_PH)
				if(ExpList())
					if (scan.Read().m_type.m_type == RIGHT_PH)
						if(ExpP())
							return true;
	}
	scan.Back(oldward);
	{scan.Back(oldward);return true;}
}

bool Parser::ExpList()
{
	int oldward = scan.nowward;
	if(Exp())
	{
		while(ExpRest()){}
		return true;
	}
	scan.Back(oldward);
	{scan.Back(oldward);return true;}
}

bool Parser::ExpRest()
{
	int oldward = scan.nowward;
	if (scan.Read().m_type.m_type != COMMA){scan.Back(oldward);return false;}
	if(!Exp()){scan.Back(oldward);return false;}
	return true;
}