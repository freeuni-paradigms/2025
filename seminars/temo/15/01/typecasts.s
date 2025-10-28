# struct fraction {
#  int numerator;
#  int denominator;
# };

# struct person {
#  int age, id;
#  struct person *next;
# };

# static char Muppets(struct person bert, struct person *ernie) { 
#  struct person **oscar;
#  ((struct fraction *)bert.next)->denominator = 0;
#  ernie = &bert;
#  oscar = &ernie;
#  (**oscar).next = ernie;
#  return bert.age;
# }

# ernie      4  bytes
# bert       12 bytes
# saved pc   4  bytes
muppets:
# struct person **oscar
addi sp, sp, -4

#  ((struct fraction *)bert.next)->denominator = 0;

# load bert.next in x10
lw x10, 16(sp)
addi x10, x10, 4
sw x0, 0(x10)

# ernie = &bert
# load bert address in x10
mv x10, sp
addi x10, x10, 8

# store x10 value to ernie
sw x10, 20(sp)

# oscar = &ernie
# load ernie addres sin x10
mv x10, sp
addi x10, x10, 20

# store x10 in oscar
sw x10, 0(sp)

#  (**oscar).next = ernie;
lw x10, 0(sp)
# *oscar
lw x10, 0(x10)
lw x11, 20(sp)
sw x11, 8(x10)

# load bert.age in x10
lw x10, 8(sp)
addi sp, sp, 4

ret
