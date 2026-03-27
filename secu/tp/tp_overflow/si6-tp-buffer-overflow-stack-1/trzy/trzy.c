#include <stdio.h>

char *mot_de_passe = "SECRET";

char *nombres[] = {
    "zero", "jeden", "dwa", "trzy", "cztery", "pięć",
};

int main() {
  int i;
  printf("Entrez un nombre.\n");
  scanf("%d", &i);
  printf("%s\n", nombres[i]);
  return 0;
}
