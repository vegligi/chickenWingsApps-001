#ifndef __TEXTUNIT_H
#define __TEXTUNIT_H

#include <cstdlib> 
#include <string>

#include <sstream> 
#include<wchar.h>

#include "cocos2d.h"

#include <iostream>
#include <locale>


class TextUnit{

 public:

	 static int Str2int(std::string str) 
	 {
		 return std::atoi( str.c_str() ); 
	 }

	 static float Str2float(std::string str)
	 {

		 return std::atof( str.c_str());
	 }
	 
	 static std::string int2Str( int i)
	 {
		 std::stringstream ss;

		 ss << i;
		 return ss.str(); 

	 }

	 static std::string float2Str( float f)
	 {
		 std::stringstream ss;

		 ss << f; 
		 return ss.str(); 

	 }


	static wchar_t * MBCS2Unicode(wchar_t * buff, const char * str)
	 {
		 wchar_t * wp = buff;
		 char * p = (char *)str;
		 while(*p)
		 {
			 if(*p & 0x80)
			 {
				 *wp = *(wchar_t *)p;
				 p++;
			 }
			 else{
				 *wp = (wchar_t) *p;
			 }
			 wp++;
			 p++;
		 }
		 *wp = 0x0000;
		 return buff;
	 }

	static char * Unicode2MBCS(char * buff, const wchar_t * str)
	 {
		 wchar_t * wp = (wchar_t *)str;
		 char * p = buff, * tmp;
		 while(*wp){
			 tmp = (char *)wp;
			 if(*wp & 0xFF00){
				 *p = *tmp;
				 p++;tmp++;
				 *p = *tmp;
				 p++;
			 }
			 else{
				 *p = *tmp;
				 p++;
			 }
			 wp++;
		 }
		 *p = 0x00;
		 return buff;
	 }

	static std::wstring str2wstr(std::string str)
	{
		size_t len = str.size();
		wchar_t * b = (wchar_t *)malloc((len+1)*sizeof(wchar_t));
		MBCS2Unicode(b,str.c_str());
		std::wstring r(b);
		free(b);
		return r;
	}

	static std::string wstr2str(std::wstring wstr)
	{
		size_t len = wstr.size();
		char * b = (char *)malloc((2*len+1)*sizeof(char));
		Unicode2MBCS(b,wstr.c_str());
		std::string r(b);
		free(b);
		return r;
	}

// 	static wchar_t * UTF8ToUnicode( const char* str )
// 	{
// 		int textlen ;
// 		wchar_t * result;
// 		textlen = MultiByteToWideChar( CP_UTF8, 0, str,-1, NULL,0 ); 
// 		result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
// 		memset(result,0,(textlen+1)*sizeof(wchar_t)); 
// 		MultiByteToWideChar(CP_UTF8, 0,str,-1,(LPWSTR)result,textlen ); 
// 		return result; 
// 	}
// 
// 	static char * UnicodeToUTF8( const wchar_t* str )
// 	{
// 		char* result;
// 		int textlen;
// 		textlen = WideCharToMultiByte( CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL );
// 		result =(char *)malloc((textlen+1)*sizeof(char));
// 		memset(result, 0, sizeof(char) * ( textlen + 1 ) );
// 		WideCharToMultiByte( CP_UTF8, 0, str, -1, result, textlen, NULL, NULL );
// 		return result;
// 	}

	static std::string ws2s(const std::wstring& ws)
	{
		std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
		setlocale(LC_ALL, "chs"); 
		const wchar_t* _Source = ws.c_str();
		size_t _Dsize = 2 * ws.size() + 1;
		char *_Dest = new char[_Dsize];
		memset(_Dest,0,_Dsize);
		wcstombs(_Dest,_Source,_Dsize);
		std::string result = _Dest;
		delete []_Dest;
		setlocale(LC_ALL, curLocale.c_str());
		return result;
	}
	static std::wstring s2ws(const std::string& s)
	{
		setlocale(LC_ALL, "chs"); 
		const char* _Source = s.c_str();
		size_t _Dsize = s.size() + 1;
		wchar_t *_Dest = new wchar_t[_Dsize];
		wmemset(_Dest, 0, _Dsize);
		mbstowcs(_Dest,_Source,_Dsize);
		std::wstring result = _Dest;
		delete []_Dest;
		setlocale(LC_ALL, "C");
		return result;
	}

	static std::vector<std::string> toVectorCharacters(const std::string& $str, int $characterWidth) {  
		int size = $str.size();    
		std::vector<std::string> result;  
		int i = 0;
		for(int i = 0 ; i < size ; i++ )
		{
			char c = $str[i];     
			if (c <= 127 && c >= 0) {   
				std::string asciiChar($str.begin() + i, $str.begin() + i + 1);     
				result.push_back(asciiChar);     
			} else {           
				std::string utf8char($str.begin() + i, $str.begin() + i + $characterWidth);   
				result.push_back(utf8char);         
				i += $characterWidth - 1;       
			} 

		}

		return result;
	}
};

#endif