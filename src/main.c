#include <stdio.h>
#include <string.h>

char *somearray[] = {"Jokster", "jamesbond", "lackingjack"};

int main() {
  for (int i = 0; i < 3; i++) {
    printf("%s", somearray[i]);
  }
  puts("");
  somearray[2] = "packer";
  for (int i = 0; i < 3; i++) {
    printf("%s", somearray[i]);
  }
  return 0;
}