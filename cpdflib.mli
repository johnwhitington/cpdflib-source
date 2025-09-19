(* CHAPTER 0. Preliminaries *)
val getLastError : unit -> int
val getLastErrorString : unit -> string
val clearError : unit -> unit

(* CHAPTER 1. Basics *)
type pdf

val fast : bool ref
val setFast : unit -> unit
val setSlow : unit -> unit
val embedStd14 : bool -> unit
val embedStd14Dir : string -> unit
val version : string
val startEnumeratePDFs : unit -> int
val enumeratePDFsKey : int -> int
val enumeratePDFsInfo : int -> string
val endEnumeratePDFs : unit -> unit
val deletePdf : int -> unit
val deleterange : int -> unit
val onexit : unit -> unit
type range = int
val parsePagespec : pdf -> string -> range
val stringOfPagespec : pdf -> range -> string
val ptOfCm : float -> float
val ptOfMm : float -> float
val ptOfIn : float -> float
val cmOfPt : float -> float
val mmOfPt : float -> float
val inOfPt : float -> float
val range : int -> int -> range
val blankrange : unit -> range
val makerange : int -> range
val writerange : range -> int -> int -> unit
val readrange : range -> int -> int
val lengthrange : range -> int
val addtorange : range -> int -> range
val even : range -> range
val odd : range -> range
val union : range -> range -> range
val difference : range -> range -> range
val removeDuplicates : range -> range
val isInRange: range -> int -> bool
val fromFile : string -> string -> pdf
val fromFileLazy : string -> string -> pdf
val fromMemory : Pdfio.rawbytes -> string -> int
val fromMemoryLazy : Pdfio.rawbytes -> string -> int
val toFile : pdf -> string -> bool -> bool -> unit
val toFileExt : pdf -> string -> bool -> bool -> bool -> bool -> bool -> unit
val toFileMemory : pdf -> bool -> bool -> Pdfio.rawbytes
val toFileMemoryExt : pdf -> bool -> bool -> bool -> bool -> bool -> Pdfio.rawbytes
val pages : pdf -> int
val pagesFast : string -> string -> int
val pagesFastMemory : string -> Pdfio.rawbytes -> int
val all : pdf -> int
val isEncrypted : pdf -> bool
val decryptPdf : pdf -> string -> unit
val decryptPdfOwner : pdf -> string -> unit
val toFileEncrypted : pdf -> int -> int array -> string -> string -> bool -> bool -> string -> unit
val toFileEncryptedExt : pdf -> int -> int array -> string -> string -> bool -> bool -> bool -> bool -> bool -> string -> unit
val toFileMemoryEncrypted : pdf -> int -> int array -> string -> string -> bool -> bool -> Pdfio.rawbytes
val toFileMemoryEncryptedExt : pdf -> int -> int array -> string -> string -> bool -> bool -> bool -> bool -> bool -> Pdfio.rawbytes
val hasPermission : pdf -> int -> bool
val encryptionKind : pdf -> int

(* CHAPTER 2. Merging and Splitting *)
val mergeSimple : pdf array -> pdf
val merge : pdf array -> bool -> bool -> pdf
val mergeSame : pdf array -> bool -> bool -> int array -> pdf
val selectPages : pdf -> range -> pdf

(* CHAPTER 3. Pages *)
val scalePages : pdf -> range -> float -> float -> unit
val scaleToFit : pdf -> range -> float -> float -> float -> unit
val scaleToFitPaper : pdf -> range -> int -> float -> unit
val scaleContents : pdf -> range -> int -> float -> float -> float -> unit
val shiftContents : pdf -> range -> float -> float -> unit
val shiftBoxes : pdf -> range -> float -> float -> unit
val rotate : pdf -> range -> int -> unit
val rotateBy : pdf -> range -> int -> unit
val rotateContents : pdf -> range -> float -> unit
val upright : pdf -> range -> unit
val hFlip : pdf -> range -> unit
val vFlip : pdf -> range -> unit
val crop : pdf -> range -> float -> float -> float -> float -> unit
val setMediabox : pdf -> range -> float -> float -> float -> float -> unit
val setCropBox : pdf -> int -> float -> float -> float -> float -> unit
val setTrimBox : pdf -> int -> float -> float -> float -> float -> unit
val setBleedBox : pdf -> int -> float -> float -> float -> float -> unit
val pageInfoJSON : pdf -> Pdfio.rawbytes
val setArtBox : pdf -> int -> float -> float -> float -> float -> unit
val getMediaBox : pdf -> int -> float * float * float * float
val getCropBox : pdf -> int -> float * float * float * float
val getArtBox : pdf -> int -> float * float * float * float
val getBleedBox : pdf -> int -> float * float * float * float
val getTrimBox : pdf -> int -> float * float * float * float
val removeCrop : pdf -> range -> unit
val removeArt : pdf -> range -> unit
val removeTrim : pdf -> range -> unit
val removeBleed : pdf -> range -> unit
val hardBox : pdf -> range -> string -> unit
val trimMarks : pdf -> range -> unit
val showBoxes : pdf -> range -> unit

(* CHAPTER 4. Encryption and Decryption *)

(* CHAPTER 5. Compression *)
val compress : pdf -> unit
val decompress : pdf -> unit
val squeezeInMemory : pdf -> unit

(* CHAPTER 6. Bookmarks *)
val startGetBookmarkInfo : pdf -> unit
val endGetBookmarkInfo : unit -> unit
val numberBookmarks : unit -> int
val getBookmarkPage : pdf -> int -> int
val getBookmarkLevel : int -> int
val getBookmarkText : int -> string
val getBookmarkOpenStatus : int -> bool
val startSetBookmarkInfo : int -> unit
val endSetBookmarkInfo : pdf -> unit
val setBookmarkPage : pdf -> int -> int -> unit
val setBookmarkLevel : int -> int -> unit
val setBookmarkText : int -> string -> unit
val setBookmarkOpenStatus : int -> bool -> unit
val getBookmarksJSON : pdf -> Pdfio.rawbytes
val setBookmarksJSON : pdf -> Pdfio.rawbytes -> unit
val tableOfContents : pdf -> string -> float -> string -> bool -> unit

(* CHAPTER 7. Presentations *)

(* CHAPTER 8. Logos, Watermarks and Stamps *)
val stampOn : pdf -> pdf -> range -> unit
val stampUnder : pdf -> pdf -> range -> unit
val stampExtended : pdf -> pdf -> range -> bool -> bool -> float -> float -> int -> bool -> unit 
val combinePages : pdf -> pdf -> pdf
val addText : bool -> pdf -> int -> string -> int -> float -> float -> float -> int -> string -> float -> float -> float -> float -> bool -> bool -> bool -> float -> Cpdfaddtext.justification -> bool -> bool -> string -> float -> bool -> unit
val textWidth : string -> string -> int
val removeText : pdf -> range -> unit
val addContent : string -> bool -> int -> int -> unit
val stampAsXObject : int -> int -> int -> string
 
(* CHAPTER 9. Multipage facilities *)
val twoUp : pdf -> unit
val twoUpStack : pdf -> unit
val impose : pdf -> float -> float -> bool -> bool -> bool -> bool -> bool -> float -> float -> float -> unit
val chop : pdf -> range -> int -> int -> bool -> bool -> bool -> unit
val chopH : pdf -> range -> bool -> float -> unit
val chopV : pdf -> range -> bool -> float -> unit
val padBefore : pdf -> range -> unit
val padAfter : pdf -> range -> unit
val padEvery : pdf -> int -> unit
val padMultiple : pdf -> int -> unit
val padMultipleBefore : pdf -> int -> unit

(* CHAPTER 10. Annotations *)
val annotationsJSON : pdf -> Pdfio.rawbytes
val removeAnnotations : pdf -> range -> unit
val setAnnotationsJSON : pdf -> Pdfio.rawbytes -> unit

(* CHAPTER 11. Document Information and Metadata *)
val getVersion : pdf -> int
val getMajorVersion : pdf -> int
val isLinearized : string -> bool
val hasObjectStreams : pdf -> bool
val id1 : pdf -> string
val id2 : pdf -> string
val hasAcroForm : pdf -> bool
val startGetSubformats : pdf -> int
val getSubformat : int -> string
val endGetSubformats : unit -> unit
val getTitle : pdf -> string
val getAuthor : pdf -> string
val getSubject : pdf -> string
val getKeywords : pdf -> string
val getCreator : pdf -> string
val getProducer : pdf -> string
val getCreationDate : pdf -> string
val getModificationDate : pdf -> string
val getTitleXMP : pdf -> string
val getAuthorXMP : pdf -> string
val getSubjectXMP : pdf -> string
val getKeywordsXMP : pdf -> string
val getCreatorXMP : pdf -> string
val getProducerXMP : pdf -> string
val getCreationDateXMP : pdf -> string
val getModificationDateXMP : pdf -> string
val getDateComponents : string -> Pdfdate.t
val dateStringOfComponents : int -> int -> int -> int -> int -> int -> int -> int -> string
val setTitle : pdf -> string -> unit
val setAuthor : pdf -> string -> unit
val setSubject : pdf -> string -> unit
val setKeywords : pdf -> string -> unit
val setCreator : pdf -> string -> unit
val setProducer : pdf -> string -> unit
val setCreationDate : pdf -> string -> unit
val setModificationDate : pdf -> string -> unit
val markTrapped : pdf -> unit
val markUntrapped : pdf -> unit
val markTrappedXMP : pdf -> unit
val markUntrappedXMP : pdf -> unit
val setTitleXMP : pdf -> string -> unit
val setAuthorXMP : pdf -> string -> unit
val setSubjectXMP : pdf -> string -> unit
val setKeywordsXMP : pdf -> string -> unit
val setCreatorXMP : pdf -> string -> unit
val setProducerXMP : pdf -> string -> unit
val setCreationDateXMP : pdf -> string -> unit
val setModificationDateXMP : pdf -> string -> unit
val hasBox : pdf -> int -> string -> bool
val numAnnots : pdf -> int -> int
val getPageRotation : pdf -> int -> int
val getPageLayout : pdf -> int
val setPageLayout : pdf -> int -> unit
val getPageMode : pdf -> int 
val setPageMode : pdf -> int -> unit
val hideToolbar : pdf -> bool -> unit
val getHideToolbar : pdf -> bool
val hideMenubar : pdf -> bool -> unit
val getHideMenubar : pdf -> bool
val hideWindowUi : pdf -> bool -> unit
val getHideWindowUi : pdf -> bool
val fitWindow : pdf -> bool -> unit
val getFitWindow : pdf -> bool
val centerWindow : pdf -> bool -> unit
val getCenterWindow : pdf -> bool
val displayDocTitle : pdf -> bool -> unit
val getDisplayDocTitle : pdf -> bool
val getNonFullScreenPageMode : pdf -> int
val nonFullScreenPageMode : pdf -> int -> unit
val openAtPage : pdf -> bool -> int -> unit
val openAtPageCustom : pdf -> string -> unit
val setMetadataFromFile : pdf -> string -> unit
val setMetadataFromByteArray : pdf -> Pdfio.rawbytes -> unit
val getMetadata : pdf -> Pdfio.rawbytes
val removeMetadata : pdf -> unit
val createMetadata : pdf -> unit
val setMetadataDate : pdf -> string -> unit
val addPageLabels : pdf -> int -> string -> int -> int -> bool -> unit
val removePageLabels : pdf -> unit
val startGetPageLabels : pdf -> int
val getPageLabelStyle : int -> int
val getPageLabelPrefix : int -> string
val getPageLabelOffset : int -> int
val getPageLabelRange : int -> int
val endGetPageLabels : unit -> unit
val getPageLabelStringForPage : pdf -> int -> string
val compositionJSON : int -> pdf -> Pdfio.rawbytes

(* CHAPTER 12. File Attachments *)
val attachFile : string -> pdf -> unit
val attachFileToPage : string -> pdf -> int -> unit
val attachFileFromMemory : Pdfio.rawbytes -> string -> int -> unit
val attachFileToPageFromMemory : Pdfio.rawbytes -> string -> int -> int -> unit
val removeAttachedFiles : pdf -> unit
val startGetAttachments : pdf -> unit
val endGetAttachments : unit -> unit
val numberGetAttachments : unit -> int
val getAttachmentName : int -> string
val getAttachmentPage : int -> int
val getAttachmentData : int -> Pdfio.rawbytes 

(* CHAPTER 13. Images *)
val startGetImages : int -> int
val getImageObjNum : int -> int
val getImagePages : int -> string
val getImageName : int -> string
val getImageHeight : int -> int
val getImageWidth : int -> int
val getImageSize : int -> int
val getImageBPC : int -> int
val getImageColSpace : int -> string
val getImageFilter : int -> string
val endGetImages : unit -> unit
val startGetImageResolution : int -> float -> int
val getImageResolutionPageNumber : int -> int
val getImageResolutionImageName : int -> string
val getImageResolutionXPixels : int -> int
val getImageResolutionYPixels : int -> int
val getImageResolutionXRes : int -> float
val getImageResolutionYRes : int -> float
val getImageResolutionObjNum : int -> int
val endGetImageResolution : unit -> unit
val imageResolutionJSON : int -> float -> Pdfio.rawbytes
val imagesJSON : int -> Pdfio.rawbytes

(* CHAPTER 14. Fonts *)
val numberFonts : unit -> int
val getFontPage : int -> int
val getFontName : int -> string
val getFontType : int -> string
val getFontEncoding : int -> string
val startGetFontInfo : int -> unit
val endGetFontInfo : unit -> unit
val fontsJSON : pdf -> Pdfio.rawbytes
val copyFont : pdf -> pdf -> range -> int -> string -> unit
val removeFonts : int -> unit

(* CHAPTER 15. PDF and JSON *)
val jsonUTF8 : bool -> unit
val outputJSON : string -> bool -> bool -> bool -> int -> unit
val outputJSONMemory : bool -> bool -> bool -> int -> Pdfio.rawbytes 
val fromJSON : string -> pdf
val fromJSONMemory : Pdfio.rawbytes -> pdf

(* CHAPTER 16. Optional Content Groups *)
val startGetOCGList : int -> int
val ocgListEntry : int -> string
val endGetOCGList : unit -> unit
val ocgCoalesce : int -> unit
val ocgRename : int -> string -> string -> unit
val ocgOrderAll : int -> unit

(* CHAPTER 17. Creating New PDFs *)
val blankDocument : float -> float -> int -> pdf
val blankDocumentPaper : int -> int -> pdf
val textToPDF : float -> float -> string -> float -> string -> pdf
val textToPDFPaper : int -> string -> float -> string -> pdf
val textToPDFMemory : float -> float -> string -> float -> Pdfio.rawbytes -> pdf
val textToPDFPaperMemory : int -> string -> float -> Pdfio.rawbytes -> pdf
val fromPNG : string -> pdf
val fromJPEG : string -> pdf
val fromPNGMemory : Pdfio.rawbytes -> pdf
val fromJPEGMemory : Pdfio.rawbytes -> pdf

(* CHAPTER 18. Drawing on PDFs *)
val drawBegin : unit -> unit
val drawEnd : pdf -> range -> unit
val drawEndExtended : pdf -> range -> bool -> int -> string -> unit
val drawTo : float -> float -> unit
val drawLine : float -> float -> unit
val drawStroke : unit -> unit
val drawRect : float -> float -> float -> float -> unit
val drawBez : float -> float -> float -> float -> float -> float -> unit
val drawBez23 : float -> float -> float -> float -> unit
val drawBez13 : float -> float -> float -> float -> unit
val drawCircle : float -> float -> float -> unit
val drawStrokeColGrey : float -> unit
val drawStrokeColRGB : float -> float -> float -> unit
val drawStrokeColCYMK : float -> float -> float -> float -> unit
val drawFillColGrey : float -> unit
val drawFillColRGB : float -> float -> float -> unit
val drawFillColCYMK : float -> float -> float -> float -> unit
val drawFill : unit -> unit
val drawFillEo : unit -> unit
val drawStrokeFill : unit -> unit
val drawStrokeFillEo : unit -> unit
val drawClose : unit -> unit
val drawClip : unit -> unit
val drawClipEo : unit -> unit
val drawThick : float -> unit
val drawCap : int -> unit
val drawJoin : int -> unit
val drawMiter : float -> unit
val drawDash : string -> unit
val drawPush : unit -> unit
val drawPop : unit -> unit
val drawMatrix : float -> float -> float -> float -> float -> float -> unit
val drawMTrans : float -> float -> unit
val drawMRot : float -> float -> float -> unit
val drawMScale : float -> float -> float -> float -> unit
val drawMShearX : float -> float -> float -> unit
val drawMShearY : float -> float -> float -> unit
val drawXObjBBox : float -> float -> float -> float -> unit
val drawXObj : string -> unit
val drawEndXObj : unit -> unit
val drawUse : string -> unit
val drawJPEG : string -> string -> unit
val drawPNG : string -> string -> unit
val drawJPEGMemory : string -> Pdfio.rawbytes -> unit
val drawPNGMemory : string -> Pdfio.rawbytes -> unit
val drawImage : string -> unit
val drawFillOpacity : float -> unit
val drawStrokeOpacity : float -> unit
val drawBT : unit -> unit
val drawET : unit -> unit
val loadFont : string -> string -> unit
val drawFont : string -> unit
val drawFontSize : float -> unit
val drawText : string -> unit
val drawSText : string -> unit
val drawLeading : float -> unit
val drawCharSpace : float -> unit
val drawWordSpace : float -> unit
val drawTextScale : float -> unit
val drawRenderMode : int -> unit
val drawRise : float -> unit
val drawNL : unit -> unit
val drawNewPage : unit -> unit

(* CHAPTER 19. Miscellaneous *)
val draft : pdf -> range -> bool -> unit
val removeAllText : pdf -> range -> unit
val blackText : pdf -> range -> unit
val blackLines : pdf -> range -> unit
val blackFills : pdf -> range -> unit
val thinLines : pdf -> range -> float -> unit
val copyId : pdf -> int -> unit
val removeId : pdf -> unit
val setVersion : pdf -> int -> unit
val setFullVersion : pdf -> int -> int -> unit
val removeDictEntry : pdf -> string -> unit
val removeDictEntrySearch : pdf -> string -> string -> unit
val replaceDictEntry : pdf -> string -> string -> unit
val replaceDictEntrySearch : pdf -> string -> string -> string -> unit
val getDictEntries : pdf -> string -> Pdfio.rawbytes
val removeClipping : pdf -> range -> unit
