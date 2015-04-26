#ifndef DFACONVERT_H
#define DFACONVERT_H

#include "TreeExpression.h"

namespace Compilers_Scanners
{
	class DFAConvert
	{
	public:
		DFAConvert(Expression* exp):DStates(), firstFlag(0), endFlag(0), m_exp(exp)
		{
			for (int i = 0;i < 128;i++)
				DTran[i].resize(0);
			Build();
		}
	public:
		vector<set<int>> DStates;
		int firstFlag;
		int endFlag;
//		int finalState;
		int size;
		vector<int> DTran[128];
		Expression* m_exp;
	public:
		void Build();
		int Find(vector<set<int>>& src, set<int>& s);
	};
}

#endif