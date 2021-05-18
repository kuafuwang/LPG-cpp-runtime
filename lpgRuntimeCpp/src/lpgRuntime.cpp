#include "lpgRuntime.h"

#include <iostream>
#include "IcuUtil.h"
#include "ConfigurationElement.h"
#include "IAst.h"
#include "ParseErrorCodes.h"
#include "StateElement.h"
#include "TokenStream.h"

#include "tuple.h"
const  std::vector< std::wstring> ParseErrorCodes::errorMsgText =
{
    /* LEX_ERROR_CODE */                      (L"unexpected character ignored"), //$NON-NLS-1$
    /* ERROR_CODE */                          (L"parsing terminated at this token"), //$NON-NLS-1$
    /* BEFORE_CODE */                         (L" inserted before this token"), //$NON-NLS-1$
    /* INSERTION_CODE */                      (L" expected after this token"), //$NON-NLS-1$
    /* INVALID_CODE */                        (L"unexpected input discarded"), //$NON-NLS-1$
    /* SUBSTITUTION_CODE, SECONDARY_CODE */   (L" expected instead of this input"), //$NON-NLS-1$
    /* DELETION_CODE */                       (L" unexpected token(s) ignored"), //$NON-NLS-1$
    /* MERGE_CODE */                          (L" formed from merged tokens"), //$NON-NLS-1$
    /* MISPLACED_CODE */                      (L"misplaced construct(s)"), //$NON-NLS-1$
    /* SCOPE_CODE */                          (L" inserted to complete scope"), //$NON-NLS-1$
    /* EOF_CODE */                            (L" reached after this token"), //$NON-NLS-1$
    /* INVALID_TOKEN_CODE, ERROR_RULE_ERROR */(L" is invalid"), //$NON-NLS-1$
    /* ERROR_RULE_WARNING */                  (L" is ignored"), //$NON-NLS-1$
    /* NO_MESSAGE_CODE */                     (L"") //$NON-NLS-1$
};
 void ConfigurationElement::retrieveStack(Array<int>& stack)
{
    StateElement* tail = last_element;
    for (int i = stack_top; i >= 0; i--)
    {
        stack[i] = tail->number;
        tail = tail->parent;
    }
}
 std::string IAst::to_utf8_string()
 {
     return IcuUtil::ws2s(toString());
 }

 std::string IToken::to_utf8_string()
 {
     return IcuUtil::ws2s(toString());
 }

  std::string TokenStream::to_utf8_string(int startOffset, int endOffset)
 {
      return IcuUtil::ws2s(toString(startOffset, endOffset));
 }
