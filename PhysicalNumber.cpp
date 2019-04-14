//
// Created by Dvir on 03/04/2019.
//

#include <sstream>
#include <algorithm>
#include "PhysicalNumber.h"
#include "cstdlib"
#include "string"
using namespace ariel;
using namespace std;






ostream& ariel:: operator<<(ostream &os, const ariel::PhysicalNumber& F) {

    switch (F.unit) {

        case Unit ::KM : os << F.value<<"[km]"; return os; //return cout<< F.value<< "[km]"<<endl;

        case Unit ::M : os << F.value<<"[m]"; return os;

        case Unit ::CM : os << F.value<<"[cm]"; return os;

        case Unit ::TON : os << F.value<<"[ton]"; return os;

        case Unit ::KG :  os << F.value<<"[kg]"; return os;

        case Unit ::G:  os << F.value<<"[g]"; return os;

        case Unit ::HOUR : os << F.value<<"[hour]"; return os;

        case Unit ::MIN : os << F.value<<"[min]"; return os;

        case Unit ::SEC : os << F.value<<"[sec]"; return os;

    }

}

istream &ariel::operator>>(istream &is, PhysicalNumber &F) {
	
    string input;
    is >> input;
	
    int counter = 0;

    size_t index = input.find_first_of('[');
    size_t lastIndex = input.find_first_of(']');
	
	if (index == 0 || index > input.size() )  {return is; }//throw invalid_argument("WRONG INPUT!");
	if (lastIndex > input.size()) return is; //throw invalid_argument("WRONG INPUT!");
	
    string value = input.substr(0,index);
    string unit = input.substr(index+1,lastIndex-index-1);

    F.value = stod(value);
    transform(unit.begin(), unit.end(), unit.begin(), ::toupper);

    for (int i = 0 ; i < 9 ; i++){
        if (unit == units[i]) counter++;
    }

    if (counter != 1) return is; //throw invalid_argument("NOT HERE!");

    switch (unit[0]){
        case 'K':{
            if (unit[1] == 'G') {
                F.unit = Unit :: KG;
                F.type = (int)F.unit % 3;
                return is;
            }
            else F.unit = Unit:: KM;
            F.type = (int)F.unit % 3;
            return is;
        }
        case 'M':{
            if (unit[1] == 'I') F.unit = Unit :: MIN;
            else F.unit = Unit:: M;
            F.type = (int)F.unit % 3;
            return is;
        }
        case 'H': {F.unit = Unit:: HOUR; F.type = (int)F.unit % 3; return is;}
        case  'T': {F.unit = Unit:: TON; F.type = (int)F.unit % 3; return is;}
        case 'S': {F.unit = Unit:: SEC; F.type = (int)F.unit % 3; return is;}
        case 'G': {F.unit = Unit:: G; F.type = (int)F.unit % 3; return is;}
        case 'C': {F.unit = Unit:: CM; F.type = (int)F.unit % 3; return is;}

    }


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
                case Unit::SEC:
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
                case Unit::CM:
                    return PhysicalNumber(result, Unit::CM);
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
    
   
    
    return *this = *this + F;

}
PhysicalNumber &PhysicalNumber::operator-=(const PhysicalNumber &F) {
    if (this->type != F.type) throw std:: invalid_argument("ERROR");
    PhysicalNumber physicalNumber(*this - F);
    this->value = physicalNumber.value;
    this->type = physicalNumber.type;
    return *this;
}
 PhysicalNumber PhysicalNumber::operator++(int) {
	PhysicalNumber copy (*this);
    this->value+=1;
    return copy;
}

PhysicalNumber PhysicalNumber::operator++() {
    this->value +=1;
    return *this;
}
 PhysicalNumber PhysicalNumber::operator--(int) {
    PhysicalNumber copy (*this);
    this->value-=1;
    return copy;
}

PhysicalNumber PhysicalNumber::operator--() {
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

    else throw std:: invalid_argument("ERROR");
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

    else throw std:: invalid_argument("ERROR");
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

    else throw std:: invalid_argument("ERROR");
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

    else throw std:: invalid_argument("ERROR");
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

    else throw std:: invalid_argument("ERROR");
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

    else throw std:: invalid_argument("ERROR");
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//----------------OTHER FUNCTIONS---------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


PhysicalNumber ariel::PhysicalNumber:: convert(const PhysicalNumber& F) {

    PhysicalNumber f(0,F.unit);
    f.type = F.type;

    switch(F.unit){

        case Unit ::TON :f.value = F.value * 1000000; break;
        case Unit ::KG :  f.value = F.value * 1000; break;
		case Unit ::G :  f.value = F.value ; break;
        case Unit ::HOUR :  f.value = F.value * 3600; break;
        case Unit ::MIN :  f.value = F.value * 60; break;
		case Unit ::SEC :  f.value = F.value ; break;
        case Unit ::KM :  f.value = F.value * 100000; break;
        case Unit ::M :  f.value = F.value * 100; break;
		case Unit ::CM :  f.value = F.value ; break;
    }

    return f;

}


























