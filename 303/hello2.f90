      program Hello
!
      implicit none

      real :: first, second, average
!        
!        talk to the computer
!
      write (6,*) 'Hello, world'

      read (5,*) first
      read (5,*) second

      average = (first+second)*0.5

      write (6,*) average

      stop 
      end 
