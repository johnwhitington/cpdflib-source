/* cpdflibtest.c */
/* Uses every function in cpdflibwrapper.h */
#include <stdio.h>
#include <stdbool.h>
#include "cpdflibwrapper.h"
int main (int argc, char ** argv)
{
  /* 0. Initialization */
  printf("***** 0. Initialisation\n\n");

  printf("caml_startup()\n");
  caml_startup(argv);

  printf("setdemo()\n");
  setdemo(false);

  printf("clearError()\n");
  clearError();

  onexit();
  /* 1. Reading and writing files */
  printf("\n***** 1. Reading and writing files\n\n");

  printf("fromFile()\n");
  int pdf = fromFile("testinputs/hello.pdf");

  printf("Afterwards, Error number = %i, Error string = %s\n", lastError, lastErrorString);

  printf("toFile()\n");
  toFile(pdf, "testoutputs/out.pdf", false, false);

  printf("toFileEncrypted()\n");
  int permissions = {noEdit};
  int encmethod = pdf40bit;
  toFileEncrypted(pdf, encmethod, &permissions, 1, "owner", "user", false, false, "testoutputs/encrypted.pdf");

  int pdfenc = fromFile("testoutputs/encrypted.pdf");

  printf("hasPermission()\n");
  printf("Haspermission %i, %i\n", hasPermission(pdf, noEdit), hasPermission(pdf, noCopy)); //Fails

  printf("encryptionKind()\n");
  printf("encryption kind is %i\n", encryptionKind(pdfenc));

  printf("decryptPdf\n");
  decryptPdf(pdfenc, "user");

  printf("toFileRecrypting()\n");
  int pdfenc2 = fromFile("testoutputs/encrypted.pdf");
  toFileRecrypting(pdfenc2, pdfenc, "user", "testoutputs/recrypted.pdf");

  printf("decryptPdfOwner()\n");
  int pdfenc3 = fromFile("testoutputs/encrypted.pdf");
  decryptPdfOwner(pdfenc3, "owner");

  deletePdf(pdf);
  deletePdf(pdfenc);
  deletePdf(pdfenc2);
  deletePdf(pdfenc3);

  onexit();
  /* Chapter 2. Merging */
  printf("\n***** 2. Merging\n\n");

  int mergepdf = fromFile("testinputs/hello.pdf");
  printf("Merging files\n");
  int pdfs[] = {mergepdf, mergepdf, mergepdf};
  printf("mergeSimple()\n");
  int merged = mergeSimple(pdfs, 3);
  toFile(merged, "testoutputs/merged.pdf", false, false);
  printf("merge()\n");
  int merged2 = merge(pdfs, 3, false, false);
  toFile(merged2, "testoutputs/merged2.pdf", false, false);

  int a = all(mergepdf);
  int b = all(mergepdf);
  int c = all(mergepdf);
  int ranges[] = {a, b, c};
  printf("mergeSame()\n");
  int merged3 = mergeSame(pdfs, 3, false, false, ranges);
  toFile(merged3, "testoutputs/merged3.pdf", false, false);

  int many = fromFile("testinputs/bookmarks.pdf");
  printf("blankrange()\n");
  int manyrange = blankrange();
  printf("rangeAdd()\n");
  int added = rangeAdd(manyrange, 1);

  printf("selectPages()\n");
  int selected = selectPages(many, added);
  toFile(selected, "testoutputs/selected.pdf", false, false);

  deletePdf(mergepdf);
  deletePdf(merged);
  deletePdf(merged2);
  deletePdf(merged3);
  deletePdf(many);
  deletePdf(selected);

  deleterange(a);
  deleterange(b);
  deleterange(c);
  deleterange(manyrange);
  deleterange(added);


  onexit();
  /* Chapter 3. Pages */
  printf("\n***** 3. Pages\n\n");

  int pages_pdf = fromFile("testinputs/london.pdf");
  int pages_all = all(pages_pdf);
  printf("scalePages()\n");
  scalePages(pages_pdf, pages_all, 2.0, 3.0);
  toFile(pages_pdf, "testoutputs/scalePages.pdf", false, false);
  printf("scaleToFit()\n");
  scaleToFit(pages_pdf, pages_all, 400.0, 400.0);
  toFile(pages_pdf, "testoutputs/scaleToFit.pdf", false, false);
  printf("scaleToFitPaper()\n");
  scaleToFitPaper(pages_pdf, pages_all, 4);
  toFile(pages_pdf, "testoutputs/a4.pdf", false, false);
  
  printf("scaleContents()\n");
  struct position p = {.anchor = topLeft, .coord1 = 20, .coord2 = 20};
  scaleContents(pages_pdf, pages_all, p, 2.0);
  toFile(pages_pdf, "testoutputs/scaleContents.pdf", false, false);
  printf("shiftContents()\n");
  shiftContents(pages_pdf, pages_all, 200.0, 100.0);
  toFile(pages_pdf, "testoutputs/shiftContents.pdf", false, false);
  printf("rotate()\n");
  rotate(pages_pdf, pages_all, 270);
  toFile(pages_pdf, "testoutputs/rotate.pdf", false, false);
  printf("rotateBy()\n");
  rotateBy(pages_pdf, pages_all, 90);
  toFile(pages_pdf, "testoutputs/rotateBy.pdf", false, false);
  printf("rotateContents()\n");
  rotateContents(pages_pdf, pages_all, 25.0);
  toFile(pages_pdf, "testoutputs/rotateContents.pdf", false, false);
  printf("upright()\n");
  upright(pages_pdf, pages_all);
  printf("hFlip()\n");
  hFlip(pages_pdf, pages_all);
  toFile(pages_pdf, "testoutputs/hFlip.pdf", false, false);
  printf("vFlip()\n");
  vFlip(pages_pdf, pages_all);
  toFile(pages_pdf, "testoutputs/vFlip.pdf", false, false);

  printf("crop()\n");
  crop(pages_pdf, pages_all, 0.0, 0.0, 200.0, 200.0);
  toFile(pages_pdf, "testoutputs/cropped.pdf", false, false);
  printf("removeCrop()\n");
  removeCrop(pages_pdf, pages_all);
  printf("removeTrim()\n");
  removeTrim(pages_pdf, pages_all);
  printf("removeArt()\n");
  removeArt(pages_pdf, pages_all);
  printf("removeBleed()\n");
  removeBleed(pages_pdf, pages_all);
  toFile(pages_pdf, "testoutputs/uncropped.pdf", false, false);

  deletePdf(pages_pdf);

  deleterange(pages_all);

  onexit();
  /* Chapter 4. Encryption */
  printf("\n***** 4. Encryption\n\n");
  /* See Chapter 1 above for what is logically in Chapter 4. */

  onexit();
  /* Chapter 5. Compression */
  printf("\n***** 5. Compression\n\n");

  int tocompress = fromFile("testinputs/london.pdf");

  printf("compress()\n");
  compress(tocompress);
  toFile(tocompress, "testoutputs/compressed.pdf", false, false);
  
  printf("decompress()\n");
  decompress(tocompress);
  toFile(tocompress, "testoutputs/decompressed.pdf", false, false);

  deletePdf(tocompress);

  onexit();
  /* Chapter 6. Bookmarks */
  printf("\n***** 6. Bookmarks\n\n");
  int book = fromFile("testinputs/bookmarks.pdf");
  printf("startGetBookmarkInfo()\n");
  startGetBookmarkInfo(book);
  printf("numberBookmarks()\n");
  int num_bookmarks = numberBookmarks();
  printf("getBookmarkLevel()\n");
  printf("getBookmarkPage()\n");
  for (int x = 0; x < num_bookmarks; x++)
  {
    printf("Bookmark at level %i points to page %i\n", getBookmarkLevel(x), getBookmarkPage(book, x));
  };
  printf("endGetBookmarkInfo()\n");
  endGetBookmarkInfo();

  printf("Make a blank range\n");
  printf("blankrange()\n");
  int r = blankrange();

  printf("Delete a range\n");
  printf("deleterange()\n");
  deleterange(r);

  int r2 = blankrange();
  printf("range()\n");
  int r3 = range(1, 10);
  printf("even()\n");
  int r4 = even(r3);
  printf("odd()\n");
  int r5 = odd(r3);
  printf("range_union()\n");
  int r6 = range_union(r4, r5);
  printf("difference()\n");
  int r7 = difference(r6, r4);
  printf("removeDuplicates()\n");
  int r8 = removeDuplicates(r7);
  printf("isInRange()\n");
  int isinrange = isInRange(r8, 4);
  printf("all()\n");
  int allrange = all(book);
  printf("rangeLength()\n");
  int l = rangeLength(r3);
  printf("rangeGet()\n");
  int l1 = rangeGet(r3, 1);

  printf("rangeAdd()\n");
  int r20 = rangeAdd(r3, 15);
  printf("rangeLength()\n");
  int rl = rangeLength(r20);
  printf("range has length %i\n", rl);
  printf("rangeGet()\n");
  for (int x = 0; x < rl; x++)
  {
    printf("at position %i the value is %i\n", x, rangeGet(r20, x));
  };

  printf("Delete the pdf\n");
  deletePdf(book);

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

  deletePdf(pdflazy);
  deletePdf(blankdoc);
  deletePdf(blanksized);

  deleterange(r2);
  deleterange(r3);
  deleterange(r4);
  deleterange(r5);
  deleterange(r6);
  deleterange(r7);
  deleterange(r8);
  deleterange(allrange);
  deleterange(r20);
  deleterange(rfrompagespec);

  onexit();
  /* Chapter 8. Logos, Watermarks and Stamps */
  printf("\n***** 8. Logos, Watermarks and Stamps\n\n");
  int stamp = fromFile("logo.pdf");
  int stampee = fromFile("testinputs/london.pdf");
  int stamp_range = all(stamp);
  printf("stampOn()\n");
  stampOn(stamp, stampee, stamp_range);
  printf("stampUnder()\n");
  stampUnder(stamp, stampee, stamp_range);
  toFile(stamp, "testoutputs/stamp_after.pdf", false, false);
  toFile(stampee, "testoutputs/stampee_after.pdf", false, false);
  int c1 = fromFile("logo.pdf");
  int c2 = fromFile("testinputs/hello.pdf");
  printf("combinePages()\n");
  int c3 = combinePages(c1, c2);
  toFile(c3, "testoutputs/c3after.pdf", false, false);

  int textfile = fromFile("testinputs/hello.pdf");
  int textfile_all = all(textfile);
  struct position textpos = {.anchor = topLeft, .coord1 = 20, .coord2 = 20};
  printf("addText()\n");
  addText(true, textfile, textfile_all, "Some Text~~~~~~~~~~!", textpos, 1.0, 1, 1, 20, 0.5, 0.5, 0.5, false, false, true, 0.5, 0, false, "");
  addText(true, textfile, textfile_all, "Some Text~~~~~~~~~~!", textpos, 1.0, 1, 1, 20, 0.5, 0.5, 0.5, false, false, true, 0.5, 0, false, "");
  toFile(textfile, "testoutputs/added_text.pdf", false, false);

  printf("addTextHowMany()\n");
  int bits = addTextHowMany();
  printf("There are %i text bits to iterate over\n", bits);
  printf("addTextReturnText()\n");
  printf("addTextReturnX()\n");
  printf("addTextReturnY()\n");
  printf("addTextReturnRotation()\n");
  printf("addTextReturnBaselineAdjustment()\n");
  for (int x = 1; x <= bits; x++)
  {
    printf("Text is %s, x is %f, y is %f, rotation = %f, baseline = %f\n",
      addTextReturnText(x),
      addTextReturnX(x),
      addTextReturnY(x),
      addTextReturnRotation(x),
      addTextReturnBaselineAdjustment());
  };

  printf("removeText()\n");
  removeText(textfile, textfile_all);
  toFile(textfile, "testoutputs/removed_text.pdf", false, false);
  int w = textWidth(1, "Some Text");
  printf("The textwidth is %i\n", w);

  deletePdf(stamp);
  deletePdf(stampee);
  deletePdf(textfile);
  deletePdf(c1);
  deletePdf(c2);
  deletePdf(c3);

  deleterange(textfile_all);
  deleterange(stamp_range);

  onexit();
  /* Chapter 9. Multipage facilities */
  printf("\n***** 9. Multipage facilities\n\n");
  int twoup = fromFile("testinputs/london.pdf");
  printf("twoUp\n");
  twoUp(twoup);
  toFile(twoup, "testoutputs/twoup.pdf", false, false);

  int pad = fromFile("testinputs/london.pdf");
  int pad_range = all(pad);
  printf("padAfter()\n");
  padAfter(pad, pad_range);
  printf("padBefore()\n");
  padBefore(pad, pad_range);
  toFile(pad, "testoutputs/padded.pdf", false, false);

  deletePdf(twoup);
  deletePdf(pad);
  deleterange(pad_range);

  onexit();
  /* Chapter 11. Document Information and Metadata */
  printf("\n***** 11. Document Information and Metadata\n\n");
  int fonts = fromFile("testinputs/london.pdf");
  printf("startGetFontInfo()\n");
  startGetFontInfo(fonts);
  printf("numberFonts()\n");
  int numfonts = numberFonts();
  printf("getFontPage()\n");
  printf("getFontName()\n");
  printf("getFontType()\n");
  printf("getFontEncoding()\n");
  for (int x = 0; x < numfonts; x++)
  {
    printf("Page %i, font %s has type %s and encoding %s\n",
      getFontPage(x),
      getFontName(x),
      getFontType(x),
      getFontEncoding(x));
  };
  printf("endGetFontInfo()");
  endGetFontInfo();

  printf("isLinarized()\n");
  printf("isLinearized = %i\n", isLinearized("testinputs/london.pdf"));
  printf("getVersion()\n");
  printf("pdf version is %i\n", getVersion(fonts));
  printf("getTitle()\n");
  printf("pdf title is %s\n", getTitle(fonts));
  printf("getAuthor()\n");
  printf("pdf author is %s\n", getAuthor(fonts));
  printf("getSubject()\n");
  printf("pdf subject is %s\n", getSubject(fonts));
  printf("getKeywords()\n");
  printf("pdf keywords is %s\n", getKeywords(fonts));
  printf("getCreator()\n");
  printf("pdf creator is %s\n", getCreator(fonts));
  printf("getProducer()\n");
  printf("pdf producer is %s\n", getProducer(fonts));

  printf("getCreationDate()\n");
  printf("Creation date is %s\n", getCreationDate(fonts));
  
  printf("getModificationDate()\n");
  printf("Modification date is %s\n", getModificationDate(fonts));
 
  printf("dateStringOfComponents()\n");
  printf("Make a date string from components: %s\n",
    dateStringOfComponents(2003, 2, 5, 4, 6, 6, 0, 0));

  printf("getDateComponents()\n");
  int year, month, day, hour, minute, second, hour_offset, minute_offset;
  getDateComponents("D:20061108125017Z", &year, &month, &day, &hour, &minute, &second, &hour_offset, &minute_offset);
  printf("Get the components from a date string D:20061108125017Z = %i, %i, %i, %i, %i, %i, %i, %i\n",
          year, month, day, hour, minute, second, hour_offset, minute_offset);

  printf("setVersion()\n");
  setVersion(fonts, 6);
  printf("setTitle()\n");
  setTitle(fonts, "Title");
  printf("setAuthor()\n");
  setAuthor(fonts, "Author");
  printf("setSubject()\n");
  setSubject(fonts, "Subject");
  printf("setKeywords()\n");
  setKeywords(fonts, "Keywords");
  printf("setCreator()\n");
  setCreator(fonts, "Creator");
  printf("setProducer()\n");
  setProducer(fonts, "Producer");
  printf("markTrapped()\n");
  markTrapped(fonts);
  printf("markUntrapped()\n");
  markUntrapped(fonts);
  printf("setCreationDate()\n");
  setCreationDate(fonts, "D:20061108125017Z");
  printf("setModificationDate()\n");
  setModificationDate(fonts, "D:20061108125017Z");
  toFile(fonts, "testoutputs/settitleetc.pdf", false, false);

  printf("setPageLayout()\n");
  setPageLayout(fonts, 4);
  printf("setPageMode()\n");
  setPageMode(fonts, 3);

  printf("hasBox()\n");
  printf("Has page one a %s box? %i\n", "/CropBox", hasBox(fonts, 1, "/CropBox")); 
  printf("Has page one a %s box? %i\n", "/BleedBox", hasBox(fonts, 1, "/BleedBox")); 
  printf("Has page one a %s box? %i\n", "/ArtBox", hasBox(fonts, 1, "/ArtBox")); 
  printf("Has page one a %s box? %i\n", "/TrimBox", hasBox(fonts, 1, "/TrimBox")); 

  double minx, maxx, miny, maxy;

  int allbox = all(fonts);

  printf("setMediabox()\n");
  setMediabox(fonts, allbox, 100, 500, 150, 550);
  printf("setCropBox()\n");
  setCropBox(fonts, allbox, 100, 500, 150, 550);
  printf("setBleedBox()\n");
  setBleedBox(fonts, allbox, 100, 500, 150, 550);
  printf("setArtBox()\n");
  setArtBox(fonts, allbox, 100, 500, 150, 550);
  printf("setTrimBox()\n");
  setTrimBox(fonts, allbox, 100, 500, 150, 550);
 
  printf("getMediaBox()\n");
  getMediaBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Media: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("getCropBox()\n");
  getCropBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Crop: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("getBleedBox()\n");
  getBleedBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Bleed: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("getArtBox()\n");
  getArtBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Art: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("getTrimBox()\n");
  getTrimBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Trim: %f %f %f %f\n", minx, maxx, miny, maxy);

  printf("hideToolbar()\n");
  hideToolbar(fonts, true);
  printf("hideMenubar()\n");
  hideMenubar(fonts, true);
  printf("hideWindowUi()\n");
  hideWindowUi(fonts, true);
  printf("fitWindow()\n");
  fitWindow(fonts, true);
  printf("centerWindow()\n");
  centerWindow(fonts, true);
  printf("displayDocTitle()\n");
  displayDocTitle(fonts, true);

  printf("setMetadataFromFile()\n");
  setMetadataFromFile(fonts, "cpdflib.ml");
  toFile(fonts, "testoutputs/metadata1.pdf", false, false);
  printf("setMetadataFromByteArray()\n");
  setMetadataFromByteArray(fonts, "BYTEARRAY", 9);
  toFile(fonts, "testoutputs/metadata2.pdf", false, false);
  int metadata_length;
  printf("getMetadata()\n");
  void* metadata = getMetadata(fonts, &metadata_length);
  printf("removeMetadata()\n");
  removeMetadata(fonts);

  deletePdf(fonts);
  deleterange(allbox);

  onexit();
  /* Chapter 12. File attachments */
  printf("\n***** 12. File attachments\n\n");
  int toattachto = fromFile("testinputs/london.pdf");
  printf("attachFile()\n");
  attachFile("cpdflibtest.c", toattachto);
  toFile(toattachto, "testoutputs/withattachment.pdf", false, false);

  printf("startGetAttachments()\n");
  startGetAttachments(toattachto);
  printf("numberGetAttachments()\n");
  int numatt = numberGetAttachments();
  printf("There are %i attachements to get\n", numatt);
  printf("getAttachmentName()\n");
  for (int x = 0; x < numatt; x++)
  {
    printf("Attachment %i is named %s\n", x, getAttachmentName(x));
  };
  printf("endGetAttachments()\n");
  endGetAttachments();

  printf("removeAttachedFiles()\n");
  removeAttachedFiles(toattachto);
  toFile(toattachto, "testoutputs/removedattachments.pdf", false, false);

  deletePdf(toattachto);

  onexit();
  /* Chapter 13. Miscellaneous */
  printf("\n***** 13. Miscellaneous\n\n");
  int london = fromFile("testinputs/london.pdf");
  int all_london = all(london);
  printf("draft()\n");
  draft(london, all_london, true);
  toFile(london, "testoutputs/draft.pdf", false, false);
  printf("blackText()\n");
  blackText(london, all_london);
  printf("blackFills()\n");
  blackFills(london, all_london);
  printf("blackLines()\n");
  blackLines(london, all_london);
  toFile(london, "testoutputs/black.pdf", false, false);
  int london2 = fromFile("testinputs/london.pdf");
  printf("thinLines()\n");
  thinLines(london2, all_london, 8.0);
  printf("copyId()\n");
  copyId(london, london2);
  toFile(london2, "testoutputs/thinlines.pdf", false, false);

  deletePdf(london);
  deletePdf(london2);
  deleterange(all_london);

  onexit();
  /* Chapter 14. Page labels */
  printf("\n***** 14. Page labels\n\n");
  int pl = fromFile("testinputs/london.pdf");
  int pl_all = all(pl);
  printf("addPageLabels()\n");
  addPageLabels(pl, 4, "PREFIX-", 1, pl_all);
  toFile(pl, "testoutputs/pagelabels.pdf", false, false);

  int toreplace = fromFile("testinputs/london.pdf");
  printf("replacePdf()\n");
  replacePdf(pl, toreplace);

  deletePdf(toreplace); //FIXME - replacePdf not doing the right thing here. Also, why is it here?
  deletePdf(pl);
  deleterange(pl_all);

  onexit();
  /* Special functionality -- Undo */
  printf("\n***** Special functionality -- Undo\n\n");
  int undotest = fromFile("testinputs/london.pdf");
  printf("aboutToUpdate()\n");
  aboutToUpdate(undotest);
  int all_undotest = all(undotest);
  thinLines(undotest, all_undotest, 8.0);
  toFile(undotest, "testoutputs/undo.pdf", false, false);
  printf("undo()\n");
  undo(undotest);
  toFile(undotest, "testoutputs/undone.pdf", false, false);
  printf("redo()\n");
  redo(undotest);
  toFile(undotest, "testoutputs/redone.pdf", false, false);

  int undotest2 = fromFile("testinputs/london.pdf");
  printf("aboutToUpdateDeep()\n");
  aboutToUpdateDeep(undotest2);

  deletePdf(undotest);
  deletePdf(undotest2);
  deleterange(all_undotest);

  onexit();
  /* Special functionality -- Encryption and permission status */
  printf("\n***** Special functionality -- Encryption and permission status\n\n");
  printf("Encryption and permission status\n");

  int enctest = fromFile("testoutputs/encrypted.pdf");
  printf("lookupPdfStatus()\n");
  printf("pdf status = %i\n", lookupPdfStatus(enctest));
  decryptPdf(enctest, "user");
  printf("hasPermissionStatus()\n");
  printf("pdf permission status = %i\n", hasPermissionStatus(enctest, 0));
  printf("lookupPdfEncryption()\n");
  printf("pdf encryption status = %i\n", lookupPdfEncryption(enctest));
  printf("lookupPdfUserPassword()\n");
  printf("pdf user password was %s\n", lookupPdfUserPassword(enctest));
  
  deletePdf(enctest);

  onexit();

  printf("*****Tests finished\n");
  return 0;
}
