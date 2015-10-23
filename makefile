main:	 mainTest.c hash_table.c err_handle/err_handle.c get_num/get_num.c
	gcc -Wall -pedantic -Winline -Wextra -g -O0 -m64 mainTest.c hash_table.c err_handle/err_handle.c get_num/get_num.c
