      program diff

!        calculate forward, central, and extrapolated differentiation
!        of a given function

      implicit none

      real :: fcos, fexp, fsq, fdsq, h, hd2, hd4, xmin, xmax, xstep
      real :: result(3)
      real :: xs(3)
      integer :: kwritecos, kwriteexp, kwritesq, x

      data kwritecos/6/, kwriteexp/7/, kwritesq/8/

      open(kwritecos, File = 'diffcos.out', Status = 'REPLACE')
      open(kwriteexp, File = 'diffexp.out', Status = 'REPLACE')
      open(kwritesq, File = 'diffsq.out', Status = 'REPLACE')
      
      xs(1) = 1.d-1
      xs(2) = 1.d0
      xs(3) = 3.d1
      
      write (kwritecos, *) "#x, h, forward, central, extrapolated, e(forward), e(central), e(extrapolated)"
	  write (kwriteexp, *) "#x, h, forward, central, extrapolated, e(forward), e(central), e(extrapolated)"
	  write (kwritesq, *) "#x, h, forward, central, extrapolated, e(forward), e(central), e(extrapolated)"
	  
      do x = 1, 3
		  h = 1
	      do while (h > 1.d-6)

		      hd2 = h*0.5d0
		      hd4 = h*0.25d0
			  
			  result(1) = (fcos(xs(x)+h) - fcos(xs(x)))/h
			  result(2) = (fcos(xs(x)+hd2) - fcos(xs(x)-hd2))/h
			  result(3) = (8.d0 *(fcos(xs(x)+hd4)-fcos(xs(x)-hd4)) - &
			 &                 (fcos(xs(x)+hd2)-fcos(xs(x)-hd2)))/(3.d0*h)
			 
			  write (kwritecos,*) xs(x), h, result(1), result(2), result(3), &
			 & abs(result(1) - sin(xs(x)))/sin(xs(x)), abs(result(2) - sin(xs(x)))/sin(xs(x)), &
			 & abs(result(3) - sin(xs(x)))/sin(xs(x))
			 
			  result(1) = (fexp(xs(x)+h) - fexp(xs(x)))/h
			  result(2) = (fexp(xs(x)+hd2) - fexp(xs(x)-hd2))/h
			  result(3) = (8.d0 *(fexp(xs(x)+hd4)-fexp(xs(x)-hd4)) - &
			 &                 (fexp(xs(x)+hd2)-fexp(xs(x)-hd2)))/(3.d0*h)
			 
			  write (kwriteexp, *) xs(x), h, result(1), result(2), result(3), &
			 & abs(result(1) - exp(xs(x)))/exp(xs(x)), abs(result(2) - exp(xs(x)))/exp(xs(x)), &
			 & abs(result(3) - exp(xs(x)))/exp(xs(x))

			  result(1) = (fsq(xs(x)+h) - fsq(xs(x)))/h
			  result(2) = (fsq(xs(x)+hd2) - fsq(xs(x)-hd2))/h
			  result(3) = (8.d0 *(fsq(xs(x)+hd4)-fsq(xs(x)-hd4)) - &
			 &                 (fsq(xs(x)+hd2)-fsq(xs(x)-hd2)))/(3.d0*h)

			  write (kwritesq,*) xs(x), h, result(1), result(2), result(3), &
			 & abs(result(1) - fdsq(xs(x)))/fdsq(xs(x)), abs(result(2) - fdsq(xs(x)))/fdsq(xs(x)), &
			 & abs(result(3) - fdsq(xs(x)))/fdsq(xs(x))
		      
		      h = h * 1.d-1
		  	  if (h < 1.d-5) EXIT
	      end do  
	            end do

      close(kwritecos)
      close(kwriteexp)
      close(kwritesq)

      stop 'data saved in diffcos.out, diffexp.out, and diffsq.out'
      
      end program diff
!--------------------------------------------------------------------------

      real function fcos(x)

      implicit none

      real ::  x

      fcos = cos(x)

      return
      end
!--------------------------------------------------------------------------

      real function fexp(x)

      implicit none

      real ::  x

      fexp = exp(x)

      return
      end
!--------------------------------------------------------------------------

      real function fsq(x)

      implicit none

      real ::  x

      fsq = sqrt(x)

      return
      end!--------------------------------------------------------------------------

	  real function fdsq(x)
	  
	  implicit none
	  
	  real :: x
	  
	  fdsq = 5.d-1 / sqrt(x)
	  
	  return 
	  end
