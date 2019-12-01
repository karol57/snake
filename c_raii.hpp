#pragma once
#include <utility>

template<typename T>
struct CallOnDestruct
{
    template<typename T2>
    CallOnDestruct(T2&& p_func) : m_func(std::forward<decltype(p_func)>(p_func)) {}
    ~CallOnDestruct() { (void)m_func(); }
private:
    T m_func;
};
template<typename T> CallOnDestruct<T> MakeCallOnDestruct(T&& p_func) { return { std::forward<T>(p_func) }; }

#define CONCAT_(x,y) x##y
#define CONCAT(x,y) CONCAT_(x,y)
#define C_RAII(on_leave_lambda) auto CONCAT(_c_raii_, __COUNTER__) = MakeCallOnDestruct(on_leave_lambda)