int 4
long
  32bit - 4 byte
  64bit - 8 byte
long long 8 byte

float  - 4 byte
double - 8 byte

01010010101
2^0 + 2^3 + 2^5 ...

2 byte - first byte positive
         second byte negative
		 
IEEE 754

(-1)^s * 1.xxxxxxx * 2^(127 - exp)
7.0
3.5 * 2^1
-1^0 * 1.75 * 2^2
xxxxx === 75
exp === 2

4 byte - 32 bit
sign  exp   xxxxxx
 1     8     23 
       11    52






smaller size -> larger size -- sign bit extend
larger -> smaller 



int i = 5;
// float f = i;
float f = *(float*)&i;
cout << f << endl;

int*

  00000000 00000000 00000000 00000101
1000      1001     1002    1003


float f = 7.0;
int i = *(int*)&f;
cout << i << endl;



short s = 2^10 + 2^2 + 2^0;
long long i = *(int*)&s;
cout << i << endl;


00000100 00000101 -------- --------

big    endian
little endian



  00000000 00111100 11000011 00000101 - big endian
  00000101 11000011 00111100 00000000 - little
