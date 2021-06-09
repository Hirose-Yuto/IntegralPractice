//
// Created by Amida on 2021/06/06.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include<tuple>
#include "polynomial.h"
#include "fraction.h"
#include<map>

class Generator{
public:
    Generator() {
        calculateSumOf_probability_not_normalized(NumOfItems);
        calculateSumOf_probability_not_normalized(Numerator);
        calculateSumOf_probability_not_normalized(Denominator);
    }
    std::string show();

    std::vector<std::string> Q_and_A();

private:
    /**
     * 多項式、積分範囲、解答を自動生成。
     */
    std::tuple<Polynomial, int, int> randomlyGenerate();

    enum Variables{
        NumOfItems,
        Numerator,
        Denominator
    };

    int get(const Variables v);

    void calculateSumOf_probability_not_normalized(const Variables v);

    double sumOfNumOfItems_probability;
    double numOfItems_probability_not_normalized(int x);
    double sumOfNumeratorOfCoefficient_probability;
    double numeratorOfCoefficient_probability_not_normalized(int x);
    double sumOfDenominatorOfCoefficient_probability;
    double denominatorOfCoefficient_probability_not_normalized(int x);

    std::map<Variables, std::function<double(int)>> probability_not_normalized = {
            {NumOfItems, [this](int x){return numOfItems_probability_not_normalized(x);}},
            {Numerator, [this](int x){return numeratorOfCoefficient_probability_not_normalized(x);}},
            {Denominator, [this](int x){return denominatorOfCoefficient_probability_not_normalized(x);}}
    };

    std::map<Variables, double*> SumOf_probability_not_normalized = {
            {NumOfItems, &this->sumOfNumOfItems_probability},
            {Numerator, &this->sumOfNumeratorOfCoefficient_probability},
            {Denominator, &this->sumOfDenominatorOfCoefficient_probability}
    };

    std::map<Variables, std::tuple<int, int>> rangeOfProbability = {
            {NumOfItems, std::make_tuple(0, 4)},
            {Numerator, std::make_tuple(0, 50)},
            {Denominator, std::make_tuple(1, 50)}
    };

};

#endif //GENERATOR_H
