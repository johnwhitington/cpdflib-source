/* cpdflibtest.c */
/* Uses every function in cpdflibwrapper.h */
#include <stdio.h>
#include <stdbool.h>
#include "cpdflibwrapper.h"
int main (int argc, char ** argv)
{
  /* 0. Initialization */
  printf("***** 0. Initialisation\n\n");

  printf("cpdf_startup()\n");
  cpdf_startup(argv);

  printf("setdemo()\n");
  cpdf_setDemo(false);

  printf("clearError()\n");
  cpdf_clearError();

  cpdf_onExit();
  /* 1. Reading and writing files */
  printf("\n***** 1. Reading and writing files\n\n");

  printf("fromFile()\n");
  int pdf = cpdf_fromFile("testinputs/hello.pdf");

  printf("Afterwards, Error number = %i, Error string = %s\n", cpdf_lastError, cpdf_lastErrorString);

  printf("toFile()\n");
  cpdf_toFile(pdf, "testoutputs/out.pdf", false, false);

  printf("toFileEncrypted()\n");
  int permissions = {cpdf_noEdit};
  int encmethod = cpdf_pdf40bit;
  cpdf_toFileEncrypted(pdf, encmethod, &permissions, 1, "owner", "user", false, false, "testoutputs/encrypted.pdf");

  int pdfenc = cpdf_fromFile("testoutputs/encrypted.pdf");

  printf("hasPermission()\n");
  printf("Haspermission %i, %i\n", cpdf_hasPermission(pdf, cpdf_noEdit), cpdf_hasPermission(pdf, cpdf_noCopy)); //Fails

  printf("encryptionKind()\n");
  printf("encryption kind is %i\n", cpdf_encryptionKind(pdfenc));

  printf("decryptPdf\n");
  cpdf_decryptPdf(pdfenc, "user");

  printf("toFileRecrypting()\n");
  int pdfenc2 = cpdf_fromFile("testoutputs/encrypted.pdf");
  cpdf_toFileRecrypting(pdfenc2, pdfenc, "user", "testoutputs/recrypted.pdf");

  printf("decryptPdfOwner()\n");
  int pdfenc3 = cpdf_fromFile("testoutputs/encrypted.pdf");
  cpdf_decryptPdfOwner(pdfenc3, "owner");

  cpdf_deletePdf(pdf);
  cpdf_deletePdf(pdfenc);
  cpdf_deletePdf(pdfenc2);
  cpdf_deletePdf(pdfenc3);

  cpdf_onExit();
  /* Chapter 2. Merging */
  printf("\n***** 2. Merging\n\n");

  int mergepdf = cpdf_fromFile("testinputs/hello.pdf");
  printf("Merging files\n");
  int pdfs[] = {mergepdf, mergepdf, mergepdf};
  printf("mergeSimple()\n");
  int merged = cpdf_mergeSimple(pdfs, 3);
  cpdf_toFile(merged, "testoutputs/merged.pdf", false, false);
  printf("merge()\n");
  int merged2 = cpdf_merge(pdfs, 3, false, false);
  cpdf_toFile(merged2, "testoutputs/merged2.pdf", false, false);

  int a = cpdf_all(mergepdf);
  int b = cpdf_all(mergepdf);
  int c = cpdf_all(mergepdf);
  int ranges[] = {a, b, c};
  printf("mergeSame()\n");
  int merged3 = cpdf_mergeSame(pdfs, 3, false, false, ranges);
  cpdf_toFile(merged3, "testoutputs/merged3.pdf", false, false);

  int many = cpdf_fromFile("testinputs/bookmarks.pdf");
  printf("blankrange()\n");
  int manyrange = cpdf_blankRange();
  printf("rangeAdd()\n");
  int added = cpdf_rangeAdd(manyrange, 1);

  printf("selectPages()\n");
  int selected = cpdf_selectPages(many, added);
  cpdf_toFile(selected, "testoutputs/selected.pdf", false, false);

  cpdf_deletePdf(mergepdf);
  cpdf_deletePdf(merged);
  cpdf_deletePdf(merged2);
  cpdf_deletePdf(merged3);
  cpdf_deletePdf(many);
  cpdf_deletePdf(selected);

  cpdf_deleteRange(a);
  cpdf_deleteRange(b);
  cpdf_deleteRange(c);
  cpdf_deleteRange(manyrange);
  cpdf_deleteRange(added);


  cpdf_onExit();
  /* Chapter 3. Pages */
  printf("\n***** 3. Pages\n\n");

  int pages_pdf = cpdf_fromFile("testinputs/london.pdf");
  int pages_all = cpdf_all(pages_pdf);
  printf("scalePages()\n");
  cpdf_scalePages(pages_pdf, pages_all, 2.0, 3.0);
  cpdf_toFile(pages_pdf, "testoutputs/scalePages.pdf", false, false);
  printf("scaleToFit()\n");
  cpdf_scaleToFit(pages_pdf, pages_all, 400.0, 400.0);
  cpdf_toFile(pages_pdf, "testoutputs/scaleToFit.pdf", false, false);
  printf("scaleToFitPaper()\n");
  cpdf_scaleToFitPaper(pages_pdf, pages_all, 4);
  cpdf_toFile(pages_pdf, "testoutputs/a4.pdf", false, false);
  
  printf("scaleContents()\n");
  struct cpdf_position p = {.cpdf_anchor = cpdf_topLeft, .cpdf_coord1 = 20, .cpdf_coord2 = 20};
  cpdf_scaleContents(pages_pdf, pages_all, p, 2.0);
  cpdf_toFile(pages_pdf, "testoutputs/scaleContents.pdf", false, false);
  printf("shiftContents()\n");
  cpdf_shiftContents(pages_pdf, pages_all, 200.0, 100.0);
  cpdf_toFile(pages_pdf, "testoutputs/shiftContents.pdf", false, false);
  printf("rotate()\n");
  cpdf_rotate(pages_pdf, pages_all, 270);
  cpdf_toFile(pages_pdf, "testoutputs/rotate.pdf", false, false);
  printf("rotateBy()\n");
  cpdf_rotateBy(pages_pdf, pages_all, 90);
  cpdf_toFile(pages_pdf, "testoutputs/rotateBy.pdf", false, false);
  printf("rotateContents()\n");
  cpdf_rotateContents(pages_pdf, pages_all, 25.0);
  cpdf_toFile(pages_pdf, "testoutputs/rotateContents.pdf", false, false);
  printf("upright()\n");
  cpdf_upright(pages_pdf, pages_all);
  printf("hFlip()\n");
  cpdf_hFlip(pages_pdf, pages_all);
  cpdf_toFile(pages_pdf, "testoutputs/hFlip.pdf", false, false);
  printf("vFlip()\n");
  cpdf_vFlip(pages_pdf, pages_all);
  cpdf_toFile(pages_pdf, "testoutputs/vFlip.pdf", false, false);

  printf("crop()\n");
  cpdf_crop(pages_pdf, pages_all, 0.0, 0.0, 200.0, 200.0);
  cpdf_toFile(pages_pdf, "testoutputs/cropped.pdf", false, false);
  printf("removeCrop()\n");
  cpdf_removeCrop(pages_pdf, pages_all);
  printf("removeTrim()\n");
  cpdf_removeTrim(pages_pdf, pages_all);
  printf("removeArt()\n");
  cpdf_removeArt(pages_pdf, pages_all);
  printf("removeBleed()\n");
  cpdf_removeBleed(pages_pdf, pages_all);
  cpdf_toFile(pages_pdf, "testoutputs/uncropped.pdf", false, false);

  cpdf_deletePdf(pages_pdf);

  cpdf_deleteRange(pages_all);

  cpdf_onExit();
  /* Chapter 4. Encryption */
  printf("\n***** 4. Encryption\n\n");
  /* See Chapter 1 above for what is logically in Chapter 4. */

  cpdf_onExit();
  /* Chapter 5. Compression */
  printf("\n***** 5. Compression\n\n");

  int tocompress = cpdf_fromFile("testinputs/london.pdf");

  printf("compress()\n");
  cpdf_compress(tocompress);
  cpdf_toFile(tocompress, "testoutputs/compressed.pdf", false, false);
  
  printf("decompress()\n");
  cpdf_decompress(tocompress);
  cpdf_toFile(tocompress, "testoutputs/decompressed.pdf", false, false);

  cpdf_deletePdf(tocompress);

  cpdf_onExit();
  /* Chapter 6. Bookmarks */
  printf("\n***** 6. Bookmarks\n\n");
  int book = cpdf_fromFile("testinputs/bookmarks.pdf");
  printf("startGetBookmarkInfo()\n");
  cpdf_startGetBookmarkInfo(book);
  printf("numberBookmarks()\n");
  int num_bookmarks = cpdf_numberBookmarks();
  printf("getBookmarkLevel()\n");
  printf("getBookmarkPage()\n");
  printf("getBookmarkText()\n");
  for (int x = 0; x < num_bookmarks; x++)
  {
    printf("Bookmark at level %i points to page %i and has text %s\n",
      cpdf_getBookmarkLevel(x),
      cpdf_getBookmarkPage(book, x),
      cpdf_getBookmarkText(x));
  };
  printf("endGetBookmarkInfo()\n");
  cpdf_endGetBookmarkInfo();

  printf("Make a blank range\n");
  printf("blankrange()\n");
  int r = cpdf_blankRange();

  printf("Delete a range\n");
  printf("deleteRange()\n");
  cpdf_deleteRange(r);

  int r2 = cpdf_blankRange();
  printf("range()\n");
  int r3 = cpdf_range(1, 10);
  printf("even()\n");
  int r4 = cpdf_even(r3);
  printf("odd()\n");
  int r5 = cpdf_odd(r3);
  printf("rangeUnion()\n");
  int r6 = cpdf_rangeUnion(r4, r5);
  printf("difference()\n");
  int r7 = cpdf_difference(r6, r4);
  printf("removeDuplicates()\n");
  int r8 = cpdf_removeDuplicates(r7);
  printf("isInRange()\n");
  int isinrange = cpdf_isInRange(r8, 4);
  printf("all()\n");
  int allrange = cpdf_all(book);
  printf("rangeLength()\n");
  int l = cpdf_rangeLength(r3);
  printf("rangeGet()\n");
  int l1 = cpdf_rangeGet(r3, 1);

  printf("rangeAdd()\n");
  int r20 = cpdf_rangeAdd(r3, 15);
  printf("rangeLength()\n");
  int rl = cpdf_rangeLength(r20);
  printf("range has length %i\n", rl);
  printf("rangeGet()\n");
  for (int x = 0; x < rl; x++)
  {
    printf("at position %i the value is %i\n", x, cpdf_rangeGet(r20, x));
  };

  printf("Delete the pdf\n");
  cpdf_deletePdf(book);

  printf("One inch is %f points\n", cpdf_ptOfIn(1.0));
  printf("One centimetre is %f points\n", cpdf_ptOfCm(1.0));
  printf("One millimetre is %f points\n", cpdf_ptOfMm(1.0));
  printf("One point is %f inches\n", cpdf_inOfPt(1.0));
  printf("One point is %f centimetres\n", cpdf_cmOfPt(1.0));
  printf("One point is %f millimetres\n", cpdf_mmOfPt(1.0));



  int pdflazy = cpdf_fromFileLazy("testinputs/hello.pdf");
 
  int blankdoc = cpdf_blankDocument(100.0, 200.0, 20);
  cpdf_toFile(blankdoc, "testoutputs/blank.pdf", false, false);

  int blanksized = cpdf_blankDocumentPaper(cpdf_a4portrait, 10);
  cpdf_toFile(blanksized, "testoutputs/blanka4.pdf", false, false);
  
  int rfrompagespec = cpdf_parsePagespec(blanksized, "1-2,5-end");
  printf("Validating pagespec gives %i\n", cpdf_validatePagespec("1-2,5-end"));

  printf("There are %i pages in the blank sized pdf\n", cpdf_pages(blanksized));
 
  printf("There are %i quick pages in the blank sized pdf\n", cpdf_pagesFast("", "testoutputs/blanka4.pdf"));

  printf("String of pagespec is %s\n", cpdf_stringOfPagespec(blanksized, rfrompagespec));

  printf("This is documents has isEncrypted = %i\n", cpdf_isEncrypted(blanksized));

  cpdf_deletePdf(pdflazy);
  cpdf_deletePdf(blankdoc);
  cpdf_deletePdf(blanksized);

  cpdf_deleteRange(r2);
  cpdf_deleteRange(r3);
  cpdf_deleteRange(r4);
  cpdf_deleteRange(r5);
  cpdf_deleteRange(r6);
  cpdf_deleteRange(r7);
  cpdf_deleteRange(r8);
  cpdf_deleteRange(allrange);
  cpdf_deleteRange(r20);
  cpdf_deleteRange(rfrompagespec);

  cpdf_onExit();
  /* Chapter 8. Logos, Watermarks and Stamps */
  printf("\n***** 8. Logos, Watermarks and Stamps\n\n");
  int stamp = cpdf_fromFile("logo.pdf");
  int stampee = cpdf_fromFile("testinputs/london.pdf");
  int stamp_range = cpdf_all(stamp);
  printf("stampOn()\n");
  cpdf_stampOn(stamp, stampee, stamp_range);
  printf("stampUnder()\n");
  cpdf_stampUnder(stamp, stampee, stamp_range);
  cpdf_toFile(stamp, "testoutputs/stamp_after.pdf", false, false);
  cpdf_toFile(stampee, "testoutputs/stampee_after.pdf", false, false);
  int c1 = cpdf_fromFile("logo.pdf");
  int c2 = cpdf_fromFile("testinputs/hello.pdf");
  printf("combinePages()\n");
  int c3 = cpdf_combinePages(c1, c2);
  cpdf_toFile(c3, "testoutputs/c3after.pdf", false, false);

  int textfile = cpdf_fromFile("testinputs/hello.pdf");
  int textfile_all = cpdf_all(textfile);
  struct cpdf_position textpos = {.cpdf_anchor = cpdf_topLeft, .cpdf_coord1 = 20, .cpdf_coord2 = 20};
  printf("addText()\n");
  cpdf_addText(true, textfile, textfile_all, "Some Text~~~~~~~~~~!", textpos, 1.0, 1, 1, 20, 0.5, 0.5, 0.5, false, false, true, 0.5, 0, false, "");
  cpdf_addText(true, textfile, textfile_all, "Some Text~~~~~~~~~~!", textpos, 1.0, 1, 1, 20, 0.5, 0.5, 0.5, false, false, true, 0.5, 0, false, "");
  cpdf_toFile(textfile, "testoutputs/added_text.pdf", false, false);

  printf("addTextHowMany()\n");
  int bits = cpdf_addTextHowMany();
  printf("There are %i text bits to iterate over\n", bits);
  printf("addTextReturnText()\n");
  printf("addTextReturnX()\n");
  printf("addTextReturnY()\n");
  printf("addTextReturnRotation()\n");
  printf("addTextReturnBaselineAdjustment()\n");
  for (int x = 1; x <= bits; x++)
  {
    printf("Text is %s, x is %f, y is %f, rotation = %f, baseline = %f\n",
      cpdf_addTextReturnText(x),
      cpdf_addTextReturnX(x),
      cpdf_addTextReturnY(x),
      cpdf_addTextReturnRotation(x),
      cpdf_addTextReturnBaselineAdjustment());
  };

  printf("removeText()\n");
  cpdf_removeText(textfile, textfile_all);
  cpdf_toFile(textfile, "testoutputs/removed_text.pdf", false, false);
  int w = cpdf_textWidth(1, "Some Text");
  printf("The textwidth is %i\n", w);

  cpdf_deletePdf(stamp);
  cpdf_deletePdf(stampee);
  cpdf_deletePdf(textfile);
  cpdf_deletePdf(c1);
  cpdf_deletePdf(c2);
  cpdf_deletePdf(c3);

  cpdf_deleteRange(textfile_all);
  cpdf_deleteRange(stamp_range);

  cpdf_onExit();
  /* Chapter 9. Multipage facilities */
  printf("\n***** 9. Multipage facilities\n\n");
  int twoup = cpdf_fromFile("testinputs/london.pdf");
  printf("twoUp\n");
  cpdf_twoUp(twoup);
  cpdf_toFile(twoup, "testoutputs/twoup.pdf", false, false);

  int pad = cpdf_fromFile("testinputs/london.pdf");
  int pad_range = cpdf_all(pad);
  printf("padAfter()\n");
  cpdf_padAfter(pad, pad_range);
  printf("padBefore()\n");
  cpdf_padBefore(pad, pad_range);
  cpdf_toFile(pad, "testoutputs/padded.pdf", false, false);

  cpdf_deletePdf(twoup);
  cpdf_deletePdf(pad);
  cpdf_deleteRange(pad_range);

  cpdf_onExit();
  /* Chapter 11. Document Information and Metadata */
  printf("\n***** 11. Document Information and Metadata\n\n");
  int fonts = cpdf_fromFile("testinputs/london.pdf");
  printf("startGetFontInfo()\n");
  cpdf_startGetFontInfo(fonts);
  printf("numberFonts()\n");
  int numfonts = cpdf_numberFonts();
  printf("getFontPage()\n");
  printf("getFontName()\n");
  printf("getFontType()\n");
  printf("getFontEncoding()\n");
  for (int x = 0; x < numfonts; x++)
  {
    printf("Page %i, font %s has type %s and encoding %s\n",
      cpdf_getFontPage(x),
      cpdf_getFontName(x),
      cpdf_getFontType(x),
      cpdf_getFontEncoding(x));
  };
  printf("endGetFontInfo()");
  cpdf_endGetFontInfo();

  printf("isLinarized()\n");
  printf("isLinearized = %i\n", cpdf_isLinearized("testinputs/london.pdf"));
  printf("getVersion()\n");
  printf("pdf version is %i\n", cpdf_getVersion(fonts));
  printf("getTitle()\n");
  printf("pdf title is %s\n", cpdf_getTitle(fonts));
  printf("getAuthor()\n");
  printf("pdf author is %s\n", cpdf_getAuthor(fonts));
  printf("getSubject()\n");
  printf("pdf subject is %s\n", cpdf_getSubject(fonts));
  printf("getKeywords()\n");
  printf("pdf keywords is %s\n", cpdf_getKeywords(fonts));
  printf("getCreator()\n");
  printf("pdf creator is %s\n", cpdf_getCreator(fonts));
  printf("getProducer()\n");
  printf("pdf producer is %s\n", cpdf_getProducer(fonts));

  printf("getCreationDate()\n");
  printf("Creation date is %s\n", cpdf_getCreationDate(fonts));
  
  printf("getModificationDate()\n");
  printf("Modification date is %s\n", cpdf_getModificationDate(fonts));
 
  printf("dateStringOfComponents()\n");
  printf("Make a date string from components: %s\n",
    cpdf_dateStringOfComponents(2003, 2, 5, 4, 6, 6, 0, 0));

  printf("getDateComponents()\n");
  int year, month, day, hour, minute, second, hour_offset, minute_offset;
  cpdf_getDateComponents("D:20061108125017Z", &year, &month, &day, &hour, &minute, &second, &hour_offset, &minute_offset);
  printf("Get the components from a date string D:20061108125017Z = %i, %i, %i, %i, %i, %i, %i, %i\n",
          year, month, day, hour, minute, second, hour_offset, minute_offset);

  printf("setVersion()\n");
  cpdf_setVersion(fonts, 6);
  printf("setTitle()\n");
  cpdf_setTitle(fonts, "Title");
  printf("setAuthor()\n");
  cpdf_setAuthor(fonts, "Author");
  printf("setSubject()\n");
  cpdf_setSubject(fonts, "Subject");
  printf("setKeywords()\n");
  cpdf_setKeywords(fonts, "Keywords");
  printf("setCreator()\n");
  cpdf_setCreator(fonts, "Creator");
  printf("setProducer()\n");
  cpdf_setProducer(fonts, "Producer");
  printf("markTrapped()\n");
  cpdf_markTrapped(fonts);
  printf("markUntrapped()\n");
  cpdf_markUntrapped(fonts);
  printf("setCreationDate()\n");
  cpdf_setCreationDate(fonts, "D:20061108125017Z");
  printf("setModificationDate()\n");
  cpdf_setModificationDate(fonts, "D:20061108125017Z");
  cpdf_toFile(fonts, "testoutputs/settitleetc.pdf", false, false);

  printf("setPageLayout()\n");
  cpdf_setPageLayout(fonts, 4);
  printf("setPageMode()\n");
  cpdf_setPageMode(fonts, 3);

  printf("hasBox()\n");
  printf("Has page one a %s box? %i\n", "/CropBox", cpdf_hasBox(fonts, 1, "/CropBox")); 
  printf("Has page one a %s box? %i\n", "/BleedBox", cpdf_hasBox(fonts, 1, "/BleedBox")); 
  printf("Has page one a %s box? %i\n", "/ArtBox", cpdf_hasBox(fonts, 1, "/ArtBox")); 
  printf("Has page one a %s box? %i\n", "/TrimBox", cpdf_hasBox(fonts, 1, "/TrimBox")); 

  double minx, maxx, miny, maxy;

  int allbox = cpdf_all(fonts);

  printf("setMediabox()\n");
  cpdf_setMediabox(fonts, allbox, 100, 500, 150, 550);
  printf("setCropBox()\n");
  cpdf_setCropBox(fonts, allbox, 100, 500, 150, 550);
  printf("setBleedBox()\n");
  cpdf_setBleedBox(fonts, allbox, 100, 500, 150, 550);
  printf("setArtBox()\n");
  cpdf_setArtBox(fonts, allbox, 100, 500, 150, 550);
  printf("setTrimBox()\n");
  cpdf_setTrimBox(fonts, allbox, 100, 500, 150, 550);
 
  printf("getMediaBox()\n");
  cpdf_getMediaBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Media: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("getCropBox()\n");
  cpdf_getCropBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Crop: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("getBleedBox()\n");
  cpdf_getBleedBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Bleed: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("getArtBox()\n");
  cpdf_getArtBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Art: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("getTrimBox()\n");
  cpdf_getTrimBox(fonts, 1, &minx, &maxx, &miny, &maxy);
  printf("Trim: %f %f %f %f\n", minx, maxx, miny, maxy);

  printf("hideToolbar()\n");
  cpdf_hideToolbar(fonts, true);
  printf("hideMenubar()\n");
  cpdf_hideMenubar(fonts, true);
  printf("hideWindowUi()\n");
  cpdf_hideWindowUi(fonts, true);
  printf("fitWindow()\n");
  cpdf_fitWindow(fonts, true);
  printf("centerWindow()\n");
  cpdf_centerWindow(fonts, true);
  printf("displayDocTitle()\n");
  cpdf_displayDocTitle(fonts, true);

  printf("setMetadataFromFile()\n");
  cpdf_setMetadataFromFile(fonts, "cpdflib.ml");
  cpdf_toFile(fonts, "testoutputs/metadata1.pdf", false, false);
  printf("setMetadataFromByteArray()\n");
  cpdf_setMetadataFromByteArray(fonts, "BYTEARRAY", 9);
  cpdf_toFile(fonts, "testoutputs/metadata2.pdf", false, false);
  int metadata_length;
  printf("getMetadata()\n");
  void* metadata = cpdf_getMetadata(fonts, &metadata_length);
  printf("removeMetadata()\n");
  cpdf_removeMetadata(fonts);

  cpdf_deletePdf(fonts);
  cpdf_deleteRange(allbox);

  cpdf_onExit();
  /* Chapter 12. File attachments */
  printf("\n***** 12. File attachments\n\n");
  int toattachto = cpdf_fromFile("testinputs/london.pdf");
  printf("attachFile()\n");
  cpdf_attachFile("cpdflibtest.c", toattachto);
  cpdf_toFile(toattachto, "testoutputs/withattachment.pdf", false, false);

  printf("startGetAttachments()\n");
  cpdf_startGetAttachments(toattachto);
  printf("numberGetAttachments()\n");
  int numatt = cpdf_numberGetAttachments();
  printf("There are %i attachements to get\n", numatt);
  printf("getAttachmentName()\n");
  for (int x = 0; x < numatt; x++)
  {
    printf("Attachment %i is named %s\n", x, cpdf_getAttachmentName(x));
  };
  printf("endGetAttachments()\n");
  cpdf_endGetAttachments();

  printf("removeAttachedFiles()\n");
  cpdf_removeAttachedFiles(toattachto);
  cpdf_toFile(toattachto, "testoutputs/removedattachments.pdf", false, false);

  cpdf_deletePdf(toattachto);

  cpdf_onExit();
  /* Chapter 13. Miscellaneous */
  printf("\n***** 13. Miscellaneous\n\n");
  int london = cpdf_fromFile("testinputs/london.pdf");
  int all_london = cpdf_all(london);
  printf("draft()\n");
  cpdf_draft(london, all_london, true);
  cpdf_toFile(london, "testoutputs/draft.pdf", false, false);
  printf("blackText()\n");
  cpdf_blackText(london, all_london);
  printf("blackFills()\n");
  cpdf_blackFills(london, all_london);
  printf("blackLines()\n");
  cpdf_blackLines(london, all_london);
  cpdf_toFile(london, "testoutputs/black.pdf", false, false);
  int london2 = cpdf_fromFile("testinputs/london.pdf");
  printf("thinLines()\n");
  cpdf_thinLines(london2, all_london, 8.0);
  printf("copyId()\n");
  cpdf_copyId(london, london2);
  cpdf_toFile(london2, "testoutputs/thinlines.pdf", false, false);

  cpdf_deletePdf(london);
  cpdf_deletePdf(london2);
  cpdf_deleteRange(all_london);

  cpdf_onExit();
  /* Chapter 14. Page labels */
  printf("\n***** 14. Page labels\n\n");
  int pl = cpdf_fromFile("testinputs/london.pdf");
  int pl_all = cpdf_all(pl);
  printf("addPageLabels()\n");
  cpdf_addPageLabels(pl, 4, "PREFIX-", 1, pl_all);
  cpdf_toFile(pl, "testoutputs/pagelabels.pdf", false, false);

  int toreplace = cpdf_fromFile("testinputs/london.pdf");
  printf("replacePdf()\n");
  cpdf_replacePdf(pl, toreplace);

  cpdf_deletePdf(toreplace); //FIXME - replacePdf not doing the right thing here. Also, why is it here?
  cpdf_deletePdf(pl);
  cpdf_deleteRange(pl_all);

  cpdf_onExit();
  /* Special functionality -- Undo */
  printf("\n***** Special functionality -- Undo\n\n");
  int undotest = cpdf_fromFile("testinputs/london.pdf");
  printf("aboutToUpdate()\n");
  cpdf_aboutToUpdate(undotest);
  int all_undotest = cpdf_all(undotest);
  cpdf_thinLines(undotest, all_undotest, 8.0);
  cpdf_toFile(undotest, "testoutputs/undo.pdf", false, false);
  printf("undo()\n");
  cpdf_undo(undotest);
  cpdf_toFile(undotest, "testoutputs/undone.pdf", false, false);
  printf("redo()\n");
  cpdf_redo(undotest);
  cpdf_toFile(undotest, "testoutputs/redone.pdf", false, false);

  int undotest2 = cpdf_fromFile("testinputs/london.pdf");
  printf("aboutToUpdateDeep()\n");
  cpdf_aboutToUpdateDeep(undotest2);

  cpdf_deletePdf(undotest);
  cpdf_deletePdf(undotest2);
  cpdf_deleteRange(all_undotest);

  cpdf_onExit();
  /* Special functionality -- Encryption and permission status */
  printf("\n***** Special functionality -- Encryption and permission status\n\n");
  printf("Encryption and permission status\n");

  int enctest = cpdf_fromFile("testoutputs/encrypted.pdf");
  printf("lookupPdfStatus()\n");
  printf("pdf status = %i\n", cpdf_lookupPdfStatus(enctest));
  cpdf_decryptPdf(enctest, "user");
  printf("hasPermissionStatus()\n");
  printf("pdf permission status = %i\n", cpdf_hasPermissionStatus(enctest, cpdf_noEdit));
  printf("lookupPdfEncryption()\n");
  printf("pdf encryption status = %i\n", cpdf_lookupPdfEncryption(enctest));
  printf("lookupPdfUserPassword()\n");
  printf("pdf user password was %s\n", cpdf_lookupPdfUserPassword(enctest));
  
  cpdf_deletePdf(enctest);

  cpdf_onExit();

  printf("*****Tests finished\n");
  return 0;
}
