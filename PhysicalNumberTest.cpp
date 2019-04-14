/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
	PhysicalNumber i(100, Unit::CM);

    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);
	PhysicalNumber e(10,Unit::SEC);
	
	PhysicalNumber f(3,Unit::TON);
	PhysicalNumber g(10,Unit::KG);
	PhysicalNumber h(2,Unit::G);

    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(e, "10[sec]")
	.CHECK_OUTPUT(f,"3[ton]")
	.CHECK_OUTPUT(d,"30[min]")
	.CHECK_OUTPUT(i,"100[cm]")
	.CHECK_OUTPUT(h,"2[g]")


    .setname("Compatible dimensions")
	.CHECK_OUTPUT(i+b, "30100[m]")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
	.CHECK_OUTPUT((f+g), "3.01[ton]")
	.CHECK_OUTPUT((d++), "31[min]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
	.CHECK_OUTPUT((a+=b), "2.6[km]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "31[min]")
    .CHECK_OUTPUT(d+c, "151[min]")
	.CHECK_OUTPUT((f+g), "3.01[ton]")
	.CHECK_OUTPUT((g+f), "3010[kg]")
	.CHECK_OUTPUT(c--, "1[hour]")
	

	



    .setname("Incompatible dimensions")
	.CHECK_EQUAL(a == a, true)
	.CHECK_EQUAL(a > b, true)
	.CHECK_EQUAL(b < a, true)
	.CHECK_EQUAL(c >= d, true)
	.CHECK_EQUAL(g < h, false)
	.CHECK_EQUAL(a != a, false)
	.CHECK_EQUAL(d != e, true)
	
    .CHECK_THROWS(a + c)
    .CHECK_THROWS(a + d)
    .CHECK_THROWS(b += c)
    .CHECK_THROWS(e - f)
	.CHECK_THROWS(f + a)
	.CHECK_THROWS(b - d)
	.CHECK_THROWS(h + e)
	
	

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
	.CHECK_OK(istringstream("100[sec]") >> b)
	.CHECK_OK(istringstream("300[g]") >> c)
	.CHECK_OK(istringstream("100[m]") >> d)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")
	.CHECK_OUTPUT((d += PhysicalNumber(10, Unit::KM)), "10100[m]")
	.CHECK_OUTPUT((a -= PhysicalNumber(300, Unit::KG)), "1400[kg]")



    
      .setname("...")

      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
