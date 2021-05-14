#pragma once
#include <vector>
template <class T>
struct IAbstractArrayList {
	std::vector<T> list;
public:
	virtual ~IAbstractArrayList() = default;
	virtual int size() = 0;
     virtual  T getElementAt(int i)=0;
     virtual std::vector<T> getList()=0;
     virtual void addElement(T elt) = 0;
    

    /**
     * @deprecated.  No longer needed as this interface now extends List.
     */
     virtual std::vector<T> getAllChildren()=0;
};
