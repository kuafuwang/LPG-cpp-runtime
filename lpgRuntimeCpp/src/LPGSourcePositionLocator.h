#pragma once
#include "ISourcePositionLocator.h"

struct LPGSourcePositionLocator :public ISourcePositionLocator {
    Object* findNode(Object* root, int offset) {
        return findNode(root, offset, offset);
    }

    Object* findNode(Object* root, int startOffset, int endOffset);

    int getStartOffset(Object* entity);

    int getEndOffset(Object* entity);

    int getLength(Object* node);

    std::string getPath(Object* entity) {
        return "";
    }
};
