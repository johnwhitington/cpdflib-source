(* CHAPTER 1. Basics *)
type pdf
val setdemo : bool -> unit
val fast : bool ref
val setFast : unit -> unit
val setSlow : unit -> unit
val version : string
val startEnumeratePDFs : unit -> int
val enumeratePDFsKey : int -> int
val enumeratePDFsInfo : int -> string
val endEnumeratePDFs : unit -> unit
val deletePdf : int -> unit
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
val blankDocument : float -> float -> int -> pdf
val blankDocumentPaper : int -> int -> pdf
val toFile : pdf -> string -> bool -> bool -> unit
val pages : pdf -> int
val pagesFast : string -> string -> int
val all : pdf -> int
val isEncrypted : pdf -> bool
val decryptPdf : pdf -> string -> unit
val decryptPdfOwner : pdf -> string -> unit
val toFileEncrypted : pdf -> int -> int array -> string -> string -> bool -> bool -> string -> unit
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

(* CHAPTER 7. Presentations *)

(* CHAPTER 8. Logos, Watermarks and Stamps *)
val stampOn : pdf -> pdf -> range -> unit
val stampUnder : pdf -> pdf -> range -> unit
val stampExtended : pdf -> pdf -> range -> bool -> bool -> float -> float -> int -> bool -> unit 
val combinePages : pdf -> pdf -> pdf
val addText : bool -> pdf -> int -> string -> int -> float -> float -> float -> int -> Pdftext.standard_font -> float -> float -> float -> float -> bool -> bool -> bool -> float -> Cpdf.justification -> bool -> bool -> string -> float -> bool -> unit
val removeText : pdf -> range -> unit
 
(* CHAPTER 9. Multipage facilities *)
val twoUp : pdf -> unit
val twoUpStack : pdf -> unit
val padBefore : pdf -> range -> unit
val padAfter : pdf -> range -> unit
val padEvery : pdf -> int -> unit
val padMultiple : pdf -> int -> unit
val padMultipleBefore : pdf -> int -> unit

(* CHAPTER 10. Annotations *)

(* CHAPTER 11. Document Information and Metadata *)
val getVersion : pdf -> int
val isLinearized : string -> bool
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
val setTitleXMP : pdf -> string -> unit
val setAuthorXMP : pdf -> string -> unit
val setSubjectXMP : pdf -> string -> unit
val setKeywordsXMP : pdf -> string -> unit
val setCreatorXMP : pdf -> string -> unit
val setProducerXMP : pdf -> string -> unit
val setCreationDateXMP : pdf -> string -> unit
val setModificationDateXMP : pdf -> string -> unit
val markTrapped : pdf -> unit
val markUntrapped : pdf -> unit
val hasBox : pdf -> int -> string -> bool
val getPageRotation : pdf -> int -> int
val setPageLayout : pdf -> int -> unit
val setPageMode : pdf -> int -> unit
val hideToolbar : pdf -> bool -> unit
val hideMenubar : pdf -> bool -> unit
val hideWindowUi : pdf -> bool -> unit
val fitWindow : pdf -> bool -> unit
val centerWindow : pdf -> bool -> unit
val displayDocTitle : pdf -> bool -> unit
val openAtPage : pdf -> bool -> int -> unit
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

(* CHAPTER 12. File Attachments *)
val attachFile : string -> pdf -> unit
val attachFileToPage : string -> pdf -> int -> unit
val removeAttachedFiles : pdf -> unit
val startGetAttachments : pdf -> unit
val endGetAttachments : unit -> unit
val numberGetAttachments : unit -> int
val getAttachmentName : int -> string
val getAttachmentPage : int -> int
val getAttachmentData : int -> Pdfio.rawbytes 

(* CHAPTER 13. Images *)
val startGetImageResolution : int -> float -> int
val getImageResolutionPageNumber : int -> int
val getImageResolutionImageName : int -> string
val getImageResolutionXPixels : int -> int
val getImageResolutionYPixels : int -> int
val getImageResolutionXRes : int -> float
val getImageResolutionYRes : int -> float
val endGetImageResolution : unit -> unit

(* CHAPTER 14. Fonts *)
val numberFonts : unit -> int
val getFontPage : int -> int
val getFontName : int -> string
val getFontType : int -> string
val getFontEncoding : int -> string
val startGetFontInfo : int -> unit
val endGetFontInfo : unit -> unit
val copyFont : pdf -> pdf -> range -> int -> string -> unit
val removeFonts : int -> unit

(* CHAPTER 15. Miscellaneous *)
val draft : pdf -> range -> bool -> unit
val removeAllText : pdf -> range -> unit
val blackText : pdf -> range -> unit
val blackLines : pdf -> range -> unit
val blackFills : pdf -> range -> unit
val thinLines : pdf -> range -> float -> unit
val copyId : pdf -> int -> unit
val removeId : pdf -> unit
val setVersion : pdf -> int -> unit
val removeDictEntry : pdf -> string -> unit
val removeClipping : pdf -> range -> unit

(* UNCATALOGUED AS YET *)
val addContent : string -> bool -> int -> int -> unit
val outputJSON : string -> bool -> bool -> int -> unit
val ocgCoalesce : int -> unit
val ocgRename : int -> string -> string -> unit
val ocgOrderAll : int -> unit
val stampAsXObject : int -> int -> int -> string
