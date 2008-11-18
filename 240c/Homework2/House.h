#ifndef HOUSE_H
#define HOUSE_H

#include <iostream>
#include <string>
#include <sstream>

class House {

 public:
	House(std::string _type) : color("Uninitialized"), type(_type) {}
				
	std::string get_type() 			{return type;}
	double get_cost() 				{return get_area()*cost_per_area + get_option_cost();}
    
    void set_color(std::string _color);

	virtual std::string serialize();
	virtual int unserialize(std::string data);
	virtual void read(std::istream& in, std::ostream& out);
	virtual void print(std::ostream& out);

 protected:
	virtual double get_area() = 0;
	virtual double get_option_cost() = 0;
	bool yntob(std::string input);
	std::string color;
	double cost_per_area;
	
 private:
	std::string type;
};
#endif
