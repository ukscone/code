#include "colors.inc"
#include "stones.inc"

camera {
	location <1, 10, -10>
	look_at <0, 0, 0>
}

sphere {
	<0, 3, 0>, 1.5
	pigment {
		color Yellow
	}
}	

plane { y, -1
	pigment {
		checker color Red, color Blue
	}
}



light_source {<-10, 10, -15> color White}
