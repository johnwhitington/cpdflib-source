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

  /* Chapter 3. Pages */

  int pages_pdf = fromFile("testinputs/london.pdf");
  int pages_all = all(pages_pdf);
  scalePages(pages_pdf, pages_all, 2.0, 3.0);
  toFile(pages_pdf, "testoutputs/scalePages.pdf", false, false);
  scaleToFit(pages_pdf, pages_all, 400.0, 400.0);
  toFile(pages_pdf, "testoutputs/scaleToFit.pdf", false, false);
  scaleToFitPaper(pages_pdf, pages_all, 4);
  toFile(pages_pdf, "testoutputs/a4.pdf", false, false);
  
  struct position p = {.anchor = topLeft, .coord1 = 20, .coord2 = 20};
  scaleContents(pages_pdf, pages_all, p, 2.0);
  toFile(pages_pdf, "testoutputs/scaleContents.pdf", false, false);
  shiftContents(pages_pdf, pages_all, 200.0, 100.0);
  toFile(pages_pdf, "testoutputs/shiftContents.pdf", false, false);
  rotate(pages_pdf, pages_all, 270);
  toFile(pages_pdf, "testoutputs/rotate.pdf", false, false);
  rotateBy(pages_pdf, pages_all, 90);
  toFile(pages_pdf, "testoutputs/rotateBy.pdf", false, false);
  rotateContents(pages_pdf, pages_all, 25.0);
  toFile(pages_pdf, "testoutputs/rotateContents.pdf", false, false);
  upright(pages_pdf, pages_all);
  hFlip(pages_pdf, pages_all);
  toFile(pages_pdf, "testoutputs/hFlip.pdf", false, false);
  vFlip(pages_pdf, pages_all);
  toFile(pages_pdf, "testoutputs/vFlip.pdf", false, false);

  crop(pages_pdf, pages_all, 0.0, 0.0, 200.0, 200.0);
  toFile(pages_pdf, "testoutputs/cropped.pdf", false, false);
  removeCrop(pages_pdf, pages_all);
  removeTrim(pages_pdf, pages_all);
  removeArt(pages_pdf, pages_all);
  removeBleed(pages_pdf, pages_all);
  toFile(pages_pdf, "testoutputs/uncropped.pdf", false, false);


  /* Chapter 5. Compression */

  printf("Compress it\n");
  compress(pdf);
  toFile(pdf, "testoutputs/compressed.pdf", false, false);
  
  printf("Decompress it\n");
  decompress(pdf);
  toFile(pdf, "testoutputs/decompressed.pdf", false, false);


  /* Chapter 6. Bookmarks */
  int book = fromFile("testinputs/bookmarks.pdf");
  startGetBookmarkInfo(book);
  int num_bookmarks = numberBookmarks();
  for (int x = 0; x < num_bookmarks; x++)
  {
    printf("Bookmark at level %i points to page %i\n", getBookmarkLevel(x), getBookmarkPage(book, x));
  };
  endGetBookmarkInfo();

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

  int r20 = rangeAdd(r3, 15);
  int rl = rangeLength(r20);
  printf("range has length %i\n", rl);
  for (int x = 0; x < rl; x++)
  {
    printf("at position %i the value is %i\n", x, rangeGet(r20, x));
  };

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

  /* Chapter 8. Logos, Watermarks and Stamps */
  int stamp = fromFile("logo.pdf");
  int stampee = fromFile("testinputs/london.pdf");
  stampOn(stamp, stampee, all(stamp));
  stampUnder(stamp, stampee, all(stamp));
  toFile(stamp, "testoutputs/stamp_after.pdf", false, false);
  toFile(stampee, "testoutputs/stampee_after.pdf", false, false);
  int c1 = fromFile("logo.pdf");
  int c2 = fromFile("testinputs/hello.pdf");
  int c3 = combinePages(c1, c2);
  toFile(c3, "testoutputs/c3after.pdf", false, false);

  int textfile = fromFile("testinputs/hello.pdf");
  int textfile_all = all(textfile);
  struct position textpos = {.anchor = topLeft, .coord1 = 20, .coord2 = 20};
  addText(true, textfile, textfile_all, "Some Text~~~~~~~~~~!", textpos, 1.0, 1, 1, 20, 0.5, 0.5, 0.5, false, false, true, 0.5, 0, false, "");
  addText(true, textfile, textfile_all, "Some Text~~~~~~~~~~!", textpos, 1.0, 1, 1, 20, 0.5, 0.5, 0.5, false, false, true, 0.5, 0, false, "");
  toFile(textfile, "testoutputs/added_text.pdf", false, false);

  int bits = addTextHowMany();
  printf("There are %i text bits to iterate over\n", bits);
  for (int x = 1; x <= bits; x++)
  {
    printf("Text is %s, x is %f, y is %f, rotation = %f, baseline = %f\n",
      addTextReturnText(x),
      addTextReturnX(x),
      addTextReturnY(x),
      addTextReturnRotation(x),
      addTextReturnBaselineAdjustment());
  };


  removeText(textfile, textfile_all);
  toFile(textfile, "testoutputs/removed_text.pdf", false, false);
  int w = textWidth(1, "Some Text");
  printf("The textwidth is %i\n", w);

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
