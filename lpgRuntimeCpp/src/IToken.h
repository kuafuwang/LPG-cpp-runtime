#pragma once
#include <string>
#include <vector>


struct IToken;
struct IPrsStream;
struct ILexStream;

struct IGetToken
{
	virtual ~IGetToken() = default;
	virtual IToken* getLeftIToken() = 0;
    virtual IToken* getRightIToken() = 0;
};
struct IToken
{
	virtual ~IToken() = default;
	static constexpr  wchar_t EOF_ = '\uffff';

  virtual    int getKind()=0;
  virtual      void setKind(int kind)=0;

  virtual      int getStartOffset()=0;
  virtual      void setStartOffset(int startOffset)=0;

  virtual       int getEndOffset()=0;
  virtual       void setEndOffset(int endOffset)=0;

  virtual      int getTokenIndex()=0;
  virtual      void setTokenIndex(int i)=0;

  virtual      int getAdjunctIndex()=0;
  virtual      void setAdjunctIndex(int i)=0;

  virtual     std::vector<IToken*>  getPrecedingAdjuncts()=0;
  virtual     std::vector<IToken*> getFollowingAdjuncts()=0;

  virtual     ILexStream* getILexStream()=0;
    /**
     * @deprecated replaced by {@link #getILexStream()}
     */
  virtual      ILexStream* getLexStream()=0;

  virtual      IPrsStream* getIPrsStream()=0;
    /**
     * @deprecated replaced by {@link #getIPrsStream()}
     */
  virtual     IPrsStream* getPrsStream()=0;

  virtual      int getLine()=0;
  virtual      int getColumn()=0;
  virtual      int getEndLine()=0;
  virtual      int getEndColumn()=0;

    /**
     * @deprecated replaced by toString()
     */
  virtual     std::wstring getValue(std::vector<wchar_t>& inputChars)=0;

  virtual      std::wstring toString()=0;
  std::string to_utf8_string();
};

