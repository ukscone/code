#ifndef DogHouse_h
#define DogHouse_h

#include "RectangleHouse.h"

class DogHouse : public RectangleHouse {

 public:
    DogHouse() : RectangleHouse("dog") {
        opt1_name = "pool";
        opt2_name = "mailbox";
        opt1_cost = 1000;
        opt2_cost = 550;
        cost_per_area = 5;
    }
    
    virtual std::string serialize();
    virtual int unserialize(std::string data);
    virtual void read(std::istream& in, std::ostream& out);
    virtual void print(std::ostream& out);
 private:
    std::string roof_type;
};
#endif
