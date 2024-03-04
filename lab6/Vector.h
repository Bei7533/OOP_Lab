#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector {
public:
  Vector();                      // creates an empty vector
  Vector(int size);              // creates a vector for holding 'size' elements
  Vector(const Vector& r);       // the copy ctor
  ~Vector();                     // destructs the vector 
  T& operator[](int index);      // accesses the specified element without bounds checking
  T& at(int index);              // accesses the specified element, throws an exception of
                                 // type 'std::out_of_range' when index <0 or >=m_nSize
  int size() const;              // return the size of the container
  void push_back(const T& x);    // adds an element to the end 
  void clear();                  // clears the contents
  bool empty() const;            // checks whether the container is empty 
  
private:
  void inflate();                // expand the storage of the container to a new capacity,
                                 // e.g. 2*m_nCapacity
  T *m_pElements;                // pointer to the dynamically allocated storage
  int m_nSize;                   // the number of elements in the container
  int m_nCapacity;               // the total number of elements that can be held in the
                                 // allocated storage
};

// Constructor
template <class T>
Vector<T>::Vector(): m_pElements(nullptr), m_nSize(0), m_nCapacity(0){}

// Constructor with size
template <class T>
Vector<T>::Vector(int size): m_pElements(new T[size]), m_nSize(size), m_nCapacity(size){}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector& r):  m_pElements(new T[r.m_nCapacity]), m_nSize(r.m_nSize), m_nCapacity(r.m_nCapacity){
    for(int i=0; i<r.m_nSize; i++) 
        m_pElements[i] = r.m_pElements[i];
}

// Destructor
template <class T>
Vector<T>::~Vector(){
    delete[] m_pElements;
}

// Accesses the element at the specified index in the Vector
template <class T>
T& Vector<T>::operator[](int index){
    return m_pElements[index];
}

// Accesses the element at the specified index in the Vector with bounds checking
template <class T>
T& Vector<T>::at(int index){
    // Throws an exception of type out_of_range if the index is out of range
    if(index<0 || index>=m_nSize)
        throw std::out_of_range("Index out of range!");
    return m_pElements[index];
}

// Returns the number of elements in the Vector
template <class T>
int Vector<T>::size() const{
    return m_nSize;
}

// Adds an element to the end of the Vector.
template <class T>
void Vector<T>::push_back(const T& x){
    // If the Vector is already at its capacity, the Vector's capacity is increased by doubling its current capacity
    if(m_nSize == m_nCapacity) inflate();
    m_pElements[m_nSize++] = x;
}

// Removes all elements from the Vector and frees the dynamically allocated memory
template <class T>
void Vector<T>::clear(){
    m_nSize = 0;
    m_nCapacity = 0;
    delete[] m_pElements;
}

// Checks if the Vector is empty
template <class T>
bool Vector<T>::empty() const{
    if(!m_nSize) return true;
    else return false;
}

// Double the capacity of the Vector 
template <class T>
void Vector<T>::inflate(){
    int new_cap = (m_nCapacity==0) ? 1 : 2*m_nCapacity;
    T* new_ele = new T[new_cap];
    for(int i=0; i<m_nCapacity; i++)
        new_ele[i] = m_pElements[i];
    delete[] m_pElements;
    m_pElements = new_ele;
    m_nCapacity = new_cap;
}

#endif