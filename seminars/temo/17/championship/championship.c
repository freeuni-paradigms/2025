#include "championship.h"

int FindWinner(void* d) {
  char *c = (char *)d;

  int scores[10] = {0};

  while (*c) {
    char byte = *c;
    
    unsigned char winner = byte & 0b11000000;
    unsigned char first = byte & 0b00111000;
    unsigned char second = byte & 0b00000111;

    first = first >> 3;

    if (winner == 0) {
      scores[first] += 1;
      scores[second] += 1;
    } else if (winner == 0b10000000) {
      scores[second] += 3;
    } else {
      scores[first] += 3;
    }
    c++;
  }

  int winner_final = 0;
  
  for (int i = 1; i < 10; i++) {
    if (scores[i] > scores[winner_final]) {
      winner_final = i;
    }
  }

  return winner_final;
}
