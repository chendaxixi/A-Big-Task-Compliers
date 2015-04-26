#ifndef SCANNER_H
#define SCANNER_H


#include "AlternationExpression.h"
#include "CharArrayExpression.h"
#include "ConcatenationExpression.h"
#include "EmptyExpression.h"
#include "LiteralExpression.h"
#include "StarExpression.h"
#include "SymbolExpression.h"
#include "Lexicon.h"
#include "Token.h"
#include "SourceReader.h"

namespace Compilers_Scanners
{
	class Scanner
	{
	public:
		Scanner():m_lexicon(), m_source(), nowward(0), forward(-1),  buffer(NULL)
		{
//			m_source.source.get(buffer1, bufferSize-1, -2);
//			buffer1[bufferSize-1] = 0;
//			m_source.source.get(buffer2, bufferSize-1, -2);
//			buffer2[bufferSize-1] = 0;
			InitLexicon();
		}
		~Scanner()
		{
			if (buffer != NULL)
				delete[] buffer;
		}
	public:
		Lexicon m_lexicon;
		SourceReader m_source;
		char* buffer;
		int nowward;
		int forward;
//		static vector<string> strList;
//		static vector<int> kindList;
	public:
		Token Read();
		bool Succeed(DFAConvert& DFA);
		Token AfterFind(TokenType& type);
		void InitLexicon();
//		int Insert();
		void Back(int oldward)
		{
			nowward = oldward;
			forward = nowward-1;
		}
		void Open(const char* szName, int nMode = ios::in)
		{
			m_source.source.open(szName, nMode);
			if (m_source.source.fail()) return;
			streampos curpos = m_source.source.tellg();
			m_source.source.seekg(0, ios::end);
			int len = m_source.source.tellg();
			m_source.source.seekg(curpos);
			buffer = new char[len+5];
			m_source.source.get(buffer, len+5, -2);
		}
	};
};

#endif