--
-- An instance of this template must have a $Export section and the export_terminals option
--
-- Macros that may be redefined in an instance of this template
--
--     $eof_token
--     $additional_interfaces
--     $super_stream_class -- subclass com.ibm.lpg.LpgLexStream for getKind
--     $prs_stream_class -- use /.PrsStream./ if not subclassing
--
-- B E G I N N I N G   O F   T E M P L A T E   LexerTemplateD
--
%Options programming_language=rt_cpp,margin=4
%Options table
%options action-block=("*.h", "/.", "./")
%options ParseTable=ParseTable
%Options prefix=Char_

--
-- This template requires that the name of the EOF token be set
-- to EOF and that the prefix be "Char_" to be consistent with
-- KeywordTemplateD.
--
%Eof
    EOF
%End

--
-- This template also requires that the name of the parser EOF
-- Token to be exported be set to EOF_TOKEN
--
%Export
    EOF_TOKEN
%End

%Define
    --
    -- Macros that are be needed in an instance of this template
    --
    $eof_token /.$_EOF_TOKEN./
    
    $additional_interfaces /../
    $super_stream_class /.LpgLexStream./
    $prs_stream_class /.IPrsStream./

    $prs_stream /. // macro prs_stream is deprecated. Use function getPrsStream
                  getPrsStream()./
    $setSym1 /. // macro setSym1 is deprecated. Use function setResult
               lexParser->setSym1./
    $setResult /. // macro setResult is deprecated. Use function setResult
                 lexParser->setSym1./
    $getSym /. // macro getSym is deprecated. Use function getLastToken
              lexParser->getSym./
    $getToken /. // macro getToken is deprecated. Use function getToken
                lexParser->getToken./
    $getLeftSpan /. // macro getLeftSpan is deprecated. Use function getLeftSpan
                   lexParser->getFirstToken./
    $getRightSpan /. // macro getRightSpan is deprecated. Use function getRightSpan
                    lexParser->getLastToken./

    --
    -- Macros useful for specifying actions
    --
    $Header
    /.
                //
                // Rule $rule_number:  $rule_text
                //./

    $DefaultAction
    /. $Header
                case $rule_number: { ./

    $BeginAction /.$DefaultAction./

    $EndAction
    /.          break;
                }./

    $BeginJava
    /.$BeginAction
                $symbol_declarations./

    $EndJava /.$EndAction./

    $NoAction
    /. $Header
                case $rule_number:
                    break; ./

    $BeginActions
    /.
         void ruleAction(int ruleNumber)
        {
            switch(ruleNumber)
            {./

    $SplitActions
    /.
                    default:
                        ruleAction$rule_number(ruleNumber);
                        break;
                }
                return;
            }

             void ruleAction$rule_number(int ruleNumber)
            {
                switch (ruleNumber)
                {./

    $EndActions
    /.
                default:
                    break;
            }
            return;
        }./
%End

%Globals
    /.
    #include <string>
    #include "ExprLexersym.h"
    #include "ExprParsersym.h"
    #include "src/IPrsStream.h"
    #include "src/LexParser.h"
    #include "src/LexStream.h"
    #include "src/ParseTable.h"
    #include "src/RuleAction.h"
    #include "src/LpgLexStream.h"
    #include "ExprLexerprs.h"
    #include "src/IToken.h"
    ./
%End

%Headers
    /.
     struct $action_type :public $super_stream_class ,public $exp_type, public $sym_type,public RuleAction$additional_interfaces
    {
        inline  static ParseTable* prs = new $prs_type();
         ParseTable* getParseTable() { return prs; }

         LexParser* lexParser = new LexParser(this, prs, this);
         LexParser* getParser() { return lexParser; }

         int getToken(int i) { return lexParser->getToken(i); }
         int getRhsFirstTokenIndex(int i) { return lexParser->getFirstToken(i); }
         int getRhsLastTokenIndex(int i) { return lexParser->getLastToken(i); }

         int getLeftSpan() { return lexParser->getToken(1); }
         int getRightSpan() { return lexParser->getLastToken(); }
  
         $action_type(const std::wstring& filename, int tab) : $super_stream_class (filename, tab)
        {
           
        }

         $action_type(shared_ptr_array<wchar_t>& input_chars, const std::wstring& filename, int tab=1)
         : $super_stream_class (input_chars, filename, tab)
        {
           
        }

    
         $action_type() {}

         std::vector<std::wstring> orderedExportedSymbols() { return $exp_type::orderedTerminalSymbols; }
         LexStream* getLexStream() { return (LexStream*) this; }

         void initializeLexer($prs_stream_class * prsStream, int start_offset, int end_offset)
        {
            if (getInputChars().size() == 0)
                throw  std::exception("LexStream was not initialized");
            setPrsStream(prsStream);
            prsStream->makeToken(start_offset, end_offset, 0); // Token list must start with a bad token
        }

         void addEOF($prs_stream_class * prsStream, int end_offset)
        {
            prsStream->makeToken(end_offset, end_offset, $eof_token); // and end with the end of file token
            prsStream->setStreamLength(prsStream->getSize());
        }

         void lexer($prs_stream_class *prsStream)
        {
            lexer(nullptr, prsStream);
        }
        
         void lexer(Monitor* monitor, $prs_stream_class * prsStream)
        {
            initializeLexer(prsStream, 0, -1);
            lexParser->parseCharacters(monitor);  // Lex the input characters
            addEOF(prsStream, getStreamIndex());
        }

         void lexer($prs_stream_class *prsStream, int start_offset, int end_offset)
        {
            lexer(nullptr, prsStream, start_offset, end_offset);
        }
        
         void lexer(Monitor* monitor, $prs_stream_class *prsStream, int start_offset, int end_offset)
        {
            if (start_offset <= 1)
                 initializeLexer(prsStream, 0, -1);
            else initializeLexer(prsStream, start_offset - 1, start_offset - 1);

            lexParser->parseCharacters(monitor, start_offset, end_offset);

            addEOF(prsStream, (end_offset >= getStreamIndex() ? getStreamIndex() : end_offset + 1));
        }

        /**
         * If a parse stream was not passed to this Lexical analyser then we
         * simply report a lexical error. Otherwise, we produce a bad token.
         */
         void reportLexicalError(int startLoc, int endLoc) {
            IPrsStream *prs_stream = getPrsStream();
            if (prs_stream == nullptr)
                $super_stream_class ::reportLexicalError(startLoc, endLoc);
            else {
                //
                // Remove any token that may have been processed that fall in the
                // range of the lexical error... then add one error token that spans
                // the error range.
                //
                for (int i = prs_stream->getSize() - 1; i > 0; i--) {
                    if (prs_stream->getStartOffset(i) >= startLoc)
                         prs_stream->removeLastToken();
                    else break;
                }
                prs_stream->makeToken(startLoc, endLoc, 0); // add an error token to the prsStream
            }        
        }
    ./
%End

%Rules
    /.$BeginActions./
%End

%Trailers
    /.
        $EndActions
    };
    ./
%End

--
-- E N D   O F   T E M P L A T E
--
