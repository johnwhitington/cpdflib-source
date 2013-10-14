/* cpdflibtest.c */
/* Uses every function in cpdflibwrapper.h */
#include <stdio.h>
#include "cpdflibwrapper.h"
int main (int argc, char ** argv)
{
  caml_startup(argv);
  int pdf = fromFile("logo.pdf");
  toFile(pdf, "out.pdf", 0, 0);
  return 0;
}
