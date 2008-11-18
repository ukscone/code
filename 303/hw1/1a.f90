PROGRAM onea
IMPLICIT NONE
	double precision x
	OPEN (10, FILE='1a.out', STATUS='REPLACE')
	
	write(10, *) '0 1'
	
	DO x = 1.d-2, 1.d1, 1.d-2
		write(10, *) x, sin(x)/x
	END DO

END PROGRAM onea
