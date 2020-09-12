#ifndef OAK_MEMORY_HPP
#define OAK_MEMORY_HPP

#include <stdio.h>

namespace oak
{
#if 0
template<typename _Tp, bool = __is_referenceable<_Tp>::value>
struct __add_lvalue_reference_helper {
    typedef _Tp type;
};

template<typename _Tp>
struct __add_lvalue_reference_helper<_Tp, true> {
    typedef _Tp& type;
};

/// add_lvalue_reference
template<typename _Tp>
struct add_lvalue_reference : public __add_lvalue_reference_helper<_Tp> {
};
#endif // if 0

//
// default_delete
//
template<class T>
class default_delete
{
public:
    default_delete() = default;
    void operator()(T* p) const
    {
        printf("delete, p = 0x%p\n", p);
        delete p;
    }
};

template<class T>
class default_delete<T[]>
{
public:
    void operator()(T* p) const
    {
        printf("delete[], p = 0x%p\n", p);
        delete[] p;
    }
};

//
// unique_ptr
//
// TODO: remove_reference for Del::pointer type
// NOTE:
// 1) std::is_integral: check if is char/int/etc.
// universal collapse: && &-> &, && && -> &&. If one of the reference is &, T is
// reduced to &, else &&.
// TODO: search SFINAE: "Substitution Failure Is Not An Error"
template<class T, class D = default_delete<T>>
class unique_ptr
{
public:
    unique_ptr() : m_p(nullptr) {}
    explicit unique_ptr(T* p) : m_p(p) {}
    unique_ptr(unique_ptr&& rhs)
    {
        m_p = rhs.release();
    }
    unique_ptr(const unique_ptr& rhs) = delete;
    unique_ptr& operator=(const unique_ptr& rhs) = delete;

    ~unique_ptr()
    {
        m_delete(m_p);
        m_p = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& rhs)
    {
        reset(rhs.release());
        m_delete = rhs.get_deleter();
        return *this;
    }

public:
    T* get() const
    {
        return m_p;
    }

    D& get_deleter()
    {
        return m_delete;
    }

    const D& get_deleter() const
    {
        return m_delete;
    }

    T* release()
    {
        T* t = m_p;
        m_p  = nullptr;
        return t;
    }

    void reset(T* p = nullptr)
    {
        m_delete(m_p);
        m_p = p;
    }

    void swap(unique_ptr& rhs)
    {
        T* t    = m_p;
        m_p     = rhs.m_p;
        rhs.m_p = t;

        D td         = m_delete;
        m_delete     = rhs.m_delete;
        rhs.m_delete = td;
    }

    operator bool() const
    {
        return get() != nullptr;
    }

    // TODO: typename add_lvalue_reference<element_type>::type
    T& operator*() const
    {
        return *get();
    }

    T* operator->() const
    {
        return get();
    }

private:
    T* m_p;
    D  m_delete;
};

} // namespace oak

#endif // OAK_MEMORY_HPP
