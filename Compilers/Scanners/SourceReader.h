#ifndef SOURCEREADER_H
#define SOURCEREADER_H

#include <fstream>
using namespace std;

namespace Compilers_Scanners
{
	class SourceReader
	{
	public:
		SourceReader():source(){}
		SourceReader(const char* szName, int nMode = ios::in):source(szName, nMode){}
	public:
		ifstream source;
	};
};

#endif