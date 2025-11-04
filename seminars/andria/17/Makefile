all: sum3 compress

sum3: tests_sum_3bit.c sum_3bit.c sum_3bit.h
	gcc -o sum_3bit tests_sum_3bit.c sum_3bit.c
	./sum_3bit

compress: tests_compress.c compress.c compress.h
	gcc -o compress tests_compress.c compress.c
	./compress
