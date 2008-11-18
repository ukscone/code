#ifndef RectangleHouse_h
#define RectangleHouse_h

#include "TwoOptionHouse.h"

class RectangleHouse : public TwoOptionHouse {

 public:
	RectangleHouse(std::string type) : TwoOptionHouse(type), 
					length(0), width(0), height(0) {}
	
	virtual std::string serialize();
	virtual int unserialize(std::string data);
	virtual void read(std::istream& in, std::ostream& out);
	virtual void print(std::ostream& out);
	
 protected:
	virtual double get_area() {return length*width*height;}
	double length, width, height;
};
#endif
