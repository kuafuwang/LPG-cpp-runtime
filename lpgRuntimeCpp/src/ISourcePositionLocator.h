#pragma once
#include <string>

#include "Object.h"

struct ISourcePositionLocator
{
	virtual ~ISourcePositionLocator() = default;
	/**
     * @param ast the root of the AST
     * @param offset the textual offset, in characters
     * @return the innermost AST node whose textual extent contains the given text offset
     */
    virtual  Object* findNode(Object* astRoot, int offset)=0;

    /**
     * @param ast the root of the AST
     * @param startOffset the beginning of the textual extent, in characters
     * @param endOffset the end of the textual extent, in characters
     * @return the innermost AST node whose textual extent completely contains the given text extent
     */
    virtual  Object* findNode(Object* astRoot, int startOffset, int endOffset)=0;

    /**
     * @param entity the program entity, e.g. AST node, token, or some
     * kind of type system object
     * @return the offset, in characters, of the beginning of the textual extent
     * spanned by the given entity
     */
    virtual int getStartOffset(Object* entity)=0;

    /**
     * @param entity the program entity, e.g. AST node, token, or some
     * kind of type system object
     * @return the offset, in characters, of the end of the textual extent spanned by the given entity
     * It should be the character offset of the last character of the token,
     * equivalent to <code>getStartOffset() + getLength() - 1</code>
     *
     *
     */
    virtual int getEndOffset(Object* entity)=0;

    /**
     * @param entity the program entity, e.g. AST node, token, or some
     * kind of type system object
     * @return the length, in characters, of the textual extent spanned by the given AST node
     */
    virtual int getLength(Object* entity)=0;

    /**
     * @return the workspace-relative or file-system absolute path to the compilation unit
     * (source or compiled, if no source) that contains the given AST node or ISourceEntity.
     * The path is in "portable" format, using the Eclipse convention '/' for the path
     * component separator.
     * @see org.eclipse.core.runtime.IPath#toPortableString()
     */
   virtual   std::string getPath(Object* node) = 0;
};

 