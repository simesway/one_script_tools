#include <iomanip>
#include <iostream>
#include "complex_number.h"
#include <numeric>
#include <cmath>

complex_number::complex_number(double R) : Re(R){}

complex_number::complex_number(double R, double I) : Re(R), Im(I){}

complex_number convpol(int i, float rad, float phi){
    float r = i*rad, p = i*phi;
    return complex_number(r*cos(p), r*sin(p));
}

double complex_number::rez(){return Re;}

double complex_number::imz(){return Im;}

complex_number& complex_number::operator+=(const complex_number &c){
    Re += c.Re;
    Im += c.Im;
    return *this;
}

complex_number& complex_number::operator-=(const complex_number &c){
    Re -= c.Re;
    Im -= c.Im;
    return *this;
}

complex_number complex_number::operator*=(const complex_number &c){
    return complex_number(this->Re * c.Re - this->Im * c.Im, 
                     this->Re * c.Im + c.Re * this->Im); 
}
complex_number operator+(const complex_number &lhs, const complex_number &rhs){
    return complex_number(lhs.Re + rhs.Re, 
                          lhs.Im + rhs.Im);
}

complex_number operator-(const complex_number &lhs, const complex_number &rhs){
    return complex_number(lhs.Re - rhs.Re, 
                          lhs.Im - rhs.Im);
}

complex_number operator*(const complex_number &lhs, const complex_number &rhs){
    return complex_number(lhs.Re * rhs.Re - lhs.Im * rhs.Im, 
                     lhs.Re * rhs.Im + rhs.Re * lhs.Im); 
}

std::ostream& operator<<(std::ostream &out, const complex_number &z){
    out << std::noshowpos << z.Re << std::showpos << z.Im << "i" << std::noshowpos;
    return out;
}
