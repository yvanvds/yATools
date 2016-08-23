/* 
 * File:   container.h
 * Author: yvan
 *
 * This container class is made for easy access and flexibility.
 * It is not optimised for speed. Objects need to have a 
 * default constructor and a copy constructor to use this 
 * container.
 * 
 * Created on January 16, 2014, 10:42 AM
 */

#pragma once
#include<map>




template <class T, typename K = void>
class container {
public:
  /*
   ptr can be used if the class needs an argument at the constructor
   */
  container(K * ptr) : _highIndex(-1), ptr(ptr) {
  }
  
  ~container() {
    for(unsigned int i = 0; i < _elements.size(); i++) {
      delete _elements[i];
    }
  }
 
  /**
   * Count the objects in the array. This can be different from the
   * highest index. If you manually assign indexes, and don't want to
   * create new elements, check with valid(index) before retrieving a value.
   * @return nr of elements
   */
  int  elms  () const {
    return _elements.size();
  }
  
  /**
   * Retrieve the highest index + 1 in de container. 
   * When assigning indexes manually (with operator[]) 
   * this can be different from the number of elements.
   * @return 
   */
  int end() {
    return _highIndex + 1;
  }
  
  /**
   * 
   * @return true if the container is empty 
   */
  bool empty () const {
    return _elements.empty();
  }
  
  /**
   * find out if the index exists in the container
   * @param pos : the index to check
   * @return true if valid
   */
  bool valid (int index) {
    return _elements.find(index) != _elements.end();
  }
 
  /**
   * Request a new element at the end of the container
   * @return reference to the new element
   */
  T &  New   (       ) {
    _elements[++_highIndex] = new T(ptr);
    return *_elements[_highIndex];
  }
  
  
  /**
   * Remove the element at this position if it exists
   * @param pos : index to remove
   * @return 
   */
  container & remove(int index) {
    typename std::map<int, T*>::iterator i = _elements.find(index);
    if (i != _elements.end()) {
      delete (*i).second;
      if((*i).first == _highIndex) _highIndex--;
      _elements.erase(i);
    }
    return *this;
  }
  
  /**
   * Clears the whole container and deletes all objects
   */
  void clear (       ) {
    for (typename std::map<int, T*>::iterator i = _elements.begin();
            i != _elements.end(); ++i) {
      delete (*i).second;
    }
    _elements.clear();
    _highIndex = -1;
  }
  
  /**
   * Get a reference to the object at this position
   * and create a new object if the index doesn't exist.
   * @param pos : the position to retrieve
   * @return a reference to the object
   */
  T & operator[](int pos) {
    typename std::map<int, T*>::iterator i = _elements.find(pos);
    if (i != _elements.end()) {
      return (*(*i).second);
    } else {
      _elements[pos] = new T(ptr);
      if(_highIndex <= pos) _highIndex = pos + 1;
      return *_elements[pos];
    }
  }
  
  T & last() {
    return *_elements[_highIndex];
  }
  
private:
  std::map<int, T*> _elements;
  int _highIndex;
  K * ptr;
  
};

template <class T>
class container<T, void> {
public:
  /*
   ptr can be used if the class needs an argument at the constructor
   */
  container() : _highIndex(-1) {
  }
  
  ~container() {
    for(unsigned int i = 0; i < _elements.size(); i++) {
      delete _elements[i];
    }
  }
 
  /**
   * Count the objects in the array. This can be different from the
   * highest index. If you manually assign indexes, and don't want to
   * create new elements, check with valid(index) before retrieving a value.
   * @return nr of elements
   */
  int  elms  () const {
    return _elements.size();
  }
  
  /**
   * Retrieve the highest index + 1 in de container. 
   * When assigning indexes manually (with operator[]) 
   * this can be different from the number of elements.
   * @return 
   */
  int end() {
    return _highIndex + 1;
  }
  
  /**
   * 
   * @return true if the container is empty 
   */
  bool empty () const {
    return _elements.empty();
  }
  
  /**
   * find out if the index exists in the container
   * @param pos : the index to check
   * @return true if valid
   */
  bool valid (int index) {
    return _elements.find(index) != _elements.end();
  }
 
  /**
   * Request a new element at the end of the container
   * @return reference to the new element
   */
  T &  New   (       ) {
    _elements[++_highIndex] = new T;
    return *_elements[_highIndex];
  }
  
  
  /**
   * Remove the element at this position if it exists
   * @param pos : index to remove
   * @return 
   */
  container & remove(int index) {
    typename std::map<int, T*>::iterator i = _elements.find(index);
    if (i != _elements.end()) {
      delete (*i).second;
      if((*i).first == _highIndex) _highIndex--;
      _elements.erase(i);
    }
    return *this;
  }
  
  /**
   * Clears the whole container and deletes all objects
   */
  void clear (       ) {
    for (typename std::map<int, T*>::iterator i = _elements.begin();
            i != _elements.end(); ++i) {
      delete (*i).second;
    }
    _elements.clear();
    _highIndex = -1;
  }
  
  /**
   * Get a reference to the object at this position
   * and create a new object if the index doesn't exist.
   * @param pos : the position to retrieve
   * @return a reference to the object
   */
  T & operator[](int pos) {
    typename std::map<int, T*>::iterator i = _elements.find(pos);
    if (i != _elements.end()) {
      return (*(*i).second);
    } else {
      _elements[pos] = new T;
      if(_highIndex <= pos) _highIndex = pos + 1;
      return *_elements[pos];
    }
  }
  
  T & last() {
    return *_elements[_highIndex];
  }
  
private:
  std::map<int, T*> _elements;
  int _highIndex;
};