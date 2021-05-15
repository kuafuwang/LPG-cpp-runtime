#pragma once
#include <string>
#include <vector>


struct TokenStream
{
	
	  
	virtual ~TokenStream() = default;
	virtual    int getToken()=0;

  virtual  int getToken(int end_token)=0;

  virtual  int getKind(int i)=0;

  virtual  int getNext(int i)=0;

  virtual  int getPrevious(int i)=0;

  virtual  std::wstring getName(int i)=0;

  virtual  int peek()=0;

  virtual  void reset(int i)=0;

  virtual  void reset()=0;

  virtual  int badToken()=0;

  virtual int getLine(int i)=0;

  virtual int getColumn(int i)=0;

  virtual  int getEndLine(int i)=0;

  virtual  int getEndColumn(int i)=0;

  virtual  bool afterEol(int i)=0;

  virtual std::wstring getFileName()=0;

  virtual int getStreamLength()=0;

  virtual int getFirstRealToken(int i)=0;

  virtual int getLastRealToken(int i)=0;

  virtual void reportError(int errorCode, int leftToken, int rightToken, const std::wstring& errorInfo)=0;

  virtual void reportError(int errorCode, int leftToken, int errorToken, int rightToken,const std::wstring& errorInfo)=0;

  virtual void reportError(int errorCode, int leftToken, int rightToken, const std::vector< std::wstring>&  errorInfo)=0;

  virtual void reportError(int errorCode, int leftToken, int errorToken, int rightToken,const std::vector< std::wstring>& errorInfo)=0;

  virtual std::wstring toString(int startOffset, int endOffset) = 0;
	
  std::string to_utf8_string(int startOffset, int endOffset);
};
