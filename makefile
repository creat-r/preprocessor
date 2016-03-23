out:main.o comment.o include.o
	cc -Wall -g  main.o comment.o include.o -o out

main.o:main.c
	cc -Wall -c -g main.c
comment.o:comment.c
	cc -Wall -c -g comment.c
include.o:include.c
	cc -Wall -c -g include.c
