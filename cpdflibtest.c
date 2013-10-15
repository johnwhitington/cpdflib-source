/* cpdflibtest.c */
/* Uses every function in cpdflibwrapper.h */
#include <stdio.h>
#include <stdbool.h>
#include "cpdflibwrapper.h"
int main (int argc, char ** argv)
{
  setbuf(stdout, NULL);

  printf("Set up OCaml runtime\n");
  caml_startup(argv);

  printf("Set demo mode for commercial programs\n");
  setdemo(false);

  printf("Load from a file\n");
  int pdf = fromFile("logo.pdf");

  printf("Write to a file\n");
  toFile(pdf, "out.pdf", 0, 0);

  printf("*****Tests finished\n");
  return 0;
}
