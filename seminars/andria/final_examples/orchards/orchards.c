#define ELEM(index, data) ((Orchard *)((char *)data + *((int *)data + index)))

typedef struct {
    short ripeFruit;
    char spoiledFruit;
} Orchard;

typedef int(HarvestFn)(short, char);

short harvest(void *orchardData, int numOrchards, HarvestFn fn) {
    int total = 0;
    for (int i = 0; i < numOrchards; i++) {
        total += fn(ELEM(i, orchardData)->ripeFruit,
                    ELEM(i, orchardData)->spoiledFruit);
    }

    return total;
}