PROGRAM sumseries
	IMPLICIT NONE
	real :: sum1, sum2, sum3
	integer :: n, maxn
	
	OPEN(10, FILE='2.out', STATUS='REPLACE')
	
	maxn = 1
	
	DO
		sum1 = 0
		sum2 = 0
		sum3 = 0
		
		DO n = 1, 2*maxn
			sum1 = sum1 + ((-1.)**n)*n/(n + 1.)
		END DO
		
		DO n = 1, maxn
			sum2 = sum2 - (2.*n - 1.)/(2.*n) + 2.*n/(2.*n + 1.)
		END DO
		
		DO n = 1, maxn
			sum3 = sum3 + 1./(2.*n*(2.*n + 1.))
		END DO
		
		WRITE(10, *) log10(real(maxn)), log10(abs((sum1 - sum3)/sum3))
		
		maxn = maxn * 2
		IF (maxn > 1.d6) EXIT
	END DO

END PROGRAM sumseries
