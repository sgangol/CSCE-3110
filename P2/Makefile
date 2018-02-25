balancing: balancing.o stack.o
		g++ stack.o balancing.o -o balancing
	
infix: infix.o stack.o
		g++ stack.o infix.o -o infix

postfix: postfix.o stack.o
		g++ stack.o postfix.o -o postfix
		
balancing.o: stack.o balancing.cpp
		g++ -c stack.o balancing.cpp

infix.o: stack.o infix2postfix.cpp
		g++ -c stack.o infix2postfix.cpp
		
postfix.o: stack.o postfixEval.cpp
		g++ -c stack.o postfixEval.cpp

stack.o: stack.cpp stack.hpp
		g++ -c stack.cpp stack.hpp
		
clean: 
		rm -f *.o balancing infix postfix

