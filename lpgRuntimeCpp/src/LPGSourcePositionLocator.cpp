#include "LPGSourcePositionLocator.h"

#include "IAst.h"

Object* LPGSourcePositionLocator::findNode(Object* root, int startOffset, int endOffset)
{
	if (! dynamic_cast<IAst*>(root))
		return root;

	IAst* astNode = (IAst*)root;

	auto children = astNode->getAllChildren();
	if (!children.empty())
	{
		for (int i = 0; i < children.size(); i++)
		{
			IAst* maybe = (IAst*)findNode(children[i], startOffset, endOffset);
			if (maybe != nullptr)
				return maybe;
		}
	}
	if (startOffset >= astNode->getLeftIToken()->getStartOffset()
		&& endOffset <= astNode->getRightIToken()->getEndOffset())
		return astNode;

	return nullptr;
}

int LPGSourcePositionLocator::getStartOffset(Object* entity)
{
	if ( dynamic_cast<IAst*>(entity))
	{
		IAst * n = (IAst*)entity;
		return n->getLeftIToken()->getStartOffset();
	}
	else if (dynamic_cast<IToken*>(entity ))
	{
		auto tok = (IToken*)entity;
		return tok->getStartOffset();
	}

	return 0;
}

int LPGSourcePositionLocator::getEndOffset(Object* entity)
{
	if (dynamic_cast<IAst*>(entity))
	{
		IAst * n = (IAst*)entity;
		return n->getRightIToken()->getEndOffset();
	}
	else if (dynamic_cast<IToken*>(entity))
	{
		auto tok = (IToken*)entity;
		return tok->getEndOffset();
	}

	return 0;
}

int LPGSourcePositionLocator::getLength(Object* node)
{
	return getEndOffset(node) - getStartOffset(node);
}
