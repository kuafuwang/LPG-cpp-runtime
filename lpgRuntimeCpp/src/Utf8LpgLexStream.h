#pragma once
#include "Utf8LexStream.h"

struct Utf8LpgLexStream :public  Utf8LexStream
{
    /**
     *
     */
    Utf8LpgLexStream() :Utf8LexStream() {

    }

    /**
     * @param tab
     */
    Utf8LpgLexStream(int tab) :Utf8LexStream(tab) {

    }

    /**
     * @param fileName
     */
    Utf8LpgLexStream(const std::wstring& fileName):Utf8LexStream(fileName)
    {
       
    }

    /**
     * @param fileName
     * @param tab
     */
    Utf8LpgLexStream(const std::wstring& fileName, int tab) :Utf8LexStream(fileName, tab)
    {
   
    }

    /**
     * @param inputChars
     * @param fileName
     */
    Utf8LpgLexStream(shared_ptr_string inputChars, const std::wstring& file_name):Utf8LexStream(inputChars, file_name) {
        
    }

    /**
     * @param lineOffsets
     * @param inputChars
     * @param fileName
     */
    Utf8LpgLexStream(std::shared_ptr< IntSegmentedTuple>& lineOffsets, shared_ptr_string inputChars,
        const std::wstring& file_name):Utf8LexStream(lineOffsets, inputChars, file_name) {
        
    }

   
    /**
     * @param inputChars
     * @param fileName
     * @param tab
     */
    Utf8LpgLexStream(shared_ptr_string inputChars, const std::wstring& file_name, int tab):Utf8LexStream(inputChars,file_name,tab)
	{
      
    }

   

    /* (non-Javadoc)
     * @see lpg.runtime.TokenStream#getKind(int)
     */
    virtual  int getKind(int i) = 0;

    virtual std::vector<std::wstring> orderedExportedSymbols() = 0;
};
