PROGRAM power_series
IMPLICIT NONE
	double precision :: sum, term, n, x

	OPEN(10, FILE='3a.out', STATUS='REPLACE')

	x = 1.d-1
	WRITE(10, *) "# x                         n                     sum                   (sum - exp(-x))/sum"
	DO
		sum = 1.d0
		term = 1.d0
		n = 1.d0
		
		DO WHILE(DABS(term)/sum > 10.d-8)
			term = -term * x/n
			sum = sum + term
			n = n + 1
		END DO
		
		WRITE(10, *) x, n, sum, (sum - exp(-x))/sum
		
		x = x * 1.d1
		IF (x > 1.d3) EXIT		
	END DO


END PROGRAM power_series
