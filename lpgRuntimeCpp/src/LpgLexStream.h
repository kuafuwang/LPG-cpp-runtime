#pragma once
#include "LexStream.h"

struct LpgLexStream :public  LexStream
{
    /**
     *
     */
    LpgLexStream() :LexStream() {

    }

    /**
     * @param tab
     */
    LpgLexStream(int tab) :LexStream(tab) {

    }

    /**
     * @param fileName
     */
    LpgLexStream(const std::wstring& fileName):LexStream(fileName)
    {
       
    }

    /**
     * @param fileName
     * @param tab
     */
    LpgLexStream(const std::wstring& fileName, int tab) :LexStream(fileName, tab)
    {
   
    }

    /**
     * @param inputChars
     * @param fileName
     */
    LpgLexStream(shared_ptr_wstring inputChars, const std::wstring& file_name):LexStream(inputChars, file_name) {
        
    }

    /**
     * @param inputChars
     * @param inputLength
     * @param fileName
     */
    LpgLexStream(shared_ptr_wstring  inputChars, int inputLength, const std::wstring& file_name)
	:LexStream(inputChars, inputLength, file_name){
     
    }

    /**
     * @param lineOffsets
     * @param inputChars
     * @param fileName
     */
    LpgLexStream(std::shared_ptr< IntSegmentedTuple>& lineOffsets, shared_ptr_wstring inputChars,
        const std::wstring& file_name):LexStream(lineOffsets, inputChars, file_name) {
        
    }

    /**
     * @param lineOffsets
     * @param inputChars
     * @param inputLength
     * @param fileName
     */
    LpgLexStream(std::shared_ptr< IntSegmentedTuple>& lineOffsets, shared_ptr_wstring inputChars, int inputLength,
        const std::wstring& file_name):LexStream(lineOffsets,inputChars, inputLength,file_name) {
      
    }

    /**
     * @param inputChars
     * @param fileName
     * @param tab
     */
    LpgLexStream(shared_ptr_wstring inputChars, const std::wstring& file_name, int tab):LexStream(inputChars,file_name,tab)
	{
      
    }

    /**
     * @param lineOffsets
     * @param inputChars
     * @param fileName
     * @param tab
     */
    LpgLexStream(shared_ptr_wstring inputChars, int inputLength, const std::wstring& fileName, int tab) :LexStream(inputChars,inputLength,fileName,tab){
      
    }

    /* (non-Javadoc)
     * @see lpg.runtime.TokenStream#getKind(int)
     */
    virtual  int getKind(int i) = 0;

    virtual std::vector<std::wstring> orderedExportedSymbols() = 0;
};
