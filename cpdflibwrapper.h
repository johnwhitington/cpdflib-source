/* A C wrapper to cpdf PDF tools library */
/* Free for non-commercial use. See LICENSE for details */
/* To purchase a license, please visit http://www.coherentpdf.com/ */

/* CHAPTER 0. Preliminaries */

/* The function cpdf_startup must be called with argv before using the library.
 * */
void cpdf_startup (char **);

/* Set demo mode. Upon library startup is false. If set, files written will
 * have the text DEMO stamped over each page. This stamping will also slow down
 * the library significantly.  */
void cpdf_setDemo(int);

/* Errors. lastError and lastErrorString hold information about the last error
 * to have occurred. They should be consulted after each call. If
 * cpdf_lastError is non-zero, there was an error, and cpdf_lastErrorString
 * gives details. If cpdf_lastError is zero, there was no error on the most
 * recent cpdf call. */
int cpdf_lastError;
char* cpdf_lastErrorString;

/* Clear the current error state. */
void cpdf_clearError (void);

/* A debug function which prints some information about resource usage. This
 * can be used to detect if PDFs or ranges are being deallocated properly. */
void cpdf_onExit (void);

/* Remove a PDF from memory, given its number. */
void cpdf_deletePdf(int);

/* Calling replacePdf(a, b) places PDF b under number a. Original a and b are
 * no longer available. */
void cpdf_replacePdf(int, int);

/* To enumerate the list of currently allocated PDFs, call
 * cpdf_startEnumeratePDFs which gives the number, n, of PDFs allocated, then
 * cpdf_enumeratePDFsInfo and cpdf_enumeratePDFsKey with index numbers from
 * 0...(n - 1). Call cpdf_endEnumeratePDFs to clean up. */
int cpdf_startEnumeratePDFs(void);
int cpdf_enumeratePDFsKey(int);
char* cpdf_enumeratePDFsInfo(int);
void cpdf_endEnumeratePDFs(void);


/* CHAPTER 1. Basics */

/* Convert a figure in centimetres to points (72 points to 1 inch) */
double cpdf_ptOfCm (double);

/* Convert a figure in millimetres to points (72 points to 1 inch) */
double cpdf_ptOfMm (double);

/* Convert a figure in inches to points (72 points to 1 inch) */
double cpdf_ptOfIn (double);

/* Convert a figure in points to centimetres (72 points to 1 inch) */
double cpdf_cmOfPt (double);

/* Convert a figure in points to millimetres (72 points to 1 inch) */
double cpdf_mmOfPt (double);

/* Convert a figure in points to inches (72 points to 1 inch) */
double cpdf_inOfPt (double);

/* A page range is a list of page numbers used to restrict operations to
 * certain pages. A page specification is a textual description of a page
 * range, such as "1-12,18-end". Here is the syntax:

 o A dash (-) defines ranges, e.g. 1-5 or 6-3.

 o A comma (,) allows one to specify several ranges, e.g. 1-2,4-5.

 o The word end represents the last page number.

 o The words odd and even can be used in place of or at the end of a page range
 to restrict to just the odd or even pages.

 o The word reverse is the same as end-1.

 o The word all is the same as 1-end.

 o A range must contain no spaces.

 o A tilde ( ̃) defines a page number counting from the end of the document
 rather than the beginning. Page  ̃1 is the last page,  ̃2 the penultimate page
 etc. */

/* Parse a page specification with reference to a given PDF (the PDF is
 * supplied so that page ranges which reference pages which do not exist are
 * rejected). */
int cpdf_parsePagespec(int, char*);

/* Validates a page specification so far as is possible in the absence of the
 * actual document */
int cpdf_validatePagespec(char *);

/* Build a page specification from a page range. For example, the range
 * containing 1,2,3,6,7,8 in a document of 8 pages might yield "1-3,6-end" */
char* cpdf_stringOfPagespec(int, int);

/* Create a range with no pages in */
int cpdf_blankRange(void);

/* Delete a range. Ranges should be deleted once finished with. */
void cpdf_deleteRange(int);

/* Build a range from one page to another inclusive. For example,
 * cpdf_range(3,7) gives the range 3,4,5,6,7 */
int cpdf_range(int, int);

/* Make a range which contains just the even pages of another range */
int cpdf_even(int);

/* Make a range which contains just the odd pages of another range */
int cpdf_odd(int);

/* Make the union of two ranges cpdf_union(a,b) gives a range containing the
 * pages in range a and range b. */
int cpdf_rangeUnion(int, int);

/* Make the difference of two ranges. cpdf_difference(a, b) gives a range
 * containing all the pages in a except for those which are also in b */
int cpdf_difference(int, int);

/* Deduplicate a range, making a new one */
int cpdf_removeDuplicates(int);

/* Give the number of pages in a range */
int cpdf_rangeLength(int);

/* Get the page number at position n in a range, where n runs from 0 to
 * rangeLength - 1. For example, cpdf_rangeGet(range, n) gives the page number
 * at position n in the range. */
int cpdf_rangeGet(int, int);

/* Calling cpdf_rangeAdd(range, page) will add the page to a range, if it is
 * not already there. */
int cpdf_rangeAdd(int, int);

/* cpdf_isInRange(range, page) returns true if the page is in the range, false
 * otherwise. */
int cpdf_isInRange(int, int);

/* Load a PDF file from a given file. Also supply a user password (possibly
 * blank) in case the file is encypted. It won't be decrypted, but sometimes
 * the password is needed just to load the file. */
int cpdf_fromFile(char*, char*);

/* Load a PDF from a file, doing only minimal parsing. The objects will be read
 * and parsed when they are actually needed. Use this when the whole file won't
 * be required. Also supply a user password (possibly blank) in case the file
 * is encypted. It won't be decrypted, but sometimes the password is needed
 * just to load the file. */
int cpdf_fromFileLazy(char*, char*);

/* Create a blank document with pages of the given width (in points), height
 * (in points), and number of pages. */
int cpdf_blankDocument(double, double, int);

/* Standard page sizes. */
enum cpdf_papersize
  {cpdf_a0portrait,
   cpdf_a1portrait,
   cpdf_a2portrait,
   cpdf_a3portrait,
   cpdf_a4portrait,
   cpdf_a5portrait,
   cpdf_a0landscape,
   cpdf_a1landscape,
   cpdf_a2landscape,
   cpdf_a3landscape,
   cpdf_a4landscape,
   cpdf_a5landscape,
   cpdf_usletterportrait,
   cpdf_usletterlandscape,
   cpdf_uslegalportrait,
   cpdf_uslegallandscape};

/* Make a blank document given a page size and number of pages. */
int cpdf_blankDocumentPaper(enum cpdf_papersize, int);

/* Return the number of pages in a PDF. */
int cpdf_pages(int);

/* Return the number of pages in a given PDF, with given user encryption
 * password.  cpdf_pagesFast(password, filename) tries to do this as fast as
 * possible, without loading the whole file. */
int cpdf_pagesFast(char*, char*);

/* cpdf_toFile (pdf, filename, linearize, make_id) writes the file to a given
 * filename. If linearize is true, it will be linearized. If make_id is true,
 * it will be given a new ID. */
void cpdf_toFile(int, char*, int, int);

/* The range containing all the pages in a given document */
int cpdf_all(int);

/* Returns true if a documented is encrypted, false otherwise. */
int cpdf_isEncrypted(int);

/* Attempt to decrypt a PDF using the given user password. The error code is
 * non-zero if the decryption fails. */
void cpdf_decryptPdf(int, char*);

/* Attempt to decrypt a PDF using the given owner password. The error code is
 * non-zero if the decryption fails. */
void cpdf_decryptPdfOwner(int, char*);

/* File permissions. These are inverted, in the sense that the presence of one
 * of them indicates a restriction. */
enum cpdf_permission
  {cpdf_noEdit,
   cpdf_noPrint,
   cpdf_noCopy,
   cpdf_noAnnot,
   cpdf_noForms,
   cpdf_noExtract,
   cpdf_noAssemble,
   cpdf_noHqPrint};

/* Encryption methods. Suffixes 'false' and 'true' indicates lack of or
 * presence of encryption for XML metadata streams */
enum cpdf_encryptionMethod
  {cpdf_pdf40bit,
   cpdf_pdf128bit,
   cpdf_aes128bitfalse,
   cpdf_aes128bittrue,
   cpdf_aes256bitfalse, /* Deprecated. Do not use for new files */
   cpdf_aes256bittrue,  /* Deprecated. Do not use for new files */
   cpdf_aes256bitisofalse,
   cpdf_aes256bitisotrue};

/* Write a file with encryption:
  cpdf_toFileEncrypted(
    pdf,                   Document
    encryption_method,     Encryption method
    permissions,           Permissions array
    permission_length,     Length of permissions array
    owner_password,        Owner password, blank if none
    user_passwordi,        User password, blank if none
    linearize,             If true, linearize
    makeid,                If true, make a new ID
    filename)              Filename
*/
void cpdf_toFileEncrypted(int, int, int*, int, char*, char*, int, int, char*);

/* Write a modified file, re-encrypting it.

cpdf_toFileRecrypting(original, decrypted_and_modified, userpw, filename)

original is the original document, as read from file. decrypted_and_modified is
the processed file, ready to write. userpw is the user password for the PDF.
filename is the name of the file to write.

The PDF 'modified' is no longer usable and can be deleted.
*/
void cpdf_toFileRecrypting(int, int, char*, char*);

/* Return true if the given permission (restriction) is present. */
int cpdf_hasPermission(int, enum cpdf_permission);

/* Return the encryption method currently in use on a file. */
enum cpdf_encryptionMethod cpdf_encryptionKind(int);

/* CHAPTER 2. Merging and Splitting */
int cpdf_mergeSimple(int*, int);

int cpdf_merge(int*, int, int, int);

int cpdf_mergeSame(int*, int, int, int, int*);

int cpdf_selectPages(int, int);

/* CHAPTER 3. Pages */
void cpdf_scalePages(int, int, double, double);
void cpdf_scaleToFit(int, int, double, double);
void cpdf_scaleToFitPaper(int, int, int);

enum cpdf_anchor
  { cpdf_posCentre,
    cpdf_posLeft,
    cpdf_posRight,
    cpdf_top,
    cpdf_topLeft,
    cpdf_topRight,
    cpdf_left,
    cpdf_bottomLeft,
    cpdf_bottom,
    cpdf_bottomRight,
    cpdf_right };

struct cpdf_position {
  int cpdf_anchor;
  double cpdf_coord1;
  double cpdf_coord2;
};

void cpdf_scaleContents(int, int, struct cpdf_position, double);
void cpdf_shiftContents(int, int, double, double);
void cpdf_rotate(int, int, int);
void cpdf_rotateBy(int, int, int);
void cpdf_rotateContents(int, int, double);
void cpdf_upright(int, int);
void cpdf_hFlip(int, int);
void cpdf_vFlip(int, int);
void cpdf_crop(int, int, double, double, double, double);
void cpdf_removeCrop(int, int);
void cpdf_removeTrim(int, int);
void cpdf_removeArt(int, int);
void cpdf_removeBleed(int, int);


/* CHAPTER 5. Compression */

/* These functions can be used to compress and decompress all the streams in a
 * PDF file, for example for manual inspection. A PDF's streams are typically
 * compressed. Do not expect compression to reduce the size of an
 * already-compressed PDF. */

/* Compress any uncompressed streams in the given PDF using the Flate
 * algorithm. */
void cpdf_compress(int);

/* Uncompress any streams in the given PDF, so long as the compression method
 * is supported. */
void cpdf_decompress(int);


/* CHAPTER 6. Bookmarks */

/* Start the bookmark retrieval process for a given PDF. */
void cpdf_startGetBookmarkInfo(int);

/* Get the number of bookmarks for the PDF given to cpdf_startGetBookmarkInfo
 * */
int cpdf_numberBookmarks(void);

/* Get bookmark level for the given bookmark (0...(n - 1)) */
int cpdf_getBookmarkLevel(int);

/* Get the bookmark target page for the given PDF (which must be the same as
 * the PDF passed to cpdf_startGetBookmarkInfo) and bookmark (0...(n - 1)) */
int cpdf_getBookmarkPage(int, int);

/* Return the text of bookmark (0...(n - 1)) */
char* cpdf_getBookmarkText(int);

/* End the bookmark retrieval process, cleaning up. */
void cpdf_endGetBookmarkInfo(void);


/* CHAPTER 7. Presentations */
/* CHAPTER 8. Logos, Watermarks and Stamps */
void cpdf_stampOn(int, int, int);
void cpdf_stampUnder(int, int, int);
int cpdf_combinePages(int, int);

void cpdf_addText(int, int, int, char*, struct cpdf_position, double, int, int,
double, double, double, double, int, int, int, double, int, int, char*);

int cpdf_addTextHowMany(void);
char* cpdf_addTextReturnText(int);
double cpdf_addTextReturnX(int);
double cpdf_addTextReturnY(int);
double cpdf_addTextReturnRotation(int);
double cpdf_addTextReturnBaselineAdjustment(void);

void cpdf_removeText(int, int);
int cpdf_textWidth (int, char*);

/* CHAPTER 9. Multipage facilities */

/* Impose a document two up */
void cpdf_twoUp(int);

/* Pad a document (first argument) before each page in the given range (second
 * argument) */
void cpdf_padBefore(int, int);

/* Pad a document (first argument) after each page in the given range (second
 * argument) */
void cpdf_padAfter(int, int);

/* CHAPTER 10. Annotations */
/* CHAPTER 11. Document Information and Metadata */
int cpdf_numberFonts(void);
int cpdf_getFontPage(int);
char* cpdf_getFontName(int);
char* cpdf_getFontType(int);
char* cpdf_getFontEncoding(int);
void cpdf_startGetFontInfo(int);
void cpdf_endGetFontInfo(void);

int cpdf_isLinearized(char*);
int cpdf_getVersion(int);
char* cpdf_getTitle(int);
char* cpdf_getAuthor(int);
char* cpdf_getSubject(int);
char* cpdf_getKeywords(int);
char* cpdf_getCreator(int);
char* cpdf_getProducer(int);
char* cpdf_getCreationDate(int);
void cpdf_getDateComponents(char*, int*, int*, int*, int*, int*, int*, int*, int*);
char* cpdf_dateStringOfComponents(int, int, int, int, int, int, int, int);
char* cpdf_getModificationDate(int);
void cpdf_setVersion(int, int);
void cpdf_setTitle(int, char*);
void cpdf_setAuthor(int, char*);
void cpdf_setSubject(int, char*);
void cpdf_setKeywords(int, char*);
void cpdf_setCreator(int, char*);
void cpdf_setProducer(int, char*);
void cpdf_setCreationDate(int, char*);
void cpdf_setModificationDate(int, char*);
void cpdf_markTrapped(int);
void cpdf_markUntrapped(int);
void cpdf_setPageLayout(int, int);
void cpdf_setPageMode(int, int);
int cpdf_hasBox(int, int, char*);
void cpdf_getMediaBox(int, int, double*, double*, double*, double*);
void cpdf_setMediabox(int, int, double, double, double, double);
void cpdf_getCropBox(int, int, double*, double*, double*, double*);
void cpdf_setCropBox(int, int, double, double, double, double);
void cpdf_getTrimBox(int, int, double*, double*, double*, double*);
void cpdf_setTrimBox(int, int, double, double, double, double);
void cpdf_getArtBox(int, int, double*, double*, double*, double*);
void cpdf_setArtBox(int, int, double, double, double, double);
void cpdf_getBleedBox(int, int, double*, double*, double*, double*);
void cpdf_setBleedBox(int, int, double, double, double, double);

void cpdf_hideToolbar(int, int);
void cpdf_hideMenubar(int, int);
void cpdf_hideWindowUi(int, int);
void cpdf_fitWindow(int, int);
void cpdf_centerWindow(int, int);
void cpdf_displayDocTitle(int, int);
void cpdf_setMetadataFromFile(int, char*);
void cpdf_setMetadataFromByteArray(int, char*, int);
void* cpdf_getMetadata(int, int*);
void cpdf_removeMetadata(int);

/* CHAPTER 12. File Attachments */

/* Attach a file, given its file name, and the pdf. It is attached at document
 * level. */
void cpdf_attachFile(char*, int);

/* Attach a file, given its file name, pdf, and the page number to which it
 * should be attached. */
void cpdf_attachFileToPage(char*, int, int);

/* Remove all page- and document-level attachments from a document */
void cpdf_removeAttachedFiles(int);

/* List information about attachments. Call cpdf_startGetAttachments first,
 * then cpdf_startGetAttachments to find out how many there are. Then
 * cpdf_getAttachmentName to return each one 0...(n - 1). Finally, call
 * cpdf_endGetAttachments to clean up. */
void cpdf_startGetAttachments(int);
int cpdf_numberGetAttachments(void);
char* cpdf_getAttachmentName(int);
void cpdf_endGetAttachments(void);


/* CHAPTER 13. Miscellaneous */

/* Make a draft document. The first argument is the document, second the range,
 * third is a boolean -- true to replace images with boxes, false to replace
 * them with nothing. */
void cpdf_draft(int, int, int);

/* Blacken all text in the given document and range */
void cpdf_blackText(int, int);

/* Blacken all lines in the given document and range */
void cpdf_blackLines(int, int);

/* Blacken all fills in the given document and range */
void cpdf_blackFills(int, int);

/* Thicken lines. cpdf_thinLines(pdf, range, min_thickness) thickens every line
 * less than min_thickness to min_thickness */
void cpdf_thinLines(int, int, double);

/* Copy the /ID from the first document to the second. */
void cpdf_copyId(int, int);


/* CHAPTER 14. Page labels */
void cpdf_addPageLabels(int, int, char*, int, int);


/* Special functionality 1. -- Encryption and Permission status */

/* Internal status of a pdf loaded by the library. This is data kept separate
 * from the actual PDF. */
enum cpdf_pdfStatus
  {cpdf_notEncrypted,
   cpdf_encrypted,
   cpdf_wasDecryptedWithUser,
   cpdf_wasDecryptedWithOwner};

/* Return the status of a PDF */
enum cpdf_pdfStatus cpdf_lookupPdfStatus(int);

/* Does a PDF have a given permission, assuming it is or was encrypted? */
int cpdf_hasPermissionStatus(int, enum cpdf_permission);

/* What is (or was) the encryption method? */
enum cpdf_encryptionMethod cpdf_lookupPdfEncryption(int);

/* Find the user password which was used to decrypt a PDF, if is has status
 * cpdf_wasDecryptedWithUser */
char* cpdf_lookupPdfUserPassword(int);


/* Special functionality 2. -- Undo */

/* Cpdf can hold multiple versions of each PDF, sharing data between them to
 * save memory. */

/* Mark a document for update. This copies the document so the change can be
 * undone later */
void cpdf_aboutToUpdate(int);

/* Same, but when a deep copy (no sharing of data) is required. */
void cpdf_aboutToUpdateDeep(int);

/* Abort such an update due to an error part-way through the update */
void cpdf_abortUpdate(int);

/* Undo a document. Returns true if managed to undo, false if nothing to undo
 * to. */
int cpdf_undo(int);

/* Redo a document. Returns true if managed to redo, false if nothing to redo
 * to. */
int cpdf_redo(int);


