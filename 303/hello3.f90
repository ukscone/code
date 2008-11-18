      program Hello
!
!       with good programming habits
!
      implicit none

      real :: first, second, average
      integer :: kread, kwrite

      data kread/5/, kwrite/6/
!        
!        talk to the computer
!
      write (kwrite,*) 'Hello, world'

      write (kwrite,*) 'Input first variable:'
      read (kread,*) first
      write (kwrite,*) 'first variable:', first


      write (kwrite,*) 'Input second variable:'
      read (kread,*) second
      write (kwrite,*) 'second variable:', second

      average = (first+second)*0.5

      write (kwrite,*) 'average of first and second variable is:', average

      stop 
      end 
