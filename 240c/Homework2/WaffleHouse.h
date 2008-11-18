#ifndef WaffleHouse_h
#define WaffleHouse_h

#include "RectangleHouse.h"

class WaffleHouse : public RectangleHouse {

 public:
    WaffleHouse() : RectangleHouse("waffle") {
        opt1_name = "forged OSHA permit";
        opt2_name = "stoned guy in the corner";
        opt1_cost = 2769;
        opt2_cost = 550;
        cost_per_area = 5;
    }
    
    virtual std::string serialize();
    virtual int unserialize(std::string data);
    virtual void read(std::istream& in, std::ostream& out);
    virtual void print(std::ostream& out);
 private:
    int num_employees;
};
#endif
