#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <fstream>
#include <sstream>


using namespace std;
using namespace ariel; 



/**
 * 
 */
TEST_CASE("read_units"){
    //units_file 1 - mb,kb
    ifstream  units_file1{"units_file1.txt"};
    NumberWithUnits::read_units(units_file1);
    NumberWithUnits a1{3,"mb"};
    NumberWithUnits b1{3000,"kb"};
    CHECK(a1==b1);
    CHECK(b1==a1);
    //units_file2 kb,mb,gb,tb 
    ifstream  units_file2{"units_file2.txt"};
    NumberWithUnits::read_units(units_file2);
    NumberWithUnits a2{1000,"mb"};
    NumberWithUnits b2{1,"gb"};
    CHECK(a2==b2);
    CHECK(b2==a2);
    NumberWithUnits a3{1000,"gb"};
    NumberWithUnits b3{1,"tb"};
    CHECK(a3==b3);
    CHECK(b3==a3);
    NumberWithUnits a4{1000,"bytes"};
    NumberWithUnits b4{1,"kb"};
    CHECK(a4==b4);
    CHECK(b4==a4);
    NumberWithUnits a5{10,"mb"};
    NumberWithUnits b5{10000,"kb"};
    CHECK(a5==b5);
    CHECK(b5==a5);
    NumberWithUnits a6{8,"tb"};
    NumberWithUnits b6{8000,"gb"};
    CHECK(a6==b6);
    CHECK(b6==a6);
    // units_file3 - 
    ifstream units_file3{"units_file3.txt"};
    NumberWithUnits::read_units(units_file3);
    NumberWithUnits a7{2,"m"};
    NumberWithUnits b7{200,"cm"};
    CHECK(a7==b7);
    CHECK(b7==a7);
    NumberWithUnits a8{1,"km"};
    NumberWithUnits b8{1000,"m"};
    NumberWithUnits c8{100000,"cm"};
    CHECK(a8==b8);
    CHECK(c8==b8);
    NumberWithUnits a9{10,"dm"};
    NumberWithUnits b9{100,"cm"};
    CHECK(a9==b9);
    CHECK(b9==a9);
    ifstream units_file4{"units_file4.txt"};
    NumberWithUnits::read_units(units_file4);
    CHECK(NumberWithUnits(1,"dm")==NumberWithUnits(10,"cm"));// verify that "dm" is still able to use 
    NumberWithUnits a10{1,"hour"};
    NumberWithUnits b10{60,"min"};
    NumberWithUnits c10{3600,"sec"};
    CHECK(a10==b10);
    CHECK(c10==b10);
    NumberWithUnits a11{1,"year"};
    NumberWithUnits b11{52,"week"};
    CHECK(a11==b11);
    CHECK(b11==a11);
    NumberWithUnits a12{2,"day"};
    NumberWithUnits b12{48,"hour"};
    CHECK(a12==b12);
    CHECK(b12==a12);



}
/**
 * 
 */
TEST_CASE("operator + "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    // km with m 
    NumberWithUnits val_a1{1 ,"km"};
    NumberWithUnits val_b1{200,"m"};
    NumberWithUnits sum1{1.2,"km"};
    NumberWithUnits sum2{1200,"m"};
    CHECK((val_a1+val_b1)==sum1);
    CHECK((val_a1+val_b1)==sum2);
    // m with cm 
    NumberWithUnits val_a2{1 ,"m"};
    NumberWithUnits val_b2{50,"cm"};
    NumberWithUnits sum3{1.5,"m"};
    NumberWithUnits sum4{150,"cm"};
    CHECK((val_a2+val_b2)==sum3);
    CHECK((val_a2+val_b2)==sum4);
    //ton with kg 
    NumberWithUnits val_a3{2,"ton"};
    NumberWithUnits val_b3{400,"kg"};
    NumberWithUnits sum5{2.4,"ton"};
    NumberWithUnits sum6{2400,"kg"};
    CHECK((val_a3+val_b3)==sum5);
    CHECK((val_b3+val_a3)==sum6);
    //hour with min 
    NumberWithUnits val_a4{1,"hour"};
    NumberWithUnits val_b4{30,"min"};
    NumberWithUnits sum7{1.5,"hour"};
    NumberWithUnits sum8{90,"min"};
    CHECK((val_a4+val_b4)==sum7);
    CHECK((val_b4+val_a4)==sum8);
    //USD with ILS
    NumberWithUnits val_a5{4.5,"USD"};
    NumberWithUnits val_b5{10,"ILS"};
    NumberWithUnits sum9{4.5+10/3.33,"USD"};
    NumberWithUnits sum10{10+(4.5*3.33),"ILS"};
    CHECK((val_a5+val_b5)==sum9);
    CHECK((val_b5+val_a5)==sum10);
    // edge cases 
    CHECK_THROWS(val_a1+val_a3);// km + ton 
    CHECK_THROWS(val_a3+val_a1); 
    CHECK_THROWS(val_a4+val_b5); //hour+ILS
    CHECK_THROWS(val_b5+val_a4);
    CHECK_THROWS(val_a2+val_b4);//m+min 
    CHECK_THROWS(val_a2+val_b4);
}
/**
 * 
 */
TEST_CASE("operator += "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    // km with m 
    NumberWithUnits val_a1{1.5,"km"};
    NumberWithUnits val_b1{1.2,"m"};
    NumberWithUnits val_c1{1.5,"km"};
    NumberWithUnits sum1{1.5+(1.2/1000),"km"};
    NumberWithUnits sum2{1501.2,"m"};
    CHECK((val_a1+=val_b1)==sum1);
    CHECK((val_b1+=val_c1)==sum2);
    // m with cm 
    NumberWithUnits val_a2{2,"m"};
    NumberWithUnits val_b2{10,"cm"};
    NumberWithUnits val_c2{2,"m"};
    NumberWithUnits sum3{2.1,"m"};
    NumberWithUnits sum4{210,"cm"};
    CHECK((val_a2+=val_b2)==sum3);
    CHECK((val_b2+=val_c2)==sum4);
    //kg with g 
    NumberWithUnits val_a3{2.5,"kg"};
    NumberWithUnits val_b3{100,"g"};
    NumberWithUnits val_c3{2.5,"kg"};
    NumberWithUnits sum5{2.6,"kg"};
    NumberWithUnits sum6{2600,"g"};
    CHECK((val_a3+=val_b3)==sum5);
    CHECK((val_b3+=val_c3)==sum6);
    //ton with kg with g 
    NumberWithUnits val_a4{1,"ton"};
    NumberWithUnits val_b4{100,"kg"};
    NumberWithUnits val_c4{1000,"g"};
    NumberWithUnits sum_abc{1.101,"ton"};
    NumberWithUnits sum_c4{1000,"g"};
    NumberWithUnits sum_b4{101,"kg"};
    CHECK((val_a4+=val_b4+=val_c4)==sum_abc);
    CHECK(val_a4==sum_abc);
    CHECK(val_c4==sum_c4);
    CHECK(val_b4==sum_b4);
    //edge cases 
    CHECK_THROWS(val_a1+=val_a3);//km+=kg
    CHECK_THROWS(val_b1+=val_b3);//m+=g
    CHECK_THROWS(val_a4+=val_b2);//ton+=cm
    CHECK_THROWS(val_b4+=val_b2);//kg+=cm 
    NumberWithUnits val_a5{1,"USD"};
    CHECK_THROWS(val_a5+=val_c4);//USD+=g
    
}
/**
 * 
 */
TEST_CASE("operator + unary "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //USD
    NumberWithUnits val_a1{1,"USD"};
    NumberWithUnits sum1{1,"USD"};
    CHECK((+val_a1)==sum1);
    //kg
    NumberWithUnits val_a2{1,"kg"};
    NumberWithUnits sum2{1,"kg"};
    CHECK((+val_a2)==sum2);
    //g
    NumberWithUnits val_a3{2,"g"};
    NumberWithUnits sum3{2,"g"};
    CHECK((+val_a3)==sum3);
    //hour
    NumberWithUnits val_a4{3.5,"hour"};
    NumberWithUnits sum4{3.5,"hour"};
    CHECK((+val_a4)==sum4);
    //min
    NumberWithUnits val_a5{1,"min"};
    NumberWithUnits sum5{1,"min"};
    CHECK((+val_a5)==sum5);
    //sec
    NumberWithUnits val_a6{-1,"sec"};
    NumberWithUnits sum6{-1,"sec"};
    CHECK((+val_a6)==sum6);
    //ILS
    NumberWithUnits val_a7{-3.4,"ILS"};
    NumberWithUnits sum7{-3.4,"ILS"};
    CHECK((+val_a7)==sum7);
    //ton
    NumberWithUnits val_a8{0,"ton"};
    NumberWithUnits sum8{0,"ton"};
    CHECK((+val_a8)==sum8);
}
/**
 * 
 */
TEST_CASE("operator - "){
     ifstream units_file{"units.txt"};
     NumberWithUnits::read_units(units_file);
    //USD
    NumberWithUnits val_a1{1,"USD"};
    NumberWithUnits sum1{-1,"USD"};
    CHECK((-val_a1)==sum1);
    //kg
    NumberWithUnits val_a2{1,"kg"};
    NumberWithUnits sum2{-1,"kg"};
    CHECK((-val_a2)==sum2);
    //g
    NumberWithUnits val_a3{2,"g"};
    NumberWithUnits sum3{-2,"g"};
    CHECK((-val_a3)==sum3);
    //hour
    NumberWithUnits val_a4{3.5,"hour"};
    NumberWithUnits sum4{-3.5,"hour"};
    CHECK((-val_a4)==sum4);
    //min
    NumberWithUnits val_a5{1,"min"};
    NumberWithUnits sum5{-1,"min"};
    CHECK((-val_a5)==sum5);
    //sec
    NumberWithUnits val_a6{-1,"sec"};
    NumberWithUnits sum6{1,"sec"};
    CHECK((-val_a6)==sum6);
    //ILS
    NumberWithUnits val_a7{-3.4,"ILS"};
    NumberWithUnits sum7{3.4,"ILS"};
    CHECK((-val_a7)==sum7);
    //ton
    NumberWithUnits val_a8{0,"ton"};
    NumberWithUnits sum8{0,"ton"};
    CHECK((-val_a8)==sum8);
    
}
/**
 * 
 */
TEST_CASE("operator -= "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    // km with m 
    NumberWithUnits val_a1{1.5,"km"};
    NumberWithUnits val_b1{1.2,"m"};
    NumberWithUnits val_c1{1.5,"km"};
    NumberWithUnits sum1{1.5-1.2/1000,"km"};
    NumberWithUnits sum2{-1498.8,"m"};
    CHECK((val_a1-=val_b1)==sum1);
    CHECK((val_b1-=val_c1)==sum2);
    // m with cm 
    NumberWithUnits val_a2{2,"m"};
    NumberWithUnits val_b2{10,"cm"};
    NumberWithUnits val_c2{2,"m"};
    NumberWithUnits sum3{1.9,"m"};
    NumberWithUnits sum4{-190,"cm"};
    CHECK((val_a2-=val_b2)==sum3);
    CHECK((val_b2-=val_c2)==sum4);
    //kg with g 
    NumberWithUnits val_a3{2.5,"kg"};
    NumberWithUnits val_b3{100,"g"};
    NumberWithUnits val_c3{2.5,"kg"};
    NumberWithUnits sum5{2.4,"kg"};
    NumberWithUnits sum6{-2400,"g"};
    CHECK((val_a3-=val_b3)==sum5);
    CHECK((val_b3-=val_c3)==sum6);
    //ton with kg with g 
    NumberWithUnits val_a4{1,"ton"};
    NumberWithUnits val_b4{100,"kg"};
    NumberWithUnits val_c4{1000,"g"};
    NumberWithUnits sum_abc{0.901,"ton"};
    NumberWithUnits sum_c4{1000,"g"};
    NumberWithUnits sum_b4{99,"kg"};
    CHECK((val_a4-=val_b4-=val_c4)==sum_abc);
    CHECK(val_a4==sum_abc);
    CHECK(val_c4==sum_c4);
    CHECK(val_b4==sum_b4);
    //edge cases 
    CHECK_THROWS(val_a1-=val_a3);//km-=kg
    CHECK_THROWS(val_b1-=val_b3);//m-=g
    CHECK_THROWS(val_a4-=val_b2);//ton-=cm
    CHECK_THROWS(val_b4-=val_b2);//kg-=cm 
    NumberWithUnits val_a5{1,"USD"};
    CHECK_THROWS(val_a5-=val_c4);//USD-=g
    
}
/**
 * 
 */
TEST_CASE("operator - unary "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //USD
    NumberWithUnits val_a1{1,"USD"};
    NumberWithUnits sum1{-1,"USD"};
    CHECK((-val_a1)==sum1);
    //kg
    NumberWithUnits val_a2{1,"kg"};
    NumberWithUnits sum2{-1,"kg"};
    CHECK((-val_a2)==sum2);
    //g
    NumberWithUnits val_a3{2,"g"};
    NumberWithUnits sum3{-2,"g"};
    CHECK((-val_a3)==sum3);
    //hour
    NumberWithUnits val_a4{3.5,"hour"};
    NumberWithUnits sum4{-3.5,"hour"};
    CHECK((-val_a4)==sum4);
    //min
    NumberWithUnits val_a5{1,"min"};
    NumberWithUnits sum5{-1,"min"};
    CHECK((-val_a5)==sum5);
    //sec
    NumberWithUnits val_a6{-1,"sec"};
    NumberWithUnits sum6{1,"sec"};
    CHECK((-val_a6)==sum6);
    //ILS
    NumberWithUnits val_a7{-3.4,"ILS"};
    NumberWithUnits sum7{3.4,"ILS"};
    CHECK((-val_a7)==sum7);
    //ton
    NumberWithUnits val_a8{0,"ton"};
    NumberWithUnits sum8{0,"ton"};
    CHECK((-val_a8)==sum8);
    
}
/**
 * 
 */
TEST_CASE("operator > "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //USD with ILS
    NumberWithUnits val_a1{1,"USD"};
    NumberWithUnits val_b1{4,"ILS"};
    CHECK((val_b1>val_a1)==true);
    //kg with g
    NumberWithUnits val_a2{0.5,"kg"};
    NumberWithUnits val_b2{400,"g"};
    CHECK((val_a2>val_b2)==true);
    //min with sec
    NumberWithUnits val_a3{2,"min"};
    NumberWithUnits val_b3{150,"sec"};
    CHECK((val_b3>val_a3)==true);
    //kg with ton
    NumberWithUnits val_a4{0.5,"ton"};
    NumberWithUnits val_b4{400,"kg"};
    CHECK((val_a4>val_b4)==true);
    //hour with sec
    NumberWithUnits val_a5{1,"hour"};
    NumberWithUnits val_b5{1000,"sec"};
    CHECK(val_a5>val_b5);
    //m with cm
    NumberWithUnits val_a6{2,"m"};
    NumberWithUnits val_b6{250,"cm"};
    CHECK((val_b6>val_a6)==true);
    //kg with g
    NumberWithUnits val_a7{0.5,"kg"};
    NumberWithUnits val_b7{400,"g"};
    CHECK((val_a7>val_b7)==true);
    //hour with min 
    NumberWithUnits val_a8{2,"hour"};
    NumberWithUnits val_b8{110,"min"};
    CHECK((val_a8>val_b8)==true);
    //edge cases
    bool a = false; 
    CHECK_THROWS(a=(val_a1>val_a8));//USD>hour
    CHECK_THROWS(a=(val_a2>val_b5));//kg>sec
    CHECK_THROWS(a=(val_b6>val_a4));//cm>ton
    CHECK_THROWS(a=(val_b1>val_b2));//ILS>g
}

/**
 * 
 */
TEST_CASE("operator >= "){
     ifstream units_file{"units.txt"};
     NumberWithUnits::read_units(units_file);
    //USD with ILS
    NumberWithUnits val_a1{1,"USD"};
    NumberWithUnits val_b1{4,"ILS"};
    CHECK((val_b1>=val_a1)==true);
    //kg with g
    NumberWithUnits val_a2{0.5,"kg"};
    NumberWithUnits val_b2{400,"g"};
    CHECK((val_a2>=val_b2)==true);
    //min with sec
    NumberWithUnits val_a3{2,"min"};
    NumberWithUnits val_b3{120,"sec"};
    CHECK((val_b3>=val_a3)==true);
    //kg with ton
    NumberWithUnits val_a4{0.5,"ton"};
    NumberWithUnits val_b4{500,"kg"};
    CHECK((val_a4>=val_b4)==true);
    //hour with sec
    NumberWithUnits val_a5{1,"hour"};
    NumberWithUnits val_b5{1000,"sec"};
    CHECK((val_a5>=val_b5)==true);
    //m with cm
    NumberWithUnits val_a6{2.5,"m"};
    NumberWithUnits val_b6{250,"cm"};
    CHECK((val_b6>=val_a6)==true);
    //kg with g
    NumberWithUnits val_a7{0.5,"kg"};
    NumberWithUnits val_b7{500,"g"};
    CHECK((val_a7>=val_b7)==true);
    //hour with min 
    NumberWithUnits val_a8{2,"hour"};
    NumberWithUnits val_b8{110,"min"};
    CHECK((val_a8>=val_b8)==true);
    //edge cases
    bool a = false; 
    CHECK_THROWS(a=(val_a1>=val_a8));//USD>hour
    CHECK_THROWS(a=(val_a2>=val_b5));//kg>sec
    CHECK_THROWS(a=(val_b6>=val_a4));//cm>ton
    CHECK_THROWS(a=(val_b1>=val_b2));//ILS>g
    
}

/**
 * 
 */
TEST_CASE("operator < "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //USD with ILS
    NumberWithUnits val_a1{4,"USD"};
    NumberWithUnits val_b1{1,"ILS"};
    CHECK((val_b1<val_a1)==true);
    //kg with g
    NumberWithUnits val_a2{0.5,"kg"};
    NumberWithUnits val_b2{600,"g"};
    CHECK((val_a2<val_b2)==true);
    //min with sec
    NumberWithUnits val_a3{1,"min"};
    NumberWithUnits val_b3{50,"sec"};
    CHECK((val_b3<val_a3)==true);
    //kg with ton
    NumberWithUnits val_a4{0.5,"ton"};
    NumberWithUnits val_b4{700,"kg"};
    CHECK((val_a4<val_b4)==true);
    //hour with sec
    NumberWithUnits val_a5{1,"hour"};
    NumberWithUnits val_b5{300000,"sec"};
    CHECK((val_a5<val_b5)==true);
    //m with cm
    NumberWithUnits val_a6{2,"m"};
    NumberWithUnits val_b6{150,"cm"};
    CHECK((val_b6<val_a6)==true);
    //kg with g
    NumberWithUnits val_a7{0.5,"kg"};
    NumberWithUnits val_b7{550,"g"};
    CHECK((val_a7<val_b7)==true);
    //hour with min 
    NumberWithUnits val_a8{2,"hour"};
    NumberWithUnits val_b8{130,"min"};
    CHECK((val_a8<val_b8)==true);
    //edge cases
    bool a = false; 
    CHECK_THROWS(a=(val_a1<val_a8));//USD<hour
    CHECK_THROWS(a=(val_a2<val_b5));//kg<sec
    CHECK_THROWS(a=(val_b6<val_a4));//cm<ton
    CHECK_THROWS(a=(val_b1<val_b2));//ILS<g
    
}

/**
 * 
 */
TEST_CASE("operator <= "){
     ifstream units_file{"units.txt"};
     NumberWithUnits::read_units(units_file);
    //USD with ILS
    NumberWithUnits val_a1{4,"USD"};
    NumberWithUnits val_b1{1,"ILS"};
    CHECK((val_b1<=val_a1)==true);
    //kg with g
    NumberWithUnits val_a2{0.5,"kg"};
    NumberWithUnits val_b2{500,"g"};
    CHECK((val_a2<=val_b2)==true);
    //min with sec
    NumberWithUnits val_a3{1,"min"};
    NumberWithUnits val_b3{60,"sec"};
    CHECK((val_b3<=val_a3)==true);
    //kg with ton
    NumberWithUnits val_a4{0.5,"ton"};
    NumberWithUnits val_b4{700,"kg"};
    CHECK((val_a4<=val_b4)==true);
    //hour with sec
    NumberWithUnits val_a5{1,"hour"};
    NumberWithUnits val_b5{3600,"sec"};
    CHECK((val_a5<=val_b5)==true);
    //m with cm
    NumberWithUnits val_a6{2,"m"};
    NumberWithUnits val_b6{200,"cm"};
    CHECK((val_b6<=val_a6)==true);
    //kg with g
    NumberWithUnits val_a7{0.5,"kg"};
    NumberWithUnits val_b7{550,"g"};
    CHECK((val_a7<=val_b7)==true);
    //hour with min 
    NumberWithUnits val_a8{2,"hour"};
    NumberWithUnits val_b8{120,"min"};
    CHECK((val_a8<=val_b8)==true);
    //edge cases
    bool a = false; 
    CHECK_THROWS(a=(val_a1<=val_a8));//USD<=hour
    CHECK_THROWS(a=(val_a2<=val_b5));//kg<=sec
    CHECK_THROWS(a=(val_b6<=val_a4));//cm<=ton
    CHECK_THROWS(a=(val_b1<=val_b2));//ILS<=g
    
}

/**
 * 
 */
TEST_CASE("operator == "){
      ifstream units_file{"units.txt"};
      NumberWithUnits::read_units(units_file);
    //USD with ILS
    NumberWithUnits val_a1{1,"USD"};
    NumberWithUnits val_b1{3.33,"ILS"};
    CHECK((val_b1==val_a1)==true);
    //kg with g
    NumberWithUnits val_a2{0.5,"kg"};
    NumberWithUnits val_b2{500,"g"};
    CHECK((val_a2==val_b2)==true);
    //min with sec
    NumberWithUnits val_a3{1,"min"};
    NumberWithUnits val_b3{60,"sec"};
    CHECK((val_b3==val_a3)==true);
    //kg with ton
    NumberWithUnits val_a4{0.5,"ton"};
    NumberWithUnits val_b4{500,"kg"};
    CHECK((val_a4==val_b4)==true);
    //hour with sec
    NumberWithUnits val_a5{1,"hour"};
    NumberWithUnits val_b5{3600,"sec"};
    CHECK((val_a5==val_b5)==true);
    //m with cm
    NumberWithUnits val_a6{2,"m"};
    NumberWithUnits val_b6{200,"cm"};
    CHECK((val_b6==val_a6)==true);
    //kg with g
    NumberWithUnits val_a7{0.55,"kg"};
    NumberWithUnits val_b7{550,"g"};
    CHECK((val_a7==val_b7)==true);
    //hour with min 
    NumberWithUnits val_a8{2,"hour"};
    NumberWithUnits val_b8{120,"min"};
    CHECK((val_a8==val_b8)==true);
    //edge cases
    bool a = false; 
    CHECK_THROWS(a=(val_a1==val_a8));//USD<=hour
    CHECK_THROWS(a=(val_a2==val_b5));//kg<=sec
    CHECK_THROWS(a=(val_b6==val_a4));//cm<=ton
    CHECK_THROWS(a=(val_b1==val_b2));//ILS<=g
    
}

/**
 * 
 */
TEST_CASE("operator != "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //USD with ILS
    NumberWithUnits val_a1{1,"USD"};
    NumberWithUnits val_b1{3.34,"ILS"};
    CHECK((val_b1!=val_a1)==true);
    //kg with g
    NumberWithUnits val_a2{0.6,"kg"};
    NumberWithUnits val_b2{500,"g"};
    CHECK((val_a2!=val_b2)==true);
    //min with sec
    NumberWithUnits val_a3{2.5,"min"};
    NumberWithUnits val_b3{60,"sec"};
    CHECK((val_b3!=val_a3)==true);
    //kg with ton
    NumberWithUnits val_a4{0.75,"ton"};
    NumberWithUnits val_b4{500,"kg"};
    CHECK((val_a4!=val_b4)==true);
    //hour with sec
    NumberWithUnits val_a5{1,"hour"};
    NumberWithUnits val_b5{3601,"sec"};
    CHECK((val_a5!=val_b5)==true);
    //m with cm
    NumberWithUnits val_a6{23,"m"};
    NumberWithUnits val_b6{230,"cm"};
    CHECK((val_b6!=val_a6)==true);
    //kg with g
    NumberWithUnits val_a7{0.55,"kg"};
    NumberWithUnits val_b7{551,"g"};
    CHECK((val_a7!=val_b7)==true);
    //hour with min 
    NumberWithUnits val_a8{2.1,"hour"};
    NumberWithUnits val_b8{120,"min"};
    CHECK((val_a8!=val_b8)==true);
    //edge cases
    bool a = false; 
    CHECK_THROWS(a=(val_a1!=val_a8));//USD<=hour
    CHECK_THROWS(a=(val_a2!=val_b5));//kg<=sec
    CHECK_THROWS(a=(val_b6!=val_a4));//cm<=ton
    CHECK_THROWS(a=(val_b1!=val_b2));//ILS<=g
    
}

/**
 * 
 */
TEST_CASE("operator ++ (postfix) "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //cm 
    NumberWithUnits val_a1{1,"cm"};
    NumberWithUnits val_b1{1,"cm"};
    NumberWithUnits val_c1{2,"cm"};
    CHECK((val_a1++)==val_b1);
    CHECK(val_a1==val_c1);
    //m 
    NumberWithUnits val_a2{1,"m"};
    NumberWithUnits val_b2{1,"m"};
    NumberWithUnits val_c2{2,"m"};
    CHECK((val_a2++)==val_b2);
    CHECK(val_a2==val_c2);
    //ton
    NumberWithUnits val_a3{3,"ton"};
    NumberWithUnits val_b3{3,"ton"};
    NumberWithUnits val_c3{4,"ton"};
    CHECK((val_a3++)==val_b3);
    CHECK(val_a3==val_c3);
    //km
    NumberWithUnits val_a4{1,"km"};
    NumberWithUnits val_b4{1,"km"};
    NumberWithUnits val_c4{2,"km"};
    NumberWithUnits val_d4{2000,"m"};
    CHECK((val_a4++)==val_b4);
    CHECK(val_a4==val_c4);
    CHECK((val_d4++)==(val_a4++));
    CHECK(val_d4!=val_a4);

}

/**
 * 
 */
TEST_CASE("operator ++ (prefix) "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //cm 
    NumberWithUnits val_a1{1,"cm"};
    NumberWithUnits val_b1{2,"cm"};
    NumberWithUnits val_c1{2,"cm"};
    CHECK((++val_a1)==val_b1);
    CHECK(val_a1==val_c1);
    //m 
    NumberWithUnits val_a2{1,"m"};
    NumberWithUnits val_b2{2,"m"};
    NumberWithUnits val_c2{2,"m"};
    CHECK((++val_a2)==val_b2);
    CHECK(val_a2==val_c2);
    //ton
    NumberWithUnits val_a3{3,"ton"};
    NumberWithUnits val_b3{4,"ton"};
    NumberWithUnits val_c3{4,"ton"};
    CHECK((++val_a3)==val_b3);
    CHECK(val_a3==val_c3);
    //km
    NumberWithUnits val_a4{1,"km"};
    NumberWithUnits val_b4{2,"km"};
    NumberWithUnits val_c4{2,"km"};
    NumberWithUnits val_d4{2000,"m"};
    CHECK((++val_a4)==val_b4);
    CHECK(val_a4==val_c4);
    CHECK((++val_d4)!=(++val_a4));
    CHECK(val_d4!=val_a4);
    
}

/**
 * 
 */
TEST_CASE("operator * NumberWithUnits*double "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //ILS
    NumberWithUnits val_a1{5,"ILS"}; 
    double val_b1 = 3; 
    NumberWithUnits sum1{15,"ILS"};
    CHECK((val_a1*val_b1)==sum1);
    //USD
    NumberWithUnits val_a2{2.5,"USD"}; 
    double val_b2 = 2.5; 
    NumberWithUnits sum2{6.25,"USD"};
    CHECK((val_a2*val_b2)==sum2);
    //km
    NumberWithUnits val_a3{4,"km"}; 
    double val_b3 = 6; 
    NumberWithUnits sum3{24,"km"};
    CHECK((val_a3*val_b3)==sum3);
    //cm
    NumberWithUnits val_a4{1.5,"cm"}; 
    double val_b4 = 0.5; 
    NumberWithUnits sum4{0.75,"cm"};
    CHECK((val_a4*val_b4)==sum4);
    //m
    NumberWithUnits val_a5{10,"m"}; 
    double val_b5 = 2.5; 
    NumberWithUnits sum5{25,"m"};
    CHECK((val_a5*val_b5)==sum5);
    //ton
    NumberWithUnits val_a6{6,"ton"}; 
    double val_b6 = 20; 
    NumberWithUnits sum6{120,"ton"};
    CHECK((val_a6*val_b6)==sum6);
    
}

/**
 * 
 */
TEST_CASE("operator * double*NumberWithUnits "){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //ILS
    NumberWithUnits val_b1{5,"ILS"}; 
    double val_a1 = 3; 
    NumberWithUnits sum1{15,"ILS"};
    CHECK((val_a1*val_b1)==sum1);
    //USD
    NumberWithUnits val_b2{2.5,"USD"}; 
    double val_a2 = 2.5; 
    NumberWithUnits sum2{6.25,"USD"};
    CHECK((val_a2*val_b2)==sum2);
    //km
    NumberWithUnits val_b3{4,"km"}; 
    double val_a3 = 6; 
    NumberWithUnits sum3{24,"km"};
    CHECK((val_a3*val_b3)==sum3);
    //cm
    NumberWithUnits val_b4{1.5,"cm"}; 
    double val_a4 = 0.5; 
    NumberWithUnits sum4{0.75,"cm"};
    CHECK((val_a4*val_b4)==sum4);
    //m
    NumberWithUnits val_b5{10,"m"}; 
    double val_a5 = 2.5; 
    NumberWithUnits sum5{25,"m"};
    CHECK((val_a5*val_b5)==sum5);
    //ton
    NumberWithUnits val_b6{6,"ton"}; 
    double val_a6 = 20; 
    NumberWithUnits sum6{120,"ton"};
    CHECK((val_a6*val_b6)==sum6);
    
}

/**
 * 
 */
TEST_CASE("operator <<"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    // km,cm,m 
    NumberWithUnits val_a1{1,"km"};
    NumberWithUnits val_b1{100,"m"};
    NumberWithUnits val_c1{50,"cm"};
    ostringstream sout;
    sout<<val_a1;
    CHECK(sout.str()=="1[km]");
    sout.str("");
    sout<<(2*val_a1);
    CHECK(sout.str()=="2[km]");
    sout.str("");
    sout<<(val_a1+val_b1);
    CHECK(sout.str()=="1.1[km]");
  //  cout<<(val_a1+val_b1)<<endl;//2.1[km]
    sout.str("");
    sout<<(val_b1+val_c1);
    CHECK(sout.str()=="100.5[m]");
   // cout<<(val_b1+val_c1)<<endl;//100.5[m]
    sout.str("");
    sout<<(val_a1>val_b1);
    CHECK(sout.str()=="1");//check if it return true
    sout.str("");
    sout<<(val_a1-val_b1);
    CHECK(sout.str()=="0.9[km]");
    
}
TEST_CASE("operator>>"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits val_a1;
    istringstream input1{"100 [ kg ]"};
    input1>>val_a1;
    //cout<<val_a1;
    CHECK(val_a1==(NumberWithUnits(100,"kg")));
    //cout<<val_a1<<endl;//100[kg]
    istringstream input2{"53.2   [m]"};
    input2>>val_a1;
    CHECK(val_a1==NumberWithUnits(53.2,"m"));
    //cout<<val_a1<<endl;//53.2[m]
    istringstream input3{"466 [ cm]"};
    input3>>val_a1;
    CHECK(val_a1==NumberWithUnits(466,"cm"));
    //cout<<val_a1<<endl;//466[cm]
    istringstream input4{"30 [tm ]"};// unknown type
    CHECK_THROWS(input4>>val_a1;);

}
