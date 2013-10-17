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
  toFile(pdf, "testoutputs/out.pdf", false, false);

  printf("Compress it\n");
  compress(pdf);
  toFile(pdf, "testoutputs/compressed.pdf", false, false);
  
  printf("Decompress it\n");
  decompress(pdf);
  toFile(pdf, "testoutputs/decompressed.pdf", false, false);
  
  printf("Make a blank range\n");
  int r = blankrange();
  onexit ();

  printf("Delete a range\n");
  deleterange(r);
  onexit();

  int r2 = blankrange();
  int r3 = range(1, 10);
  int r4 = even(r3);
  int r5 = odd(r3);
  int r6 = range_union(r4, r5);
  int r7 = difference(r6, r4);
  int r8 = removeDuplicates(r7);
  int isinrange = isInRange(r8, 4);
  int allrange = all(pdf);
  int l = rangeLength(r3);
  int l1 = rangeGet(r3, 1);

  printf("Delete the pdf\n");
  deletePdf(pdf);

  printf("One inch is %f points\n", ptOfIn(1.0));
  printf("One centimetre is %f points\n", ptOfCm(1.0));
  printf("One millimetre is %f points\n", ptOfMm(1.0));
  printf("One point is %f inches\n", inOfPt(1.0));
  printf("One point is %f centimetres\n", cmOfPt(1.0));
  printf("One point is %f millimetres\n", mmOfPt(1.0));



  int pdflazy = fromFileLazy("testinputs/hello.pdf");
 
  int blankdoc = blankDocument(100.0, 200.0, 20);
  toFile(blankdoc, "testoutputs/blank.pdf", false, false);

  int blanksized = blankDocumentPaper(a4portrait, 10);
  toFile(blanksized, "testoutputs/blanka4.pdf", false, false);
  
  //int rfrompagespec = parsePagespec(blanksized, "1-2,3-end");
  //printf("Validating pagespec gives %i\n", validatePagespec("1-2,3-end"));

  //printf("There are %i pages in the blank sized pdf\n", pages(blanksized));
 
  //printf("There are %i quick pages in the blank sized pdf\n", pagesFast("", "testoutputs/blanka4.pdf"));

  replacePdf(blankdoc, blanksized);

  onexit();

  printf("*****Tests finished\n");
  return 0;
}
