FFOPTS = -c 
.SUFFIXES: .o .f90

OBJS   = plotf1ofx.o f1ofx.o

#-----------------------------------------------------------------------------------

plot : $(OBJS)
	f95 -o plot $(OBJS)

plotf1ofx.o : plotf1ofx.f90
	f95 $(FFOPTS) plotf1ofx.f90

f1ofx.o : f1ofx.f90
	f95 $(FFOPTS) f1ofx.f90
