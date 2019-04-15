//
// Created by Dvir on 03/04/2019.
//

#ifndef PHYSICALNUMBER_PHYSICALNUMBER_HPP
#define PHYSICALNUMBER_PHYSICALNUMBER_HPP

#include <iostream>
#include "Unit.h"
#include <exception>


namespace ariel{
    using namespace std;
    static const char* units[] = {"ton","hour","km","kg","min","m","g","sec","cm"};

    class PhysicalNumber{

    private:

        Unit unit;
        double value;
        int type;

    public:
        //constructors
        PhysicalNumber(double value, Unit unit){
            this->unit = unit;
            this->value = value;
            type = (int)unit % 3;
        }


        //copy constructor

        PhysicalNumber(PhysicalNumber &physicalNumber){
            this->value = physicalNumber.value;
            this->unit = physicalNumber.unit;
            this->type = physicalNumber.type;
        }

        PhysicalNumber();

        //friends
        friend ostream& operator<< (ostream& os, const PhysicalNumber& F);
        friend istream& operator>> (istream& is, PhysicalNumber& F);

        //operators
        PhysicalNumber operator+ (const PhysicalNumber& f);
        PhysicalNumber operator- (const PhysicalNumber& F2);
        PhysicalNumber operator- ();
        PhysicalNumber operator+ ();
        PhysicalNumber& operator+=(const PhysicalNumber& F);
        PhysicalNumber& operator-=(const PhysicalNumber& F);
         PhysicalNumber operator++ (int);
        PhysicalNumber operator++ ();
         PhysicalNumber operator-- (int);
        PhysicalNumber operator-- ();









        //compare operators
        bool operator > (const PhysicalNumber& F);
        bool operator <= (const PhysicalNumber& F);
        bool operator >= (const PhysicalNumber& F);
        bool operator < (const PhysicalNumber& F);
        bool operator == (const PhysicalNumber& F);
        bool operator != (const PhysicalNumber& F);


    private:
        PhysicalNumber convert (const PhysicalNumber& F);

    };

};
#endif //PHYSICALNUMBER_PHYSICALNUMBER_HPP
