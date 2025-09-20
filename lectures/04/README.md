https://excalidraw.com/#json=766J-vAhiT5ZwjhPbdpfd,I4ted0vQUGw9cogSQSZDVw

struct fraction {
	int num;
	int denum;
};

Activation Record
8 byte = 4 + 4
num - 0 offset
denum - 4 offset


fraction f;
f.num = 22;
f.denum = 7;

((fraction*)&(f.denum))->num = 12;
((fraction*)&(f.denum))->denum = 20;

// ((fraction)(f.denum))->num = 12;


// arrays

int a[10];
a[0] = 1;
a[1] = 10;
a[9] = 15;
a[10] = 100;
a[-4] = 200;

a === &a[0]
&a[k] === a + k === address of a + k * sizeof(elem type)

*(a+k) === a[k] // syntactic sugar


// array of structs

struct Student {
  char* name;
  char id[8];
  int num_units;
};

Student s[4];
s[0].num_units = 21;
s[2].name = strdup("ABCD"); // heap
s[2].name[2] C
// zero character \0 --> 0 "0"
s[3].name = s[0].id + 6;




strcpy(dst, src);

strcpy(s[1].id, "40415xx");
strcpy(s[3].name, "1234567");



//

int x = 5;
int y = 7;
swap(&x, &y);


