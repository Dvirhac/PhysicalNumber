//
// Created by Dvir on 03/04/2019.
//

#include <sstream>
#include <algorithm>
#include "PhysicalNumber.h"
#include "stdlib.h"
#include "string"
using namespace ariel;
using namespace std;



static string units[] = {"ton","hour","km","kg","min","m","g","sec","cm"};



ostream& ariel:: operator<<(ostream &os, const ariel::PhysicalNumber& F) {

    switch (F.unit) {

        case Unit ::km : cout<< F.value<< "[km]"<<endl; break;

        case Unit ::m : cout<< F.value<< "[m]"<<endl; break;

        case Unit ::cm : cout<< F.value<< "[cm]"<<endl; break;

        case Unit ::ton : cout<< F.value<< "[ton]"<<endl; break;

        case Unit ::kg : cout<< F.value<< "[kg]"<<endl; break;

        case Unit ::g: cout<< F.value<< "[g]"<<endl; break;

        case Unit ::hour : cout<< F.value<< "[hour]"<<endl; break;

        case Unit ::min : cout<< F.value<< "[min]"<<endl; break;

        case Unit ::sec : cout<< F.value<< "[sec]"<<endl; break;

    }

}

istream &ariel::operator>>(istream &is, PhysicalNumber &F) {
    string input;
    is >> input;

    size_t index = input.find_first_of('[');
    size_t lastIndex = input.find_first_of(']');
    string value = input.substr(0,index);
    string unit = input.substr(index+1,lastIndex-index-1);

    F.value = stod(value);
    transform(unit.begin(), unit.end(), unit.begin(), ::tolower);


    switch (unit[0]){
        case 'k':{
            if (unit[1] == 'g') F.unit = Unit :: kg;
                else F.unit = Unit:: km;
                break;
        }
        case 'm':{
            if (unit[1] == 'i') F.unit = Unit :: min;
            else F.unit = Unit:: m;
            break;
        }
        case 'h': F.unit = Unit:: hour; break;
        case  't': F.unit = Unit:: ton; break;
        case 's': F.unit = Unit:: sec; break;
        case 'g': F.unit = Unit:: g; break;
        case 'c': F.unit = Unit:: cm; break;

    }
    F.type = (int)F.unit % 3;

}




PhysicalNumber ariel:: PhysicalNumber:: operator+ (const PhysicalNumber& f)  {

    PhysicalNumber F1 (convert(*this));
    PhysicalNumber F2 (convert(f));

    Unit f1U = this->unit;
    Unit f2U = f.unit;


    if (F1.type == F2.type){
        double  result = F1.value + F2.value;

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //----------------------MASS----------------------
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        if ( F1.type % 3 == 0 ){
            switch (f1U){
                case Unit :: ton:
                    return PhysicalNumber(result/1000000 , Unit::ton);
                case Unit :: kg:
                    return PhysicalNumber(result/1000 , Unit::kg);
                case Unit :: g:
                    return PhysicalNumber(result , Unit::g);

            }

        }

            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //----------------------TIME----------------------
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        else if (F1.type % 3 == 1 ){
            switch (f1U) {
                case Unit::hour:
                    return PhysicalNumber(result / 3600 , Unit::hour);
                case Unit::min:
                    return PhysicalNumber(result / 60, Unit::min);
                case Unit::g:
                    return PhysicalNumber(result, Unit::sec);
            }
        }

            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //---------------------LENGTH---------------------
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        else {

            switch (f1U) {
                case Unit::km:
                    return PhysicalNumber(result / 100000 , Unit::km);
                case Unit::m:
                    return PhysicalNumber(result / 100, Unit::m);
                case Unit::g:
                    return PhysicalNumber(result, Unit::cm);
            }

        }


    } else{
        string num1 = units[(int)this->unit];
        string num2 = units[(int)f.unit];
        string s1 = "Units do not match - [";
        string s2 = "] cannot be converted to [";
        string s3 = "]";
        throw std:: invalid_argument(s1 + num1 +s2 +num2 + s3 );
    }

}

PhysicalNumber ariel::PhysicalNumber:: operator- (const PhysicalNumber& F2){
    PhysicalNumber newF2(-(F2.value),F2.unit);
    return (*this + newF2);
}


PhysicalNumber  ariel::PhysicalNumber:: operator-() {
    return PhysicalNumber(-(this->value),this->unit);
}

PhysicalNumber PhysicalNumber::operator+() {

    return *this;
}


PhysicalNumber& ariel:: PhysicalNumber:: operator+=(const PhysicalNumber &F) {
    if (this->type != F.type) throw "CANNOT ADD";
    PhysicalNumber physicalNumber(*this + F);
    this->value = physicalNumber.value;
    this->type = physicalNumber.type;
    return *this;

}
PhysicalNumber &PhysicalNumber::operator-=(const PhysicalNumber &F) {
    if (this->type != F.type) throw "CANNOT ADD";
    PhysicalNumber physicalNumber(*this - F);
    this->value = physicalNumber.value;
    this->type = physicalNumber.type;
    return *this;
}
PhysicalNumber& PhysicalNumber::operator++(int) {

    this->value+=1;
    return *this;
}

PhysicalNumber &PhysicalNumber::operator++() {
    this->value +=1;
    return *this;
}
PhysicalNumber &PhysicalNumber::operator--(int) {
    this->value -=1;
    return *this;
}

PhysicalNumber &PhysicalNumber::operator--() {
    this->value -=1;
    return *this;
}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//----------------COMPARE OPERATORS---------------------------
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



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//----------------OTHER FUNCTIONS---------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


PhysicalNumber ariel::PhysicalNumber:: convert(const PhysicalNumber& F) {

    PhysicalNumber f(0,F.unit);
    f.type = F.type;

    switch(F.unit){

        case Unit ::ton :f.value = F.value * 1000000; break;
        case Unit ::kg :  f.value = F.value * 1000; break;
        case Unit ::hour :  f.value = F.value * 3600; break;
        case Unit ::min :  f.value = F.value * 60; break;
        case Unit ::km :  f.value = F.value * 100000; break;
        case Unit ::m :  f.value = F.value * 100; break;
    }

    return f;

}


























