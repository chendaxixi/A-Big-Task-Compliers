#ifndef SETTEMPLATE_H
#define SETTEMPLATE_H

#include <set>
using std::set;

template<class T>
void SetUnion(set<T>&set1, set<T>&set2, set<T>&set3)
{
	set<T>::iterator sbegin1 = set1.begin();
	set<T>::iterator sbegin2 = set2.begin();
	set<T>::iterator send1 = set1.end();
	set<T>::iterator send2 = set2.end();
	while (sbegin1 != send1)
	{
		while ((sbegin2 != send2) && (*sbegin2 < *sbegin1))
		{
			set3.insert(*sbegin2);
			sbegin2++;
		}
		while ((sbegin2 != send2) && (sbegin1 != send1) && (*sbegin1 == *sbegin2))
		{
			set3.insert(*sbegin2);
			sbegin1++;
			sbegin2++;
		}
		while ((sbegin1 != send1) && (*sbegin1 < *sbegin2))
		{
			set3.insert(*sbegin1);
			sbegin1++;
		}
	}
	while (sbegin2 != send2)
	{
		set3.insert(*sbegin2);
		sbegin2++;
	}
}

#endif