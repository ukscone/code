      program plotf1ofx
!
!       plot function given in as f1ofx
!
      implicit none

      double precision :: x, deltax, xa, xb
      double precision :: f1ofx
      double precision :: xx(50), fxx(50)
      double precision :: dnumber
      integer :: i

      integer :: kread, kwrite

      data kread/5/, kwrite/6/
!
      deltax = 0.1d0 
      xa = 0.0d0
      xb = 2.0d0

      xx(0) = xa
      fxx(0) = f1ofx(xa)

      do i=1,20
        xx(i) = xa + i * deltax
        fxx(i) = f1ofx(xx(i))
      end do

      write (kwrite,*) 'plot output from f1ofx, with 20 points.'
      do i=0,20
        write (kwrite,10000) xx(i),fxx(i)
      end do

10000 format (1x,f6.3,2x,d14.6)
  
      stop 
      end 
