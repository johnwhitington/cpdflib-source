/* Very simple test. Requires a file "hello.pdf" in the CWD */
#include <stdbool.h>
#include "cpdflibwrapper.h"

int main (int argc, char ** argv)
{
  /* Initialist cpdf. */
  cpdf_startup(argv);

  /* Clear the error state */
  cpdf_clearError();

  /* We will take the input hello.pdf and repeat it three times */
  int mergepdf = cpdf_fromFile("hello.pdf", "");

  /* Check the error state */
  if (cpdf_lastError) return 1;

  /* The array of PDFs to merge */
  int pdfs[] = {mergepdf, mergepdf, mergepdf};

  /* Clear the error state */
  cpdf_clearError();

  /* Merge them */
  int merged = cpdf_mergeSimple(pdfs, 3);
  
  /* Check the error state */
  if (cpdf_lastError) return 1;

  /* Clear the error state */
  cpdf_clearError();

  /* Write output */
  cpdf_toFile(merged, "merged.pdf", false, false);

  /* Check the error state */
  if (cpdf_lastError) return 1;

  return 0;
}
