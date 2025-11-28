#ifndef PARADIGMS_ROBOTS_COMPETITION_H_
#define PARADIGMS_ROBOTS_COMPETITION_H_

#include <stdbool.h>
#include <pthread.h>

#include "robot.h"

typedef struct {
  // აქ დაამატეთ ცვლადები
} Competition;

// უკეთებს შეჯიბრს ინიციალიზაციას.
void CompetitionInit(Competition* comp);
// უნდა გაუშვას შეჯიბრის მენეჯმენტისთვის მთავარი ნაკადი.
void CompetitionStart(Competition* comp);
// უნდა აკრძალოს შეჯიბრში ახალი მონაწილეების დამატება,
// დაელოდოს უკვე დამატებულ მონაწილეებს შორის გამარჯვებულს,
// და დააბრუნოს იგი.
const Robot* CompetitionStop(Competition* comp);
// აბრუნებს true თუ რობოტი წარმატებით დაემატა შეჯიბრში,
// და false წინააღმდეგ შემთხვევაში.
bool CompetitionAddParticipant(Competition* comp, const Robot* robot);

#endif // PARADIGMS_ROBOTS_COMPETITION_H_
