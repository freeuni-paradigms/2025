#ifndef PARADIGMS_PACKED_VECTOR_H_
#define PARADIGMS_PACKED_VECTOR_H_

typedef void(*MapFn)(int index, int size, void* elem, void* aux);

typedef struct {
  // IMPLEMENT
} Vector;

// ინიციალიზაცია უნდა გაუეკთოს მოცემულ ვექტორს.
// ვექტორში შესანახი ელემენტების რაოდენობა წინასწარ არის განსაზღვრული n-ით.
void VectorInit(Vector* v, int n);
// უნდა გაათავისუფლოს ვექტორის მიერ გამოყენებული დინამიური მეხსიერება.
void VectorDestroy(Vector* v);
// მოცემულ index ინდექსზე უნდა ჩაწეროს elem_size ზომის (ბაიტებში) ელემენტი
// რომელიც ინახება elem მისამართზე.
void VectorSet(Vector* v, int index, int elem_size, void* elem);
// უკან უნდა დააბრუნოს index ინდექსზე შენახული ელემენტის მისამართი, ხოლო elem_size
// ცვლადში უნდა ჩაწეროს ამ ელემენტის ზომა ბაიტებში.
// თუ მოცემულ ინდექსზე არ არის ელემენტი ჩაწერილი მაშინ elem_size-ში უნდა ჩაწეროს 0,
// ხოლო უკან უნდა დააბრუნოს NULL.
void* VectorGet(Vector* v, int index, int* elem_size);
// ადგილები უნდა გაუცვალოს i და j ინდექსზე მყოფ ელემენტებს.
void VectorSwap(Vector* v, int i, int j);
// ვექტორში შენახული ყველა არანულოვანი ზომის ელემენტისთვის უნდა გამოიძახოს
// გადმოცემული map_fn ფუნქცია, რომელსაც არგუმენტებად უნდა გადასცეს:
// * მიმდინარე ელემენტის ინდექსი
// * ამ ელემენტის ზომა ბაიტებში
// * ამ ელემენტის მნიშვნელობის მისამართი
// * და VectorMap-ისთვის კლიენტის მიერ გადმოცემული aux მნიშვნელობა.
void VectorMap(Vector* v, MapFn map_fn, void* aux);

#endif // PARADIGMS_PACKED_VECTOR_H_
