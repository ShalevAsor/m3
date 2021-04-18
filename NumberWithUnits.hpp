#pragma once 
#include <iostream> 
#include <fstream>
#include <sstream> 
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>


namespace ariel{

    class NumberWithUnits{

        private: 

            double value;

            std::string type; 

       

           static bool same_family(const std::string& type1,const std::string& type2);

           static double convert_to_first(const std::string& first_type,const std::string& second_type,const double second_value);

           static std::istream& check_next_char(std::istream& is,char c);

           static std::istream& check_type(std::istream& is,std::string& type);

           static void add_rate(const std::string& two_types,const double rate);

           

           static void update_family(const std::string& type1,const std::string& type2,const double val1,const double val2);

           std::unordered_set<std::string> family_members;





        public: //need to add destructor , copy constructor and operator=
            
            static std::unordered_map<std::string,double> units_rate;

         
           static std::unordered_map<std::string,std::unordered_set<std::string>> units_family;
             static std::unordered_map<std::string,double> units_list;

            //constructors

            NumberWithUnits(double val=0,std::string t="cm"):value(val),type(t){
              
            }

            //methods
            static void read_units(std::ifstream& file); 

            double& get_value(){
                return this->value;
            }
            std::string& get_type(){
                return this->type;
            }


            //operators - arithmetic 
             NumberWithUnits operator+ (const NumberWithUnits& other)const;
                

            NumberWithUnits& operator+= (const NumberWithUnits& other);

             NumberWithUnits operator+ ()const;

             NumberWithUnits operator- (const NumberWithUnits& other)const;

            NumberWithUnits& operator-= (const NumberWithUnits& other);

             NumberWithUnits operator- ()const;

            //
            bool operator> (const NumberWithUnits& other)const;

            bool operator>= (const NumberWithUnits& other)const;

            bool operator!= (const NumberWithUnits& other)const;

            bool operator<= (const NumberWithUnits& other)const; 

            bool operator< (const NumberWithUnits& other)const;

            bool operator== (const NumberWithUnits& other)const;

            //postfix 

            const NumberWithUnits operator++(int){
                NumberWithUnits copy(value,type);
                value++;
                return copy;

            }
            //prefix

            NumberWithUnits& operator++ (){
                value++;
                return *this;
            }

             NumberWithUnits operator*(const double& other)const;


           friend   NumberWithUnits operator* (const double& first,const NumberWithUnits& other); 

     friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& nwu); 

     friend std::istream& operator>> (std::istream& is, NumberWithUnits& nwu); //1:00
    };
};