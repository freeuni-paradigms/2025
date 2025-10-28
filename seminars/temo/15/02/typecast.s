# struct fraction {
#  int numerator;   0
#  int denominator; 4
# };

# struct person {
#  int age, id;           age - 0, id - 4
#  struct person *next;   next - 8
# };

# static char Muppets(struct person bert, struct person *ernie) {
#  struct person **oscar;
#  ((struct fraction *)bert.next)->denominator = 0;
#  ernie = &bert;
#  oscar = &ernie;
#  (**oscar).next = ernie;
#  return bert.age;
# }

# person *ernie | 4  bytes  20
# person bert   | 12 bytes  8
# saved pc      | 4  bytes  4
muppets:
#  struct person **oscar;   0
addi sp, sp, -4

#  ((struct fraction *)bert.next)->denominator = 0;
#  load bert.next in x10
lw x10, 16(sp)

sw x0, 4(x10)


# ernie = &bert
# load bert address in x10
addi x10, sp, 8
# store x10 in ernie
sw x10, 20(sp)

# oscar = &ernie
addi x10, sp, 20
# store x10 in oscar
sw x10, 0(sp)

#  (**oscar).next = ernie;
# load oscar in x10
lw x10, 0(sp)
# load *oscar in x10
lw x10, 0(x10) # x10 = oscar *
# load ernie in x11
lw x11, 20(sp)
# store ernie in x10
sw x11, 8(x10)

#  return bert.age;
# load bert.age in x10
lb x10, 8(sp)

# shrink stack

addi sp, sp, 4

ret
