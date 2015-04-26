#include "TreeExpression.h"

using namespace Compilers_Scanners;

int TreeExpression::size = 0;
vector<set<int>> TreeExpression::followpos;
vector<char> TreeExpression::charpos;

void TreeExpression::Build()
{
	switch (m_exp->m_type)
	{
	case ExpressionType::Empty:
		m_root = Leaf;
		nullable = true;
		break;
	case ExpressionType::Symbol:
		m_root = Leaf;
		CreateFollow();
		firstpos.insert(size);
		lastpos.insert(size);
		charpos.push_back(m_exp->GetSymbol());
		size++;
		nullable = false;
		break;
	case Alternation:
		m_root = Union;
		m_left = new TreeExpression(m_exp->GetLeft());
		m_right = new TreeExpression(m_exp->GetRight());
		nullable = m_left->nullable || m_right->nullable;
		SetUnion(m_left->firstpos, m_right->firstpos, firstpos);
		SetUnion(m_left->lastpos, m_right->lastpos, lastpos);
		break;
	case Concatenation:
		m_root = Concat;
		m_left = new TreeExpression(m_exp->GetLeft());
		m_right = new TreeExpression(m_exp->GetRight());
		nullable = m_left->nullable && m_right->nullable;
		if (m_left->nullable)
			SetUnion(m_left->firstpos, m_right->firstpos, firstpos);
		else
			firstpos = m_left->firstpos;
		if (m_right->nullable)
			SetUnion(m_left->lastpos, m_right->lastpos, lastpos);
		else
			lastpos = m_right->lastpos;
		InsertFollow(m_left->lastpos, m_right->firstpos);
		break;
	case KleeneStar:
		m_root = Star;
		m_left = new TreeExpression(m_exp->GetStarExp());
		m_right = NULL;
		nullable = true;
		firstpos = m_left->firstpos;
		lastpos = m_left->lastpos;
		InsertFollow(lastpos, firstpos);
		break;
	case AlternationCharArray:
		m_root = Leaf;
		nullable = false;
		CharArrayIntoTree(m_exp->GetCharArray());
		break;
	case StringLiteral:
		StringLiteralIntoTree(m_exp->GetString());
		break;
	default:
		break;
	}
}

void TreeExpression::CreateFollow()
{
	set<int> s;
	followpos.push_back(s);
}

void TreeExpression::InsertFollow(set<int>& s1, set<int>& s2)
{
	set<int>::iterator sbegin = s1.begin();
	set<int>::iterator send = s1.end();
	while (sbegin != send)
	{
		followpos[*sbegin].insert(s2.begin(), s2.end());
		sbegin++;
	}
}

void TreeExpression::CharArrayIntoTree(vector<char>& charArray)
{
	int n = charArray.size();
	for (int i = 0;i < n;i++)
	{
		CreateFollow();
		firstpos.insert(size);
		lastpos.insert(size);
		charpos.push_back(charArray[i]);
		size++;
	}
}

void TreeExpression::StringLiteralIntoTree(string& str)
{
	int n = str.length();
	if (n == 1)
	{
		m_root = Leaf;
		CreateFollow();
		firstpos.insert(size);
		lastpos.insert(size);
		charpos.push_back(str[0]);
		size++;
		nullable = false;
		return;
	}
	string s1 = str.substr(0, n-1);
	string s2(1, str[n-1]);
	m_root = Concat;
	m_left = new TreeExpression(Expression::Literal(s1));
	m_right = new TreeExpression(Expression::Literal(s2));
	nullable = m_left->nullable && m_right->nullable;
	if (m_left->nullable)
		SetUnion(m_left->firstpos, m_right->firstpos, firstpos);
	else
	firstpos = m_left->firstpos;
	if (m_right->nullable)
		SetUnion(m_left->lastpos, m_right->lastpos, lastpos);
	else
		lastpos = m_right->lastpos;
	InsertFollow(m_left->lastpos, m_right->firstpos);	
}