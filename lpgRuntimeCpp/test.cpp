

#include <iostream>
#include <ostream>

#include "ExprLexer.h"
#include "ExprParser.h"
#include "src/IMessageHandler.h"

struct MessageHandle : public IMessageHandler
{
	void handleMessage(int errorCode, std::vector<int> msgLocation, std::vector<int> errorLocation,
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
    MessageHandle handle;
  
    typedef  unsigned char byte;
    ExprLexer lex(LR"(C:\Users\kuafu\source\repos\lpg2\Debug\jikespg.g)",4);
   // lex.setMessageHandler(&handle);
    ExprParser  prs(&lex);
  //  prs.setMessageHandler(&handle);
    lex.lexer(&prs);
    prs.parser();
   
}


