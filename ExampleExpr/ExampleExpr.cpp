

#include <iostream>
#include <ostream>

#include "ExprLexer.h"
#include "ExprParser.h"
#include "IMessageHandler.h"

struct MessageHandle : public IMessageHandler
{
	void handleMessage(int errorCode, const Location& msgLocation, const Location& errorLocation,
	                   const std::wstring& filename, const std::vector<std::wstring>& errorInfo) override
	{
		
        std::wcout << "filename:" << filename << std::endl;
        std::wcout << "errorCode:" << errorCode << std::endl;
		for(auto& it : errorInfo)
		{
            std::wcout << "\terrorInfo:" << it << std::endl;
		}
       
	}
};

int main(void)
{
    
    int idd = 2;
    MessageHandle  handle;
  
    typedef  unsigned char byte;
    ExprLexer lex(LR"(D:\workspace\New_Parser\lpg\src\jikespg.g)",4);
   lex.setMessageHandler(&handle);
    ExprParser  prs(&lex);
   // prs.setMessageHandler(&handle);
    lex.lexer(&prs);
    prs.parser();
   
}


