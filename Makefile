TRGDIR=./
OBJ=./obj
FLAGS= -Wall -pedantic -std=c++17 -iquote inc


__START__: ${OBJ} ${OBJ}/main.o ${OBJ}/Plansza.o ${OBJ}/Gracz.o 
	g++ -o ${TRGDIR}/gra ${OBJ}/main.o ${OBJ}/Plansza.o ${OBJ}/Gracz.o 

${OBJ}:	
	mkdir ${OBJ}

${OBJ}/main.o: src/main.cpp inc/Plansza.hh inc/Gracz.hh
	g++ -c ${FLAGS} -o ${OBJ}/main.o src/main.cpp

${OBJ}/Plansza.o:inc/Plansza.hh src/Plansza.cpp
	g++ -c ${FLAGS} -o ${OBJ}/Plansza.o src/Plansza.cpp

${OBJ}/Gracz.o:inc/Gracz.hh src/Gracz.cpp inc/Plansza.hh
	g++ -c ${FLAGS} -o ${OBJ}/Gracz.o src/Gracz.cpp
