final: sh.o utils.o utils.h ls.o cd.o cat.o mkdir.o rm.o echo.o pwd.o date.o cat mkdir ls rm date
	gcc sh.o -g utils.o  ls.o cd.o cat.o mkdir.o rm.o echo.o pwd.o date.o -o sh -lpthread
cat: catBin.c commands.h cat.o utils.h
	gcc catBin.c cat.o utils.o -o cat
ls: lsBin.c commands.h ls.o
	gcc lsBin.c ls.o -o ls
mkdir: mkdirBin.c commands.h mkdir.o utils.h
	gcc mkdirBin.c mkdir.o utils.o -o mkdir
rm: rmBin.c commands.h rm.o utils.h
	gcc rmBin.c rm.o utils.o -o rm
date: dateBin.c commands.h utils.h date.o
	gcc dateBin.c date.o utils.o -o date
sh.o: sh.c utils.h
	gcc -c sh.c
utils.o: utils.c utils.h commands.h
	gcc -c utils.c
ls.o: ls.c
	gcc -c ls.c
cat.o: cat.c utils.h
	gcc -c cat.c 
cd.o: cd.c
	gcc -c cd.c
mkdir.o: mkdir.c
	gcc -c mkdir.c
rm.o: rm.c utils.h
	gcc -c rm.c utils.c
echo.o: echo.c utils.h
	gcc -c echo.c 
pwd.o: pwd.c
	gcc -c pwd.c
date.o: date.c utils.h
	gcc -c date.c
test: test.c
	gcc test.c -o test
clean:
	rm sh *.o ls mkdir cat date rm *.out test *.gch -v