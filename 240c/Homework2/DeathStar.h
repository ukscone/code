#ifndef DeathStar_h
#define DeathStar_h

#include "SphereHouse.h"

class DeathStar : public SphereHouse {

 public:
    DeathStar() : SphereHouse("sith lord") {
        opt1_name = "cover for your exhaust port";
        opt2_name = "functional weapon";
        opt1_cost = 500;
        opt2_cost = 10000000;
        cost_per_area = 25;
    }
    
    virtual std::string serialize();
    virtual int unserialize(std::string data);
    virtual void read(std::istream& in, std::ostream& out);
    virtual void print(std::ostream& out);
 private:
    double tractor_beam_strength;
};
#endif
