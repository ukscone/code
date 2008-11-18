PROGRAM quadratic1
	IMPLICIT NONE
	
	real :: a, b, c
	integer :: n
	OPEN(10, FILE='1a.out', STATUS='REPLACE')
	
	write(*, *) "Input a, b, and c"
	
	a = 1
	b = 1
	c = 1.d-1
	
	DO n = 1, 100
		write(10, *) (-b + sqrt(b**2 - 4*a*c))/(2*a), (-b - sqrt(b**2 - 4*a*c))/(2*a)
		write(10, *) (-2*c)/(b + sqrt(b**2 - 4*a*c)), (-2*c)/(b - sqrt(b**2 - 4*a*c))
		c = c * 1.d-1
	END DO
	
END PROGRAM quadratic1
