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

    /*
     *  @property   内存分配并对齐
     *  @func       分配n*sizeof(T)个字节的内存给pointer,
     *              且内存的地址是alignment的倍数
     *              alignment必须是2的幂
     *  @param_in   n           要分配T类型内存单元的大小
     *  @return     pointer     返回分配内存的首地址
    */
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

//
template <typename T, size_t ALIGNMENT = 16>
using AlignedMemory = std::vector<T, AlignedAllocator<T, ALIGNMENT>>;

template <typename T,size_t alignment>
inline
AlignedAllocator<T,alignment>::AlignedAllocator(void)
{
}

template <typename T,size_t alignment>
template <typename T_other,size_t alignment_other>
inline
AlignedAllocator<T,alignment>::AlignedAllocator
    (AlignedAllocator<T_other,alignment_other> const& other)
{}

template <typename T,size_t alignment>
inline typename AlignedAllocator<T,alignment>::pointer
AlignedAllocator<T,alignment>::allocate(unsigned long n)
{
    if (n > this->max_size())
        throw std::bad_alloc();
    size_t size = n * sizeof(T);
    pointer p = nullptr;
#if defined(_WIN32)
    //TODO:WINDOWS
#elif defined(linux)
    //调用posix_memalign( )
    //成功时会返回size字节的动态内存，并且这块内存的地址是alignment的倍数。
    //参数alignment必须是2的幂，还是void指针的大小的倍数。
    // 返回的内存块的地址放在了memptr里面，函数返回值是0.
    //调用失败时，没有内存会被分配，memptr的值没有被定义
    //---------------------
    //作者：unix21
    //来源：CSDN
    //原文：https://blog.csdn.net/unix21/article/details/12893171
    //版权声明：本文为博主原创文章，转载请附上博文链接！
    if (::posix_memalign(&reinterpret_cast<void*&>(p),alignment,size))
        throw std::bad_alloc();
#endif
    return p;
}

template <typename T,size_t alignment>
inline void
AlignedAllocator<T,alignment>::deallocate(util::AlignedAllocator<T, alignment>::pointer p, unsigned long n)
{
#ifdef _WIN32
    //TODO:WINDOWS
#else
    ::free(p);
#endif
}



UTIL_NAMESPACE_END
#endif //MATH_ALIGNED_ALLOCATOR_HPP
