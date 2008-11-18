#ifndef BeaverDam_h
#define BeaverDam_h

#include "RectangleHouse.h"

class BeaverDam : public RectangleHouse {

 public:
    BeaverDam() : RectangleHouse("beaver") {
        opt1_name = "yacht";
        opt2_name = "snorkel";
        opt1_cost = 5000;
        opt2_cost = 50;
        cost_per_area = 3.5;
    }
    
    virtual std::string serialize();
    virtual int unserialize(std::string data);
    virtual void read(std::istream& in, std::ostream& out);
    virtual void print(std::ostream& out);
 private:
    std::string wood_type;
};
#endif
