struct human {
    int doug;
    short emmyjo[2];
};

struct other {
    char *freddie;
    struct human charlie;
    struct human *henrietta;
};

static struct human **AskingQuestions(struct human *heroes);
static struct human **BeginCalm(short *conformity, struct other *gooddeeds)
{
    conformity[*conformity] = 0;                                                // Line 1
    gooddeeds += ((struct human *) (gooddeeds->henrietta[0].emmyjo))->doug;     // Line 2
    return AskingQuestions((struct human *) &gooddeeds);                        // Line 3
}


struct human **AskingQuestions(struct human *heroes) {
    // addi sp, sp, -12
    // lh t1, 8(sp)
    // sw t1, 4(sp)
    // lw t2, 12(sp)
    // BNE t2, 0, endif
    // lw t3, 0(sp)
    // addi t4, t3, 8
    // sw t4, 0(sp)
    // endif:
    // addi a0, sp, 12
    // addi sp, sp, 12
    // ret

    int a, b, c;                            // line 1
    b = (short)c;                           // line 2, 3
    if (heroes->doug == 0)        // line 4
    {
        a += 8;                             // line 5, 6, 7 
    }

    return &heroes;                         // line 8, 9, 10, 11
}

