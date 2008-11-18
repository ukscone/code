#ifndef TwoOptionHouse_h
#define TwoOptionHouse_h

#include "House.h"

class TwoOptionHouse : public House {

 public:
    TwoOptionHouse(std::string type) :
                        House(type), name("Uninitialized"), opt1(false), opt2(false) {}
    
    void set_name(std::string _name);
    std::string get_name() {return name;}
    
    virtual std::string serialize();
	virtual int unserialize(std::string data);
	virtual void read(std::istream& in, std::ostream& out);
	virtual void print(std::ostream& out);
	
 protected:
    virtual double get_option_cost() {return opt1*opt1_cost + opt2*opt2_cost;}
    std::string btoyn(bool val);
 
    std::string name;
    std::string opt1_name;
    std::string opt2_name;
    bool opt1;
    bool opt2;
    double opt1_cost;
    double opt2_cost;
};
#endif
