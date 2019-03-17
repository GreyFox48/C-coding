#include <stdio.h>

void
print_scrambled(char *message)
{
  int i = 3;
  do {
    printf("%c", (*message)+i);
  } while (*++message);
  printf("\n");
}

int
main()
{
  char * message = NULL;
  char * msg = "Hello, world.";

  // corrected Matthew Olsen 10/14/2015 
  message = msg;

  print_scrambled(msg);
  print_scrambled(message);

  return 0;
}
