#ifndef SphereHouse_h
#define SphereHouse_h

#include "TwoOptionHouse.h"

#define PI 3.14

class SphereHouse : public TwoOptionHouse {

 public:
	SphereHouse(std::string type) : TwoOptionHouse(type), 
					radius(0), theta(0), phi(0) {}
	
	virtual std::string serialize();
	virtual int unserialize(std::string data);
	virtual void read(std::istream& in, std::ostream& out);
	virtual void print(std::ostream& out);
	
 protected:
	virtual double get_area() 
	    {return 4.0*PI*radius*radius*radius*(theta/360)*(phi/360)/3.0;}
	double radius;
	double theta, phi;
};
#endif
