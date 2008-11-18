#ifndef PolarBearIgloo_h
#define PolarBearIgloo_h

#include "SphereHouse.h"

class PolarBearIgloo : public SphereHouse {

 public:
    PolarBearIgloo() : SphereHouse("polar bear") {
        opt1_name = "seal dispenser";
        opt2_name = "pair of ice skates";
        opt1_cost = 15000;
        opt2_cost = 125;
        cost_per_area = 5;
    }
    
    virtual std::string serialize();
    virtual int unserialize(std::string data);
    virtual void read(std::istream& in, std::ostream& out);
    virtual void print(std::ostream& out);
 private:
    double latitude;
};
#endif
