/* Uses every function in cpdflibwrapper.h */
#include <stdio.h>
#include <stdbool.h>
#include "cpdflibwrapper.h"

void
prerr (void)
{
  printf ("(%i | %s)\n", cpdf_lastError, cpdf_lastErrorString);
}

int
main (int argc, char **argv)
{
/* CHAPTER 0. Preliminaries */
  printf ("***** CHAPTER 0. Preliminaries\n");
  printf ("---cpdf_startup()\n");
  cpdf_startup (argv);
  prerr ();
  printf ("---cpdf_version()\n");
  printf ("version = %s\n", cpdf_version ());
  prerr ();
  printf ("---cpdf_setFast()\n");
  cpdf_setFast ();
  prerr ();
  printf ("---cpdf_setSlow()\n");
  cpdf_setSlow ();
  prerr ();
  printf ("---cpdf_clearError()\n");
  cpdf_clearError ();
  prerr ();
  printf ("---cpdf_onExit()\n");
  cpdf_onExit ();

/* CHAPTER 1. Basics */
  printf ("***** CHAPTER 1. Basics\n");
  printf ("---cpdf_fromFile()\n");
  int f = cpdf_fromFile ("cpdflibmanual.pdf", "");
  prerr ();
  printf ("---cpdf_fromFileLazy()\n");
  int f2 = cpdf_fromFileLazy ("cpdflibmanual.pdf", "");
  prerr ();
  int buflen;
  void *buf = cpdf_toMemory (f, false, false, &buflen);
  FILE *fp;
  printf ("---cpdf_fromMemory()\n");
  int frommem = cpdf_fromMemory (buf, buflen, "");
  cpdf_toFile (frommem, "testoutputs/fromMemory.pdf", false, false);
  prerr ();
  printf ("---cpdf_fromMemoryLazy()\n");
  int frommemlazy = cpdf_fromMemoryLazy (buf, buflen, "");
  prerr ();
  cpdf_toFile (frommemlazy, "testoutputs/fromMemoryLazy.pdf", false, false);
  printf ("---cpdf_blankDocument()\n");
  int blankdoc = cpdf_blankDocument (100.0, 200.0, 20);
  prerr ();
  cpdf_toFile (blankdoc, "testoutputs/blank.pdf", false, false);
  printf ("---cpdf_blankDocumentPaper()\n");
  int blanksized = cpdf_blankDocumentPaper (cpdf_a4portrait, 10);
  prerr ();
  cpdf_toFile (blanksized, "testoutputs/blanka4.pdf", false, false);
  printf ("---cpdf_deletePdf()\n");
  cpdf_deletePdf (f);
  prerr ();
  printf ("---cpdf_replacePdf()\n");
  cpdf_replacePdf (f2, frommem);
  prerr ();
  cpdf_toFile (f2, "testoutputs/blanka4.pdf", false, false);
  printf ("---cpdf_startEnumeratePDFs()\n");
  int numpdfs = cpdf_startEnumeratePDFs ();
  prerr ();
  for (int x = 0; x < numpdfs; x++)
    {
      printf ("---cpdf_enumeratePDFsKey()\n");
      int key = cpdf_enumeratePDFsKey (x);
      prerr ();
      printf ("---cpdf_enumeratePDFsInfo()\n");
      char *info = cpdf_enumeratePDFsInfo (x);
      prerr ();
      printf ("For key %i, info is %s\n", key, info);
    }
  printf ("---cpdf_endEnumeratePDFs)\n");
  cpdf_endEnumeratePDFs ();
  prerr ();
  printf ("---cpdf_ptOfIn()\n");
  printf ("One inch is %f points\n", cpdf_ptOfIn (1.0));
  prerr ();
  printf ("---cpdf_ptOfCm()\n");
  printf ("One centimetre is %f points\n", cpdf_ptOfCm (1.0));
  prerr ();
  printf ("---cpdf_ptOfMm()\n");
  printf ("One millimetre is %f points\n", cpdf_ptOfMm (1.0));
  prerr ();
  printf ("---cpdf_inOfPt()\n");
  printf ("One point is %f inches\n", cpdf_inOfPt (1.0));
  prerr ();
  printf ("---cpdf_cmOfPt()\n");
  printf ("One point is %f centimetres\n", cpdf_cmOfPt (1.0));
  prerr ();
  printf ("---cpdf_mmOfPt()\n");
  printf ("One point is %f millimetres\n", cpdf_mmOfPt (1.0));
  prerr ();
  printf ("---cpdf_range()\n");
  int range = cpdf_range (1, 5);
  prerr ();
  printf ("---cpdf_all()\n");
  int range_all = cpdf_all (f2);
  prerr ();
  printf ("---cpdf_even()\n");
  int range_even = cpdf_even (range_all);
  prerr ();
  printf ("---cpdf_odd()\n");
  int range_odd = cpdf_odd (range_all);
  prerr ();
  printf ("---cpdf_rangeUnion\n");
  int range_union = cpdf_rangeUnion (range, range_all);
  prerr ();
  printf ("---cpdf_difference()\n");
  int range_difference = cpdf_difference (range, range_all);
  prerr ();
  printf ("---cpdf_removeDuplicates()\n");
  int range_remove_dups = cpdf_removeDuplicates (range_all);
  prerr ();
  printf ("---cpdf_rangeLength()\n");
  int range_length = cpdf_rangeLength (range_all);
  prerr ();
  printf ("---cpdf_rangeGet()\n");
  int range_get = cpdf_rangeGet (range_all, 0);
  prerr ();
  printf ("---cpdf_rangeAdd()\n");
  int range_add = cpdf_rangeAdd (range_all, 20);
  prerr ();
  printf ("---cpdf_isInRange()\n");
  int range_is_in_range = cpdf_isInRange (range_all, 5);
  prerr ();
  cpdf_deletePdf (f2);
  cpdf_deletePdf (frommemlazy);
  cpdf_deletePdf (blankdoc);
  cpdf_deletePdf (blanksized);
  cpdf_deleteRange (range);
  cpdf_deleteRange (range_all);
  cpdf_deleteRange (range_even);
  cpdf_deleteRange (range_odd);
  cpdf_deleteRange (range_union);
  cpdf_deleteRange (range_difference);
  cpdf_deleteRange (range_remove_dups);
  cpdf_deleteRange (range_length);
  cpdf_deleteRange (range_get);
  cpdf_deleteRange (range_add);
  cpdf_deleteRange (range_is_in_range);
  cpdf_onExit ();

/*
int cpdf_parsePagespec (int, const char[]);
int cpdf_validatePagespec (const char[]);
char *cpdf_stringOfPagespec (int, int);
int cpdf_blankRange (void);
int cpdf_pages (int);
int cpdf_pagesFast (const char[], const char[]);
void cpdf_toFile (int, const char[], int, int);
void cpdf_toFileExt (int, const char[], int, int, int, int, int);
void *cpdf_toMemory (int, int, int, int *);
int cpdf_isEncrypted (int);
int is_linearized (const char[]);
void cpdf_decryptPdf (int, const char[]);
void cpdf_decryptPdfOwner (int, const char[]);
void cpdf_toFileEncrypted
  (int, int, int *, int, const char[], const char[], int, int, const char[]);
void cpdf_toFileEncryptedExt
  (int, int, int *, int, const char[], const char[], int, int, int, int, int,
   const char[]);
int cpdf_hasPermission (int, enum cpdf_permission);
enum cpdf_encryptionMethod cpdf_encryptionKind (int);
enum cpdf_pdfStatus cpdf_lookupPdfStatus (int);
int cpdf_hasPermissionStatus (int, enum cpdf_permission);
enum cpdf_encryptionMethod cpdf_lookupPdfEncryption (int);
char *cpdf_lookupPdfUserPassword (int); */

/* CHAPTER 2. Merging and Splitting */
  printf ("***** CHAPTER 2. Merging and Splitting\n");
  int mergepdf = cpdf_fromFile ("cpdflibmanual.pdf", "");
  int pdfs[] = { mergepdf, mergepdf, mergepdf };
  printf ("---cpdf_mergeSimple()\n");
  int merged = cpdf_mergeSimple (pdfs, 3);
  prerr ();
  cpdf_toFile (merged, "testoutputs/merged.pdf", false, false);
  printf ("---cpdf_merge()\n");
  int merged2 = cpdf_merge (pdfs, 3, false, false);
  prerr ();
  cpdf_toFile (merged2, "testoutputs/merged2.pdf", false, false);
  int a = cpdf_all (mergepdf);
  int b = cpdf_all (mergepdf);
  int c = cpdf_all (mergepdf);
  int ranges[] = { a, b, c };
  printf ("---cpdf_mergeSame()\n");
  int merged3 = cpdf_mergeSame (pdfs, 3, false, false, ranges);
  prerr ();
  cpdf_toFile (merged3, "testoutputs/merged3.pdf", false, false);
  printf ("---cpdf_selectPages()\n");
  int range_select = cpdf_range (1, 3);
  int selected = cpdf_selectPages (mergepdf, range_select);
  prerr ();
  cpdf_toFile (selected, "testoutputs/selected.pdf", false, false);
  cpdf_deletePdf (mergepdf);
  cpdf_deletePdf (merged);
  cpdf_deletePdf (merged2);
  cpdf_deletePdf (merged3);
  cpdf_deletePdf (selected);
  cpdf_deleteRange (a);
  cpdf_deleteRange (b);
  cpdf_deleteRange (c);
  cpdf_deleteRange (range_select);
  cpdf_onExit ();

/* CHAPTER 3. Pages */
  printf ("***** CHAPTER 3. Pages\n");
  int pagespdf = cpdf_fromFile ("cpdflibmanual.pdf", "");
  int r3 = cpdf_all (pagespdf);
  printf ("---cpdf_scalePages()\n");
  cpdf_scalePages (pagespdf, r3, 1.5, 1.8);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/scalepages.pdf", false, false);
  printf ("---cpdf_scaleToFit()\n");
  cpdf_scaleToFit (pagespdf, r3, 1.5, 1.8, 0.9);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/scaletofit.pdf", false, false);
  printf ("---cpdf_scaleToFitPaper()\n");
  cpdf_scaleToFitPaper (pagespdf, r3, cpdf_a4portrait, 0.8);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/scaletofitpaper.pdf", false, false);
  printf ("---cpdf_scaleContents()\n");
  struct cpdf_position p = {.cpdf_anchor = cpdf_topLeft,.cpdf_coord1 =
      20,.cpdf_coord2 = 20 };
  cpdf_scaleContents (pagespdf, r3, p, 2.0);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/scalecontents.pdf", false, false);
  printf ("---cpdf_shiftContents()\n");
  cpdf_shiftContents (pagespdf, r3, 1.5, 1.25);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/shiftcontents.pdf", false, false);
  printf ("---cpdf_rotate()\n");
  cpdf_rotate (pagespdf, r3, 90);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/rotate.pdf", false, false);
  printf ("---cpdf_rotateBy()\n");
  cpdf_rotateBy (pagespdf, r3, 90);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/rotateby.pdf", false, false);
  printf ("---cpdf_rotateContents()\n");
  cpdf_rotateContents (pagespdf, r3, 35.0);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/rotatecontents.pdf", false, false);
  printf ("---cpdf_upright()\n");
  cpdf_upright (pagespdf, r3);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/upright.pdf", false, false);
  printf ("---cpdf_hFlip()\n");
  cpdf_hFlip (pagespdf, r3);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/hflip.pdf", false, false);
  printf ("---cpdf_vFlip()\n");
  cpdf_vFlip (pagespdf, r3);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/vflip.pdf", false, false);
  printf ("---cpdf_crop()\n");
  cpdf_crop (pagespdf, r3, 0.0, 0.0, 400.0, 500.0);
  prerr ();
  printf ("---cpdf_trimMarks()\n");
  cpdf_trimMarks (pagespdf, r3);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/trim_marks.pdf", false, false);
  printf ("---cpdf_showBoxes()\n");
  cpdf_showBoxes (pagespdf, r3);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/show_boxes.pdf", false, false);
  printf ("---cpdf_hardBox()\n");
  cpdf_hardBox (pagespdf, r3, "/MediaBox");
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/hard_box.pdf", false, false);
  cpdf_toFile (pagespdf, "testoutputs/crop.pdf", false, false);
  printf ("---cpdf_removeCrop()\n");
  cpdf_removeCrop (pagespdf, r3);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/remove_crop.pdf", false, false);
  printf ("---cpdf_removeTrim()\n");
  cpdf_removeTrim (pagespdf, r3);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/remove_trim.pdf", false, false);
  printf ("---cpdf_removeArt()\n");
  cpdf_removeArt (pagespdf, r3);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/remove_art.pdf", false, false);
  printf ("---cpdf_removeBleed()\n");
  cpdf_removeBleed (pagespdf, r3);
  prerr ();
  cpdf_toFile (pagespdf, "testoutputs/remove_bleed.pdf", false, false);
  cpdf_deletePdf (pagespdf);
  cpdf_deleteRange (r3);
  cpdf_onExit ();

/* CHAPTER 4. Encryption */
/* Encryption covered under Chapter 1 in cpdflib. */

/* CHAPTER 5. Compression */
  printf ("***** CHAPTER 5. Compression\n");
  int tocompress = cpdf_fromFile ("cpdflibmanual.pdf", "");
  printf ("---cpdf_compress()\n");
  cpdf_compress (tocompress);
  prerr ();
  cpdf_toFile (tocompress, "testoutputs/compressed.pdf", false, false);
  printf ("---cpdf_decompress()\n");
  cpdf_decompress (tocompress);
  prerr ();
  cpdf_toFile (tocompress, "testoutputs/decompressed.pdf", false, false);
  printf ("---cpdf_squeezeInMemory()\n");
  cpdf_squeezeInMemory (tocompress);
  cpdf_toFile (tocompress, "testoutputs/squeezedinmemory.pdf", false, false);
  prerr ();
  cpdf_deletePdf (tocompress);
  cpdf_onExit ();

/* CHAPTER 6. Bookmarks */
  printf ("***** CHAPTER 6. Bookmarks\n");
  int markspdf = cpdf_fromFile ("cpdflibmanual.pdf", "");
  printf ("---cpdf_startGetBookmarkInfo()\n");
  cpdf_startGetBookmarkInfo (markspdf);
  printf ("---cpdf_numberBookmarks()\n");
  int n_marks = cpdf_numberBookmarks ();
  prerr ();
  printf ("There are %i bookmarks\n", n_marks);
  for (int x = 0; x < n_marks; x++)
    {
      int level = cpdf_getBookmarkLevel (x);
      int page = cpdf_getBookmarkPage (markspdf, x);
      char *text = cpdf_getBookmarkText (x);
      int open = cpdf_getBookmarkOpenStatus (x);
      printf
	("Bookmark at level %i points to page %i and has text \"%s\" and open %i\n",
	 level, page, text, open);
    }
  prerr ();
  printf ("---cpdf_startGetBookmarkInfo()\n");
  cpdf_endGetBookmarkInfo ();
  prerr ();
  printf ("---cpdf_startSetBookmarkInfo()\n");
  cpdf_startSetBookmarkInfo (1);
  prerr ();
  cpdf_setBookmarkLevel (0, 0);
  cpdf_setBookmarkPage (markspdf, 0, 20);
  cpdf_setBookmarkOpenStatus (0, true);
  cpdf_setBookmarkText (0, "New bookmark!");
  prerr ();
  printf ("---cpdf_endSetBookmarkInfo()\n");
  cpdf_endSetBookmarkInfo (markspdf);
  prerr ();
  cpdf_deletePdf (markspdf);
  cpdf_onExit ();

/* CHAPTER 7. Presentations */
/* Not included in the library version */

/* CHAPTER 8. Logos, Watermarks and Stamps */

/*void cpdf_stampOn (int, int, int);
void cpdf_stampUnder (int, int, int);
void cpdf_stampExtended (int, int, int, int, int, struct cpdf_position, int);
int cpdf_combinePages (int, int);
void cpdf_addText (int,         
                   int,         
                   int,         
                   const char[],        
                   struct cpdf_position,        
                   double,
                   int,  
                   enum cpdf_font,
                   double,     
                   double,   
                   double,  
                   double, 
                   int,       
                   int,     
                   int,      
                   double,    
                   enum cpdf_justification,
                   int,  
                   int, 
                   const char[], 
                   double,   
                   int      
  );
void cpdf_addTextSimple (int, 
                         int, 
                         const char[],
                         struct cpdf_position,
                         enum cpdf_font,
                         double);
int cpdf_addTextHowMany (void);
char *cpdf_addTextReturnText (int);
double cpdf_addTextReturnX (int);
double cpdf_addTextReturnY (int);
double cpdf_addTextReturnRotation (int);
double cpdf_addTextReturnBaselineAdjustment (void);
void cpdf_removeText (int, int);
int cpdf_textWidth (enum cpdf_font, const char[]);*/

/* CHAPTER 9. Multipage facilities */
  printf ("***** CHAPTER 9. Multipage facilities\n");
  int mp = cpdf_fromFile ("cpdflibmanual.pdf", "");
  printf ("---cpdf_twoUp()\n");
  cpdf_twoUp (mp);
  prerr ();
  printf ("---cpdf_twoUpStack()\n");
  cpdf_twoUpStack (mp);
  prerr ();
  int r = cpdf_range (1, 10);
  printf ("---cpdf_padBefore()\n");
  cpdf_padBefore (mp, r);
  prerr ();
  printf ("---cpdf_padAfter()\n");
  cpdf_padAfter (mp, r);
  prerr ();
  printf ("---cpdf_padEvery()\n");
  cpdf_padEvery (mp, 5);
  prerr ();
  printf ("---cpdf_padMultiple()\n");
  cpdf_padMultiple (mp, 10);
  prerr ();
  printf ("---cpdf_padMultipleBefore()\n");
  cpdf_padMultipleBefore (mp, 23);
  prerr ();
  cpdf_toFile (mp, "testoutputs/mp.pdf", false, false);
  cpdf_deletePdf (mp);
  cpdf_deleteRange (r);
  cpdf_onExit ();

/* CHAPTER 10. Annotations */

/* Not in the library version */

/* CHAPTER 11. Document Information and Metadata */
  printf ("***** CHAPTER 11. Document Information and Metadata\n");
  int info = cpdf_fromFile ("cpdflibmanual.pdf", "");
  int r_info = cpdf_all(info);
  printf ("---cpdf_isLinearized()\n");
  printf ("is_linearized:%i\n", cpdf_isLinearized ("cpdflibmanual.pdf"));
  prerr ();
  printf ("---cpdf_getVersion()\n");
  printf ("minor version:%i\n", cpdf_getVersion (info));
  prerr ();
  printf ("---cpdf_getMajorVersion()\n");
  printf ("major version:%i\n", cpdf_getMajorVersion (info));
  prerr ();
  char *title = cpdf_getTitle (info);
  printf("title: %s\n", title);
  char *author = cpdf_getAuthor (info);
  printf("author: %s\n", author);
  char *subject = cpdf_getSubject (info);
  printf("subject: %s\n", subject);
  char *keywords = cpdf_getKeywords (info);
  printf("keywords: %s\n", keywords);
  char *creator = cpdf_getCreator (info);
  printf("creator: %s\n", creator);
  char *producer = cpdf_getProducer (info);
  printf("producer: %s\n", producer);
  char *creationdate = cpdf_getCreationDate (info);
  printf("creationdate: %s\n", creationdate);
  char *modificationdate = cpdf_getModificationDate (info);
  printf("modificationdate: %s\n", modificationdate);
  char *titleXMP = cpdf_getTitleXMP (info);
  printf("titleXMP: %s\n", titleXMP);
  char *authorXMP = cpdf_getAuthorXMP (info);
  printf("authorXMP: %s\n", authorXMP);
  char *subjectXMP = cpdf_getSubjectXMP (info);
  printf("subjectXMP: %s\n", subjectXMP);
  char *keywordsXMP = cpdf_getKeywordsXMP (info);
  printf("keywordsXMP: %s\n", keywordsXMP);
  char *creatorXMP = cpdf_getCreatorXMP (info);
  printf("creatorXMP: %s\n", creatorXMP);
  char *producerXMP = cpdf_getProducerXMP (info);
  printf("producerXMP: %s\n", producerXMP);
  char *creationdateXMP = cpdf_getCreationDateXMP (info);
  printf("creationdateXMP: %s\n", creationdateXMP);
  char *modificationdateXMP = cpdf_getModificationDateXMP (info);
  printf("modificationdateXMP: %s\n", modificationdateXMP);
  prerr();
  printf ("---cpdf_setTitle()\n");
  cpdf_setTitle (info, "new title");
  prerr();
  printf ("---cpdf_setAuthor()\n");
  cpdf_setAuthor (info, "new author");
  prerr();
  printf ("---cpdf_setSubject()\n");
  cpdf_setSubject (info, "new subject");
  prerr();
  printf ("---cpdf_setKeywords()\n");
  cpdf_setKeywords (info, "new keywords");
  prerr();
  printf ("---cpdf_setCreator()\n");
  cpdf_setCreator (info, "new creator");
  prerr();
  printf ("---cpdf_setProducer()\n");
  cpdf_setProducer (info, "new producer");
  prerr();
  printf ("---cpdf_setCreationDate()\n");
  cpdf_setCreationDate (info, "now");
  prerr();
  printf ("---cpdf_setModificationDate()\n");
  cpdf_setModificationDate (info, "now");
  prerr();
  printf ("---cpdf_setTitleXMP()\n");
  cpdf_setTitleXMP (info, "new title XMP");
  prerr();
  printf ("---cpdf_setAuthorXMP()\n");
  cpdf_setAuthorXMP (info, "new author XMP");
  prerr();
  printf ("---cpdf_setSubjectXMP()\n");
  cpdf_setSubjectXMP (info, "new subject XMP");
  prerr();
  printf ("---cpdf_setKeywordsXMP()\n");
  cpdf_setKeywordsXMP (info, "new keywords XMP");
  prerr();
  printf ("---cpdf_setCreatorXMP()\n");
  cpdf_setCreatorXMP (info, "new creator XMP");
  prerr();
  printf ("---cpdf_setProducerXMP()\n");
  cpdf_setProducerXMP (info, "new producer XMP");
  prerr();
  printf ("---cpdf_setCreationDateXMP()\n");
  cpdf_setCreationDateXMP (info, "now");
  prerr();
  printf ("---cpdf_setModificationDateXMP()\n");
  cpdf_setModificationDateXMP (info, "now");
  prerr();
  cpdf_toFile(info, "testoutputs/setinfo.pdf", false, false);
  printf ("---cpdf_getDateComponents()\n");
  int year, month, day, hour, minute, second, hour_offset, minute_offset;
  cpdf_getDateComponents ("D:20061108125017Z", &year, &month, &day, &hour,
                          &minute, &second, &hour_offset, &minute_offset);
  prerr();
  printf
    ("D:20061108125017Z = %i, %i, %i, %i, %i, %i, %i, %i\n",
     year, month, day, hour, minute, second, hour_offset, minute_offset);
  printf("---cpdf_getPageRotation");
  int rotation = cpdf_getPageRotation(info, 1);
  prerr();
  printf("/Rotate on page 1 = %i\n", rotation);
  printf("---cpdf_hasBox()\n");
  int hasbox = cpdf_hasBox(info, 1, "/CropBox");
  prerr();
  printf("hasbox: %i\n", hasbox);
  double minx, maxx, miny, maxy;
  printf ("---cpdf_getMediaBox()\n");
  cpdf_getMediaBox (info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf ("Media: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf ("---cpdf_getCropBox()\n");
  cpdf_getCropBox (info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf ("Crop: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf ("--cpdf_getBleedBox()\n");
  cpdf_getBleedBox (info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf ("Bleed: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf ("---cpdf_getArtBox()\n");
  cpdf_getArtBox (info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf ("Art: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf ("---cpdf_getTrimBox()\n");
  cpdf_getTrimBox (info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf ("Trim: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf ("---cpdf_setMediabox()\n");
  cpdf_setMediabox (info, r_info, 100, 500, 150, 550);
  prerr();
  printf ("---cpdf_setCropBox()\n");
  cpdf_setCropBox (info, r_info, 100, 500, 150, 550);
  prerr();
  printf ("---cpdf_setTrimBox()\n");
  cpdf_setTrimBox (info, r_info, 100, 500, 150, 550);
  prerr();
  printf ("---cpdf_setArtBox()\n");
  cpdf_setArtBox (info, r_info, 100, 500, 150, 550);
  prerr();
  printf ("---cpdf_setBleedBox()\n");
  cpdf_setBleedBox (info, r_info, 100, 500, 150, 550);
  prerr();
  cpdf_toFile(info, "testoutputs/setboxes.pdf", false, false);
  printf ("---cpdf_markTrapped()\n");
  cpdf_markTrapped (info);
  prerr();
  printf ("---cpdf_markTrappedXMP()\n");
  cpdf_markTrappedXMP (info);
  prerr();
  cpdf_toFile(info, "testoutputs/trapped.pdf", false, false);
  printf ("---cpdf_markUntrapped()\n");
  cpdf_markUntrapped (info);
  prerr();
  printf ("---cpdf_markUntrappedXMP()\n");
  cpdf_markUntrappedXMP (info);
  prerr();
  cpdf_toFile(info, "testoutputs/untrapped.pdf", false, false);
  printf("---cpdf_setPageLayout()\n");
  cpdf_setPageLayout (info, cpdf_twoColumnLeft);
  prerr();
  printf("---cpdf_setPageMode()\n");
  cpdf_setPageMode (info, cpdf_useOutlines);
  prerr();
  printf("---cpdf_hideToolbar()\n");
  cpdf_hideToolbar (info, true);
  prerr();
  printf("---cpdf_hideMenubar()\n");
  cpdf_hideMenubar (info, true);
  prerr();
  printf("---cpdf_setWindowUi()\n");
  cpdf_hideWindowUi (info, true);
  prerr();
  printf("---cpdf_fitWindow()\n");
  cpdf_fitWindow (info, true);
  prerr();
  printf("---cpdf_centerWindow()\n");
  cpdf_centerWindow (info, true);
  prerr();
  printf("---cpdf_displayDocTitle()\n");
  cpdf_displayDocTitle (info, true);
  prerr();
  printf("---cpdf_openAtPage()\n");
  cpdf_openAtPage (info, true, 4);
  prerr();
  cpdf_toFile(info, "testoutputs/open.pdf", false, false);
  printf("---cpdf_setMetadataFromFile()\n");
  cpdf_setMetadataFromFile (info, "cpdflib.ml");
  prerr();
  cpdf_toFile (info, "testoutputs/metadata1.pdf", false, false);
  printf ("---cpdf_setMetadataFromByteArray()\n");
  cpdf_setMetadataFromByteArray (info, "BYTEARRAY", 9);
  prerr();
  cpdf_toFile (info, "testoutputs/metadata2.pdf", false, false);
  int metadata_length;
  printf ("---cpdf_getMetadata()\n");
  void *metadata;
  metadata = cpdf_getMetadata (info, &metadata_length);
  prerr();
  printf ("---cpdf_removeMetadata()\n");
  cpdf_removeMetadata (info);
  prerr();
  printf ("---cpdf_createMetadata()\n");
  cpdf_createMetadata (info);
  prerr();
  cpdf_toFile (info, "testoutputs/metadata3.pdf", false, false);
  cpdf_setMetadataDate (info, "now");
  prerr();
  cpdf_toFile (info, "testoutputs/metadata4.pdf", false, false);
  printf ("---cpdf_addPageLabels()\n");
  cpdf_addPageLabels (info, cpdf_uppercaseRoman, "PREFIX-", 1, r_info, false);
  prerr();
  printf ("---cpdf_startGetPageLabels()\n");
  int pln = cpdf_startGetPageLabels (info);
  printf ("There are %i labels\n", pln);
  prerr();
  printf ("---cpdf_getPageLabelStyle()\n");
  int pl1 = cpdf_getPageLabelStyle (0);
  prerr();
  printf ("---cpdf_getPageLabelPrefix()\n");
  char *pl2 = cpdf_getPageLabelPrefix (0);
  prerr();
  printf ("---cpdf_getPageLabelOffset()\n");
  int pl3 = cpdf_getPageLabelOffset (0);
  prerr();
  printf ("---cpdf_getPageLabelRange()\n");
  int pl4 = cpdf_getPageLabelRange (0);
  prerr();
  printf("Page label: %i, %s, %i, %i\n", pl1, pl2, pl3, pl4);
  printf ("---cpdf_endGetPageLabels()\n");
  cpdf_endGetPageLabels ();
  prerr();
  printf ("---cpdf_addPageLabelStringForPage()\n");
  char *pllabel = cpdf_getPageLabelStringForPage (info, 1);
  prerr();
  printf("Label string is %s\n", pllabel);
  cpdf_removePageLabels (info);
  prerr();
  cpdf_toFile (info, "testoutputs/pagelabels.pdf", false, false);
  cpdf_deletePdf(info);
  cpdf_deleteRange(r_info);
  cpdf_onExit ();

/* CHAPTER 12. File Attachments */
  printf ("***** CHAPTER 12. File Attachments\n");
  int attachments = cpdf_fromFile ("testinputs/has_attachments.pdf", "");
  printf ("---cpdf_attachFile()\n");
  cpdf_attachFile ("testinputs/image.pdf", attachments);
  prerr ();
  printf ("---cpdf_attachFileToPage()\n");
  cpdf_attachFileToPage ("testinputs/image.pdf", attachments, 1);
  prerr ();
  printf ("---cpdf_attachFileFromMemory\n");
  cpdf_attachFileFromMemory ((void *) 0, 0, "metadata.txt", attachments);
  prerr ();
  printf ("---cpdf_attachFileToPageFromMemory\n");
  cpdf_attachFileToPageFromMemory ((void *) 0, 0, "metadata.txt", attachments,
				   1);
  prerr ();
  cpdf_toFile (attachments, "testoutputs/with_attachments.pdf", false, false);
  printf ("---cpdf_numberGetAttachments()\n");
  cpdf_startGetAttachments (attachments);
  prerr ();
  printf ("---cpdf_numberGetAttachments()\n");
  int numatt = cpdf_numberGetAttachments ();
  prerr ();
  printf ("There are %i attachements to get\n", numatt);
  for (int x = 0; x < numatt; x++)
    {
      printf ("Attachment %i is named %s\n", x, cpdf_getAttachmentName (x));
      printf ("It is on page %i\n", cpdf_getAttachmentPage (x));
      int length;
      cpdf_getAttachmentData (x, &length);
      printf ("Contains %i bytes of data\n", length);
    };
  prerr ();
  printf ("---cpdf_endGetAttachments()\n");
  cpdf_endGetAttachments ();
  prerr ();
  printf ("cpdf_removeAttachedFiles()\n");
  cpdf_removeAttachedFiles (attachments);
  prerr ();
  cpdf_toFile (attachments, "testoutputs/removed_attachments.pdf", false,
	       false);
  cpdf_deletePdf (attachments);
  cpdf_onExit ();

/* CHAPTER 13. Images */
  printf ("***** CHAPTER 13. Images\n");
  int images = cpdf_fromFile ("testinputs/image.pdf", "");
  printf ("---cpdf_startGetImageResolution()\n");
  int n = cpdf_startGetImageResolution (images, 500000.);
  prerr ();
  for (int x = 0; x < n; x++)
    {
      int page = cpdf_getImageResolutionPageNumber (x);
      char *name = cpdf_getImageResolutionImageName (x);
      int xp = cpdf_getImageResolutionXPixels (x);
      int yp = cpdf_getImageResolutionYPixels (x);
      double xres = cpdf_getImageResolutionXRes (x);
      double yres = cpdf_getImageResolutionYRes (x);
      printf ("IMAGE: %i, %s, %i, %i, %f, %f\n", page, name, xp, yp, xres,
	      yres);
    }
  prerr ();
  printf ("---cpdf_endGetImageResolution()\n");
  cpdf_endGetImageResolution ();
  prerr ();
  cpdf_deletePdf (images);
  cpdf_onExit ();

/* CHAPTER 14. Fonts */
  printf ("***** CHAPTER 14. Fonts\n");
  int fonts = cpdf_fromFile ("cpdflibmanual.pdf", "");
  int fonts2 = cpdf_fromFile ("frontmatter.pdf", "");
  printf ("---cpdf_startGetFontInfo()\n");
  cpdf_startGetFontInfo (fonts);
  prerr ();
  printf ("---cpdf_numberFonts()\n");
  int n_fonts = cpdf_numberFonts ();
  prerr ();
  for (int x = 0; x < n_fonts; x++)
    {
      printf ("Page %i, font %s has type %s and encoding %s\n",
	      cpdf_getFontPage (x),
	      cpdf_getFontName (x),
	      cpdf_getFontType (x), cpdf_getFontEncoding (x));
    };
  prerr ();
  printf ("---cpdf_endGetFontInfo()\n");
  cpdf_endGetFontInfo ();
  prerr ();
  printf ("---cpdf_removeFonts()\n");
  int fontrange = cpdf_all (fonts);
  cpdf_removeFonts (fonts);
  prerr ();
  cpdf_toFile (fonts, "testoutputs/remove_fonts.pdf", false, false);
  printf ("---cpdf_copyFont()\n");
  cpdf_copyFont (fonts, fonts2, fontrange, 1, "/F0");
  prerr ();
  cpdf_deletePdf (fonts);
  cpdf_deletePdf (fonts2);
  cpdf_deleteRange (fontrange);
  cpdf_onExit ();

/* CHAPTER 15. Miscellaneous */
  printf ("***** CHAPTER 15. Miscellaneous\n");
  int misc = cpdf_fromFile ("cpdflibmanual.pdf", "");
  int misc2 = cpdf_fromFile ("frontmatter.pdf", "");
  int misc_r = cpdf_all (misc);
  printf ("---cpdf_draft()\n");
  cpdf_draft (misc, misc_r, true);
  prerr ();
  printf ("---cpdf_removeAlltext()\n");
  cpdf_removeAllText (misc, misc_r);
  prerr ();
  printf ("---cpdf_blackText()\n");
  cpdf_blackText (misc, misc_r);
  prerr ();
  printf ("---cpdf_blackLines()\n");
  cpdf_blackLines (misc, misc_r);
  prerr ();
  printf ("---cpdf_blackFills()\n");
  cpdf_blackFills (misc, misc_r);
  prerr ();
  printf ("---cpdf_thinLines()\n");
  cpdf_thinLines (misc, misc_r, 2.0);
  prerr ();
  printf ("---cpdf_copyId()\n");
  cpdf_copyId (misc2, misc);
  prerr ();
  printf ("---cpdf_removeId()\n");
  cpdf_removeId (misc);
  prerr ();
  printf ("---cpdf_setVersion()\n");
  cpdf_setVersion (misc, 1);
  prerr ();
  printf ("---cpdf_removeDictEntry()\n");
  cpdf_removeDictEntry (misc, "/Producer");
  prerr ();
  printf ("---cpdf_removeClipping()\n");
  cpdf_removeClipping (misc, misc_r);
  prerr ();
  cpdf_toFile (misc, "testoutputs/misc.pdf", false, false);
  cpdf_deletePdf (misc);
  cpdf_deletePdf (misc2);
  cpdf_deleteRange (misc_r);
  cpdf_onExit ();

/* CHAPTER 16. Undocumented or Experimental */
  printf ("***** CHAPTER 16. Undocumented or Experimental\n");
  int undoc = cpdf_fromFile ("cpdflibmanual.pdf", "");
  int logo = cpdf_fromFile ("logo.pdf", "");
  int r_undoc = cpdf_all (undoc);
  printf ("---cpdf_stampAsXObject()\n");
  char *name = cpdf_stampAsXObject (undoc, r_undoc, logo);
  prerr ();
  char content[200];
  sprintf (content,
	   "q 1 0 0 1 100 100 cm %s Do Q q 1 0 0 1 300 300 cm %s Do Q q 1 0 0 1 500 500 cm %s Do Q",
	   name, name, name);
  printf ("---cpdf_addContent()\n");
  cpdf_addContent (content, true, undoc, r_undoc);
  prerr ();
  printf ("---cpdf_outputJSON()\n");
  cpdf_outputJSON ("testoutputs/json.json", true, true, undoc);
  prerr ();
  printf ("---cpdf_OCGCoalesce()\n");
  cpdf_OCGCoalesce (undoc);
  prerr ();
  printf ("---cpdf_OCGRename()\n");
  cpdf_OCGRename (undoc, "a", "b");
  prerr ();
  printf ("---cpdf_OCGOrderAll()\n");
  cpdf_OCGOrderAll (undoc);
  prerr ();
  printf ("---cpdf_setDemo()\n");
  cpdf_setDemo (true);
  prerr ();
  cpdf_toFile (undoc, "testoutputs/demo.pdf", false, false);
  cpdf_deletePdf (undoc);
  cpdf_deletePdf (logo);
  cpdf_deleteRange (r_undoc);
  cpdf_onExit ();
  return 0;
}
