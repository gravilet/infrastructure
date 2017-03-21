#ifndef INCLUDE_INTEGER_H_
#define INCLUDE_INTEGER_H_


#include <iostream>

namespace gravilet {

    /**
     * Задание - создать свой класс, который бы реализовывал основной функционал
     * встроенного типа 'int' :
     * a+b               integer& operator+=(const integer& a);
     * a-b               ??? хватит ли operator+ ??? НЕТ
     * a+1
     * a+2.0
     * a*b
     * a/b
     * a = arr[i]
     * a == b           +
     * a != b           +
     * cin >> a         +
     * cout << b        +
     * 1+a
     * a=b              +
     */
class integer {
 private:
    int value;

 public:
    // constructors
    explicit integer(int a = 0) : value(a) {}
    explicit integer(double a) : value(static_cast<int>(a)) {}
    // operator== / operator!=
    friend bool operator==(const integer& a, const integer& b);
    friend bool operator!=(const integer& a, const integer& b);
    friend bool operator==(int a, const integer& b);
    friend bool operator!=(int a, const integer& b);
    friend bool operator==(double a, const integer& b);
    friend bool operator!=(double a, const integer& b);
    bool operator==(int a);
    bool operator!=(int a);
    bool operator==(double a);
    bool operator!=(double a);
    // for cout/cin
    friend std::ostream& operator<<(std::ostream& s, const integer& v);
    friend std::istream& operator>>(std::istream& s, integer& v);
    // operator+ / operator+=
    friend integer operator+(integer a, const integer& b);
    integer& operator+=(const integer& a);
    // operator=
    integer& operator=(const integer& a);
//        integer& operator=(int a);
//        integer& operator=(double a);
};

}  // namespace gravilet

#endif  // INCLUDE_INTEGER_H_
