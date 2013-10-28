/* cpdflibwrapper.h */
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
double cpdf_ptOfCm (double);
double cpdf_ptOfMm (double);
double cpdf_ptOfIn (double);
double cpdf_cmOfPt (double);
double cpdf_mmOfPt (double);
double cpdf_inOfPt (double);

int cpdf_parsePagespec(int, char*);
int cpdf_validatePagespec(char *);
char* cpdf_stringOfPagespec(int, int);

int cpdf_blankRange(void);
void cpdf_deleteRange(int);
int cpdf_range(int, int);
int cpdf_even(int);
int cpdf_odd(int);
int cpdf_rangeUnion(int, int);
int cpdf_difference(int, int);
int cpdf_removeDuplicates(int);
int cpdf_rangeLength(int);
int cpdf_rangeGet(int, int);
int cpdf_rangeAdd(int, int);
int cpdf_isInRange(int, int);

int cpdf_fromFile(char*);

int cpdf_fromFileLazy(char*);

int cpdf_blankDocument(double, double, int);

enum cpdf_papersize {cpdf_a0portrait, cpdf_a1portrait, cpdf_a2portrait, cpdf_a3portrait, cpdf_a4portrait, cpdf_a5portrait, cpdf_a0landscape, cpdf_a1landscape, cpdf_a2landscape, cpdf_a3landscape, cpdf_a4landscape, cpdf_a5landscape, cpdf_usletterportrait, cpdf_usletterlandscape, cpdf_uslegalportrait, cpdf_uslegallandscape};

int cpdf_blankDocumentPaper(int, int);

int cpdf_pages(int);

int cpdf_pagesFast(char*, char*);

void cpdf_toFile(int, char*, int, int);

int cpdf_all(int);

int cpdf_isEncrypted(int);


void cpdf_decryptPdf(int, char*);

void cpdf_decryptPdfOwner(int, char*);

enum cpdf_permission {cpdf_noEdit, cpdf_noPrint, cpdf_noCopy, cpdf_noAnnot, cpdf_noForms, cpdf_noExtract, cpdf_noAssemble, cpdf_noHqPrint};

enum cpdf_encryptionMethod {cpdf_pdf40bit, cpdf_pdf128bit, cpdf_aes128bitfalse, cpdf_aes128bittrue};

void cpdf_toFileEncrypted(int, int, int*, int, char*, char*, int, int, char*);

void cpdf_toFileRecrypting(int, int, char*, char*);

int cpdf_hasPermission(int, enum cpdf_permission);

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

enum cpdf_anchor { cpdf_posCentre, cpdf_posLeft, cpdf_posRight, cpdf_top, cpdf_topLeft, cpdf_topRight, cpdf_left, cpdf_bottomLeft, cpdf_bottom, cpdf_bottomRight, cpdf_right };

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
void cpdf_compress(int);

void cpdf_decompress(int);

/* CHAPTER 6. Bookmarks */
void cpdf_startGetBookmarkInfo(int);
void cpdf_endGetBookmarkInfo(void);
int cpdf_numberBookmarks(void);
int cpdf_getBookmarkLevel(int);
int cpdf_getBookmarkPage(int, int);

/* CHAPTER 7. Presentations */
/* CHAPTER 8. Logos, Watermarks and Stamps */
void cpdf_stampOn(int, int, int);
void cpdf_stampUnder(int, int, int);
int cpdf_combinePages(int, int);
void cpdf_addText(int, int, int, char*, struct cpdf_position, double, int, int, double, double, double, double, int, int, int, double, int, int, char*);
int cpdf_addTextHowMany(void);
char* cpdf_addTextReturnText(int);
double cpdf_addTextReturnX(int);
double cpdf_addTextReturnY(int);
double cpdf_addTextReturnRotation(int);
double cpdf_addTextReturnBaselineAdjustment(void);

void cpdf_removeText(int, int);
int cpdf_textWidth (int, char*);

/* CHAPTER 9. Multipage facilities */
void cpdf_twoUp(int);
void cpdf_padBefore(int, int);
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
void cpdf_attachFile(char*, int);
void cpdf_removeAttachedFiles(int);
void cpdf_startGetAttachments(int);
int cpdf_numberGetAttachments(void);
void cpdf_endGetAttachments(void);
char* cpdf_getAttachmentName(int);

/* CHAPTER 13. Miscellaneous */
void cpdf_draft(int, int, int);
void cpdf_blackText(int, int);
void cpdf_blackLines(int, int);
void cpdf_blackFills(int, int);
void cpdf_thinLines(int, int, double);
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


