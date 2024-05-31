#ifndef HELLO_H_
#define HELLO_H_

#include <iostream>

class Hello {
private:
    int m_value;
public: 
    Hello() : m_value(0) {}
    virtual ~Hello() {}
    void addOne() {m_value++;};
    int getValue() {return m_value;};
    void setValue(int i) {m_value = i;};
};

#endif