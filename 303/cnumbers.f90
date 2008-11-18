      program cnumbers
!
!        explore complex numbers 
!
      implicit none

      integer :: nphi, ii 
      integer :: kread, kwrite

      double precision :: pi
      double precision :: xx,yy,r,phi
      double complex   ::  zz,lnzz

      data kread/5/, kwrite/6/

!        calculate pi

      pi = acos(0.d0)*2.d0

      write (kwrite,*) pi

      r=1.d0

      write (kwrite,*) 'complex numbers for r=1'

      do ii=-16,16,1

		  phi=float(ii)*0.25d0*pi

		  xx=r*cos(phi)
		  yy=r*sin(phi)

		  zz=dcmplx(xx,yy)
		  lnzz=log(zz)

		  write (kwrite,10000) ii,phi,xx,yy,lnzz

      end do

10000 format(i3,1x,3f8.4,1x,2f8.4)


      stop 
      end
