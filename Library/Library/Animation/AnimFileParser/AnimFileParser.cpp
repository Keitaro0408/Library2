﻿/**
 * @file   AnimFileParser.cpp
 * @brief  AnimFileParserクラスの実装
 * @author kotani
 */
#include "AnimFileParser.h"

Lib::AnimFileParser::~AnimFileParser()
{
	ReleaseLoadBuffer();
}

void Lib::AnimFileParser::FileLoad(LPCTSTR _pFileName)
{
	ReleaseLoadBuffer();
	fopen_s(&m_pFile, _pFileName, "r");
	fseek(m_pFile, 0, SEEK_END);
	m_FileSize = ftell(m_pFile) + 1;
	fseek(m_pFile, 0, SEEK_SET);

	m_pBuffer = new TCHAR[m_FileSize];
	m_pTmpBuffer = new TCHAR[m_FileSize];
	memset(m_pBuffer, '\0', m_FileSize);
	memset(m_pTmpBuffer, '\0', m_FileSize);
	m_pBuffer[m_FileSize - 1] = '\0';
	m_pTmpBuffer[m_FileSize - 1] = '\0';

	fread(m_pBuffer, m_FileSize, 1, m_pFile);
	fclose(m_pFile);
}

bool Lib::AnimFileParser::ReadData(LPCTSTR _pGroupName, std::vector<float>* _pData)
{
	TCHAR* pContext;

	TCHAR* pBuffer = strstr(m_pBuffer, _pGroupName);
	if (pBuffer == nullptr)
	{
		return false;
	}

	strcpy_s(m_pTmpBuffer, m_FileSize, pBuffer);
	//見つけたグループを終わりまで取ってくる
	strcpy_s(m_pTmpBuffer, m_FileSize, strtok_s(m_pTmpBuffer, "}", &pContext));

	//最初のグループ名はいらないので保存しない
	strtok_s(m_pTmpBuffer, "{,", &pContext);

	while (1)
	{
		pBuffer = strtok_s(nullptr, "{,", &pContext);

		if (pBuffer == nullptr)
		{
			break;
		}
		else
		{
			_pData->push_back(static_cast<float>(atof(pBuffer)));
		}
	}
	return true;
}

void Lib::AnimFileParser::ReleaseLoadBuffer()
{
	delete[] m_pBuffer;
	m_pBuffer = nullptr;

	delete[] m_pTmpBuffer;
	m_pTmpBuffer = nullptr;
}

