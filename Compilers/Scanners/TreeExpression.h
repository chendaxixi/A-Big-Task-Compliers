#ifndef TREEEXPRESSION_H
#define TREEEXPRESSION_H

#include "Expression.h"
#include "SetTemplate.h"

namespace Compilers_Scanners
{
	enum RegularOp
	{
		Concat,
		Union,
		Star,
		Leaf
	};
	class TreeExpression;
	class TreeExpression
	{
	public:
		TreeExpression(Expression* exp):m_root(Leaf), m_exp(exp), firstpos(), lastpos(),
			m_left(NULL), m_right(NULL), nullable(false)
		{
			Build();
		}
		~TreeExpression()
		{
			if (m_left != NULL)
				delete m_left;
			if (m_right != NULL)
				delete m_right;
		}
	public:
		RegularOp m_root;
		TreeExpression *m_left, *m_right;
		Expression* m_exp;
		bool nullable;
		set<int> firstpos, lastpos;
		static vector<set<int>> followpos;
		static vector<char> charpos;
		static int size;
	public:
		void Build();
		void CreateFollow();
		void InsertFollow(set<int>& s1, set<int>& s2);
		void CharArrayIntoTree(vector<char>& charArray);
		void StringLiteralIntoTree(string& str);
	};
}

#endif