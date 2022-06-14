/* Very simple test. Requires a file "hello.pdf" in the parent of the CWD */
#include <stdbool.h>
#include "../cpdflibwrapper.h"

int main (int argc, char ** argv)
{
  /* Initialise cpdf */
  cpdf_startup(argv);

  /* We will take the input hello.pdf and repeat it three times */
  int pdf = cpdf_fromFile("../hello.pdf", "");

  /* Check the error state */
  if (cpdf_lastError) return 1;

  cpdf_replaceDictEntry(pdf, "/Rotate", "{I : 90}");

  /* Clear the error state */
  cpdf_clearError();

  if (cpdf_lastError) return 1;

  cpdf_clearError();

  /* Write output */
  cpdf_toFile(pdf, "rde.pdf", false, false);

  /* Check the error state */
  if (cpdf_lastError) return 1;

  return 0;
}
