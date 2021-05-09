#include "lpgRuntime.h"

#include "ConfigurationElement.h"
#include "ParseErrorCodes.h"
#include "StateElement.h"
#include "tuple.h"
const  std::vector< std::wstring> ParseErrorCodes::errorMsgText =
{
    /* LEX_ERROR_CODE */                      (L"ParseErrorCodes.LEX_ERROR_CODE"), //$NON-NLS-1$
    /* ERROR_CODE */                          (L"ParseErrorCodes.ERROR_CODE"), //$NON-NLS-1$
    /* BEFORE_CODE */                         (L"ParseErrorCodes.BEFORE_CODE"), //$NON-NLS-1$
    /* INSERTION_CODE */                      (L"ParseErrorCodes.INSERTION_CODE"), //$NON-NLS-1$
    /* INVALID_CODE */                        (L"ParseErrorCodes.INVALID_CODE"), //$NON-NLS-1$
    /* SUBSTITUTION_CODE, SECONDARY_CODE */   (L"ParseErrorCodes.SUBSTITUTION_CODE"), //$NON-NLS-1$
    /* DELETION_CODE */                       (L"ParseErrorCodes.DELETION_CODE"), //$NON-NLS-1$
    /* MERGE_CODE */                          (L"ParseErrorCodes.MERGE_CODE"), //$NON-NLS-1$
    /* MISPLACED_CODE */                      (L"ParseErrorCodes.MISPLACED_CODE"), //$NON-NLS-1$
    /* SCOPE_CODE */                          (L"ParseErrorCodes.SCOPE_CODE"), //$NON-NLS-1$
    /* EOF_CODE */                            (L"ParseErrorCodes.EOF_CODE"), //$NON-NLS-1$
    /* INVALID_TOKEN_CODE, ERROR_RULE_ERROR */(L"ParseErrorCodes.INVALID_TOKEN_CODE"), //$NON-NLS-1$
    /* ERROR_RULE_WARNING */                  (L"ParseErrorCodes.ERROR_RULE_WARNING"), //$NON-NLS-1$
    /* NO_MESSAGE_CODE */                     (L"ParseErrorCodes.NO_MESSAGE_CODE") //$NON-NLS-1$
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

int main(void)
 {
    return 0;
 }