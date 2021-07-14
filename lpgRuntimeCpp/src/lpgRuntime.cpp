#include "lpgRuntime.h"

#include <iostream>
#include "IcuUtil.h"
#include "ConfigurationElement.h"
#include "IAst.h"
#include "ParseTableProxy.h"
#include "ParseErrorCodes.h"
#include "StateElement.h"
#include "TokenStream.h"
#include "ParseTable.h"
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

struct IToken::Data
{
    void* data=nullptr;
};
IToken::IToken():d_ptr(nullptr)
{
}

IToken::~IToken()
{
    delete d_ptr;
}

std::string IToken::to_utf8_string()
 {
     return IcuUtil::ws2s(toString());
 }

void IToken::setExtData(void* _v)
{
	if(!d_ptr)
	{
        d_ptr = new Data();
	}
  
    d_ptr->data = _v;
}

void* IToken::getExtData() const
{
    return  d_ptr->data;
}

std::string TokenStream::to_utf8_string(int startOffset, int endOffset)
 {
      return IcuUtil::ws2s(toString(startOffset, endOffset));
 }




  ParseTableProxy::ParseTableProxy(ParseTable* prs) : _prs(prs), ERROR_SYMBOL(prs->getErrorSymbol()),
                                                      SCOPE_UBOUND(prs->getScopeUbound()),
                                                      SCOPE_SIZE(prs->getScopeSize()),
                                                      MAX_NAME_LENGTH(prs->getMaxNameLength()),
                                                      NUM_STATES(prs->getNumStates()),
                                                      NT_OFFSET(prs->getNtOffset()),
                                                      LA_STATE_OFFSET(prs->getLaStateOffset()),
                                                      MAX_LA(prs->getMaxLa()),
                                                      NUM_RULES(prs->getNumRules()),
                                                      NUM_NONTERMINALS(prs->getNumNonterminals()),
                                                      NUM_SYMBOLS(prs->getNumSymbols()),
                                                      START_STATE(prs->getStartState()),
                                                      IDENTIFIER_SYMBOL(prs->getIdentifier_SYMBOL()),
                                                      EOFT_SYMBOL(prs->getEoftSymbol()),
                                                      EOLT_SYMBOL(prs->getEoltSymbol()),
                                                      ACCEPT_ACTION(prs->getAcceptAction()),
                                                      ERROR_ACTION(prs->getErrorAction()),
                                                      BACKTRACK(prs->getBacktrack()),
                                                      isValidForParser(prs->isValidForParser()),
                                                      _isNullable(prs->get_isNullable_data()),
                                                      _prosthesesIndex(prs->get_prosthesesIndex_data()),
                                                      _isKeyword(prs->get_isKeyword_data()),
                                                      _baseCheck(prs->get_baseCheck_data()), _rhs(prs->get_rhs_data()),
                                                      _baseAction(prs->get_baseAction_data()), _lhs(prs->get_lhs_data()),
                                                      _termCheck(prs->get_termCheck_data()),
                                                      _termAction(prs->get_termAction_data())

  {
  }

