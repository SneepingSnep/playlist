#include <stdio.h>
#include <stdlib.h>
struct somestruct {
  int data;
  struct somestruct *next;
};
typedef struct somestruct somestruct;
struct somestruct *headpointer;

int structcounter = 0;
somestruct insert(int value, struct somestruct *previousstruct, bool done) {
  somestruct nextstruct = {.data = value};
  if (previousstruct == nullptr) {
    headpointer = &nextstruct;
  } else {
    previousstruct->next = &nextstruct;
  }
  if (done) {
    nextstruct.next = nullptr;
  }
  structcounter++;
  return nextstruct;
}

somestruct *insertvalue(int value, int index) {
  int counter = 0;
  somestruct *nextstruct = malloc(sizeof(somestruct));
  nextstruct->data = value;
  somestruct *adress = headpointer;
  for (int i = 0; i < index; i++) {
    adress = adress->next;
  }
  nextstruct->next = adress->next;
  adress->next = nextstruct;

  return nextstruct;
}

somestruct *insert2(int value, somestruct *previousstruct, bool done) {
  somestruct *nextstruct = malloc(sizeof(somestruct));
  nextstruct->data = value;
  if (previousstruct == nullptr) {
    headpointer = nextstruct;
  } else {
    previousstruct->next = nextstruct;
  }
  if (done) {
    nextstruct->next = nullptr;
  }
  structcounter++;
  return nextstruct;
}

void chancgenode(int index, int value) {
  somestruct *adress = headpointer;
  for (int i = 0; i < index; i++) {
  }
}

void elements() {
  somestruct *adress = headpointer;
  while (adress) {
    printf("%d\n", adress->data);
    adress = adress->next;
  }
}

int main() {
  //   struct somestruct firststruct = insert(19, nullptr, false);
  //   struct somestruct secondstruct = insert(99, &firststruct, false);
  //   struct somestruct thirdstruct = insert(37, &secondstruct, true);
  somestruct *firststruct = insert2(19, nullptr, false);
  somestruct *secondstruct = insert2(99, firststruct, false);
  somestruct *thirdstruct = insert2(37, secondstruct, true);
  somestruct *insertion = insertvalue(2, 1);

  return 0;
}