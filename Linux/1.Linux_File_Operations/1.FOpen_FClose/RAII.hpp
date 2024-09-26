#ifndef RAII_HPP
#define RAII_HPP

#define C_FLFE // C风格文件操作

#ifdef C_FLFE
#include <cstdio>
#endif // C_FLFE

// 利用对象的生命周期管理资源的申请与释放
template <class T>
class RAII {
public:
    RAII(T* data) : _data(data) {}

    ~RAII() {
        if (_data) {
            fclose(_data);
        }
    }

    operator bool() {
        return _data;
    }

    T* operator->() {
        return _data;
    }

    T& operator*() {
        return *_data;
    }

    void reset(T* data = nullptr) {
        if (_data) {
            fclose(_data);
        }
        _data = data;
    }

    T* get() const {
        return _data;
    }

private:
    T* _data;
};

#endif // RAII_HPP
