      program rdecay

!        calculate radiactive decay for a given number of nucleons n0 and
!        a given decay constant lambda as function of time

      implicit none

      double precision :: n0, dt, lambda
      double precision :: ngold(1000), t(1000)
      double precision :: ngoldprint(100), timeprint(100), sec

      integer :: j, tmax, jjmax, isec

      integer :: kwrite

      data kwrite/6/

!        initialize


      n0   = 
      tmax = 
      dt   = 
      lambda = 

      t(1) =0.d0
      ngold(1)=n0
     
!        propagate solution in time

      do j=1,tmax
        ngold(j+1) = ngold(j) - ngold(j)*lambda*dt
      end do 

!        prepare output


      do j=1,tmax
      timeprint(j)  = float(j-1)*dt 
      ngoldprint(j) = ngold(j)
      end do

!        write output

      open (kwrite, File = 'nuclei.out', Status = 'Unknown')

      write (kwrite,*)  'Decay of ',n0,&
     &     ' Nuclei with a decay constant lambda',lambda
      write (kwrite,*) ' Time stip:',dt,' day. tmax: ',tmax 
  
      jjmax=tmax 

      do j=1,jjmax
      write (kwrite,10000) timeprint(j),ngoldprint(j)
      end do     


10000 format(4x,d10.2,4x, d11.5) 

      close(kwrite)

      stop 
      
      end program rdecay
