carttest: shopping_cart.o node.o main.o
	g++ -Wall -g shopping_cart.o node.o main.o -o carttest
	
main.o: main.cc shopping_cart.h
	g++ -Wall -g -c main.cc -o main.o
	
node.o: node.cc node.h
	g++ -Wall -g -c node.cc -o node.o
	
shoppingcart.o: shopping_cart.cc shopping_cart.h
	g++ -Wall -g -c shopping_cart.cc -o shoppingcart.o

clean:
	rm -f *.o
	
cleanall: clean
	rm carttest
