#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <iostream>
#include <limits>

namespace Alloc {
    template <class T>
    class Allocator {
    public:
       typedef T value_type;
       typedef T* pointer;
       typedef const T* const_pointer;
       typedef T& reference;
       typedef const T& const_reference;
       typedef std::size_t size_type;
       typedef std::ptrdiff_t difference_type;

       template <class U>
       struct rebind {
           typedef Allocator<U> other;
       };

       T* address (T& value) const {
           return &value;
       }
       T* address (const T& value) const {
           return &value;
       }

       Allocator() throw() {
       }
       Allocator(const Allocator&) throw() {
       }
       template <class U>
         Allocator (const Allocator<U>&) throw() {
       }
       ~Allocator() throw() {
       }

       std::size_t max_size () const throw() {
           return std::numeric_limits<std::size_t>::max() / sizeof(T);
       }

       T* allocate (std::size_t num, const void* = 0) {
           T* ret = (T*)(::operator new(num * sizeof(T)));
           return ret;
       }

       void construct (T* p, const T& value) {
           new((void*)p)T(value);
       }

       void destroy (T* p) {
           p->~T();
       }

       void deallocate (T* p, std::size_t num) {
           ::operator delete((void*)p);
       }
    };

   template <class T1, class T2>
   bool operator== (const Allocator<T1>&,
                    const Allocator<T2>&) throw() {
       return true;
   }
   template <class T1, class T2>
   bool operator!= (const Allocator<T1>&,
                    const Allocator<T2>&) throw() {
       return false;
   }
}
#endif // ALLOCATOR_H
