//
// Created by Amida on 2021/06/06.
//

#ifndef FRACTION_H
#define FRACTION_H

#include<string>

class Fraction{
public:
    int numerator;
    int denominator;

    Fraction(int n, int d = 1) {
        this->numerator = n;
        this->denominator = d;
        reduction();
    };

    Fraction operator+(const Fraction& f);

    Fraction operator-(const Fraction& f);

    Fraction operator*(const Fraction& f);

    Fraction operator/(const Fraction& f);

    Fraction pow(const int& p);

    std::string show();

private:
    int gcd(int a, int b);

    void reduction();
};

#endif //FRACTION_H
