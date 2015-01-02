/* 
 * File:   memcontainer.h
 * Author: yvan
 *
 * Created on January 2, 2015, 6:32 PM
 */

#ifndef MEMCONTAINER_H
#define	MEMCONTAINER_H

template <class T>
class Memc {
public:
  Memc & clear();
  Memc & del  ();
  
  int elms() const;
  
  T & operator[](int i);
  const T & operator[](int i) const;
  
  T & first();
  const T & first() const;
  
  T & last();
  const T & last() const;
  
  T & New();
  T & NewAt(int i);
  
  bool contains(const T * elm) const;
  
  Memc & remove(int i, bool keep_order = false);
  Memc & removeLast();
  
  Memc & operator=(const Memc<T> &src);
  
  explicit Memc(int elms=32);
  Memc(const Memc & src);
  
};

#include "memcontainer.cpp"

#endif	/* MEMCONTAINER_H */

