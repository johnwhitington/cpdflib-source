/* cpdflibwrapper.h */
/* A C wrapper to cpdf PDF tools library */
/* Free for non-commercial use. See LICENSE for details */
/* To purchase a license, please visit http://www.coherentpdf.com/ */

/* This function must be called with argv before using the library. */
extern void caml_startup (char **);

/* Errors */
int lastError;
char* lastErrorString;
void clearError (void);

void onexit (void);

/* Undo support */

/* Undo a document. Returns true if managed to undo, false if nothing to undo to. */
int undo(int);

/* Redo a document. Returns true if managed to redo, false if nothing to redo to. */
int redo(int);

/* Mark a document for update. This copies the document so the change can be undone later */
void aboutToUpdate(int);
void aboutToUpdateDeep(int);

/* Abort such an update due to an error part-way through the update */
void abortUpdate(int);

int startEnumeratePDFs(void);
int enumeratePDFsKey(int);
char* enumeratePDFsInfo(int);
void endEnumeratePDFs(void);

void deletePdf(int);
void replacePdf(int, int);

void setdemo(int);

/* CHAPTER 1. Basics */
double ptOfCm (double);
double ptOfMm (double);
double ptOfIn (double);
double cmOfPt (double);
double mmOfPt (double);
double inOfPt (double);

int parsePagespec(int, char*);
int validatePagespec(char *);
char* stringOfPagespec(int, int);

int blankrange(void);
void deleterange(int);
int range(int, int);
int even(int);
int odd(int);
int range_union(int, int);
int difference(int, int);
int removeDuplicates(int);
int rangeLength(int);
int rangeGet(int, int);
int rangeAdd(int, int);
int isInRange(int, int);

int fromFile(char*);

int fromFileLazy(char*);

//int fromFileDecrypt(char*, char*);

int blankDocument(double, double, int);

enum papersize {a0portrait, a1portrait, a2portrait, a3portrait, a4portrait, a5portrait, a0landscape, a1landscape, a2landscape, a3landscape, a4landscape, a5landscape, usletterportrait, usletterlandscape, uslegalportrait, uslegallandscape};

int blankDocumentPaper(int, int);

int pages(int);

int pagesFast(char*, char*);

void toFile(int, char*, int, int);

int all(int);

int isEncrypted(int);
int lookupPdfStatus(int);
int hasPermissionStatus(int, int);
int lookupPdfEncryption(int);
char* lookupPdfUserPassword(int);

/* Make it happen imperatively. Need to fix this/document in .NET version... */
void decryptPdf(int, char*);

void decryptPdfOwner(int, char*);

enum permission {noEdit, noPrint, noCopy, noAnnot, noForms, noExtract, noAssemble, noHqPrint};

enum encryption_method {pdf40bit, pdf128bit, aes128bitfalse, aes128bittrue};

void toFileEncrypted(int, int, int*, int, char*, char*, int, int, char*);

void toFileRecrypting(int, int, char*, char*);

int hasPermission(int, enum permission);

enum encryption_method encryptionKind(int);

/* CHAPTER 2. Merging and Splitting */
int mergeSimple(int*, int);

int merge(int*, int, int, int);

int mergeSame(int*, int, int, int, int*);

int selectPages(int, int);

//int* splitOnBookmarks(int, int, int*);

/* CHAPTER 3. Pages */
void scalePages(int, int, double, double);
void scaleToFit(int, int, double, double);
void scaleToFitPaper(int, int, int);

enum anchor { posCentre, posLeft, posRight, top, topLeft, topRight, left, bottomLeft, bottom, bottomRight, right };

struct position {
  int anchor;
  double coord1;
  double coord2;
};

void scaleContents(int, int, struct position, double);
void shiftContents(int, int, double, double);
void rotate(int, int, int);
void rotateBy(int, int, int);
void rotateContents(int, int, double);
void upright(int, int);
void hFlip(int, int);
void vFlip(int, int);
void crop(int, int, double, double, double, double);
void removeCrop(int, int);
void removeTrim(int, int);
void removeArt(int, int);
void removeBleed(int, int);




/* CHAPTER 5. Compression */
void compress(int);

void decompress(int);

/* CHAPTER 6. Bookmarks */
void startGetBookmarkInfo(int);
void endGetBookmarkInfo(void);
int numberBookmarks(void);
int getBookmarkLevel(int);
int getBookmarkPage(int, int);

/* CHAPTER 7. Presentations */
/* CHAPTER 8. Logos, Watermarks and Stamps */
void stampOn(int, int, int);
void stampUnder(int, int, int);
int combinePages(int, int);
void addText(int, int, int, char*, struct position, double, int, int, double, double, double, double, int, int, int, double, int, int, char*);
int addTextHowMany(void);
char* addTextReturnText(int);
double addTextReturnX(int);
double addTextReturnY(int);
double addTextReturnRotation(int);
double addTextReturnBaselineAdjustment(void);

void removeText(int, int);
int textWidth (int, char*);

/* CHAPTER 9. Multipage facilities */
void twoUp(int);
void padBefore(int, int);
void padAfter(int, int);

/* CHAPTER 10. Annotations */
/* CHAPTER 11. Document Information and Metadata */
int numberFonts(void);
int getFontPage(int);
char* getFontName(int);
char* getFontType(int);
char* getFontEncoding(int);
void startGetFontInfo(int);
void endGetFontInfo(void);

int isLinearized(char*);
int getVersion(int);
char* getTitle(int);
char* getAuthor(int);
char* getSubject(int);
char* getKeywords(int);
char* getCreator(int);
char* getProducer(int);
char* getCreationDate(int);
void getDateComponents(char*, int*, int*, int*, int*, int*, int*, int*, int*);
char* dateStringOfComponents(int, int, int, int, int, int, int, int);
char* getModificationDate(int);
void setVersion(int, int);
void setTitle(int, char*);
void setAuthor(int, char*);
void setSubject(int, char*);
void setKeywords(int, char*);
void setCreator(int, char*);
void setProducer(int, char*);
void setCreationDate(int, char*);
void setModificationDate(int, char*);
void markTrapped(int);
void markUntrapped(int);
void setPageLayout(int, int);
void setPageMode(int, int);
int hasBox(int, int, char*);
void getMediaBox(int, int, double*, double*, double*, double*);
void setMediabox(int, int, double, double, double, double);
void getCropBox(int, int, double*, double*, double*, double*);
void setCropBox(int, int, double, double, double, double);
void getTrimBox(int, int, double*, double*, double*, double*);
void setTrimBox(int, int, double, double, double, double);
void getArtBox(int, int, double*, double*, double*, double*);
void setArtBox(int, int, double, double, double, double);
void getBleedBox(int, int, double*, double*, double*, double*);
void setBleedBox(int, int, double, double, double, double);

void hideToolbar(int, int);
void hideMenubar(int, int);
void hideWindowUi(int, int);
void fitWindow(int, int);
void centerWindow(int, int);
void displayDocTitle(int, int);
void setMetadataFromFile(int, char*);
void setMetadataFromByteArray(int, char*, int);
void* getMetadata(int, int*);
void removeMetadata(int);

/* CHAPTER 12. File Attachments */
void attachFile(char*, int);
void removeAttachedFiles(int);
void startGetAttachments(int);
int numberGetAttachments(void);
void endGetAttachments(void);
char* getAttachmentName(int);

/* CHAPTER 13. Miscellaneous */
void draft(int, int, int);
void blackText(int, int);
void blackLines(int, int);
void blackFills(int, int);
void thinLines(int, int, double);
void copyId(int, int);

void addPageLabels(int, int, char*, int, int);


