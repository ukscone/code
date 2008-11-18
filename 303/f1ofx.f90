      double precision function f1ofx (x)
!
!       function cos x - x
!
      implicit none

      double precision :: x
      double precision :: f1ofx

      f1ofx = cos (x) - x
     
      return  
      end 
