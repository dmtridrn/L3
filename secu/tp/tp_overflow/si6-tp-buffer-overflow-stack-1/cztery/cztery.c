#include <stdio.h>

void print_password(void) {
  printf("%s\n", "SECRET");
}

void read_name() {
  char buf[32];
  scanf("%s", buf);
}

int main() {
  printf("Entrez votre nom :\n");
  read_name();
  return 0;
}

