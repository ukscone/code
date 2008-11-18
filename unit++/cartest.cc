#include <unit++/unit++.h>
#include "car.h"
using namespace std;
using namespace unitpp;
namespace {
  class CarTestSuite : public suite
         {
         void testCarHasMaker() {
         Car myCar;
         assert_eq("maker check", CRASH, myCar.getMaker() );
         //this is a design decicion: default maker is CRASH motor co.
         }
         void testCarHasColor() {
         Car myCar;
         assert_eq("color check", BLUE, myCar.getColor() );
         //another design decision: default color is blue
         }
         void testColorChange() {
         Car myCar;
         //we could do this
         //assert_eq("colorchanged check", BLUE, myCar.getColor() );
         myCar.setColor(GREEN);
         assert_eq("colorchanged check", GREEN, myCar.getColor() );
         }
  public:
         CarTestSuite() : suite("CarTestSuite")
         {
         add("CarHasMaker", testcase(this, "testCarHasMaker", &CarTestSuite::testCarHasMaker));
         add("CarHasColor", testcase(this, "testCarHasColor", &CarTestSuite::testCarHasColor));
         add("ColorChange", testcase(this, "testColorChange", &CarTestSuite::testColorChange));
         suite::main().add("CarTestSuite", this);
         }
  };
  CarTestSuite * theTest = new CarTestSuite();
}
