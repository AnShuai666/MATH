/*
 * 日期:	2019-04-24
 * 时间:	18:43
 * 姓名:	安帅
 * @func    常用内存对齐
*/

#ifndef MATH_ALIGNED_ALLOCATOR_HPP
#define MATH_ALIGNED_ALLOCATOR_HPP

#include <memory>
#include <vector>
#include <cstddef>
#include "util/define.h"
#if defined(_WIN32)
    #include <malloc.h>
#endif
UTIL_NAMESPACE_BEGIN

template <typename T,size_t alignment>
struct AlignedAllocator
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T const* const_pointer;
    typedef T& reference;
    typedef T const& const_reference;
    typedef std::size_t  size_type;
    typedef ptrdiff_t difference_type;//ptrdiff_t类型变量通常用来保存两个指针减法操作的结果。long int

    template <class U>
    struct rebind
    {
        typedef AlignedAllocator<U,alignment> other;
    };

public:
    AlignedAllocator(void);

    template <class T_other,size_t alignment_other>
    AlignedAllocator(AlignedAllocator<T_other,alignment_other> const&);

    pointer allocate(size_type n);
    void deallocate(pointer p, size_type n);
    size_type max_size(void) const;
    void construct(pointer p,const_reference other);
    void destroy(pointer p);

    template <typename T_other,size_t alignment_other>
    bool operator==(AlignedAllocator<T_other,alignment_other> const&);

    template <typename T_other,size_t alignment_other>
    bool operator!=(AlignedAllocator<T_other,alignment_other> const&);
};



UTIL_NAMESPACE_END
#endif //MATH_ALIGNED_ALLOCATOR_HPP
