#include "integer.h"

namespace gravilet {

    // operator== / operator!=
    bool operator==(const integer& a, const integer& b) {
        return (a.value == b.value);
    }
    bool operator!=(const integer& a, const integer& b) {
        return (a.value != b.value);
    }
//    bool operator==(int a, const integer& b) {
//        return (a == b.value);
//    }
//    bool operator!=(int a, const integer& b) {
//        return (a != b.value);
//    }
    bool operator==(double a, const integer& b) {
        return (a == b.value);
    }
    bool operator!=(double a, const integer& b) {
        return (a != b.value);
    }
//    bool integer::operator==(int a) {
//        return (this->value == a);
//    }
//    bool integer::operator!=(int a) {
//        return (this->value != a);
//    }
    bool integer::operator==(double a) {
        return (this->value == a);
    }
    bool integer::operator!=(double a) {
        return (this->value != a);
    }

    // for cout/cin
    std::ostream& operator<<(std::ostream& s, const integer& v) {
        s << v.value;
        return s;
    }
    std::istream& operator>>(std::istream& s, integer& v) {
        s >> v.value;
        return s;
    }

    // operator+ / operator+=
    integer operator+(integer a, const integer& b) {
        std::cout << "integer operator+(integer a, const integer& b) : a = "
                  << a << "; b = " << b << "\n";
        a += b;
        return a;
    }
    integer& integer::operator+=(const integer& a) {
        this->value += a.value;
        return *this;
    }
    double integer::operator+(double e) {
        return this->value + e;
    }
    double operator+(double a, const integer& b) {
        return a + b.value;
    }

    // operator- / operator-=
    integer operator-(integer a, const integer& b) {
        std::cout << "integer operator-(integer a, const integer& b) : a = "
                  << a << "; b = " << b << "\n";
        a -= b;
        return a;
    }
    integer& integer::operator-=(const integer& a) {
        this->value -= a.value;
        return *this;
    }
    double integer::operator-(double e) {
        return this->value - e;
    }
    double operator-(double a, const integer& b) {
        return a - b.value;
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
    integer& integer::operator=(double a) {
        this->value = static_cast<int>(a);
        return *this;
    }

    // operator[]
//    integer& operator[](integer* vector, const integer& idx) {
//        return vector[idx.value];
//    }
//    double operator[](integer* vector, const integer& idx) {
//        return vector[idx.value].value;
//    }

    //
//    double& operator=(double a, const integer& b) {
//        a = b.value;
//        return a;
//    }

}   // namespace gravilet
