//
// Created by Dvir on 03/04/2019.
//

#ifndef PHYSICALNUMBER_PHYSICALNUMBER_HPP
#define PHYSICALNUMBER_PHYSICALNUMBER_HPP

#include <iostream>
#include "Unit.hpp"
namespace ariel{
    using namespace std;
    class PhysicalNumber{

    public:

        Unit unit;
        double value;
        int type;
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

        //operators
        friend ostream& operator<< (ostream& os, const PhysicalNumber& F);

        PhysicalNumber operator+ (const PhysicalNumber& f);
        PhysicalNumber operator- ( PhysicalNumber F2);
        PhysicalNumber operator- ();

        //compare operatorss
        bool operator > (const PhysicalNumber& F);
        bool operator <= (const PhysicalNumber& F);
        bool operator >= (const PhysicalNumber& F);
        bool operator < (const PhysicalNumber& F);
        bool operator == (const PhysicalNumber& F);
        bool operator != (const PhysicalNumber& F);


        //functions
        PhysicalNumber convert (const PhysicalNumber& F);

    };

};
#endif //PHYSICALNUMBER_PHYSICALNUMBER_HPP
