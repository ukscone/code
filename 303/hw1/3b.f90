PROGRAM power_seriesb
IMPLICIT NONE
	
	double precision :: sum, term, x
	INTEGER n

	OPEN(10, FILE='3b.out', STATUS='REPLACE')

	x = 1.d-1
	WRITE(10, *) "# x                         n                     sum                   (sum - exp(-x))/sum"
	DO
		sum = 1.d0
		term = 1.d0
		n = 1
		
		DO WHILE(DABS(term)/sum > 10.d-8)
			term = ((-1)**n)*(x**n)/Factorial(n)
			sum = sum + term
			n = n + 1
		END DO
		
		WRITE(10, *) x, n, sum, (sum - exp(-x))/sum
		
		x = x * 1.d1
		IF (x > 1.d3) EXIT		
	END DO
	
CONTAINS

	INTEGER FUNCTION Factorial(a)
		IMPLICIT NONE
		INTEGER, INTENT(IN) :: a
		INTEGER :: s
		DO s = a, 1, -1
			Factorial = Factorial * s
		END DO
	END FUNCTION Factorial

END PROGRAM power_seriesb
