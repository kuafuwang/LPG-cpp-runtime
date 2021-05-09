#pragma once
#include <string>
#include <vector>

struct ParseErrorCodes
{
   
    
         static constexpr  int  LEX_ERROR_CODE = 0,
            ERROR_CODE = 1,
            BEFORE_CODE = 2,
            INSERTION_CODE = 3,
            INVALID_CODE = 4,
            SUBSTITUTION_CODE = 5,
            SECONDARY_CODE = 5,
            DELETION_CODE = 6,
            MERGE_CODE = 7,
            MISPLACED_CODE = 8,
            SCOPE_CODE = 9,
            EOF_CODE = 10,
            INVALID_TOKEN_CODE = 11,
            ERROR_RULE_ERROR_CODE = 11,
            ERROR_RULE_WARNING_CODE = 12,
            NO_MESSAGE_CODE = 13;

         static   const std::vector< std::wstring> errorMsgText;
    

};
