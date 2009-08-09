#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <class T>
class Singleton{
public:
    static T* Instance()
    {
        static T myTemplate;
        return &myTemplate;
    }
};

#endif
