


#pragma once
#include "Any.h"
#include "Exception.h"
#include "IAbstractArrayList.h"
#include "IAst.h"
#include "ILexStream.h"

namespace ExprParser_top_level_ast{
  struct Visitor;
  struct ArgumentVisitor;
  struct ResultVisitor;
  struct ResultArgumentVisitor;
  struct Ast;
  struct AbstractAstList;
  struct AstToken;
  struct E;
  struct T;
  struct F;
  struct ParenExpr;
  struct AbstractVisitor;
  struct AbstractResultVisitor;
struct Visitor
{
    virtual void visit(AstToken *n)=0;
    virtual void visit(E *n)=0;
    virtual void visit(T *n)=0;
    virtual void visit(F *n)=0;
    virtual void visit(ParenExpr *n)=0;

    virtual void visit(Ast *n)=0;
};
struct ArgumentVisitor
{
    virtual void visit(AstToken *n, Object* o)=0;
    virtual void visit(E *n, Object* o)=0;
    virtual void visit(T *n, Object* o)=0;
    virtual void visit(F *n, Object* o)=0;
    virtual void visit(ParenExpr *n, Object* o)=0;

  virtual  void visit(Ast *n, Object* o)=0;
};
struct ResultVisitor
{
  virtual  lpg::Any visit(AstToken *n)=0;
  virtual  lpg::Any visit(E *n)=0;
  virtual  lpg::Any visit(T *n)=0;
  virtual  lpg::Any visit(F *n)=0;
  virtual  lpg::Any visit(ParenExpr *n)=0;

  virtual  lpg::Any visit(Ast *n)=0;
};
struct ResultArgumentVisitor
{
  virtual  lpg::Any visit(AstToken *n, Object* o)=0;
  virtual  lpg::Any visit(E *n, Object* o)=0;
  virtual  lpg::Any visit(T *n, Object* o)=0;
  virtual  lpg::Any visit(F *n, Object* o)=0;
  virtual  lpg::Any visit(ParenExpr *n, Object* o)=0;

  virtual  lpg::Any visit(Ast *n, Object* o)=0;
};
struct Ast :public IAst
{
    IAst* getNextAst() { return nullptr; }
     IToken* leftIToken=nullptr;
        IToken*    rightIToken=nullptr;
    IAst* getParent()
    {
        throw UnsupportedOperationException("noparent-saved option in effect");
    }

    IToken* getLeftIToken() { return leftIToken; }
    IToken* getRightIToken() { return rightIToken; }
    std::vector<IToken*> getPrecedingAdjuncts() { return leftIToken->getPrecedingAdjuncts(); }
    std::vector<IToken*> getFollowingAdjuncts() { return rightIToken->getFollowingAdjuncts(); }

    std::wstring toString()
    {
        return leftIToken->getILexStream()->toString(leftIToken->getStartOffset(), rightIToken->getEndOffset());
    }

    Ast(IToken* token) { this->leftIToken = this->rightIToken = token; }
    Ast(IToken* leftIToken, IToken* rightIToken)
    {
        this->leftIToken = leftIToken;
        this->rightIToken = rightIToken;
    }

    void initialize() {}

    std::vector<IAst*> getChildren()
    {
        throw UnsupportedOperationException("noparent-saved option in effect");
    }
    std::vector<IAst*> getAllChildren() { return getChildren(); }

     virtual void accept(Visitor* v)=0;
     virtual void accept(ArgumentVisitor *v, Object* o)=0;
     virtual lpg::Any accept(ResultVisitor *v)=0;
     virtual lpg::Any accept(ResultArgumentVisitor *v, Object* o)=0;
    void accept(IAstVisitor* v) {}
};

struct AbstractAstList :public Ast ,public IAbstractArrayList<Ast*>
{
    bool leftRecursive;
    int size() { return list.size(); }
   std::vector<Ast   *> getList() { return list; }
    Ast *getElementAt(int i) { return (Ast*) list.at(leftRecursive ? i : list.size() - 1 - i); }
   std::vector<IAst    *> getArrayList()
    {
        if (! leftRecursive) // reverse the list 
        {
            for (int i = 0, n = list.size() - 1; i < n; i++, n--)
            {
                auto ith = list[i];
                 auto nth = list[n];
                list[i]=(nth);
                list[n]=(ith);
            }
            leftRecursive = true;
        }
         return  std::vector<IAst*>(list.begin(), list.end());
    }
    /**
     * @deprecated replaced by {@link #addElement()}
     *
     */
    bool add(Ast *element)
    {
        addElement(element);
        return true;
    }

    void addElement(Ast *element)
    {
        list.push_back(element);
        if (leftRecursive)
             rightIToken = element->getRightIToken();
        else leftIToken =  element->getLeftIToken();
    }

    AbstractAstList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):Ast(leftIToken, rightIToken)
    {
        this->leftRecursive = leftRecursive;
    }

    AbstractAstList(Ast *element, bool leftRecursive):Ast(element->getLeftIToken(), element->getRightIToken())
    {
         this->leftRecursive = leftRecursive;
        list.push_back(element);
    }

};

struct AstToken :public  Ast
{
    AstToken(IToken* token):Ast(token){ }
    IToken* getIToken() { return leftIToken; }
    std::wstring toString() { return leftIToken->toString(); }


    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }
};

/**
 *<em>
 *<li>Rule 2:  E ::= T
 *</em>
 *<p>
 *<b>
 *<li>Rule 1:  E ::= E + T
 *</b>
 */
struct E :public Ast
{
    Ast *lpg_E;
    Ast *lpg_T;

    Ast *getE() { return lpg_E; };
    void setE(Ast *lpg_E) { this->lpg_E = lpg_E; }
    Ast *getT() { return lpg_T; };
    void setT(Ast *lpg_T) { this->lpg_T = lpg_T; }

    E(IToken* leftIToken, IToken* rightIToken,
      Ast *lpg_E,
      Ast *lpg_T):Ast(leftIToken, rightIToken)    {
        this->lpg_E = lpg_E;
        this->lpg_T = lpg_T;
        initialize();
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }
};

/**
 *<em>
 *<li>Rule 4:  T ::= F
 *</em>
 *<p>
 *<b>
 *<li>Rule 3:  T ::= T * F
 *</b>
 */
struct T :public Ast
{
    Ast *lpg_T;
    Ast *lpg_F;

    Ast *getT() { return lpg_T; };
    void setT(Ast *lpg_T) { this->lpg_T = lpg_T; }
    Ast *getF() { return lpg_F; };
    void setF(Ast *lpg_F) { this->lpg_F = lpg_F; }

    T(IToken* leftIToken, IToken* rightIToken,
      Ast *lpg_T,
      Ast *lpg_F):Ast(leftIToken, rightIToken)    {
        this->lpg_T = lpg_T;
        this->lpg_F = lpg_F;
        initialize();
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }
};

/**
 *<b>
 *<li>Rule 5:  F ::= IntegerLiteral
 *</b>
 */
struct F :public AstToken
{
    F(IToken* token) :AstToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }
};

/**
 *<b>
 *<li>Rule 6:  F ::= ( E )
 *</b>
 */
struct ParenExpr :public Ast
{
    Ast *lpg_E;

    Ast *getE() { return lpg_E; };
    void setE(Ast *lpg_E) { this->lpg_E = lpg_E; }

    ParenExpr(IToken* leftIToken, IToken* rightIToken,
              Ast *lpg_E):Ast(leftIToken, rightIToken)    {
        this->lpg_E = lpg_E;
        initialize();
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }
};

struct AbstractVisitor :public Visitor, public ArgumentVisitor
{
    virtual void unimplementedVisitor(const std::string &s)=0;

 virtual   void visit(AstToken *n) { unimplementedVisitor("visit(AstToken)"); }
  virtual  void visit(AstToken *n, Object* o) { unimplementedVisitor("visit(AstToken, Object)"); }

 virtual   void visit(E *n) { unimplementedVisitor("visit(E)"); }
  virtual  void visit(E *n, Object* o) { unimplementedVisitor("visit(E, Object)"); }

 virtual   void visit(T *n) { unimplementedVisitor("visit(T)"); }
  virtual  void visit(T *n, Object* o) { unimplementedVisitor("visit(T, Object)"); }

 virtual   void visit(F *n) { unimplementedVisitor("visit(F)"); }
  virtual  void visit(F *n, Object* o) { unimplementedVisitor("visit(F, Object)"); }

 virtual   void visit(ParenExpr *n) { unimplementedVisitor("visit(ParenExpr)"); }
  virtual  void visit(ParenExpr *n, Object* o) { unimplementedVisitor("visit(ParenExpr, Object)"); }


  virtual  void visit(Ast *n)
    {
        if (dynamic_cast< AstToken*>(n)){ visit((AstToken*) n);return;}
        if (dynamic_cast< E*>(n)){ visit((E*) n);return;}
        if (dynamic_cast< T*>(n)){ visit((T*) n);return;}
        if (dynamic_cast< F*>(n)){ visit((F*) n);return;}
        if (dynamic_cast< ParenExpr*>(n)){ visit((ParenExpr*) n);return;}
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
    void visit(Ast *n, Object* o)
    {
        if (dynamic_cast<AstToken*>(n)) {visit((AstToken*) n, o);return;}
        if (dynamic_cast<E*>(n)) {visit((E*) n, o);return;}
        if (dynamic_cast<T*>(n)) {visit((T*) n, o);return;}
        if (dynamic_cast<F*>(n)) {visit((F*) n, o);return;}
        if (dynamic_cast<ParenExpr*>(n)) {visit((ParenExpr*) n, o);return;}
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
};
struct AbstractResultVisitor :public ResultVisitor,public ResultArgumentVisitor
{
    virtual lpg::Any unimplementedVisitor(const std::string& s);

    lpg::Any visit(AstToken *n) { return unimplementedVisitor("visit(AstToken)"); }
    lpg::Any visit(AstToken *n, Object* o) { return  unimplementedVisitor("visit(AstToken, Object)"); }

    lpg::Any visit(E *n) { return unimplementedVisitor("visit(E)"); }
    lpg::Any visit(E *n, Object* o) { return  unimplementedVisitor("visit(E, Object)"); }

    lpg::Any visit(T *n) { return unimplementedVisitor("visit(T)"); }
    lpg::Any visit(T *n, Object* o) { return  unimplementedVisitor("visit(T, Object)"); }

    lpg::Any visit(F *n) { return unimplementedVisitor("visit(F)"); }
    lpg::Any visit(F *n, Object* o) { return  unimplementedVisitor("visit(F, Object)"); }

    lpg::Any visit(ParenExpr *n) { return unimplementedVisitor("visit(ParenExpr)"); }
    lpg::Any visit(ParenExpr *n, Object* o) { return  unimplementedVisitor("visit(ParenExpr, Object)"); }


    lpg::Any visit(Ast *n)
    {
        if (dynamic_cast<AstToken*>(n) ) return visit((AstToken*) n);
        if (dynamic_cast<E*>(n) ) return visit((E*) n);
        if (dynamic_cast<T*>(n) ) return visit((T*) n);
        if (dynamic_cast<F*>(n) ) return visit((F*) n);
        if (dynamic_cast<ParenExpr*>(n) ) return visit((ParenExpr*) n);
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
    lpg::Any visit(Ast *n, Object *o)
    {
        if (dynamic_cast<AstToken*>(n) ) return visit((AstToken*) n, o);
        if (dynamic_cast<E*>(n) ) return visit((E*) n, o);
        if (dynamic_cast<T*>(n) ) return visit((T*) n, o);
        if (dynamic_cast<F*>(n) ) return visit((F*) n, o);
        if (dynamic_cast<ParenExpr*>(n) ) return visit((ParenExpr*) n, o);
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
};

};
