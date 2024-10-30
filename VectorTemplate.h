#pragma once
#include "assert.h"
#include "algorithm"
#include "functional"

using std::function;
using std::swap;
template <typename TElement>
class VectorIterator;

template <typename TElement>
class Vector
{
public:
    /**
     * Constructor
     */
    Vector();
    /**
     * Copy constructor
     * @param other = Vector
     */
    Vector(const Vector& other);
    /**
     * Deconstructor
     */
    ~Vector();
    /**
     * Assignment operator
     * @param other = Vector
     * @return = Vector
     */
    Vector& operator=(const Vector& other);
    /**
     * Move constructor
     * @param other = Vector
     */
    Vector(Vector&& other) noexcept ;
    /**
     * Move assignment
     * @param other = Vector
     * @return = Vector
     */
    Vector& operator=(Vector&& other) noexcept ;

    /**
     * Adds an item to the end of the vector
     * @param el = TElement
     */
    void add(const TElement& el);

    /**
     * Returns the item at the given index
     * @param poz = int
     * @return = TElement
     */
    TElement& get(int poz) const;
    /**
     * Sets the item at index poz to value el
     * @param poz = int
     * @param el = TElement
     */
    void set(int poz,const TElement& el);
    /**
     * Return the size of the vector
     * @return = int
     */
    int size() const noexcept;
    /**
     * Sorts the vector
     */
    void sort(function<bool(const TElement&, const TElement&)>fct);
    /**
     * Deletes the item from the given position
     * @param poz = int
     */
    void del(int poz);
    friend class VectorIterator<TElement>;

    VectorIterator<TElement> begin() const;
    VectorIterator<TElement> end() const;

private:
    int len{0};
    int cap{5};
    TElement* elems;

    /**
     * Checks if the vector needs to be resized, and resizes it if needed
     */
    void checkCapacity();
};

template<typename TElement>
void Vector<TElement>::del(int poz) {
    for(int i = poz; i<len-1;i++)
    {
        elems[i] = elems[i+1];
    }
    len--;
}


template<typename TElement>
Vector<TElement>::Vector(): elems{new TElement[5]}{}

template<typename TElement>
Vector<TElement>::Vector(const Vector<TElement> &other) : elems(new TElement[other.cap]) {
    for(int i = 0;i<other.len;i++)
        elems[i] = other.elems[i];
    len = other.len;
    cap = other.cap;
}

template<typename TElement>
Vector<TElement> &Vector<TElement>::operator=(const Vector<TElement> &other) {
    if(this == &other) return *this;
    delete[] elems;
    elems = new TElement[other.cap];
    for(int i = 0;i<other.len;i++)
        elems[i] = other.elems[i];
    len = other.len;
    cap = other.cap;
    return *this;
}

template<typename TElement>
Vector<TElement>::~Vector(){
    delete[] elems;
}

template<typename TElement>
Vector<TElement>::Vector(Vector<TElement> &&other)  noexcept : len(other.len), cap(other.cap), elems(other.elems) {
    other.elems = nullptr;
    other.len = 0;
    other.cap = 0;
}

template<typename TElement>
Vector<TElement> &Vector<TElement>::operator=(Vector<TElement> &&other)  noexcept {
    if(this == other) return *this;
    delete[] elems;
    elems = other.elems;
    len = other.elems;
    cap = other.cap;
    other.elems = nullptr;
    other.len = 0;
    other.cap = 0;
    return *this;
}

template<typename TElement>
void Vector<TElement>::add(const TElement &el) {
    checkCapacity();
    elems[len++] = el;
}
template<typename TElement>
TElement& Vector<TElement>::get(int poz) const {
    return elems[poz];
}
template<typename TElement>
void Vector<TElement>::set(int poz, const TElement &el) {
    elems[poz] = el;
}

template<typename TElement>
int Vector<TElement>::size() const noexcept {
    return len;
}

template<typename TElement>
void Vector<TElement>::checkCapacity() {
    if(len < cap) return;
    cap *= 2;
    TElement* aux = new TElement[cap];
    for(int i = 0;i<len;i++) aux[i] = elems[i];
    delete[] elems;
    elems = aux;
}

template<typename TElement>
void Vector<TElement>::sort(function<bool(const TElement&, const TElement&)>fct) {
    for(int i = 0;i<len-1;i++)
        for(int j = i + 1;j<len;j++)
            if(!fct(elems[i], elems[j])) swap(elems[i], elems[j]);
}

template <typename TElement>
VectorIterator<TElement> Vector<TElement>::begin() const {
    return VectorIterator<TElement>(*this);
}

template <typename TElement>
VectorIterator<TElement> Vector<TElement>::end() const {
    return VectorIterator<TElement>(*this, len);
}

template<typename TElement>
class VectorIterator {
    private:
        const Vector<TElement>& vect;
        int poz = 0;
    public:
        explicit VectorIterator(const Vector<TElement>& vect) noexcept;
        VectorIterator(const Vector<TElement>& vect, int poz) noexcept;
        [[nodiscard]] bool valid() const;
        TElement& element() const;
        void next();
        TElement& operator*();
        VectorIterator& operator++();
        bool operator==(const VectorIterator& other) noexcept;
        bool operator!=(const VectorIterator& other) noexcept;
    };

template<typename TElement>
VectorIterator<TElement>::VectorIterator(const Vector<TElement>& vect) noexcept:vect{ vect} {}

template<typename TElement>
VectorIterator<TElement>::VectorIterator(const Vector<TElement>& vect, int poz) noexcept: vect{vect},poz{poz} {}

template<typename TElement>
bool VectorIterator<TElement>::valid() const {
    return poz < vect.len;
}

template<typename TElement>
TElement& VectorIterator<TElement>::element() const {
    return vect.elems[poz];
}

template<typename TElement>
void VectorIterator<TElement>::next() {
    poz++;
}

template<typename TElement>
TElement& VectorIterator<TElement>::operator*() {
    return element();
}

template<typename TElement>
VectorIterator<TElement>& VectorIterator<TElement>::operator++() {
    next();
    return *this;
}

template<typename TElement>
bool VectorIterator<TElement>::operator==(const VectorIterator<TElement> &other) noexcept {
    return poz == other.poz;
}

template<typename TElement>
bool VectorIterator<TElement>::operator!=(const VectorIterator<TElement> &other) noexcept {
    return !(*this == other);
}

void testVector();