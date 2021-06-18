#ifndef TUPLE_INCLUDED
#define TUPLE_INCLUDED

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory>
#include <stdexcept>
#include <vector>
//
// Wrapper for a simple array
//


//
// Wrapper for a simple array
//
template <class T>
class Array
{
    int size;
    T* info;

public:
    Array() : size(0),
        info(NULL)
    {}

    Array(int size_) : size(size_)
    {
        info = new T[size];
    }

    Array(int size_, T value) : size(size_)
    {
        info = new T[size];
        Initialize(value);

        return;
    }

    ~Array()
    {
        delete[] info;
    }

    void Initialize(T init_value)
    {
        for (int i = 0; i < size; i++)
            info[i] = init_value;
    }

    void Resize(int new_size)
    {
        if (new_size > size)
        {
            T* old_info = info;
            info = (T*)memmove(new T[new_size], old_info, size * sizeof(T));
            delete[] old_info;
        }
        size = new_size;

        return;
    }

    void Reallocate(int new_size)
    {
        if (new_size > size)
        {
            T* old_info = info;
            info = (T*) new T[new_size];
            delete[] old_info;
        }
        size = new_size;

        return;
    }

    //
    // Set all fields in the array to val.
    //
    void Memset(int val = 0)
    {
        memset(info, val, size * sizeof(T));
    }

    //
    // Set all field in the array to 0 starting at index i.
    //
    void MemReset(int i = 0)
    {
        if (size == 0)
            return;

        //
        // Use this code when debugging to force a crash instead of
        // allowing the assertion to be raised.
        //
        //if (i < 0 || i >= size)
        //{
        //    Array<T> *a = NULL;
        //    a -> size = 0;
        //}
        assert(!OutOfRange(i));

        int length = size - i;
        memset(&info[i], 0, length * sizeof(T));
    }

    int Size() { return size; }

    //
    // Can the array be indexed with i?
    //
    inline bool OutOfRange(const int i) { return (i < 0 || i >= size); }

    //
    // Return the ith element of the array
    //
    T& operator[](const int i)
    {
        //
        // Use this code when debugging to force a crash instead of
        // allowing the assertion to be raised.
        //
        //if (i < 0 || i >= size)
        //{
        //    Array<T> *a = NULL;
        //    a -> size = 0;
        //}
        assert(!OutOfRange(i));

        return info[i];
    }

    T& at(const int i)
    {
        if (OutOfRange(i))
        {
            throw  std::out_of_range("invalid index subscript");
        }
        return info[i];

    }
};

//
// This Tuple template class can be used to construct a dynamic
// array of arbitrary objects. The space for the array is allocated
// in blocks of _size 2**LOG_BLKSIZE. In declaring a tuple the user
// may specify an estimate of how many elements he expects. Based
// on that estimate, suitable values are calculated for log_blksize
// and base_increment. If these estimates are found to be off later,
// more space will be allocated.
//
template <class T>
class Tuple
{
protected:

    enum { DEFAULT_LOG_BLKSIZE = 3, DEFAULT_BASE_INCREMENT = 4 };

    Array<T*> base;
    int top,
        _size;

    int log_blksize,
        base_increment;

    inline int Blksize() { return (1 << log_blksize); }

    //
    // Allocate another block of storage for the dynamic array.
    //
    inline void AllocateMoreSpace()
    {
        //
        // The variable _size always indicates the maximum number of
        // elements that has been allocated for the array.
        // Initially, it is set to 0 to indicate that the array is empty.
        // The pool of available elements is divided into segments of _size
        // 2**log_blksize each. Each segment is pointed to by a slot in
        // the array base.
        //
        // By dividing _size by the _size of the segment we obtain the
        // index for the next segment in base. If base is full, it is
        // reallocated.
        //
        //
        int k = _size >> log_blksize; /* which segment? */

        //
        // If the base is overflowed, reallocate it and initialize the new elements to NULL.
        //
        if (k == base.Size())
        {
            base.Resize(k == 0 ? base_increment : k * 2);
            base.MemReset(k); // initialize the new base elements
        }

        //
        // We allocate a new segment and place its adjusted address in
        // base[k]. The adjustment allows us to index the segment directly,
        // instead of having to perform a subtraction for each reference.
        // See operator[] below.
        //
        base[k] = new T[Blksize()];
        base[k] -= _size;

        //
        // Finally, we update SIZE.
        //
        _size += Blksize();

        return;
    }

public:

    //
    // This function is invoked with an integer argument n. It ensures
    // that enough space is allocated for n elements in the dynamic array.
    // I.e., that the array will be indexable in the range  (0..n-1)
    //
    // Note that this function can be used as a garbage collector.  When
    // invoked with no argument(or 0), it frees up all dynamic space that
    // was allocated for the array.
    //
    inline void Resize(const int n = 0)
    {
        //if (n < 0)
        //{
        //    Tuple<T> *p = NULL;
        //    p -> top = 0;
        //}
        assert(n >= 0);

        //
        // If array did not previously contain enough space, allocate
        // the necessary additional space. Otherwise, if the array had
        // more blocks than are needed, release the extra blocks.
        //
        if (n > _size)
        {
            do
            {
                AllocateMoreSpace();
            } while (n > _size);
        }
        else if (n < _size)
        {
            // slot is the index of the base element whose block
            // will contain the (n-1)th element.
            int slot = (n <= 0 ? -1 : (n - 1) >> log_blksize);

            for (int k = (_size >> log_blksize) - 1; k > slot; k--)
            {
                _size -= Blksize();
                base[k] += _size;
                delete[] base[k];
                base[k] = NULL;
            }

            if (slot < 0)
                base.Resize(0);
        }

        top = n;
    }

    //
    // This function is used to reset the _size of a dynamic array without
    // allocating or deallocting space. It may be invoked with an integer
    // argument n which indicates the new _size or with no argument which
    // indicates that the _size should be reset to 0.
    //
    inline void reset(const int n = 0)
    {
        //
        // Use this code when debugging to force a crash instead of
        // allowing the assertion to be raised.
        //
        // if (! (n >= 0 && n <= top))
        // {
        //     Tuple<T> *p = NULL;
        //     p -> top = 0;
        // }
        //
        assert(n >= 0 && n <= top);

        top = n;
    }
    //
// Return a reference to the ith element of the dynamic array.
//
// Note that no check is made here to ensure that 0 <= i < top.
// Such a check might be useful for debugging and a range exception
// should be thrown if it yields true.
//
    T& get(int i)
    {
        if (OutOfRange(i)) {
            throw std::out_of_range("out of range");
        }
        return (*this)[i];
    }
    //
// Insert an element in the dynamic array at the location indicated.
//
    void set(int i, T element)
    {
        (*this)[i] = element;
    }
    //
    // Return length of the dynamic array.
    //
    inline int Length() { return top; }
    inline int size() { return top; }
    //
    // Can the tuple be indexed with i?
    //
    inline bool OutOfRange(const int i) { return (i < 0 || i >= top); }

    //
    // Return a reference to the ith element of the dynamic array.
    //
    // Note that no check is made here to ensure that 0 <= i < top.
    // Such a check might be useful for debugging and a range exception
    // should be thrown if it yields true.
    //
    inline T& operator[](const int i)
    {
        //
        // Use this code when debugging to force a crash instead of
        // allowing the assertion to be raised.
        //
        //if (! (i >= 0 && i < top))
        //{
        //    Tuple<T> *p = NULL;
        //    p -> top = 0;
        //}
        assert(!OutOfRange(i));

        return base[i >> log_blksize][i];
    }

    //
    // Add an element to the dynamic array and return the top index.
    //
    inline int nextIndex()
    {
        int i = top++;
        if (i == _size)
            AllocateMoreSpace();
        return i;
    }

    inline void Push(T elt) { this->Next() = elt; }
    inline void add(T elt) { this->Next() = elt; }
    //
    // Not "return (*this)[--top]" because that may violate an invariant
    // in operator[].
    //
    inline T Pop() { assert(top != 0); top--; return base[top >> log_blksize][top]; }
    inline T Top() { assert(top != 0); return (*this)[top - 1]; }

    //
    // Add an element to the dynamic array and return a reference to
    // that new element.
    //
    inline T& Next() { int i = nextIndex(); return base[i >> log_blksize][i]; }

    //
    // Assignment of a dynamic array to another.
    //
    inline Tuple<T>& operator=(Tuple<T>& rhs)
    {
        if (this != &rhs)
        {
            Resize(rhs.top);
            for (int i = 0; i < rhs.top; i++)
                base[i >> log_blksize][i] = rhs.base[i >> log_blksize][i];
        }

        return *this;
    }

    //
    // Equality comparison of a dynamic array to another.
    //
    bool operator==(Tuple<T>& rhs)
    {
        if (this != &rhs)
        {
            if (this->top != rhs.top)
                return false;
            for (int i = 0; i < rhs.top; i++)
            {
                if (base[i >> log_blksize][i] != rhs.base[i >> log_blksize][i])
                    return false;
            }
        }
        return true;
    }

    //
    // Constructor of a Tuple
    //
    Tuple(unsigned estimate = 0)
    {
        if (estimate == 0)
        {
            log_blksize = DEFAULT_LOG_BLKSIZE;
            base_increment = DEFAULT_BASE_INCREMENT;
        }
        else
        {
            for (log_blksize = 1; (((unsigned)1 << log_blksize) < estimate) && (log_blksize < 31); log_blksize++)
                ;
            if (log_blksize <= DEFAULT_LOG_BLKSIZE)
                base_increment = 1;
            else if (log_blksize < 13)
            {
                base_increment = (unsigned)1 << (log_blksize - 4);
                log_blksize = 4;
            }
            else
            {
                base_increment = (unsigned)1 << (log_blksize - 8);
                log_blksize = 8;
            }
            base_increment++; // add a little margin to avoid reallocating the base.
        }

        _size = 0;
        top = 0;
    }

    //
    // Constructor of a Tuple
    //
    Tuple(int log_blksize_, int base_increment_) : log_blksize(log_blksize_),
        base_increment(base_increment_)
    {
        _size = 0;
        top = 0;
    }

    //
    // Initialization of a dynamic array.
    //
    Tuple(Tuple<T>& rhs) : log_blksize(rhs.log_blksize),
        base_increment(rhs.base_increment)
    {
        _size = 0;
        *this = rhs;
    }

    //
    // Destructor of a dynamic array.
    //
    ~Tuple() { Resize(0); }

    void Initialize(T value)
    {
        for (int i = 0; i < top; i++)
            (*this)[i] = value;
        return;
    }

    void Reverse()
    {
        for (int head = 0, tail = Length() - 1; head < tail; head++, tail--)
        {
            T temp = (*this)[head];
            (*this)[head] = (*this)[tail];
            (*this)[tail] = temp;

        }

        return;
    }

    // ********************************************************************************************** //

    //
    // Return the total _size of temporary space allocated.
    //
    inline size_t SpaceAllocated(void)
    {
        return ((base.Size() * sizeof(T**)) + (_size * sizeof(T)));
    }

    //
    // Return the total _size of temporary space used.
    //
    inline size_t SpaceUsed(void)
    {
        return (((_size >> log_blksize) * sizeof(T**)) + (top * sizeof(T)));
    }

};


//
//
//
template <class T>
class ConvertibleArray : public Tuple<T>
{
public:

    ConvertibleArray(int estimate = 0) : Tuple<T>(estimate),
        array(NULL)
    {}

    ConvertibleArray(int log_blksize, int base_increment) : Tuple<T>(log_blksize, base_increment),
        array(NULL)
    {}

    ~ConvertibleArray() { delete[] array; }

    //
    // This function converts a tuple into a regular array and destroys the
    // original tuple.
    //
    inline T*& Array()
    {
        if ((!array) && Tuple<T>::top > 0)
        {
            array = new T[Tuple<T>::top];

            int i = 0,
                processed_size = 0,
                n = (Tuple<T>::top - 1) >> Tuple<T>::log_blksize; // the last non-empty slot!
            while (i < n)
            {
                memmove(&array[processed_size], Tuple<T>::base[i] + processed_size, Tuple<T>::Blksize() * sizeof(T));
                delete[](Tuple<T>::base[i] + processed_size);
                i++;
                processed_size += Tuple<T>::Blksize();
            }
            memmove(&array[processed_size], Tuple<T>::base[n] + processed_size, (Tuple<T>::top - processed_size) * sizeof(T));
            delete[](Tuple<T>::base[n] + processed_size);
            Tuple<T>::base.Resize(0);
            Tuple<T>::_size = 0;
        }

        return array;
    }

    inline T& operator[](const int i)
    {
        //
        // Use this code when debugging to force a crash instead of
        // allowing the assertion to be raised.
        //
        // if (! (i >= 0 && i < top))
        // {
        //     ConvertibleArray<T> *p = NULL;
        //     p -> array = 0;
        // }
        assert(!Tuple<T>::OutOfRange(i));

        return (array ? array[i] : Tuple<T>::base[i >> Tuple<T>::log_blksize][i]);
    }

    inline void Resize(const int n = 0) { assert(false); }
    inline void Reset(const int n = 0) { assert(false); }
    inline T& Next()
    {
        assert(!array);

        int i = Tuple<T>::nextIndex();
        return Tuple<T>::base[i >> Tuple<T>::log_blksize][i];
    }
    inline Tuple<T>& operator=(const Tuple<T>& rhs)
    {
        assert(false);
        return *this;
    }

private:

    T* array;
};

template <class T>
class Stack : private Tuple<T>
{
public:
    bool IsEmpty() { return Length() == 0; }

    int Length() { return Tuple<T>::Length(); }

    void Reset(int n = 0) { Tuple<T>::reset(n); }

    void Push(T t)
    {
        Tuple<T>::Next() = t;
    }

    T Pop()
    {
        assert(!IsEmpty());
        int last_index = Length() - 1;
        T t = (*this)[last_index];
        Reset(last_index);

        return t;
    }

    void Pop(T& t)
    {
        assert(!IsEmpty());
        int last_index = Length() - 1;
        t = (*this)[last_index];
        Reset(last_index);

        return;
    }

    T& Top()
    {
        assert(!IsEmpty());
        return (*this)[Length() - 1];
    }
};

template <class T>
class BoundedArray
{
    int lbound,
        ubound;
    T* info;

public:

    BoundedArray() : lbound(0),
        ubound(-1),
        info(NULL)
    {}

    BoundedArray(int lbound_, int ubound_) : lbound(lbound_),
        ubound(ubound_)
    {
        assert(ubound >= lbound);
        info = (new T[Size()]) - lbound;
    }

    BoundedArray(int lbound_, int ubound_, T init_value) : lbound(lbound_),
        ubound(ubound_)
    {
        assert(ubound >= lbound);
        info = (new T[Size()]) - lbound;
        Initialize(init_value);
    }

    ~BoundedArray()
    {
        info += lbound;
        delete[] info;
    }

    void Initialize(T init_value)
    {
        for (int i = lbound; i <= ubound; i++)
            info[i] = init_value;
    }

    void Resize(int new_lbound, int new_ubound)
    {
        if (new_ubound < new_lbound)
        {
            info += lbound;
            delete[] info;

            info = NULL;
            lbound = new_lbound;
            ubound = new_ubound;
        }
        else
        {
            T* old_info = info;
            int new_size = new_ubound - new_lbound + 1;
            info = new T[new_size];
            if (old_info)
            {
                old_info += lbound;
                if (new_lbound == lbound && new_ubound > ubound)
                    memmove(info, old_info, Size() * sizeof(T));
                delete[] old_info;
            }

            info -= new_lbound;
            lbound = new_lbound;
            ubound = new_ubound;
        }

        return;
    }

    void Memset(int val = 0)
    {
        memset(info + lbound, val, Size() * sizeof(T));
    }

    void MemReset()
    {
        memset(info + lbound, 0, Size() * sizeof(T));
    }

    int Lbound() { return lbound; }
    int Ubound() { return ubound; }
    int Size() { return ubound - lbound + 1; }

    //
    // Can the tuple be indexed with i?
    //
    inline bool OutOfRange(const int i) { return (i < lbound || i > ubound); }

    //
    // Return the ith element of the array
    //
    T& operator[](const int i)
    {
        //
        // Use this code when debugging to force a crash instead of
        // allowing the assertion to be raised.
        //
        //if (i < lbound || i > ubound)
        //{
        //    BoundedArray<T> *a = NULL;
        //    a -> lbound = 0;
        //}
        assert(!OutOfRange(i));

        return info[i];
    }
};




template <class T>
class shared_ptr_array
{
    std::shared_ptr< std::vector<T> >  _data;

public:
    shared_ptr_array() : _data(new std::vector<T>())
    {

    }
    shared_ptr_array(T* start, int length) :_data(new std::vector<T>(start, start + length))
    {

    }
    shared_ptr_array(T* start, T* end) :_data(new std::vector<T>(start, end))
    {

    }
    shared_ptr_array(typename std::vector<T>::const_iterator start,
        typename std::vector<T>::const_iterator end) :_data(new std::vector<T>(start, end))
    {

    }

    shared_ptr_array(std::vector<T>&& buf) :_data(new std::vector<T>(std::move(buf)))
    {

    }
    shared_ptr_array(const std::vector<T>& buf) :_data(new std::vector<T>(buf))
    {

    }

    shared_ptr_array(int size_) : _data(new std::vector<T>(size_, {}))
    {

    }

    shared_ptr_array(int size_, T value) : _data(new std::vector<T>(size_, value))
    {

    }
    shared_ptr_array(const shared_ptr_array& rhs) :_data(rhs._data)
    {
    }

    shared_ptr_array(shared_ptr_array&& rhs) noexcept :_data(rhs._data)
    {
    }

    ~shared_ptr_array()
    {

    }
    void swap(shared_ptr_array& other) noexcept {
        _data.swap(other);
    }
    shared_ptr_array& operator=(const shared_ptr_array& rhs)
    {
        _data = rhs._data;
        return  *this;
    }
    shared_ptr_array& operator=(shared_ptr_array&& right) noexcept { // take resource from _Right
        _data.swap(right._data);
        return *this;
    }

    shared_ptr_array& operator=(std::vector<T>&& buf)
    {
        _data->swap(buf);
        return  *this;
    }

    shared_ptr_array& operator=(const std::vector<T>& buf)
    {
        (*_data) = buf;
        return  *this;
    }

    int size()const
    {
        return _data->size();
    }
    T* data()const
    {
        return &_data->operator[](0);
    }
    //
    // Return the ith element of the array
    //
    T& operator[](const int i)const
    {
        return   _data->operator[](i);
    }
    bool operator!() const
    {
        return  !operator()();
    }
    bool operator()() const
    {
        if (!_data) return false;
        return (!_data->empty());
    }
};

template <class T>
class shared_ptr_basic_string
{
    using  string_type = std::basic_string<T>;



public:
    std::shared_ptr < string_type > _data;
    bool initilize = false;
    string_type& get_string_type() const {
        return *_data.get();
    }
    shared_ptr_basic_string() : _data(new string_type())
    {

    }
    shared_ptr_basic_string(T* start, int length) :_data(new string_type(start, start + length)), initilize(true)
    {

    }
    shared_ptr_basic_string(T* start, T* end) :_data(new std::vector<T>(start, end)), initilize(true)
    {

    }
    shared_ptr_basic_string(typename string_type::const_iterator start,
        typename string_type::const_iterator end) :_data(new string_type(start, end)), initilize(true)
    {

    }

    shared_ptr_basic_string(string_type&& buf) :_data(new string_type(std::move(buf))), initilize(true)
    {

    }
    shared_ptr_basic_string(const string_type& buf) :_data(new string_type(buf)), initilize(true)
    {

    }

    shared_ptr_basic_string(int size_) : _data(new string_type(size_, {})), initilize(true)
    {

    }

    shared_ptr_basic_string(int size_, T value) : _data(new string_type(size_, value)), initilize(true)
    {

    }
    shared_ptr_basic_string(const shared_ptr_basic_string& rhs) :_data(rhs._data), initilize(true)
    {
    }

    shared_ptr_basic_string(shared_ptr_basic_string&& rhs) noexcept :_data(rhs._data), initilize(true)
    {
    }

    ~shared_ptr_basic_string()
    {

    }
    void swap(shared_ptr_basic_string& other) noexcept {
        _data.swap(other);
        std::swap(initilize, other.initilize);
    }
    shared_ptr_basic_string& operator=(const shared_ptr_basic_string& rhs)
    {
        _data = rhs._data;
        initilize = rhs.initilize;
        return  *this;
    }
    shared_ptr_basic_string& operator=(shared_ptr_basic_string&& right) noexcept { // take resource from _Right
        _data.swap(right._data);
        std::swap(initilize, right.initilize);
        return *this;
    }

    shared_ptr_basic_string& operator=(string_type&& buf)
    {
        _data->swap(buf);
        initilize = true;
        return  *this;
    }

    shared_ptr_basic_string& operator=(const string_type& buf)
    {
        (*_data) = buf;
        initilize = true;
        return  *this;
    }

    int size()const
    {
        return _data->size();
    }
    int length() const
    {
        return  _data->length();
    }
    T* data() const
    {
        return &_data->operator[](0);
    }
    //
    // Return the ith element of the array
    //
    T& operator[](const int i)const
    {
        return   _data->operator[](i);
    }
    T& at(const int i)const
    {
        return   _data->at(i);
    }
    bool operator!() const
    {
        return  !operator()();
    }
    bool operator()() const
    {
        return    initilize;
    }
    string_type substr(const size_t _Off = 0, const size_t _Count = string_type::npos) const {
        // return [_Off, _Off + _Count) as new string
        return _data->substr(_Off, _Count);
    }

};


using shared_ptr_string = shared_ptr_basic_string<char>;
using shared_ptr_wstring = shared_ptr_basic_string<wchar_t>;

namespace System
{
    template <class T>
    void arraycopy(T& src, int  srcPos,
        T& dest, int destPos,
        int length)
    {
        for (int i = 0; i < length; ++i)
        {
            dest[destPos + i] = src[srcPos + i];
        }
    }
}










typedef  Tuple<int> IntTuple;
#endif /* #ifndef TUPLE_INCLUDED */
