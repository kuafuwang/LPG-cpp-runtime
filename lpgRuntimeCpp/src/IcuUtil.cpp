#include "IcuUtil.h"


#include <cassert>
#include <unicode/ucsdet.h>
#include <unicode/ucnv.h>

#include <cstdio>
#include <utility>
#include <string>
#include <vector>
using namespace  std;
namespace IcuUtil
{

	pair<string, int> detectTextEncoding(const char* data, int len)
	{
		string matchMost;
		int confidence = 0;
		int matchCount = 0;
		const UCharsetMatch** csm;
		UErrorCode status = U_ZERO_ERROR;
		UCharsetDetector* csd = ucsdet_open(&status);
		if (status != U_ZERO_ERROR)
			return pair<string, int>("", 0);

		ucsdet_setText(csd, data, len, &status);
		if (U_FAILURE(status))
			goto DET_ERROR;

		
		csm = ucsdet_detectAll(csd, &matchCount, &status);
		if (U_FAILURE(status))
			goto DET_ERROR;

		if (matchCount <= 0)
			goto DET_ERROR;

		confidence = ucsdet_getConfidence(csm[0], &status);
		if (U_FAILURE(status))
			goto DET_ERROR;

		matchMost = ucsdet_getName(csm[0], &status);
		if (U_FAILURE(status))
			goto DET_ERROR;

		return pair<string, int>(matchMost, confidence);

	DET_ERROR:
		ucsdet_close(csd);
		return pair<string, int>(string(), 0);
	}

	std::string ws2s(std::wstring const& wstr)
	{
		return  {};
	}

	std::wstring s2ws(std::string const& str)
	{
		return  {};
	}

	std::pair<std::string, int> detectFileEncoding(const wchar_t* fileName)
	{
		FILE* pFile = nullptr;
		_wfopen_s(&pFile,fileName, L"r");
		pair<string, int> encoding;
		assert(pFile);
		if (!pFile)
			return  encoding;
		struct _stat64i32 statbuf;
		_wstat64i32(fileName, &statbuf);
		const auto bufsize = statbuf.st_size;
		char* buf = new char[bufsize];

		uint32_t count = fread(buf, 1, bufsize, pFile);
		fclose(pFile);

		encoding = detectTextEncoding(buf, count);

		delete[] buf;
		return encoding;
	}
	bool getFileUnicodeContent(const wchar_t* fileName,vector<wchar_t>& content)
	{
		FILE* pFile = nullptr;
		_wfopen_s(&pFile,fileName, L"r");
		
		if (!pFile)
			return  false;
		
		struct _stat32 statbuf;
		_wstat32(fileName, &statbuf);
		const auto bufsize = statbuf.st_size;
		std::vector<char> holder( bufsize, 0);
		
		uint32_t count = fread(&holder[0], 1, bufsize, pFile);
		fclose(pFile);
		holder.resize(count);
		const pair<string, int> detectResult = detectTextEncoding(&holder[0], count);
		std::string strEncoding;
		if (detectResult.second > 70)
			strEncoding = detectResult.first;
		else
		{
			strEncoding = getDefaultEncoding();
		}
		content.resize(bufsize);
	
		bool flush = false;
		UErrorCode errcode = U_ZERO_ERROR;
		UConverter* pFromCnv = ucnv_open(strEncoding.data(), &errcode);
		if (U_FAILURE(errcode)) return false;
		UErrorCode inerr = U_ZERO_ERROR;

		
		const char* in_source = &holder[0];
		UChar* tmp_target = (UChar*)content.data();
		const auto tmp_buf = tmp_target;
		
		ucnv_toUnicode(pFromCnv, &tmp_target, tmp_target + content.size(), &in_source, in_source + holder.size(), NULL, flush, &inerr);
		if (U_FAILURE(inerr))
			return false;
	    count = tmp_target - tmp_buf;
		content.resize(count);
		
		return true;
	}
	/*
	 * toConverterName,      转换后的字符编码
	 * fromConverterName,    转换前的字符编码
	 * target,               存储转换后的字符串， 传出参数
	 * targetCapacity,       存储容量，target的大小
	 * source，              需要转换的字符串
	 * sourceLength,         source的大小
	**/
	int convert(const char* toConverterName,
		const char* fromConverterName,
		char* target,
		int32_t targetCapacity,
		const char* source,
		int32_t sourceLength, __out int& outlen)
	{
		UErrorCode error = U_ZERO_ERROR;
		outlen = ucnv_convert(toConverterName, fromConverterName, target, targetCapacity, source, sourceLength, &error);

		return error;
	}
	const string& getDefaultEncoding()
	{
		static string defaultEncoding;
		if (defaultEncoding.empty()) {
			UErrorCode errCode = U_ZERO_ERROR;
			UConverter* dftCnv = ucnv_open(NULL, &errCode);
			const char* defEncodingName = ucnv_getName(dftCnv, &errCode);//ucnv_getDefaultName();
			if (defEncodingName) {
				const char* standarName = ucnv_getStandardName(defEncodingName, "IANA", &errCode);//name of the standard governing the names; MIME and IANA are such standard 
				if (standarName == NULL) {
					standarName = ucnv_getStandardName(defEncodingName, "MIME", &errCode);
				}
				if (standarName == NULL)
					defaultEncoding = defEncodingName;
				else
					defaultEncoding = standarName;
			}

			ucnv_close(dftCnv);
		}

		return defaultEncoding;
	}

	const string getCheckedEncoding(const pair<string, int>& encoding)
	{
		string encode;
		if (!encoding.first.empty() && encoding.second > 50)
			encode = encoding.first;
		else
			encode = getDefaultEncoding();

		return encode;
	}

}