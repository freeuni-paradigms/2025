import collections
import sys
import subprocess


MAIN = """
.data
.LC0:
        .string "[TEST #1] StructSum( 0, fill_with_threes)  test_result="
        .string ""
.LC1:
        .string "[TEST #2] StructSum( 2, fill_with_threes)  test_result="
        .string ""
.LC2:
        .string "[TEST #3] StructSum(-2, fill_with_threes)  test_result="
        .string ""
.LC3:
        .string "[TEST #4] StructSum( 0, fill_with_2pows)   test_result="
        .string ""
.LC4:
        .string "[TEST #5] StructSum( 2, fill_with_2pows)   test_result="
        .string ""
.LC5:
        .string "[TEST #6] StructSum(-2, fill_with_2pows)   test_result="
        .string ""
.LC6:
        .word 84082944

.text
# CALLS MAIN FUNCTION; DO NOT REMOVE
call main

populate_threes:
	lw x13, 0(sp)
	lw x10, 4(sp)
	addi x11, x13, 3
	la x15, .LC6
	lb x17, 0(x15)
	add x16, x10, x17
	sb x11, 0(x16)
	lb x17, 1(x15)
	add x16, x10, x17
	sh x11, 0(x16)
	lb x17, 2(x15)
	add x16, x10, x17
	sh x11, 0(x16)
	lb x17, 3(x15)
	add x16, x10, x17
	sw x11, 0(x16)
	li x3, 0
	li x4, 0
	li x5, 0
	li x6, 0
	li x7, 0
	li x8, 0
	li x9, 0
	li x10, 0
	li x11, 0
	li x12, 0
	li x13, 0
	li x14, 0
	li x15, 0
	li x16, 0
	li x17, 0
	li x18, 0
	li x19, 0
	li x20, 0
	li x21, 0
	li x22, 0
	li x23, 0
	li x24, 0
	li x25, 0
	li x26, 0
	li x27, 0
	li x28, 0
	li x29, 0
	li x30, 0
	li x31, 0
	ret

populate_2pows:
	lw x13, 0(sp)
	lw x10, 4(sp)
	addi x11, x13, 2
	la x15, .LC6
	lb x17, 0(x15)
	add x16, x10, x17
	sb x11, 0(x16)
	addi x11, x13, 4
	lb x17, 1(x15)
	add x16, x10, x17
	sh x11, 0(x16)
	addi x11, x13, 8
	lb x17, 2(x15)
	add x16, x10, x17
	sh x11, 0(x16)
	addi x11, x13, 16
	lb x17, 3(x15)
	add x16, x10, x17
	sw x11, 0(x16)
	li x3, 0
	li x4, 0
	li x5, 0
	li x6, 0
	li x7, 0
	li x8, 0
	li x9, 0
	li x10, 0
	li x11, 0
	li x12, 0
	li x13, 0
	li x14, 0
	li x15, 0
	li x16, 0
	li x17, 0
	li x18, 0
	li x19, 0
	li x20, 0
	li x21, 0
	li x22, 0
	li x23, 0
	li x24, 0
	li x25, 0
	li x26, 0
	li x27, 0
	li x28, 0
	li x29, 0
	li x30, 0
	li x31, 0
	ret

main:
"""

CALL_1 = """
        addi    sp,sp,-64
        sw      ra,60(sp)
        sw      s0,56(sp)
        addi    s0,sp,64
        sw      a0,-52(s0)
        sw      a1,-56(s0)

        la    a1, populate_threes
        li      a0,0
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-20(s0)
        la    a5, .LC0
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-20(s0)
        addi    a5,a5,-15
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall

        li      a5,0
        mv      a0,a5
        lw      ra,60(sp)
        lw      s0,56(sp)
        addi    sp,sp,64
		  li a0, 10
		  ecall
        jr      ra
"""


CALL_2 = """
        addi    sp,sp,-64
        sw      ra,60(sp)
        sw      s0,56(sp)
        addi    s0,sp,64
        sw      a0,-52(s0)
        sw      a1,-56(s0)

        la    a1, populate_threes
        li      a0,2
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-24(s0)
        la    a5, .LC1
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-24(s0)
        addi    a5,a5,-25
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall

        li      a5,0
        mv      a0,a5
        lw      ra,60(sp)
        lw      s0,56(sp)
        addi    sp,sp,64
		  li a0, 10
		  ecall
        jr      ra
"""


CALL_3 = """
        addi    sp,sp,-64
        sw      ra,60(sp)
        sw      s0,56(sp)
        addi    s0,sp,64
        sw      a0,-52(s0)
        sw      a1,-56(s0)

        la    a1, populate_threes
        li      a0,-2
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-28(s0)
        la    a5, .LC2
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-28(s0)
        addi    a5,a5,-5
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall

        li      a5,0
        mv      a0,a5
        lw      ra,60(sp)
        lw      s0,56(sp)
        addi    sp,sp,64
		  li a0, 10
		  ecall
        jr      ra
"""


CALL_4 = """
        addi    sp,sp,-64
        sw      ra,60(sp)
        sw      s0,56(sp)
        addi    s0,sp,64
        sw      a0,-52(s0)
        sw      a1,-56(s0)

        la    a1, populate_2pows
        li      a0,0
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-32(s0)
        la    a5, .LC3
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-32(s0)
        addi    a5,a5,-34
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall

        li      a5,0
        mv      a0,a5
        lw      ra,60(sp)
        lw      s0,56(sp)
        addi    sp,sp,64
		  li a0, 10
		  ecall
        jr      ra
"""


CALL_5 = """
        addi    sp,sp,-64
        sw      ra,60(sp)
        sw      s0,56(sp)
        addi    s0,sp,64
        sw      a0,-52(s0)
        sw      a1,-56(s0)

	    la    a1, populate_2pows
        li      a0,2
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-36(s0)
        la    a5, .LC4
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-36(s0)
        addi    a5,a5,-44
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall

        li      a5,0
        mv      a0,a5
        lw      ra,60(sp)
        lw      s0,56(sp)
        addi    sp,sp,64
		  li a0, 10
		  ecall
        jr      ra
"""


CALL_6 = """
        addi    sp,sp,-64
        sw      ra,60(sp)
        sw      s0,56(sp)
        addi    s0,sp,64
        sw      a0,-52(s0)
        sw      a1,-56(s0)

	    la    a1, populate_2pows
        li      a0,-2
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-40(s0)
        la    a5, .LC5
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-40(s0)
        addi    a5,a5,-24
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall

        li      a5,0
        mv      a0,a5
        lw      ra,60(sp)
        lw      s0,56(sp)
        addi    sp,sp,64
		  li a0, 10
		  ecall
        jr      ra
"""


def RunTest(sol, call):
    with open("run.s", "w") as out:
        out.write(MAIN)
        out.write(call)
        out.write(sol)
    p = subprocess.run(
        ["java", "-jar", "/venus/venus.jar", "run.s"],
        capture_output=True,
    )
    if p.returncode != 0:
        print("crash")
        return 2
    out = p.stdout.decode("ASCII").rstrip()
    print(out)
    if out.endswith("test_result=1"):
        return 0
    elif out.endswith("test_result=0"):
        return 1
    else:
        return 2

def Test_1(sol):
    return RunTest(sol, CALL_1)


def Test_2(sol):
    return RunTest(sol, CALL_2)


def Test_3(sol):
    return RunTest(sol, CALL_3)


def Test_4(sol):
    return RunTest(sol, CALL_4)


def Test_5(sol):
    return RunTest(sol, CALL_5)


def Test_6(sol):
    return RunTest(sol, CALL_6)


TESTS = [
    Test_1,
    Test_2,
    Test_3,
    Test_4,
    Test_5,
    Test_6,
]


def Run(sol, test_funcs):
    tests = {fn.__name__: fn for fn in test_funcs}
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("-lt", "--list_tests", action="store_true")
    parser.add_argument("-rt", "--run_test", choices=tests.keys(), action="store")
    parser.add_argument("-cof", "--crash_on_failure", action="store_true")
    parser.add_argument("-rf", "--results_file", action="store", type=argparse.FileType("r"))
    args = parser.parse_args()
    if args.list_tests:
        for test in tests.keys():
            print(test)
        return
    if args.run_test:
        print(args.run_test)
        sys.exit(tests[args.run_test](sol))
    elif args.results_file:
        CalculateScore(args.results_file)
        return
    sys.exit(5)


def CalculateScore(inp):
    Result = collections.namedtuple("Result", ["name", "succeeded", "memory"])
    tests = []
    for l in inp.readlines():
        items = l.split()
        tests.append(Result(items[0], int(items[1]), int(items[2])))
    num_tests = len(tests)
    num_succeeded = 0
    for t in tests:
        num_succeeded += t.succeeded
    print(1.0 * num_succeeded / num_tests)


def GetSol():
    with open("struct_sum.s", "r") as inp:
        in_sol = False
        sol = ""
        for l in inp.readlines():
            if l.startswith("##### YOUR CODE STARTS HERE ######"):
                in_sol = True
                continue
            elif l.startswith("### TEST CODE BELOW ###"):
                return sol
            elif in_sol:
                sol += l
    sys.exit(3)


def main():
    Run(GetSol(), TESTS)


if __name__ == "__main__":
    main()
