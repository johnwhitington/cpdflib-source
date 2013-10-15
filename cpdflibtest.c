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

  printf("Clear the error state\n");
  clearError();

  printf("Load from a file\n");
  int pdf = fromFile("testinputs/hello.pdf");
 
  printf("Error number = %i, Error string = %s\n", lastError, lastErrorString);

  printf("Write to a file\n");
  toFile(pdf, "testoutputs/out.pdf", 0, 0);

  printf("Delete the pdf\n");
  deletePdf(pdf);

  printf("One inch is %f points\n", ptOfIn(1.0));
  printf("One centimetre is %f points\n", ptOfCm(1.0));
  printf("One millimetre is %f points\n", ptOfMm(1.0));
  printf("One point is %f inches\n", inOfPt(1.0));
  printf("One point is %f centimetres\n", cmOfPt(1.0));
  printf("One point is %f millimetres\n", mmOfPt(1.0));

  onexit();

  printf("*****Tests finished\n");
  return 0;
}
