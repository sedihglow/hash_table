main:	 mainTest.c hash_table.c err_handle/err_handle.c get_num/get_num.c
	gcc -Wall -pedantic -Winline -Wextra -g -O2 -m64 mainTest.c hash_table.c err_handle/err_handle.c get_num/get_num.c
