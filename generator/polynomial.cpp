//
// Created by Amida on 2021/06/06.
//

#include <iostream>
#include "polynomial.h"

void Polynomial::add(Polynomial::Monomial m) {
    this->polynomial.push_back(m);
}

Fraction Polynomial::substitute(int x) {
    Fraction result = Fraction(0);
    for(int i = 0; i < (int)this->polynomial.size(); i++) {
        auto tmp = this->polynomial[i].substitute(3);
        result = result + tmp;
    }
    return result;
}

Polynomial* Polynomial::indefiniteIntegral() {
    Polynomial* result = new Polynomial();
    for(int i = 0; i < (int)this->polynomial.size(); i++) {
        result->polynomial.push_back(this->polynomial[i].indefiniteIntegral());
    }
    return result;
};

Fraction Polynomial::definiteIntegral(int from, int to) {
    Fraction result = Fraction(0);
    for(int i = 0; i < (int)this->polynomial.size(); i++) {
        result = result + this->polynomial[i].definiteIntegral(from, to);
    }
    return result;
}

std::string Polynomial::show() {
    std::string result;
    if ((int)this->polynomial.size() > 1) {
        result += "\\left(";
    }
    for(int i = 0; i < (int)this->polynomial.size(); i++) {
        Monomial m = this->polynomial[i];
        if(m.coefficient.numerator == 0) {continue;}
        if(m.index == 1) {
            result += m.coefficient.show() + " x";
        } else if(m.index == 0){
            result += m.coefficient.show();
        } else {
            result += m.coefficient.show() + " x^{" + std::to_string(m.index) + "}";
        }
        if(i != (int)this->polynomial.size() - 1) {
            result += " + ";
        }
    }
    if ((int)this->polynomial.size() > 1) {
        result += "\\right)";
    }
    return result;
}


Fraction Polynomial::Monomial::substitute(int x) {
    return this->coefficient * (Fraction(x).pow(this->index));
}

Polynomial::Monomial Polynomial::Monomial::indefiniteIntegral() {
    Polynomial::Monomial integral = Polynomial::Monomial(this->coefficient, this->index);
    integral.index += 1;
    integral.coefficient = integral.coefficient / Fraction(integral.index);
    return integral;
}

Fraction Polynomial::Monomial::definiteIntegral(int from, int to) {
    Polynomial::Monomial ind = this->indefiniteIntegral();
    return ind.substitute(to) - ind.substitute(from);
}