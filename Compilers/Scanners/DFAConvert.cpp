#include "DFAConvert.h"

using namespace Compilers_Scanners;

void DFAConvert::Build()
{
	TreeExpression::size = 0;
	TreeExpression::followpos.resize(0);
	TreeExpression::charpos.resize(0);
	TreeExpression tree(m_exp);
	size = TreeExpression::size;
	DStates.push_back(tree.firstpos);
	for (int i = 0;i < 128;i++)
		DTran[i].push_back(-1);
	endFlag++;
	set<int> s;
	set<int>::iterator s1;
	set<int>::iterator s2;
	set<int>::iterator stemp1;
	set<int>::iterator stemp2;
	int temp;
	while (firstFlag < endFlag)
	{
		for (int c = 0;c < 128;c++)
		{
			s1 = DStates[firstFlag].begin();
			s2 = DStates[firstFlag].end();
			s.clear();
			while (s1 != s2)
			{
				if (tree.charpos[*s1] == c)
				{
					stemp1 = tree.followpos[*s1].begin();
					stemp2 = tree.followpos[*s1].end();
					while (stemp1 != stemp2)
					{
						s.insert(*stemp1);
						stemp1++;
					}
				}
				s1++;
			}
			if (s.size() > 0)
			{
				temp = Find(DStates, s);
				if (temp == -1)
				{
					DStates.push_back(s);
					for (int i = 0;i < 128;i++)
						DTran[i].push_back(-1);
					temp = DStates.size()- 1;
					endFlag++;
				}
				DTran[c][firstFlag] = temp;
			}
		}
		firstFlag++;
	}
}

int DFAConvert::Find(vector<set<int>>& src, set<int>& s)
{
	int n = src.size();
	for (int i = 0;i < n;i++)
		if (src[i] == s)
			return i;
	return -1;
}
