//
// Created by Amida on 2021/06/06.
//

#include "fraction.h"

#include <cstdlib>
#include <iostream>

Fraction Fraction::operator+(const Fraction& f) {
    auto s = new Fraction(this->numerator * f.denominator + this->denominator * f.numerator,
                          this->denominator * f.denominator);
    s->reduction();
    return *s;
}

Fraction Fraction::operator-(const Fraction& f) {
    auto d = new Fraction(this->numerator * f.denominator - this->denominator * f.numerator,
                          this->denominator * f.denominator);
    d->reduction();
    return *d;
}

Fraction Fraction::operator*(const Fraction& f) {
    auto p = new Fraction(this->numerator * f.numerator,
                          this->denominator * f.denominator);
    p->reduction();
    return *p;
}

Fraction Fraction::operator/(const Fraction& f) {
    auto q = new Fraction(this->numerator * f.denominator,
                          this->denominator * f.numerator);
    q->reduction();
    return *q;
}

Fraction Fraction::pow(const int& p) {
    auto x = new Fraction(1);
    for(int i =0; i < p; i++) {
        x->denominator *= this->denominator;
        x->numerator *= this->numerator;
    }
    x->reduction();
    return *x;
}

std::string Fraction::show() {
    if (this->denominator == 1) {return std::to_string(this->numerator);}
    if (this->denominator == -1) {return std::to_string(-this->numerator);}
    if (this->numerator < 0) {
        return "-\\frac{" + std::to_string(-this->numerator) + "}{" + std::to_string(this->denominator) + "}";
    } else {
        return "\\frac{" + std::to_string(this->numerator) + "}{" + std::to_string(this->denominator) + "}";
    }
}

int Fraction::gcd(int a, int b) {
    // Fraction特有処理
    if (a==0) {return b;}
    if(a < b) {return gcd(b, a);}
    a %= b;
    if(a == 0) {return b;}
    return gcd(b, a);
}

void Fraction::reduction() {
    int t = gcd(std::abs(this->numerator), std::abs(this->denominator));
    this->numerator /= t;
    this->denominator /= t;
    if(this->numerator < 0 && this->denominator < 0) {
        this->numerator *= -1;
        this->denominator *= -1;
    }
}