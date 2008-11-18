PROGRAM two
	double precision pi
	double precision x, y, z, phi, r
	
	pi = atan(0.d0)*2.d0
	r = 1
	
	OPEN(10, FILE='2.out', STATUS='REPLACE')
	
	DO phi = -1.6d1, 1.6d1, 5.d-2
		x = r*cos(phi)
		y = r*sin(phi)
		z = dcmplx(x, y)
		WRITE(10, *) phi, x, y, sqrt(z), log(z), atan(y/x)
	END DO
	
END PROGRAM two
