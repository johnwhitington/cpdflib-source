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
  
  int rfrompagespec = parsePagespec(blanksized, "1-2,5-end");
  printf("Validating pagespec gives %i\n", validatePagespec("1-2,5-end"));

  printf("There are %i pages in the blank sized pdf\n", pages(blanksized));
 
  printf("There are %i quick pages in the blank sized pdf\n", pagesFast("", "testoutputs/blanka4.pdf"));

  printf("String of pagespec is %s\n", stringOfPagespec(blanksized, rfrompagespec));

  printf("This is documents has isEncrypted = %i\n", isEncrypted(blanksized));

  /* Chapter 9. Multipage facilities */
  printf("Two up\n");
  twoUp(blanksized);
  toFile(blanksized, "testoutputs/twoup.pdf", false, false);
  padAfter(pdflazy, allrange);
  padBefore(pdflazy, allrange);
  toFile(pdflazy, "testoutputs/padded.pdf", false, false);


  /* Chapter 11. Document Information and Metadata */
  int fonts = fromFile("testinputs/london.pdf");
  startGetFontInfo(fonts);
  int numfonts = numberFonts();
  for (int x = 0; x < numfonts; x++)
  {
    printf("Page %i, font %s has type %s and encoding %s\n",
      getFontPage(x),
      getFontName(x),
      getFontType(x),
      getFontEncoding(x));
  };
  endGetFontInfo();

  printf("isLinearized = %i\n", isLinearized("testinputs/london.pdf"));
  printf("pdf version is %i\n", getVersion(fonts));
  printf("pdf title is %s\n", getTitle(fonts));
  printf("pdf author is %s\n", getAuthor(fonts));
  printf("pdf subject is %s\n", getSubject(fonts));
  printf("pdf keywords is %s\n", getKeywords(fonts));
  printf("pdf creator is %s\n", getCreator(fonts));
  printf("pdf producer is %s\n", getProducer(fonts));

  printf("Creation date is %s\n", getCreationDate(fonts));
  
  printf("Modification date is %s\n", getModificationDate(fonts));
 
  printf("Make a date string from components: %s\n",
    dateStringOfComponents(2003, 2, 5, 4, 6, 6, 0, 0));

  int year, month, day, hour, minute, second, hour_offset, minute_offset;
  getDateComponents("D:20061108125017Z", &year, &month, &day, &hour, &minute, &second, &hour_offset, &minute_offset);
  printf("Get the components from a date string D:20061108125017Z = %i, %i, %i, %i, %i, %i, %i, %i\n",
          year, month, day, hour, minute, second, hour_offset, minute_offset);

  setVersion(fonts, 6);
  setTitle(fonts, "Title");
  setAuthor(fonts, "Author");
  setSubject(fonts, "Subject");
  setKeywords(fonts, "Keywords");
  setCreator(fonts, "Creator");
  setProducer(fonts, "Producer");
  markTrapped(fonts);
  markUntrapped(fonts);
  setCreationDate(fonts, "D:20061108125017Z");
  setModificationDate(fonts, "D:20061108125017Z");
  toFile(fonts, "testoutputs/settitleetc.pdf", false, false);

  setPageLayout(fonts, 4);
  setPageMode(fonts, 3);

  printf("Has page one a %s box? %i\n", "/CropBox", hasBox(fonts, 1, "/CropBox")); 
  printf("Has page one a %s box? %i\n", "/BleedBox", hasBox(fonts, 1, "/BleedBox")); 
  printf("Has page one a %s box? %i\n", "/ArtBox", hasBox(fonts, 1, "/ArtBox")); 
  printf("Has page one a %s box? %i\n", "/TrimBox", hasBox(fonts, 1, "/TrimBox")); 

  double minx, maxx, miny, maxy;

  int allbox = all(fonts);

  setMediabox(fonts, allbox, 100, 500, 150, 550);
  setCropBox(fonts, allbox, 100, 500, 150, 550);
  setBleedBox(fonts, allbox, 100, 500, 150, 550);
  setArtBox(fonts, allbox, 100, 500, 150, 550);
  setTrimBox(fonts, allbox, 100, 500, 150, 550);
  
  getMediaBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Media: %f %f %f %f\n", minx, maxx, miny, maxy);
  getCropBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Crop: %f %f %f %f\n", minx, maxx, miny, maxy);
  getBleedBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Bleed: %f %f %f %f\n", minx, maxx, miny, maxy);
  getArtBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Art: %f %f %f %f\n", minx, maxx, miny, maxy);
  getTrimBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Trim: %f %f %f %f\n", minx, maxx, miny, maxy);

  hideToolbar(fonts, true);
  hideMenubar(fonts, true);
  hideWindowUi(fonts, true);
  fitWindow(fonts, true);
  centerWindow(fonts, true);
  displayDocTitle(fonts, true);

  setMetadataFromFile(fonts, "cpdflib.ml");
  toFile(fonts, "testoutputs/metadata1.pdf", false, false);
  setMetadataFromByteArray(fonts, "BYTEARRAY", 9);
  toFile(fonts, "testoutputs/metadata2.pdf", false, false);
  int metadata_length;
  void* metadata = getMetadata(fonts, &metadata_length);
  removeMetadata(fonts);

  /* Chapter 12. File attachments */
  int toattachto = fromFile("testinputs/london.pdf");
  attachFile("cpdflibtest.c", toattachto);
  toFile(toattachto, "testoutputs/withattachment.pdf", false, false);

  startGetAttachments(toattachto);
  int numatt = numberGetAttachments();
  printf("There are %i attachements to get\n", numatt);
  for (int x = 0; x < numatt; x++)
  {
    printf("Attachment %i is named %s\n", x, getAttachmentName(x));
  };
  endGetAttachments();

  removeAttachedFiles(toattachto);
  toFile(toattachto, "testoutputs/removedattachments.pdf", false, false);

  /* Chapter 13. Miscellaneous */
  int london = fromFile("testinputs/london.pdf");
  int all_london = all(london);
  draft(london, all_london, true);
  toFile(london, "testoutputs/draft.pdf", false, false);
  blackText(london, all_london);
  blackFills(london, all_london);
  blackLines(london, all_london);
  toFile(london, "testoutputs/black.pdf", false, false);
  int london2 = fromFile("testinputs/london.pdf");
  thinLines(london2, all_london, 8.0);
  copyId(pdflazy, london2);
  toFile(london2, "testoutputs/thinlines.pdf", false, false);

  /* Page labels */
  addPageLabels(london2, 4, "PREFIX-", 1, all_london);
  toFile(london2, "testoutputs/pagelabels.pdf", false, false);

  replacePdf(blankdoc, blanksized);

  onexit();

  printf("*****Tests finished\n");
  return 0;
}
