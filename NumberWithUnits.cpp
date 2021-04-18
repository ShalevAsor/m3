#include "NumberWithUnits.hpp"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace ariel;




        
           
               unordered_map<string,unordered_set<string>> NumberWithUnits::units_family={{"",unordered_set<string>()}};
               unordered_map<string,double> NumberWithUnits::units_list={{"",1}};
               unordered_map<string,double> NumberWithUnits::units_rate={{}};
                
               
           
            //methods
             void NumberWithUnits::read_units(std::ifstream& file){
                 uint  val_a = 0;
                 double  val_b = 0;
                 string type_a;
                 string type_b;
                 char c=0;
            
                    if(!file){throw "file error";}
                    while(file>>val_a>>type_a>>c>>val_b>>type_b){
                        string type_a_b= type_a+type_b;
                        double val_a_b = val_a/val_b;
                        string type_b_a= type_b+type_a;
                        double val_b_a=val_b/val_a;
                        NumberWithUnits::units_list[type_a]=val_a/val_b;
                        NumberWithUnits::units_list[type_b]=val_b/val_a;
                        add_rate(type_a_b,val_a_b);
                        add_rate(type_b_a,val_b_a);
                        update_family(type_a,type_b,val_a,val_b);
                       
                        if(NumberWithUnits::units_family.at(type_a).size()>2){
                              for(auto it = NumberWithUnits::units_family.at(type_a).begin();it!=NumberWithUnits::units_family.at(type_a).end();++it){
                                   
                                  string combination_a = *it +type_a;
                                      string combination_b = type_a+*it ; 
                                  if(NumberWithUnits::units_rate.find(combination_a)==NumberWithUnits::units_rate.end()){
                                       
                                      
                                      double rate_a = NumberWithUnits::units_list.at(*it) ; 
                                      
                                       
                                        add_rate(combination_a,rate_a/val_a_b);
                                        add_rate(combination_b,val_a_b/rate_a);
                                         
                                  }
                              }
                              for(auto it = NumberWithUnits::units_family.at(type_b).begin();it!=NumberWithUnits::units_family.at(type_b).end();++it){
                                      string combination_a = *it +type_b;
                                      string combination_b = type_b+*it ; 
                                  if(NumberWithUnits::units_rate.find(combination_b)==NumberWithUnits::units_rate.end()){
                                     
                                      double rate_b = NumberWithUnits::units_list.at(*it) ; 
                                      

                                        add_rate(combination_a,rate_b/val_b_a);
                                        add_rate(combination_b,val_b_a/rate_b);
                                  }
                              }

                            
                        }

                    }
                

            }

            //private methods 
            
            void NumberWithUnits::add_rate(const string& two_types,const double rate){
                NumberWithUnits::units_rate[two_types]=rate; 
            }
           
           

            void NumberWithUnits::update_family(const string& type1,const string& type2,const double val1,const double val2){
                NumberWithUnits::units_family[type2].insert(type1);
                    NumberWithUnits::units_family[type1].insert(type2);
                    
                   
                    for(auto  it=NumberWithUnits::units_family.at(type1).begin();it!=NumberWithUnits::units_family[type1].end();++it){
                        string t=*it;
                        if(NumberWithUnits::units_family.at(t).find(type1)==NumberWithUnits::units_family.at(t).end()){
                            NumberWithUnits::units_family.at(t).insert(type1);
                            

                        }
                        if(NumberWithUnits::units_family.at(t).find(type2)==NumberWithUnits::units_family.at(t).end()){
                            NumberWithUnits::units_family.at(t).insert(type2);
                           
                        }
                        
                    }
                    for(auto  it=NumberWithUnits::units_family.at(type2).begin();it!=NumberWithUnits::units_family[type2].end();++it){
                        string t=*it;
                        if(NumberWithUnits::units_family.at(t).find(type1)==NumberWithUnits::units_family.at(t).end()){
                            NumberWithUnits::units_family.at(t).insert(type1);
                          

                        }
                        if(NumberWithUnits::units_family.at(t).find(type2)==NumberWithUnits::units_family.at(t).end()){
                            NumberWithUnits::units_family.at(t).insert(type2);
                           

                        }
                        
                    }

                 }
            

            

            double NumberWithUnits::convert_to_first(const string& first_type,const string& second_type,const double second_value){ 
                if(first_type==second_type){return second_value;}
                string types = first_type+second_type;
                //cout<<types<<endl;

                return (NumberWithUnits::units_rate.at(types)*second_value);
                
            }

            bool NumberWithUnits::same_family(const string& type1,const string& type2){
                if(NumberWithUnits::units_family.at(type1).find(type2)!=NumberWithUnits::units_family.at(type1).end()){return true;}
                if(NumberWithUnits::units_family.at(type2).find(type1)!=NumberWithUnits::units_family.at(type2).end()){return true;}

                return false;
                
            }

            istream& NumberWithUnits::check_next_char(istream& is,char c){
                char actual=0; 
                is>>actual; 
                if(!is){return is;} // in case that it couldnt insert the char 

                if(actual!=c){//wrong format
                    is.setstate(ios::failbit);
                }

                return is;//inserted successfully 

            }

            istream& NumberWithUnits::check_type(istream& is,string &new_type){
                string actual;
                string temp;
                
                is>>actual;
                if(actual.at(actual.size()-1)==']'){
                  for(uint i=0;i<actual.size()-1;i++){
                      temp+=actual.at(i);
                  }
                  actual=temp;
                }

                for(const auto & pair : NumberWithUnits::units_list ){
                    if(pair.first==actual){
                        new_type=actual;
                        return is;
                    }
                }

                is.setstate(ios::failbit);//wrong type format 
                throw std::out_of_range{"unknown units type"};
                return is;
            }
            //operators 
             NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& other)const{
                if(!same_family(this->type,other.type)){throw out_of_range{ "Different units type"};}
                return NumberWithUnits(this->value+convert_to_first(this->type,other.type,other.value),this->type);
            }

            NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other){
                if(!same_family(this->type,other.type)){throw out_of_range{ "Different units type"};}
                double temp_val = convert_to_first(this->type,other.type,other.value);
                this->value+=temp_val;
                return *this;
            }

             NumberWithUnits NumberWithUnits::operator+ ()const{
                return (NumberWithUnits(value,type));
            } 

              NumberWithUnits NumberWithUnits::operator- (const NumberWithUnits& other)const{
                if(!same_family(this->type,other.type)){throw out_of_range{ "Different units type"};}
                return NumberWithUnits(this->value-convert_to_first(this->type,other.type,other.value),this->type);
            }

            NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits& other){
                 if(!same_family(this->type,other.type)){throw out_of_range{ "Different units type"};}
                double temp_val = convert_to_first(this->type,other.type,other.value);
                this->value-=temp_val;
                return *this;
            }

              NumberWithUnits NumberWithUnits::operator- ()const{

                return (NumberWithUnits(-this->value,this->type));
            }

            bool NumberWithUnits::operator> (const NumberWithUnits& other)const{
                if(!same_family(this->type,other.type)){throw out_of_range{ "Different units type"};}
                double temp_val = convert_to_first(this->type,other.type,other.value);
               
                return (this->value>temp_val);
                
            } 

            bool NumberWithUnits::operator>= (const NumberWithUnits& other)const{
                if(!same_family(this->type,other.type)){throw out_of_range{ "Different units type"};}
                double temp_val = convert_to_first(this->type,other.type,other.value);
                return (this->value>=temp_val);
            }

            bool NumberWithUnits::operator!= (const NumberWithUnits& other)const{
                return (!(*this==other));
            }

            bool NumberWithUnits::operator<= (const NumberWithUnits& other)const{
                if(!same_family(this->type,other.type)){throw out_of_range{ "Different units type"};}
                double temp_val = convert_to_first(this->type,other.type,other.value);
                return (this->value<=temp_val);
            }  

            bool NumberWithUnits::operator< (const NumberWithUnits& other)const{
                if(!same_family(this->type,other.type)){throw out_of_range{ "Different units type"};}
                double temp_val = convert_to_first(this->type,other.type,other.value);
                return (this->value<temp_val);
            }

            bool NumberWithUnits::operator== (const NumberWithUnits& other)const{
                if(!same_family(this->type,other.type)){throw out_of_range{ "Different units type"};}
                double temp_val = convert_to_first(this->type,other.type,other.value);
            
                return (this->value==temp_val);
            }

           
            

             NumberWithUnits NumberWithUnits::operator*(const double& other)const{
                return NumberWithUnits(other*this->value,this->type);
            }

               NumberWithUnits ariel::operator* (const double& first,const NumberWithUnits& other){

                  return NumberWithUnits(other.value*first,other.type);
                

            }
            

      std::ostream& ariel::operator<< (std::ostream& os,const NumberWithUnits& nwu){
          os<<nwu.value<<'['<<nwu.type<<']';
         return os;
     }

      std::istream& ariel::operator>> (std::istream& is, NumberWithUnits& nwu){
          double new_val=0;
          string new_type;
          ios::pos_type start_position = is.tellg();
          if( !(is>>new_val) 
          || !(NumberWithUnits::check_next_char(is,'['))
          ||!(NumberWithUnits::check_type(is,new_type)) ){
                auto error_state = is.rdstate(); // error 
                is.clear();// clear the error
                is.seekg(start_position);
                is.clear(error_state);
          }
          else{  
              nwu.get_value()=new_val;
              nwu.get_type()=new_type;
          }
         return is;
     }
