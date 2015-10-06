/* Squeeze the manual. */
#include <stdbool.h>
#include "cpdflibwrapper.h"

int main (int argc, char ** argv)
{
  /* Initialise cpdf */
  cpdf_startup(argv);

  /* Clear the error state */
  cpdf_clearError();

  /* We will take the input hello.pdf and repeat it three times */
  int pdf = cpdf_fromFile("cpdflibmanual.pdf", "");

  /* Check the error state */
  if (cpdf_lastError) return 1;

  cpdf_clearError();

  /* Squeeze it */
  cpdf_squeezeInMemory(pdf);
  
  /* Check the error state */
  if (cpdf_lastError) return 1;

  /* Clear the error state */
  cpdf_clearError();

  /* Write output. We make sure to use toFileExt, and make object streams. */
  cpdf_toFileExt(pdf, "squeezed.pdf", false, false, true, true, true);

  /* Check the error state */
  if (cpdf_lastError) return 1;

  return 0;
}
