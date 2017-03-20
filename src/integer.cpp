#include "integer.h"

namespace gravilet {

    bool operator==(const integer& a, const integer& b) {
        return (a.value == b.value);
    }

    bool operator!=(const integer& a, const integer& b) {
        return (a.value != b.value);
    }

    bool operator==(int a, const integer& b) {
        return (a == b.value);
    }

    bool operator!=(int a, const integer& b) {
        return (a != b.value);
    }

    bool operator==(double a, const integer& b) {
        return (a == b.value);
    }

    bool operator!=(double a, const integer& b) {
        return (a != b.value);
    }

    bool integer::operator==(int a) {
        return (this->value == a);
    }

    bool integer::operator!=(int a) {
        return (this->value != a);
    }

    bool integer::operator==(double a) {
        return (this->value == a);
    }

    bool integer::operator!=(double a) {
        return (this->value != a);
    }

    std::ostream& operator<<(std::ostream& s, const integer& v)
    {
        s << v.value;
        return s;
    }
    std::istream& operator>>(std::istream& s, integer& v)
    {
        s >> v.value;
        return s;
    }

    integer& integer::operator+=(const integer& a) {
        this->value += a.value;
        return *this;
    }

    integer operator+(integer a, const integer& b) {
        std::cout << "integer operator+(integer a, const integer& b) : a = " << a << "; b = " << b << "\n";
        a += b;
        return a;
    }

    // operator=
    integer& integer::operator=(const integer& a) {
        this->value = a.value;
        return *this;
    }
//    integer& integer::operator=(int a) {
//        this->value = a;
//        return *this;
//    }
//    integer& integer::operator=(double a) {
//        this->value = int(a);
//        return *this;
//    }


}   // namespace grailet