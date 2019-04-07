//
// Created by Dvir on 03/04/2019.
//

#include "PhysicalNumber.h"
#include "stdlib.h"
#include "string"

using namespace ariel;
using namespace std;




ostream& ariel:: operator<<(ostream &os, const ariel::PhysicalNumber& F) {

    switch (F.unit) {

        case Unit ::KM : cout<< F.value<< "[KM]"<<endl; break;

        case Unit ::M : cout<< F.value<< "[M]"<<endl; break;

        case Unit ::CM : cout<< F.value<< "[CM]"<<endl; break;

        case Unit ::TON : cout<< F.value<< "[TON]"<<endl; break;

        case Unit ::KG : cout<< F.value<< "[KG]"<<endl; break;

        case Unit ::G: cout<< F.value<< "[G]"<<endl; break;

        case Unit ::HOUR : cout<< F.value<< "[HOUR]"<<endl; break;

        case Unit ::MIN : cout<< F.value<< "[MIN]"<<endl; break;

        case Unit ::SEC : cout<< F.value<< "[SEC]"<<endl; break;

    }


}


PhysicalNumber ariel:: PhysicalNumber:: operator+ (const PhysicalNumber& f)  {

    PhysicalNumber F1 (convert(*this));
    PhysicalNumber F2 (convert(f));

    Unit f1U = this->unit;
    Unit f2U = f.unit;


    cout<<"the res is " <<  F1.value+F2.value<<endl;
    if (F1.type == F2.type){
        double  result = F1.value + F2.value;

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //----------------------MASS----------------------
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        if ( F1.type % 3 == 0 ){
            switch (f1U){
                case Unit :: TON:
                    return PhysicalNumber(result/1000000 , Unit::TON);
                case Unit :: KG:
                    return PhysicalNumber(result/1000 , Unit::KG);
                case Unit :: G:
                    return PhysicalNumber(result , Unit::G);

            }

        }

            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //----------------------TIME----------------------
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        else if (F1.type % 3 == 1 ){
            switch (f1U) {
                case Unit::HOUR:
                    return PhysicalNumber(result / 3600 , Unit::HOUR);
                case Unit::MIN:
                    return PhysicalNumber(result / 60, Unit::MIN);
                case Unit::G:
                    return PhysicalNumber(result, Unit::SEC);
            }
        }

            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //---------------------LENGTH---------------------
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        else {

            switch (f1U) {
                case Unit::KM:
                    return PhysicalNumber(result / 100000 , Unit::KM);
                case Unit::M:
                    return PhysicalNumber(result / 100, Unit::M);
                case Unit::G:
                    return PhysicalNumber(result, Unit::CM);
            }

        }

    }


    else throw "CANOT OPARATE";

}

PhysicalNumber ariel::PhysicalNumber:: operator- ( PhysicalNumber F2){
    PhysicalNumber newF2(-(F2.value),F2.unit);
    return (*this + newF2);
}


PhysicalNumber  ariel::PhysicalNumber::operator-() {
    return PhysicalNumber(-(this->value),this->unit);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//----------------COMPArE OPERATORS---------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


bool ariel::PhysicalNumber:: operator > (const PhysicalNumber& F){
    cout<<boolalpha;
    if (this->type == F.type)
    {
        PhysicalNumber compare(convert(*this));
        PhysicalNumber compare2(convert(F));
        bool check = (compare.value > compare2.value);
        return check;
    }

    else throw"CANNOT COMPARE";
}

bool ariel::PhysicalNumber:: operator <= (const PhysicalNumber& F){
    cout<<boolalpha;
    if (this->type == F.type)
    {
        PhysicalNumber compare(convert(*this));
        PhysicalNumber compare2(convert(F));

        bool check = (compare.value == compare2.value|| compare.value < compare2.value);
        return check;
    }

    else throw"CANNOT COMPARE";
}

bool ariel :: PhysicalNumber:: operator >= (const PhysicalNumber& F){
    cout<<boolalpha;
    if (this->type == F.type)
    {
        PhysicalNumber compare(convert(*this));
        PhysicalNumber compare2(convert(F));

        bool check = (compare.value >= compare2.value);
        return check;
    }

    else throw"CANNOT COMPARE";
}

bool ariel :: PhysicalNumber:: operator < (const PhysicalNumber& F){
    cout<<boolalpha;
    if (this->type == F.type)
    {
        PhysicalNumber compare(convert(*this));
        PhysicalNumber compare2(convert(F));

        bool check = (compare.value < compare2.value);
        return check;
    }

    else throw"CANNOT COMPARE";
}

bool ariel :: PhysicalNumber:: operator == (const PhysicalNumber& F){
    cout<<boolalpha;
    if (this->type == F.type)
    {
        PhysicalNumber compare(convert(*this));
        PhysicalNumber compare2(convert(F));

        bool check = (compare.value == compare2.value);
        return check;
    }

    else throw"CANNOT COMPARE";
}

bool ariel :: PhysicalNumber:: operator != (const PhysicalNumber& F){
    cout<<boolalpha;
    if (this->type == F.type)
    {
        PhysicalNumber compare(convert(*this));
        PhysicalNumber compare2(convert(F));

        bool check = (compare.value != compare2.value);
        return check;
    }

    else throw"CANNOT COMPARE";
}












PhysicalNumber ariel::PhysicalNumber:: convert(const PhysicalNumber& F) {

    PhysicalNumber f(0,F.unit);
    f.type = F.type;

    switch(F.unit){

        case Unit ::TON :f.value = F.value * 1000000; break;
        case Unit ::KG :  f.value = F.value * 1000; break;
        case Unit ::HOUR :  f.value = F.value * 3600; break;
        case Unit ::MIN :  f.value = F.value * 60; break;
        case Unit ::KM :  f.value = F.value * 100000; break;
        case Unit ::M :  f.value = F.value * 100; break;
    }

    return f;

}




