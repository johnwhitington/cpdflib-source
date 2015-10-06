(* CHAPTER 1. Basics *)
open Pdfutil

let dbg = ref false

(* Demo Handling *)
let demo = ref false 

let nobble pdf =
  if !demo then
    Cpdf.recompress_pdf (Cpdf.process_pages (Cpdf.nobble_page pdf) pdf (ilist 1 (Pdfpage.endpage pdf)))
  else
    pdf

let setdemo b =
  if !dbg then flprint "Cpdflib.setdemo\n";
  demo := b

let _ = Callback.register "setdemo" setdemo

(* Error Handling *)
exception Cpdflib_error of string

let noerror = 0
let basicError = 1

(* The last error recorded. 0 = no error, else an error *)
let lastError = ref noerror

(* Return the last error recorded. *)
let getLastError () =
  !lastError

(* The Error string, valid if lastError <> 0 *)
let lastErrorString = ref ""

(* Return the last error string *)
let getLastErrorString () =
  !lastErrorString

(* Clear the error status *)
let clearError () =
  lastError := noerror

(* Used within all functions to wrap the error up *)
let handle_error fn e =
  let errstr = Printf.sprintf "ERROR: %s: %s" fn (Printexc.to_string e) in
    prerr_endline errstr;
    lastError := basicError;
    lastErrorString := errstr

let _ = Callback.register "getLastError" getLastError
let _ = Callback.register "getLastErrorString" getLastErrorString
let _ = Callback.register "clearError" clearError

(* Dummy return values for each possible return type *)
let err_int = 0
let err_float = 0.
let err_unit = ()
let err_bool = false
let err_string = ""
let err_array = [||]
let err_date =
  {Pdfdate.year = 0;
   Pdfdate.month = 0;
   Pdfdate.day = 0;
   Pdfdate.hour = 0;
   Pdfdate.minute = 0;
   Pdfdate.second = 0;
   Pdfdate.hour_offset = 0;
   Pdfdate.minute_offset = 0}
let err_data = Pdfio.raw_of_bytes (Pdfio.mkbytes 0)
let err_box = (0., 0., 0., 0.)

(* Basic Types and Functions *)
let ptOfCm x =
  if !dbg then flprint "Cpdflib.ptOfCm\n";
  try Pdfunits.convert 0. Pdfunits.Centimetre Pdfunits.PdfPoint x with e ->
    handle_error "ptOfCm" e; err_float

let ptOfMm x =
  if !dbg then flprint "Cpdflib.ptOfMm\n";
  try Pdfunits.convert 0. Pdfunits.Millimetre Pdfunits.PdfPoint x with e ->
    handle_error "ptOfMm" e; err_float

let ptOfIn x =
  if !dbg then flprint "Cpdflib.ptOfIn\n";
  try Pdfunits.convert 0. Pdfunits.Inch Pdfunits.PdfPoint x with e ->
    handle_error "ptOfIn" e; err_float

let cmOfPt x =
  if !dbg then flprint "Cpdflib.cmOfPt\n";
  try Pdfunits.convert 0. Pdfunits.PdfPoint Pdfunits.Centimetre x with e ->
    handle_error "cmOfPt" e; err_float

let mmOfPt x =
  if !dbg then flprint "Cpdflib.mmOfPt\n";
  try Pdfunits.convert 0. Pdfunits.PdfPoint Pdfunits.Millimetre x with e ->
    handle_error "mmOfPt" e; err_float

let inOfPt x =
  if !dbg then flprint "Cpdflib.inOfPt\n";
  try Pdfunits.convert 0. Pdfunits.PdfPoint Pdfunits.Inch x with e ->
    handle_error "inOfPt" e; err_float

let ptOfCm x =
  if !dbg then flprint "Cpdflib.ptOfCm\n";
  try Pdfunits.convert 0. Pdfunits.Centimetre Pdfunits.PdfPoint x with e ->
    handle_error "ptOfCm" e; err_float

let _ = Callback.register "ptOfCm" ptOfCm
let _ = Callback.register "ptOfMm" ptOfMm
let _ = Callback.register "ptOfIn" ptOfIn
let _ = Callback.register "cmOfPt" cmOfPt
let _ = Callback.register "mmOfPt" mmOfPt
let _ = Callback.register "inOfPt" inOfPt

type range = int

let ranges = null_hash ()

let rangekey = ref 0

let new_range arr =
  incr rangekey;
  Hashtbl.add ranges !rangekey arr;
  !rangekey

let lookup_range i =
  Hashtbl.find ranges i

let blankrange () =
  if !dbg then flprint "Cpdflib.blankrange\n";
  try new_range (Array.make 0 0) with e -> handle_error "blankrange" e; err_int

let writerange r p n =
  if !dbg then flprint "Cpdflib.writerange\n";
  try Array.set (lookup_range r) p n with e -> handle_error "writerange" e; err_unit

let makerange len =
  if !dbg then flprint "Cpdflib.makerange\n";
  try new_range (Array.make len 0) with e -> handle_error "makerange" e; err_int

let lengthrange r =
  if !dbg then flprint "Cpdflib.lengthrange\n";
  try Array.length (lookup_range r) with e -> handle_error "lengthrange" e; err_int

let readrange r p =
  if !dbg then flprint "Cpdflib.readrange\n";
  try (lookup_range r).(p) with e -> handle_error "readrange" e; err_int

let addtorange r p =
  if !dbg then flprint "Cpdflib.addtorange\n";
  try
    let old = lookup_range r in
      let len = Array.length old in
        let arr = Array.make (len + 1) 0 in
          Array.blit old 0 arr 0 len;
          arr.(len) <- p;
          new_range arr
  with
    e -> handle_error "addtorange" e; err_int

let deleterange r =
  if !dbg then flprint "Cpdflib.deleterange\n";
  try Hashtbl.remove ranges r with e -> handle_error "deleterange" e; err_unit

let _ = Callback.register "blankrange" blankrange
let _ = Callback.register "writerange" writerange
let _ = Callback.register "makerange" makerange
let _ = Callback.register "lengthrange" lengthrange
let _ = Callback.register "readrange" readrange
let _ = Callback.register "addtorange" addtorange
let _ = Callback.register "deleterange" deleterange
 
type pdfdoc = Pdf.t

type range_arr = int array

(* Manipulating ranges *)
let range f t =
  let l =
    if f < t then ilist f t else rev (ilist f t)
  in
    Array.of_list l

let even r =
  Array.of_list (keep even (Array.to_list r))
  
let odd r =
  Array.of_list (keep odd (Array.to_list r))

let union r r' =
  Array.of_list (setify (Array.to_list r @ Array.to_list r'))

let difference r r' =
  Array.of_list (setminus_preserving_order (Array.to_list r) (Array.to_list r'))

let removeDuplicates r =
  Array.of_list (setify_preserving_order (Array.to_list r))

let sort r =
  Array.of_list (sort compare (Array.to_list r))

let range a b =
  if !dbg then flprint "Cpdflib.range\n";
  try new_range (range a b) with e -> handle_error "range" e; err_int

let even r =
  if !dbg then flprint "Cpdflib.even\n";
  try new_range (even (lookup_range r)) with e -> handle_error "even" e; err_int

let odd r =
  if !dbg then flprint "Cpdflib.odd\n";
  try new_range (odd (lookup_range r)) with e -> handle_error "odd" e; err_int

let union a b =
  if !dbg then flprint "Cpdflib.union\n";
  try new_range (union (lookup_range a) (lookup_range b)) with e -> handle_error "union" e; err_int

let difference a b =
  if !dbg then flprint "Cpdflib.difference\n";
  try new_range (difference (lookup_range a) (lookup_range b)) with e -> handle_error "difference" e; err_int

let removeDuplicates r =
  if !dbg then flprint "Cpdflib.removeDuplicates\n";
  try new_range (removeDuplicates (lookup_range r)) with e -> handle_error "removeDuplicated" e; err_int

let isInRange r i =
  if !dbg then flprint "Cpdflib.isInRange\n";
  try mem i (Array.to_list (lookup_range r)) with e -> handle_error "isInRange" e; err_bool

let _ = Callback.register "range" range
let _ = Callback.register "even" even
let _ = Callback.register "odd" odd
let _ = Callback.register "range_union" union
let _ = Callback.register "difference" difference
let _ = Callback.register "removeDuplicates" removeDuplicates
let _ = Callback.register "isInRange" isInRange

type pdf = int

type extra_encryption_info =
  Pdfcrypt.permission list *
  Pdfwrite.encryption_method option *
  string option (* user password *)

type encryption_status =
   | NotEncrypted
   | Encrypted
   | WasDecryptedWithUser of extra_encryption_info
   | WasDecryptedWithOwner of extra_encryption_info 

let initial_encryption_status pdf =
  (*Printf.printf "initial_encryption_status: encrypted = %b\n" (Pdfcrypt.is_encrypted pdf);
  flprint "\n";*)
  if Pdfcrypt.is_encrypted pdf then Encrypted else NotEncrypted

(* Store the PDF and return the integer key *)
let pdfs = null_hash ()

let pdfkey = ref 0

let new_pdf pdf =
  incr pdfkey;
  (*Printf.printf "new_pdf %i" !pdfkey;
  flprint "\n";*)
  Hashtbl.add pdfs !pdfkey ([], (pdf, initial_encryption_status pdf), []);
  !pdfkey

let lookup_pdf i =
  (*Printf.printf "lookup_pdf : %i PDFs in table" (Hashtbl.length pdfs);
  flprint "\n";*)
  match Hashtbl.find pdfs i with (_, (pdf, _), _) -> pdf

let number_of_encryption_status = function
  | NotEncrypted -> 0
  | Encrypted -> 1
  | WasDecryptedWithUser _ -> 2
  | WasDecryptedWithOwner _ -> 3

let lookup_pdf_status i =
  match Hashtbl.find pdfs i with (_, (_, enc), _) -> enc

let lookupPdfStatus i =
  if !dbg then flprint "Cpdflib.lookupPdfStatus\n";
  try
    number_of_encryption_status (lookup_pdf_status i)
  with
    e -> handle_error "lookupPdfStatus" e; err_int

let set_pdf_status i status =
  let l, (pdf, _), r = Hashtbl.find pdfs i in
    Hashtbl.replace pdfs i (l, (pdf, status), r) 

let delete_pdf i =
  Hashtbl.remove pdfs i

let replace_pdf i pdf =
  let l, (_, enc), r = Hashtbl.find pdfs i in
    Hashtbl.replace pdfs i (l, (pdf, enc), r)

let enumeratePairs = ref []

let info_of_pdf _ = "info"

(* debug window *)
let list_pdfs () =
  Printf.printf "PDFs in memory\n";
  Hashtbl.iter (fun i _ -> Printf.printf "%i " i) pdfs;
  flprint "\n"

let startEnumeratePDFs () =
  if !dbg then flprint "Cpdflib.startEnumeratePDFs\n";
  try
    Hashtbl.iter
      (fun k v -> enumeratePairs := (k, info_of_pdf v)::!enumeratePairs)
      pdfs;
    length !enumeratePairs
  with
    e -> handle_error "startEnumeratePDFs" e; err_int

let enumeratePDFsKey i =
  if !dbg then flprint "Cpdflib.enumeratePDFsKey\n";
  try fst (select (i + 1) !enumeratePairs) with e -> handle_error "enumeratePDFsKey" e; err_int

let enumeratePDFsInfo i =
  if !dbg then flprint "Cpdflib.enumeratePDFsInfo\n";
  try snd (select (i + 1) !enumeratePairs) with e -> handle_error "enumeratePDFsInfo" e; err_string

let endEnumeratePDFs () =
  if !dbg then flprint "Cpdflib.endEnumeratePDFs\n";
  try enumeratePairs := [] with e -> handle_error "endEnumeratePDFs" e; err_unit

(* Remove a PDF from memory *)
let deletePdf i =
  if !dbg then flprint "Cpdflib.deletePdf\n";
  try delete_pdf i with e -> handle_error "deletePdf" e; err_unit

(* Replace a PDF under the same pdf number *)
let replacePdf x y =
  if !dbg then flprint "Cpdflib.replacePdf\n";
  try
    replace_pdf x (lookup_pdf y);
    delete_pdf y
  with e -> handle_error "replacePdf" e; err_unit

let flatten_encryptionKind = function
  | None | Some Pdfwrite.AlreadyEncrypted -> 0
  | Some Pdfwrite.PDF40bit -> 1
  | Some Pdfwrite.PDF128bit -> 2
  | Some Pdfwrite.AES128bit true -> 3
  | Some Pdfwrite.AES128bit false -> 4
  | Some Pdfwrite.AES256bit true -> 5
  | Some Pdfwrite.AES256bit false -> 6
  | Some Pdfwrite.AES256bitISO true -> 7
  | Some Pdfwrite.AES256bitISO false -> 8

(* hasPermissionStatus looks for a permission in the /status/ of a PDF, not the PDF itself *)
let hasPermissionStatus i tocheck =
  if !dbg then flprint "Cpdflib.hasPermissionStatus\n";
  let status_permissions i =
    match lookup_pdf_status i with
    | NotEncrypted | Encrypted ->
        failwith "hasPermissionStatus - not decryptedWithUser or DecryptedWithOwner"
    | WasDecryptedWithUser (l, _, _) | WasDecryptedWithOwner (l, _, _) -> l 
  in
    try
      mem
        (match tocheck with
         | 0 -> Pdfcrypt.NoEdit
         | 1 -> Pdfcrypt.NoPrint
         | 2 -> Pdfcrypt.NoCopy
         | 3 -> Pdfcrypt.NoAnnot
         | 4 -> Pdfcrypt.NoForms
         | 5 -> Pdfcrypt.NoExtract
         | 6 -> Pdfcrypt.NoAssemble
         | 7 -> Pdfcrypt.NoHqPrint
         | _ -> raise (Failure "hasPermissionStatus"))
        (status_permissions i)
    with
      e -> handle_error "hasPermissionStatus" e; err_bool

(* lookupPdfEncryption looks for the encryption type in the /status/ of a PDF
which is decryptedWithUser or decryptedWithOwner *)
let lookupPdfEncryption i =
  if !dbg then flprint "Cpdflib.lookupPdfEncryption\n";
  try
    match lookup_pdf_status i with
    | NotEncrypted | Encrypted ->
        failwith "lookupPdfEncryption - not decryptedWithOwner or DecryptedWithUser"
    | WasDecryptedWithOwner (_, ek, _) | WasDecryptedWithUser (_, ek, _) ->
        flatten_encryptionKind ek
  with
    e -> handle_error "lookupPdfEncryption" e; err_int

let lookupPdfUserPassword i =
  if !dbg then flprint "Cpdflib.lookupPdfUserPassword\n";
  try
    match lookup_pdf_status i with
    | WasDecryptedWithUser (_, _, Some pw) -> pw
    | _ -> failwith "lookupPdfUserPassword failure"
  with
    e -> handle_error "lookupPdfUserPassword" e; err_string

let _ = Callback.register "startEnumeratePDFs" startEnumeratePDFs
let _ = Callback.register "enumeratePDFsKey" enumeratePDFsKey
let _ = Callback.register "enumeratePDFsInfo" enumeratePDFsInfo
let _ = Callback.register "endEnumeratePDFs" endEnumeratePDFs
let _ = Callback.register "deletePdf" deletePdf
let _ = Callback.register "replacePdf" replacePdf
let _ = Callback.register "lookupPdfStatus" lookupPdfStatus
let _ = Callback.register "hasPermissionStatus" hasPermissionStatus
let _ = Callback.register "lookupPdfEncryption" lookupPdfEncryption
let _ = Callback.register "lookupPdfUserPassword" lookupPdfUserPassword

(* Undo support *)

(* Undo. We move the head of the left list into position, if it exists. *)
let undo i =
  if !dbg then flprint "Cpdflib.undo\n";
  try
    match Hashtbl.find pdfs i with
    | (l::ls, p, rs) -> Hashtbl.replace pdfs i (ls, l, p::rs); true
    | ([], _, _) -> false
  with
    e -> handle_error "undo" e; err_bool

(* Redo. We move the head of the right list into position, and add pdf to left list *)
let redo i =
  if !dbg then flprint "Cpdflib.redo\n";
  try
    match Hashtbl.find pdfs i with
    | (ls, p, r::rs) -> Hashtbl.replace pdfs i (p::ls, r, rs); true
    | (_, _, []) -> false
  with
    e -> handle_error "redo" e; false

let copy_pdf from =
  {Pdf.major = from.Pdf.major;
   Pdf.minor = from.Pdf.minor;
   Pdf.root = from.Pdf.root;
   Pdf.objects = from.Pdf.objects;
   Pdf.trailerdict = from.Pdf.trailerdict;
   Pdf.saved_encryption = from.Pdf.saved_encryption;
   Pdf.was_linearized = from.Pdf.was_linearized}

let deep_copy_pdf = Pdf.deep_copy

(* Do an update. Copy PDF to left list *)
let aboutToUpdate i =
  if !dbg then flprint "Cpdflib.aboutToUpdate\n";
  try
    match Hashtbl.find pdfs i with
    | (ls, (p, enc), rs) -> Hashtbl.replace pdfs i ((p, enc)::ls, (copy_pdf p, enc), rs)
  with
    e -> handle_error "aboutToUpdate" e; err_unit

let aboutToUpdateDeep i =
  if !dbg then flprint "Cpdflib.aboutToUpdateDeep\n";
  try
    match Hashtbl.find pdfs i with
    | (ls, (p, enc), rs) -> Hashtbl.replace pdfs i ((p, enc)::ls, (Pdf.deep_copy p, enc), rs)
  with
    e -> handle_error "aboutToUpdateDeep" e; err_unit

(* Abort an update - throw current PDF away, go back to last one, which must exist. *)
let abortUpdate i =
  if !dbg then flprint "Cpdflib.abortUpdate\n";
  try
    match Hashtbl.find pdfs i with
    | (l::ls, _, rs) -> Hashtbl.replace pdfs i (ls, l, rs)
    | _ -> raise (Failure "abortUpdate")
  with
    e -> handle_error "abortUpdate" e; err_unit

let _ = Callback.register "undo" undo
let _ = Callback.register "redo" redo
let _ = Callback.register "aboutToUpdate" aboutToUpdate
let _ = Callback.register "aboutToUpdateDeep" aboutToUpdateDeep
let _ = Callback.register "abortUpdate" abortUpdate

let parsePagespec pdf str =
  if !dbg then flprint "Cpdflib.parsePagespec\n";
  try
    new_range (Array.of_list (Cpdf.parse_pagespec (lookup_pdf pdf) str))
  with
    e -> handle_error "parsePagespec" e; err_int

let stringOfPagespec pdf range =
  if !dbg then flprint "Cpdflib.stringOfPagespec\n";
  try
    Cpdf.string_of_pagespec (lookup_pdf pdf) (Array.to_list (lookup_range range))
  with
    e -> handle_error "stringOfPagespec" e; err_string

let validatePagespec spec =
  if !dbg then flprint "Cpdflib.validatePagespec\n";
  try
    Cpdf.validate_pagespec spec
  with
    e -> handle_error "validatePagespec" e; err_bool

let _ = Callback.register "parsePagespec" parsePagespec
let _ = Callback.register "stringOfPagespec" stringOfPagespec
let _ = Callback.register "validatePagespec" validatePagespec

(* Read a file, no attempt at decryption, unless it's the blank user password. *)
let fromFile filename userpw =
  if !dbg then flprint "Cpdflib.fromFile\n";
  try
    new_pdf (Pdfread.pdf_of_file (Some userpw) None filename)
  with
    e -> handle_error "fromFile" e; err_int

let fromMemory rawbytes userpw =
  if !dbg then flprint "Cpdflib.fromMemory\n";
  try
    new_pdf
      (Pdfread.pdf_of_input
         (Some userpw)
         None
         (Pdfio.input_of_bytes
         (Pdfio.bytes_of_raw rawbytes)))
  with
    e -> handle_error "fromMemory" e; err_int

(* Same, but don't attempt to decrypt, and read it lazily. Use only when
decryption not required at any time. *)
let fromFileLazy filename userpw =
  if !dbg then flprint "Cpdflib.fromFileLazy\n";
  try
    new_pdf (Pdfread.pdf_of_channel_lazy (Some userpw) None (open_in_bin filename))
  with
    e -> handle_error "fromFileLazy" e; err_int

let fromMemoryLazy rawbytes userpw =
  if !dbg then flprint "Cpdflib.fromMemoryLazy\n";
  try
    new_pdf
      (Pdfread.pdf_of_input_lazy
         (Some userpw)
         None
         (Pdfio.input_of_bytes
         (Pdfio.bytes_of_raw rawbytes)))
  with
    e -> handle_error "fromMemoryLazy" e; err_int

(* Simple full write to a file *)
let toFile pdf filename linearize make_id =
  if !dbg then flprint "Cpdflib.toFile\n";
  try
    let pdf = lookup_pdf pdf in
      Pdf.remove_unreferenced pdf;
      Pdfwrite.pdf_to_file_options linearize None make_id (nobble pdf) filename
  with
    e -> handle_error "toFile" e; err_unit

let toFileExt
  pdf filename linearize make_id preserve_objstm generate_objstm compress_objstm
=
  if !dbg then flprint "Cpdflib.toFileOptions\n";
  try
    let pdf = lookup_pdf pdf in
      Pdf.remove_unreferenced pdf;
      Pdfwrite.pdf_to_file_options
        ~preserve_objstm ~generate_objstm ~compress_objstm
        linearize None make_id (nobble pdf) filename
  with
    e -> handle_error "toFileOptions" e; err_unit

(* Write to memory. FIXME make_id does nothing *)
let toFileMemory pdf linearize make_id =
  if !dbg then flprint "Cpdflib.toFileMemory\n";
  try
    let pdf = lookup_pdf pdf in
      Pdf.remove_unreferenced pdf;
      let o, bytes = Pdfio.input_output_of_bytes (100 * 1024) in
        Pdfwrite.pdf_to_output linearize None (nobble pdf) o;
        Pdfio.raw_of_bytes
          (Pdfio.extract_bytes_from_input_output o bytes)
  with
    e -> handle_error "toFileMemory" e; err_data

let blankDocument width height pages =
  if !dbg then flprint "Cpdflib.blankDocument\n";
  try new_pdf (Cpdf.blank_document width height pages) with
    e -> handle_error "blankDocument" e; err_int

let papersize_of_int = function
  | 0 -> Pdfpaper.a0
  | 1 -> Pdfpaper.a1
  | 2 -> Pdfpaper.a2
  | 3 -> Pdfpaper.a3
  | 4 -> Pdfpaper.a4
  | 5 -> Pdfpaper.a5
  | 6 -> Pdfpaper.landscape Pdfpaper.a0
  | 7 -> Pdfpaper.landscape Pdfpaper.a1
  | 8 -> Pdfpaper.landscape Pdfpaper.a2
  | 9 -> Pdfpaper.landscape Pdfpaper.a3
  | 10 -> Pdfpaper.landscape Pdfpaper.a4
  | 11 -> Pdfpaper.landscape Pdfpaper.a5
  | 12 -> Pdfpaper.usletter
  | 13 -> Pdfpaper.landscape Pdfpaper.usletter
  | 14 -> Pdfpaper.uslegal
  | 15 -> Pdfpaper.landscape Pdfpaper.uslegal
  | _ -> raise (Failure "unknown papersize")

let blankDocumentPaper papersize pages =
  if !dbg then flprint "Cpdflib.blankDocumentPaper\n";
  try new_pdf (Cpdf.blank_document_paper (papersize_of_int papersize) pages) with
    e -> handle_error "blankDocumentPaper" e; err_int

(* Number of pages in a PDF *)
let pages i =
  if !dbg then flprint "Cpdflib.pages\n";
  try Pdfpage.endpage (lookup_pdf i) with
    e -> handle_error "pages" e; err_int

let pagesFast password filename =
  if !dbg then flprint "Cpdflib.pagesFast\n";
  try
    let channel = open_in_bin filename in
      let r = Cpdf.endpage_io (Pdfio.input_of_channel channel) (Some password) None in
        close_in channel;
        r
  with
    e -> handle_error "pagesfast" e; err_int

(* The full range with all pages. *)
let all pdf =
  if !dbg then flprint "Cpdflib.all\n";
  Array.of_list (ilist 1 (pages pdf))

let all i =
  try new_range (all i) with
    e -> handle_error "all" e; err_int

let isEncrypted i =
  if !dbg then flprint "Cpdflib.isEncrypted\n";
  try Pdfcrypt.is_encrypted (lookup_pdf i) with
    e -> handle_error "isEncrypted" e; err_bool

let hasPermission pdf tocheck =
  if !dbg then flprint "Cpdflib.hasPermission\n";
  try
    mem
      (match tocheck with
       | 0 -> Pdfcrypt.NoEdit
       | 1 -> Pdfcrypt.NoPrint
       | 2 -> Pdfcrypt.NoCopy
       | 3 -> Pdfcrypt.NoAnnot
       | 4 -> Pdfcrypt.NoForms
       | 5 -> Pdfcrypt.NoExtract
       | 6 -> Pdfcrypt.NoAssemble
       | 7 -> Pdfcrypt.NoHqPrint
       | _ -> raise (Failure "hasPermission"))
      (Pdfread.permissions (lookup_pdf pdf))
  with
    e -> handle_error "hasPermission" e; err_bool

let encryptionKind pdf =
  if !dbg then flprint "Cpdflib.encryptionKind\n";
  try
    flatten_encryptionKind (Pdfread.what_encryption (lookup_pdf pdf))
  with
    e -> handle_error "encryptionKind" e; err_int

let _ = Callback.register "hasPermission" hasPermission
let _ = Callback.register "encryptionKind" encryptionKind

(* If marked as encrypted, and we successfully decrypt, mark as
WasDecryptedWithUser, otherwise leave as is. *)
let decryptPdf i p =
  if !dbg then flprint "Cpdflib.decryptPdf\n";
  let decryptPdf_inner pdf password =
    match Pdfcrypt.decrypt_pdf password pdf with
    | Some pdf, _ -> pdf
    | None, _ -> failwith "decrypt_pdf_inner"
  in
    try
      let before_status = lookup_pdf_status i
      and before_permissions = Pdfread.permissions (lookup_pdf i)
      and before_encryptionkind = Pdfread.what_encryption (lookup_pdf i) in
        replace_pdf i (decryptPdf_inner (lookup_pdf i) p);
        if not (isEncrypted i) && before_status = Encrypted
          then set_pdf_status i (WasDecryptedWithUser (before_permissions, before_encryptionkind, Some p))
    with
      e -> handle_error "decryptPdf" e; err_unit

(* If marked as encrypted, and we successfully decrypt, mark as
WasDecryptedWithOwner, otherwise leave as it. *)
let decryptPdfOwner i p =
  if !dbg then flprint "Cpdflib.decryptPdfOwner\n";
  let decryptPdfOwner_inner pdf password =
    match Pdfcrypt.decrypt_pdf_owner password pdf with
    | Some pdf -> pdf
    | None -> failwith "decrypt_pdf_owner"
  in
    try
      let before_status = lookup_pdf_status i
      and before_permissions = Pdfread.permissions (lookup_pdf i)
      and before_encryptionkind = Pdfread.what_encryption (lookup_pdf i) in
        replace_pdf i (decryptPdfOwner_inner (lookup_pdf i) p);
        if not (isEncrypted i) && before_status = Encrypted
          then set_pdf_status i (WasDecryptedWithOwner (before_permissions, before_encryptionkind, None))
    with
      e -> handle_error "decryptPdfOwner" e; err_unit

let toFileEncrypted_inner
  ?(preserve_objstm = true) ?(generate_objstm = false)
  ?(compress_objstm = true)
  pdf encryption_method permissions owner_password user_password linearize makeid filename
=
  if !dbg then flprint "Cpdflib.toFileEncrypted\n";
  try
    let encryption =
      {Pdfwrite.encryption_method = encryption_method;
       Pdfwrite.permissions = Array.to_list permissions;
       Pdfwrite.owner_password = owner_password;
       Pdfwrite.user_password = user_password}
    in
      Pdfwrite.pdf_to_file_options linearize (Some encryption) makeid pdf filename
  with
    e -> handle_error "toFileEncrypted" e; err_unit

let toFileEncrypted i mthd perms user owner linearize makeid filename =
  try
    let mthd =
      match mthd with
      | 0 -> Pdfwrite.PDF40bit
      | 1 -> Pdfwrite.PDF128bit
      | 2 -> Pdfwrite.AES128bit false
      | 3 -> Pdfwrite.AES128bit true
      | 4 -> Pdfwrite.AES256bit false
      | 5 -> Pdfwrite.AES256bit true
      | 6 -> Pdfwrite.AES256bitISO false
      | 7 -> Pdfwrite.AES256bitISO true
      | _ -> failwith "bad encryption method"
    and perms =
      Array.map
        (function
         | 0 -> Pdfcrypt.NoEdit
         | 1 -> Pdfcrypt.NoPrint
         | 2 -> Pdfcrypt.NoCopy
         | 3 -> Pdfcrypt.NoAnnot
         | 4 -> Pdfcrypt.NoForms
         | 5 -> Pdfcrypt.NoExtract
         | 6 -> Pdfcrypt.NoAssemble
         | 7 -> Pdfcrypt.NoHqPrint
         | _ -> failwith "unknown permission")
        perms
    in
      Pdf.remove_unreferenced (lookup_pdf i);
      toFileEncrypted_inner
        (lookup_pdf i) mthd perms user owner linearize makeid filename
  with
    e -> handle_error "toFileEncrypted" e; err_unit

let toFileEncryptedExt
  i mthd perms user owner linearize makeid
  preserve_objstm generate_objstm compress_objstm filename
=
  try
    let mthd =
      match mthd with
      | 0 -> Pdfwrite.PDF40bit
      | 1 -> Pdfwrite.PDF128bit
      | 2 -> Pdfwrite.AES128bit false
      | 3 -> Pdfwrite.AES128bit true
      | 4 -> Pdfwrite.AES256bit false
      | 5 -> Pdfwrite.AES256bit true
      | 6 -> Pdfwrite.AES256bitISO false
      | 7 -> Pdfwrite.AES256bitISO true
      | _ -> failwith "bad encryption method"
    and perms =
      Array.map
        (function
         | 0 -> Pdfcrypt.NoEdit
         | 1 -> Pdfcrypt.NoPrint
         | 2 -> Pdfcrypt.NoCopy
         | 3 -> Pdfcrypt.NoAnnot
         | 4 -> Pdfcrypt.NoForms
         | 5 -> Pdfcrypt.NoExtract
         | 6 -> Pdfcrypt.NoAssemble
         | 7 -> Pdfcrypt.NoHqPrint
         | _ -> failwith "unknown permission")
        perms
    in
      Pdf.remove_unreferenced (lookup_pdf i);
      toFileEncrypted_inner
        ~preserve_objstm ~generate_objstm ~compress_objstm
        (lookup_pdf i) mthd perms user owner linearize makeid filename
  with
    e -> handle_error "toFileEncrypted" e; err_unit

(*let toFileRecrypting original decrypted_and_modified userpw filename =
  if !dbg then flprint "Cpdflib.toFileRecrypting\n";
  try
    Pdfwrite.pdf_to_file_options
      ?recrypt:(Some userpw)
      (lookup_pdf original)
      (lookup_pdf decrypted_and_modified)
      filename
  with
    e -> handle_error "toFileRecrypting" e; err_unit*)

let _ = Callback.register "fromFile" fromFile
let _ = Callback.register "fromFileLazy" fromFileLazy
let _ = Callback.register "fromMemory" fromMemory
let _ = Callback.register "fromMemoryLazy" fromMemoryLazy
let _ = Callback.register "decryptPdf" decryptPdf
let _ = Callback.register "decryptPdfOwner" decryptPdfOwner
let _ = Callback.register "toFile" toFile
let _ = Callback.register "toFileExt" toFile
let _ = Callback.register "toFileMemory" toFileMemory
let _ = Callback.register "blankDocument" blankDocument
let _ = Callback.register "blankDocumentPaper" blankDocumentPaper
let _ = Callback.register "pages" pages
let _ = Callback.register "pagesFast" pagesFast
let _ = Callback.register "all" all
let _ = Callback.register "isEncrypted" isEncrypted
let _ = Callback.register "toFileEncrypted" toFileEncrypted
let _ = Callback.register "toFileEncryptedExt" toFileEncryptedExt
(*let _ = Callback.register "toFileRecrypting" toFileRecrypting*)

(* CHAPTER 2. Merging and Splitting *)
let list_all pdf = ilist 1 (pages pdf)

let mergeSimple (pdfarr : pdfdoc array) pdfnums =
  match pdfarr with
  | [||] -> raise (Failure "merge_simple: no pdfs")
  | _ ->
      let pdfs = Array.to_list pdfarr in
        Pdfmerge.merge_pdfs
          true false (map string_of_int (ilist 1 (length pdfs))) pdfs
          (map list_all (Array.to_list pdfnums))

let mergeSimple pdfs =
  if !dbg then flprint "Cpdflib.mergeSimple\n";
  try
    new_pdf (mergeSimple (Array.map lookup_pdf pdfs) pdfs)
  with
    e -> handle_error "mergeSimple" e; err_int

let merge pdfarr retain_numbering remove_duplicate_fonts rawpdfs =
  match pdfarr with
  | [||] -> raise (Failure "merge: no pdfs")
  | _ ->
      let pdfs = Array.to_list pdfarr in
        Pdfmerge.merge_pdfs
          retain_numbering remove_duplicate_fonts (map string_of_int (ilist 1 (length pdfs)))
          pdfs (map list_all rawpdfs) 

let merge pdfs retain_numbering remove_duplicate_fonts =
  if !dbg then flprint "Cpdflib.merge\n";
  try
    new_pdf
      (merge (Array.map lookup_pdf pdfs) retain_numbering remove_duplicate_fonts (Array.to_list pdfs))
  with
    e -> handle_error "merge" e; err_int

(* For use when the selection of pages must be done here rather than previously *)
let mergeSameRange pdfarr retain_numbering remove_duplicate_fonts (names : string array) (ranges : int list list) =
  if Array.length pdfarr <> Array.length names || Array.length pdfarr <> length ranges || Array.length pdfarr = 0
    then raise (Failure "merge_same: incorrect array lengths");
  let pdfs = Array.to_list pdfarr
  and names = Array.to_list names in
    Pdfmerge.merge_pdfs retain_numbering remove_duplicate_fonts names pdfs ranges 

let mergeSame pdfs retain_numbering remove_duplicate_fonts ranges =
  if !dbg then flprint "Cpdflib.mergeSame\n";
  (*Printf.printf "mergesame: %i pdfs\n" (Array.length pdfs);
  List.iter2
    (fun pdf range ->
       Printf.printf "pdf %i range %i (which is)" pdf range;
       iter (Printf.printf "%i ") (Array.to_list (lookup_range range));
       flprint "\n")
    (Array.to_list pdfs)
    (Array.to_list ranges);
    flprint "\n";*)
  try
    new_pdf
      (mergeSameRange
         (Array.map lookup_pdf pdfs)
            retain_numbering
            remove_duplicate_fonts
            (Array.map string_of_int pdfs)
            (map (fun x -> Array.to_list (lookup_range x)) (Array.to_list ranges)))
  with
    e -> handle_error "mergeSame" e; err_int

let selectPages pdf range =
  if !dbg then flprint "Cpdflib.selectPages\n";
  try
    new_pdf (Pdfpage.pdf_of_pages ~retain_numbering:true (lookup_pdf pdf) (Array.to_list (lookup_range range)))
  with
    e -> handle_error "selectPages" e; err_int

let splitOnBookmarks pdf level =
  if !dbg then flprint "Cpdflib.splitOnBookmarks\n";
  try
    let pdfs = Array.of_list (Cpdf.split_on_bookmarks (lookup_pdf pdf) level) in
      Array.map new_pdf pdfs
  with
    e -> handle_error "splitOnBookmarks" e; err_array

let _ = Callback.register "mergeSimple" mergeSimple
let _ = Callback.register "merge" merge
let _ = Callback.register "mergeSame" mergeSame
let _ = Callback.register "selectPages" selectPages
let _ = Callback.register "splitOnBookmarks" splitOnBookmarks

(* CHAPTER 3. Pages *)
let read_position f1 f2 = function
  | 0 -> Cpdf.PosCentre (f1, f2)
  | 1 -> Cpdf.PosLeft (f1, f2)
  | 2 -> Cpdf.PosRight (f1, f2)
  | 3 -> Cpdf.Top f1
  | 4 -> Cpdf.TopLeft f1
  | 5 -> Cpdf.TopRight f1
  | 6 -> Cpdf.Left f1
  | 7 -> Cpdf.BottomLeft f1
  | 8 -> Cpdf.Bottom f1
  | 9 -> Cpdf.BottomRight f1
  | 10 -> Cpdf.Right f1
  | 11 -> Cpdf.Diagonal
  | 12 -> Cpdf.ReverseDiagonal
  | _ -> failwith "read_position"

(* For turning functions which return a new PDF into ones which update the given
pdf. The PDF which is newly created should be thrown away. *)
let update_pdf (copyfrom : Pdf.t) (copyto : Pdf.t) =
  copyto.Pdf.major <- copyfrom.Pdf.major;
  copyto.Pdf.minor <- copyfrom.Pdf.minor;
  copyto.Pdf.root <- copyfrom.Pdf.root;
  copyto.Pdf.objects <- copyfrom.Pdf.objects;
  copyto.Pdf.trailerdict <- copyfrom.Pdf.trailerdict

let scalePages i range sx sy =
  if !dbg then flprint "Cpdflib.scalePages\n";
  try
    update_pdf (Cpdf.scale_pdf sx sy (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "scalePages" e; err_unit

let scaleToFit i range w h =
  if !dbg then flprint "Cpdflib.scaleToFit\n";
  try
    update_pdf (Cpdf.scale_to_fit_pdf 1. w h () (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "scaleToFit" e; err_unit

let points_of_papersize p =
  let u = Pdfpaper.unit p
  and w = Pdfpaper.width p
  and h = Pdfpaper.height p in
    let c  = Pdfunits.convert 0. u Pdfunits.PdfPoint in
      c w, c h

let scaleToFitPaper i range papersize =
  if !dbg then flprint "Cpdflib.scaleToFitPaper\n";
  try
    let w, h = points_of_papersize (papersize_of_int papersize) in
      update_pdf (Cpdf.scale_to_fit_pdf 1. w h () (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "scaleToFitPaper" e; err_unit

let shiftContents i range dx dy =
  if !dbg then flprint "Cpdflib.shiftContents\n";
  try
    update_pdf (Cpdf.shift_pdf dx dy (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "shiftContents" e; err_unit

let scaleContents pdf range pos f1 f2 factor =
  if !dbg then flprint "Cpdflib.scaleContents\n";
  try
    update_pdf (Cpdf.scale_contents (read_position f1 f2 pos) factor (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "scaleContents" e; err_unit

let rotate i range angle =
  if !dbg then flprint "Cpdflib.rotate\n";
  try
    update_pdf (Cpdf.rotate_pdf angle (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "rotate" e; err_unit

let rotateBy i range angle =
  if !dbg then flprint "Cpdflib.rotateBy\n";
  try
    update_pdf (Cpdf.rotate_pdf_by angle (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "rotateBy" e; err_unit

let rotateContents i range angle =
  if !dbg then flprint "Cpdflib.rotateContents\n";
  try
    update_pdf (Cpdf.rotate_contents angle (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "rotateContents" e; err_unit

let upright i range =
  if !dbg then flprint "Cpdflib.upright\n";
  try
    update_pdf (Cpdf.upright (Array.to_list (lookup_range range)) (lookup_pdf i)) (lookup_pdf i)
  with
    e -> handle_error "upright" e; err_unit

let hFlip i range =
  if !dbg then flprint "Cpdflib.hFlip\n";
  try
    update_pdf (Cpdf.hflip_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "hFlip" e; err_unit

let vFlip i range =
  if !dbg then flprint "Cpdflib.vFlip\n";
  try
    update_pdf (Cpdf.vflip_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "vFlip" e; err_unit

let crop i range x y w h =
  if !dbg then flprint "Cpdflib.crop\n";
  try
    update_pdf (Cpdf.crop_pdf x y w h (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "crop" e; err_unit

let removeCrop i range =
  if !dbg then flprint "Cpdflib.removeCrop\n";
  try
    update_pdf (Cpdf.remove_cropping_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "removeCrop" e; err_unit

let removeTrim i range =
  if !dbg then flprint "Cpdflib.removeTrim\n";
  try
    update_pdf (Cpdf.remove_trim_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "removeTrim" e; err_unit

let removeArt i range =
  if !dbg then flprint "Cpdflib.removeArt\n";
  try
    update_pdf (Cpdf.remove_art_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "removeArt" e; err_unit

let removeBleed i range =
  if !dbg then flprint "Cpdflib.removeBleed\n";
  try
    update_pdf (Cpdf.remove_bleed_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "removeBleed" e; err_unit

let setMediabox i range minx maxx miny maxy =
  if !dbg then flprint "Cpdflib.setMediabox\n";
  try
    update_pdf
      (Cpdf.set_mediabox minx miny (maxx -. minx) (maxy -. miny) (lookup_pdf i) (Array.to_list (lookup_range range))) 
      (lookup_pdf i)
  with
    e -> handle_error "setMediaBox" e; err_unit

let _ = Callback.register "scalePages" scalePages
let _ = Callback.register "scaleToFit" scaleToFit
let _ = Callback.register "scaleToFitPaper" scaleToFitPaper
let _ = Callback.register "shiftContents" shiftContents
let _ = Callback.register "scaleContents" scaleContents
let _ = Callback.register "rotate" rotate
let _ = Callback.register "rotateBy" rotateBy
let _ = Callback.register "rotateContents" rotateContents
let _ = Callback.register "upright" upright
let _ = Callback.register "hFlip" hFlip
let _ = Callback.register "vFlip" vFlip
let _ = Callback.register "crop" crop
let _ = Callback.register "removeCrop" removeCrop
let _ = Callback.register "removeArt" removeArt
let _ = Callback.register "removeTrim" removeTrim
let _ = Callback.register "removeBleed" removeBleed
let _ = Callback.register "setMediabox" setMediabox

(* CHAPTER 5. Compression *)
let compress pdf =
  if !dbg then flprint "Cpdflib.compress\n";
  try update_pdf (Cpdf.recompress_pdf (lookup_pdf pdf)) (lookup_pdf pdf) with
    e -> handle_error "compress" e; err_unit

let decompress pdf =
  if !dbg then flprint "Cpdflib.decompress\n";
  try update_pdf (Cpdf.decompress_pdf (lookup_pdf pdf)) (lookup_pdf pdf) with
    e -> handle_error "decompress" e; err_unit

let _ = Callback.register "compress" compress
let _ = Callback.register "decompress" decompress

(* CHAPTER 6. Bookmarks *)
let bookmarkinfo = ref [||]

(* Actually get the font info and store in an array. *)
let startGetBookmarkInfo pdf =
  if !dbg then flprint "Cpdflib.startGetBookmarkInfo\n";
  try
    bookmarkinfo := Array.of_list (Pdfmarks.read_bookmarks (lookup_pdf pdf))
  with
    e -> handle_error "startGetBookmarkInfo" e; err_unit

(* Throw the information away. *)
let endGetBookmarkInfo () =
  if !dbg then flprint "Cpdflib.endGetBookmarkInfo\n";
  try
    bookmarkinfo := [||]
  with
    e -> handle_error "endGetBookmarkInfo" e; err_unit

let numberBookmarks () =
  if !dbg then flprint "Cpdflib.numberBookmarks\n";
  try Array.length !bookmarkinfo with 
    e -> handle_error "numberBookmarks" e; err_int 

let getBookmarkPage pdf serial =
  if !dbg then flprint "Cpdflib.getBookmarkPage\n";
  try
    let page =
      Pdfpage.pagenumber_of_target (lookup_pdf pdf) !bookmarkinfo.(serial).Pdfmarks.target
    in
      page
  with
    e -> handle_error "getBookmarkPage" e; err_int

let getBookmarkLevel serial =
  if !dbg then flprint "Cpdflib.getBookmarkLevel\n";
  try !bookmarkinfo.(serial).Pdfmarks.level with
    e -> handle_error "getBookmarkLevel" e; err_int

let getBookmarkText serial =
  if !dbg then flprint "Cpdflib.getBookmarkText\n";
  try !bookmarkinfo.(serial).Pdfmarks.text with
    e -> handle_error "getBookmarkText" e; err_string

let _ = Callback.register "numberBookmarks" numberBookmarks
let _ = Callback.register "getBookmarkPage" getBookmarkPage
let _ = Callback.register "getBookmarkLevel" getBookmarkLevel
let _ = Callback.register "getBookmarkText" getBookmarkText
let _ = Callback.register "startGetBookmarkInfo" startGetBookmarkInfo
let _ = Callback.register "endGetBookmarkInfo" endGetBookmarkInfo

(* CHAPTER 7. Presentations *)
(* CHAPTER 8. Logos, Watermarks and Stamps *)
let stampOn pdf pdf2 range =
  if !dbg then flprint "Cpdflib.stampOn\n";
  try
    update_pdf
      (Cpdf.stamp
         (Cpdf.BottomLeft 0.)
         false
         false
         false
         false
         true
         (Array.to_list (lookup_range range))
         (lookup_pdf pdf)
         (lookup_pdf pdf2))
      (lookup_pdf pdf2)
  with
    e -> handle_error "stampOn" e; err_unit

let stampUnder pdf pdf2 range =
  if !dbg then flprint "Cpdflib.stampUnder\n";
  try
    update_pdf
      (Cpdf.stamp
         (Cpdf.BottomLeft 0.)
         false
         false
         false
         false
         false
         (Array.to_list (lookup_range range))
         (lookup_pdf pdf)
         (lookup_pdf pdf2))
      (lookup_pdf pdf2)
  with
    e -> handle_error "stampUnder" e; err_unit

let combinePages pdf pdf2 =
  if !dbg then flprint "Cpdflib.combinePages\n";
  try
    new_pdf (Cpdf.combine_pages false (lookup_pdf pdf2) (lookup_pdf pdf) false false true)
  with
    e -> handle_error "combinePages" e; err_int

let removeText pdf range =
  if !dbg then flprint "Cpdflib.removeText\n";
  try
    update_pdf (Cpdf.removetext (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "removeText" e; err_unit

type font = Pdftext.standard_font

type color = {r: float; g: float ; b: float}

let white = {r = 1.; g = 1.; b = 1.}

let black = {r = 0.; g = 0.; b = 0.}

let red = {r = 1.; g = 0.; b = 0.}

let green = {r = 0.; g = 1.; b = 0.}

let blue = {r = 0.; g = 0.; b = 1.}

let rgb r g b = {r = r; g = g; b = b}

let addTextHowMany () =
  if !dbg then flprint "Cpdflib.addTextHowMany\n";
  try Cpdf.metrics_howmany () with
    e -> handle_error "addTextHowMany" e; err_int

let addTextReturnText i =
  if !dbg then flprint "Cpdflib.addTextReturnText\n";
  try Cpdf.metrics_text i with
    e -> handle_error "addTextReturnText" e; err_string

let addTextReturnX i =
  if !dbg then flprint "Cpdflib.addTextReturnX\n";
  try Cpdf.metrics_x i with
    e -> handle_error "addTextReturnX" e; err_float

let addTextReturnY i =
  if !dbg then flprint "Cpdflib.addTextReturnY\n";
  try Cpdf.metrics_y i with
    e -> handle_error "addTextReturnY" e; err_float

let addTextReturnRotation i =
  if !dbg then flprint "Cpdflib.addTextReturnRotation\n";
  try Cpdf.metrics_rot i with
    e -> handle_error "addTextReturnRotation" e; err_float

let addTextReturnBaselineAdjustment () =
  if !dbg then flprint "Cpdflib.addTextReturnBaselineAdjustment\n";
  try Cpdf.metrics_baseline_adjustment () with
    e -> handle_error "addTextReturnBaselineAdjustment" e; err_float

let _ = Callback.register "addTextHowMany" addTextHowMany
let _ = Callback.register "addTextReturnText" addTextReturnText
let _ = Callback.register "addTextReturnX" addTextReturnX
let _ = Callback.register "addTextReturnY" addTextReturnY
let _ = Callback.register "addTextReturnRotation" addTextReturnRotation
let _ = Callback.register "addTextReturnBaselineAdjustment" addTextReturnBaselineAdjustment

let addText_inner
  metrics pdf range text position linespacing bates font fontsize color underneath cropbox outline opacity justification midline filename
=
  let fontname = Pdftext.string_of_standard_font font
  and color = color.r, color.g, color.b in
    let newpdf =
      (Cpdf.addtexts
         metrics
         1.0 outline false fontname (Some font) false (* embed font FIXME
         *)bates None color position linespacing fontsize
         underneath text (Array.to_list range) Cpdf.Horizontal cropbox opacity
         justification midline false (* topline. FIXME *) filename pdf)
    in
      if not metrics then
        begin
          pdf.Pdf.root <- newpdf.Pdf.root;
          pdf.Pdf.objects <- newpdf.Pdf.objects;
          pdf.Pdf.trailerdict <- newpdf.Pdf.trailerdict
        end

let addText
  metrics pdf range text pos f1 f2 linespace bates font size r g b
  underneath cropbox outline opacity justification midline filename
=
  if !dbg then flprint "Cpdflib.addText\n";
  try
    addText_inner metrics (lookup_pdf pdf) (lookup_range range) text (read_position f1 f2 pos)
    linespace bates font size (rgb r g b) underneath cropbox outline opacity justification midline filename
  with
    e -> handle_error "addText" e; err_unit

let textWidth font text =
  if !dbg then flprint "Cpdflib.textwidth\n";
  try
    Pdfstandard14.textwidth false font text
  with
    e -> handle_error "textWidth" e; err_int

let _ = Callback.register "stampOn" stampOn
let _ = Callback.register "stampUnder" stampUnder
let _ = Callback.register "combinePages" combinePages
let _ = Callback.register "removeText" removeText
let _ = Callback.register "addText" addText
let _ = Callback.register "textWidth" textWidth

(* CHAPTER 9. Multipage facilities *)
let twoUp pdf =
  if !dbg then flprint "Cpdflib.twoUp\n";
  try
    update_pdf (Cpdf.twoup (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "twoUp" e; err_unit

let padBefore pdf range =
  if !dbg then flprint "Cpdflib.padBefore\n";
  try
    update_pdf (Cpdf.padbefore (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "padBefore" e; err_unit
 
let padAfter pdf range =
  if !dbg then flprint "Cpdflib.padAfter\n";
  try
    update_pdf (Cpdf.padafter (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "padAfter" e; err_unit

let _ = Callback.register "twoUp" twoUp
let _ = Callback.register "padBefore" padBefore
let _ = Callback.register "padAfter" padAfter

(* CHAPTER 10. Annotations *)
(* CHAPTER 11. Document Information and Metadata *)

let isLinearized string =
  try
    Pdfread.is_linearized (Pdfio.input_of_channel (open_in_bin string))
  with
    e -> handle_error "isLinearized" e; err_bool

let _ = Callback.register "isLinearized" isLinearized

let fontinfo = ref [||]

(* Actually get the font info and store in an array. *)
let startGetFontInfo pdf =
  if !dbg then flprint "Cpdflib.startGetFontInfo\n";
  try
    fontinfo := Array.of_list (Cpdf.list_fonts (lookup_pdf pdf))
  with
    e -> handle_error "startGetFontInfo" e; err_unit

(* Throw the information away. *)
let endGetFontInfo () =
  if !dbg then flprint "Cpdflib.endGetFontInfo\n";
  try fontinfo := [||] with e -> handle_error "endGetFontInfo" e; err_unit

let numberFonts () =
  if !dbg then flprint "Cpdflib.numberFonts\n";
  try Array.length !fontinfo with e -> handle_error "numberFonts" e; err_int

let getFontPage serial =
  if !dbg then flprint "Cpdflib.getFontPage\n";
  try let x, _, _, _, _ = !fontinfo.(serial) in x with e -> handle_error "getFontPage" e; err_int

let getFontName serial =
  if !dbg then flprint "Cpdflib.getFontName\n";
  try let _, _, _, x, _ = !fontinfo.(serial) in x with e -> handle_error "getFontName" e; err_string

let getFontType serial =
  if !dbg then flprint "Cpdflib.getFontType\n";
  try let _, _, x, _, _ = !fontinfo.(serial) in x with e -> handle_error "getFontType" e; err_string

let getFontEncoding serial =
  if !dbg then flprint "Cpdflib.getFontEncoding\n";
  try let _, _, _, _, x = !fontinfo.(serial) in x with e -> handle_error "getFontEncoding" e; err_string

let _ = Callback.register "numberFonts" numberFonts
let _ = Callback.register "getFontPage" getFontPage
let _ = Callback.register "getFontName" getFontName
let _ = Callback.register "getFontType" getFontType
let _ = Callback.register "getFontEncoding" getFontEncoding
let _ = Callback.register "startGetFontInfo" startGetFontInfo
let _ = Callback.register "endGetFontInfo" endGetFontInfo

let getVersion pdf =
  if !dbg then flprint "Cpdflib.getVersion\n";
  try (lookup_pdf pdf).Pdf.minor with e -> handle_error "getVersion" e; err_int

let getTitle pdf =
  if !dbg then flprint "Cpdflib.getTitle\n";
  try
    Cpdf.get_info_utf8 (lookup_pdf pdf) "/Title"
  with
    e -> handle_error "getTitle" e; err_string

let getAuthor pdf =
  if !dbg then flprint "Cpdflib.getAuthor\n";
  try
    Cpdf.get_info_utf8 (lookup_pdf pdf) "/Author"
  with
    e -> handle_error "getAuthor" e; err_string

let getSubject pdf =
  if !dbg then flprint "Cpdflib.getSubject\n";
  try
    Cpdf.get_info_utf8 (lookup_pdf pdf) "/Subject"
  with
    e -> handle_error "getSubject" e; err_string

let getKeywords pdf =
  if !dbg then flprint "Cpdflib.getKeywords\n";
  try
    Cpdf.get_info_utf8 (lookup_pdf pdf) "/Keywords"
  with
    e -> handle_error "getKeywords" e; err_string

let getCreator pdf =
  if !dbg then flprint "Cpdflib.getCreator\n";
  try
    Cpdf.get_info_utf8 (lookup_pdf pdf) "/Creator"
  with
    e -> handle_error "getCreator" e; err_string

let getProducer pdf =
  if !dbg then flprint "Cpdflib.getProducer\n";
  try
    Cpdf.get_info_utf8 (lookup_pdf pdf) "/Producer"
  with
    e -> handle_error "getProducer" e; err_string

let getCreationDate pdf =
  if !dbg then flprint "Cpdflib.getCreationDate\n";
  try
    Cpdf.get_info_utf8 (lookup_pdf pdf) "/CreationDate"
  with
    e -> handle_error "getCreationDate" e; err_string

let getModificationDate pdf =
  if !dbg then flprint "Cpdflib.getModificationDate\n";
  try
    Cpdf.get_info_utf8 (lookup_pdf pdf) "/ModDate"
  with
    e -> handle_error "getModificationDate" e; err_string

let getDateComponents str =
  if !dbg then flprint "Cpdflib.getDateComponents\n";
  try Pdfdate.date_of_string str with
    e -> handle_error "getDateComponents" e; err_date

let dateStringOfComponents year month day hour minute second hour_offset minute_offset =
  if !dbg then flprint "Cpdflib.dateStringOfComponents\n";
  try
    Pdfdate.string_of_date
      {Pdfdate.year = year;
       Pdfdate.month = month;
       Pdfdate.day = day;
       Pdfdate.hour = hour;
       Pdfdate.minute = minute;
       Pdfdate.second = second;
       Pdfdate.hour_offset = hour_offset;
       Pdfdate.minute_offset = minute_offset}
  with
    e -> handle_error "dateStringOfComponents" e; err_string

let setVersion pdf version =
  if !dbg then flprint "Cpdflib.setVersion\n";
  try
    (lookup_pdf pdf).Pdf.minor <- version
  with
    e -> handle_error "setVersion" e; err_unit

let setTitle pdf title =
  if !dbg then flprint "Cpdflib.setTitle\n";
  try
    let title = Pdftext.pdfdocstring_of_utf8 title in
      update_pdf (Cpdf.set_pdf_info ("/Title", Pdf.String title, 1) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setTitle" e; err_unit

let setAuthor pdf author =
  if !dbg then flprint "Cpdflib.setAuthor\n";
  try
    let author = Pdftext.pdfdocstring_of_utf8 author in
      update_pdf (Cpdf.set_pdf_info ("/Author", Pdf.String author, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setAuthor" e; err_unit

let setSubject pdf subject =
  if !dbg then flprint "Cpdflib.setSubject\n";
  try
    let subject = Pdftext.pdfdocstring_of_utf8 subject in
      update_pdf (Cpdf.set_pdf_info ("/Subject", Pdf.String subject, 1) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setSubject" e; err_unit

let setKeywords pdf keywords =
  if !dbg then flprint "Cpdflib.setKeywords\n";
  try
    let keywords = Pdftext.pdfdocstring_of_utf8 keywords in
      update_pdf (Cpdf.set_pdf_info ("/Keywords", Pdf.String keywords, 1) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setKeywords" e; err_unit

let setCreator pdf creator =
  if !dbg then flprint "Cpdflib.setCreator\n";
  try
    let creator = Pdftext.pdfdocstring_of_utf8 creator in
      update_pdf (Cpdf.set_pdf_info ("/Creator", Pdf.String creator, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "SetCreator" e; err_unit

let setProducer pdf producer =
  if !dbg then flprint "Cpdflib.setProducer\n";
  try      
    let producer = Pdftext.pdfdocstring_of_utf8 producer in
      update_pdf (Cpdf.set_pdf_info ("/Producer", Pdf.String producer, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setProducer" e; err_unit

let setCreationDate pdf date =
  if !dbg then flprint "Cpdflib.setCreationDate\n";
  try
    let date = Pdftext.pdfdocstring_of_utf8 date in
      update_pdf (Cpdf.set_pdf_info ("/CreationDate", Pdf.String (Cpdf.expand_date date), 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setCreationDate" e; err_unit

let setModificationDate pdf date =
  if !dbg then flprint "Cpdflib.setModificationDate\n";
  try
    let date = Pdftext.pdfdocstring_of_utf8 date in
      update_pdf (Cpdf.set_pdf_info ("/ModDate", Pdf.String (Cpdf.expand_date date), 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setModificationDate" e; err_unit

let markTrapped pdf =
  if !dbg then flprint "Cpdflib.markTrapped\n";
  try
    update_pdf (Cpdf.set_pdf_info ("/Trapped", Pdf.Boolean true, 3) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "markTrapped" e; err_unit

let markUntrapped pdf =
  if !dbg then flprint "Cpdflib.markUntrapped\n";
  try
    update_pdf (Cpdf.set_pdf_info ("/Trapped", Pdf.Boolean false, 3) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "markUntrapped" e; err_unit

type layout =
  | SinglePage
  | OneColumn
  | TwoColumnLeft
  | TwoColumnRight
  | TwoPageLeft
  | TwoPageRight

let string_of_layout = function
  | SinglePage -> "SinglePage"
  | OneColumn -> "OneColumn"
  | TwoColumnLeft -> "TwoColumnLeft"
  | TwoColumnRight -> "TwoColumnRight"
  | TwoPageLeft -> "TwoPageLeft"
  | TwoPageRight -> "TwoPageRight"

let setPageLayout pdf layout =
  if !dbg then flprint "Cpdflib.setPageLayout\n";
  try
    let layout =
      match layout with
      | 0 -> SinglePage
      | 1 -> OneColumn
      | 2 -> TwoColumnLeft
      | 3 -> TwoColumnRight
      | 4 -> TwoPageLeft
      | 5 -> TwoPageRight
      | _ -> failwith "setPageLayout"
    in
      update_pdf (Cpdf.set_page_layout (lookup_pdf pdf) (string_of_layout layout)) (lookup_pdf pdf)
  with
    e -> handle_error "setPageLayout" e; err_unit

type pagemode =
  | UseNone
  | UseOutlines
  | UseThumbs
  | FullScreen
  | UseOC
  | UseAttachments

let string_of_mode = function
  | UseNone -> "UseNone"
  | UseOutlines -> "UseOutlines"
  | UseThumbs -> "UseThumbs"
  | FullScreen -> "FullScreen"
  | UseOC -> "UseOC"
  | UseAttachments -> "UseAttachments"

let setPageMode pdf mode =
  if !dbg then flprint "Cpdflib.setPageMode\n";
  try
    let mode =
      match mode with
      | 0 -> UseNone
      | 1 -> UseOutlines
      | 2 -> UseThumbs
      | 3 -> FullScreen
      | 4 -> UseOC
      | 5 -> UseAttachments
      | _ -> failwith "setPageMode"
    in
      update_pdf (Cpdf.set_page_mode (lookup_pdf pdf) (string_of_mode mode)) (lookup_pdf pdf)
  with
    e -> handle_error "setPageMode" e; err_unit

let hideToolbar pdf b =
  if !dbg then flprint "Cpdflib.hideToolbar\n";
  try
    update_pdf (Cpdf.set_viewer_preference ("/HideToolbar", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "hideToolbar" e; err_unit

let hideMenubar pdf b =
  if !dbg then flprint "Cpdflib.hideMenubar\n";
  try
    update_pdf (Cpdf.set_viewer_preference ("/HideMenubar", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "hideMenubar" e; err_unit

let hideWindowUi pdf b =
  if !dbg then flprint "Cpdflib.hideWindowUi\n";
  try
    update_pdf (Cpdf.set_viewer_preference ("/HideWindowUI", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "hideWindowUi" e; err_unit

let fitWindow pdf b =
  if !dbg then flprint "Cpdflib.fitWindow\n";
  try
    update_pdf (Cpdf.set_viewer_preference ("/FitWindow", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "fitWindow" e; err_unit

let centerWindow pdf b =
  if !dbg then flprint "Cpdflib.centerWindow\n";
  try
    update_pdf (Cpdf.set_viewer_preference ("/CenterWindow", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "centerWindow" e; err_unit

let displayDocTitle pdf b =
  if !dbg then flprint "Cpdflib.displayDocTitle\n";
  try
    update_pdf (Cpdf.set_viewer_preference ("/DisplayDocTitle", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "displayDocTitle" e; err_unit

let setMetadataFromFile pdf filename =
  if !dbg then flprint "Cpdflib.setMetadataFromFile\n";
  try
    update_pdf (Cpdf.set_metadata false filename (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setMetadataFromFile" e; err_unit

let setMetadataFromByteArray pdf bytes =
  if !dbg then flprint "Cpdflib.setMetadataFromByteArray\n";
  try
    update_pdf (Cpdf.set_metadata_from_bytes false (Pdfio.bytes_of_raw bytes) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setMetadataFromByteArray" e; err_unit

let getMetadata pdf =
  if !dbg then flprint "Cpdflib.getMetadata\n";
  try
    match Cpdf.get_metadata (lookup_pdf pdf) with
      None -> err_data
    | Some data -> Pdfio.raw_of_bytes data
  with
    e -> handle_error "getMetadata" e; err_data

let removeMetadata pdf =
  if !dbg then flprint "Cpdflib.removeMetadata\n";
  try
    update_pdf (Cpdf.remove_metadata (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "removeMetadata" e; err_unit

let hasBox pdf pagenumber boxname =
  if !dbg then flprint "Cpdflib.hasBox\n";
  try Cpdf.hasbox (lookup_pdf pdf) pagenumber boxname with
    e -> handle_error "hasBox" e; err_bool

type box =
  {minx : float;
   maxx : float;
   miny : float;
   maxy : float}

type page_info =
  {pimediabox : box;
   cropbox : box;
   bleedbox : box;
   artbox : box;
   trimbox : box}

let getPageInfo pdf =
  Array.of_list
    (map
       (function (page : Pdfpage.t) ->
         let m_minx, m_miny, m_maxx, m_maxy =
           match page.Pdfpage.mediabox with
           | Pdf.Array [a; b; c; d] ->
               Pdf.getnum a, Pdf.getnum b, Pdf.getnum c, Pdf.getnum d
           | _ -> 0., 0., 0., 0.
         in
           let c_minx, c_miny, c_maxx, c_maxy =
             match Pdf.lookup_direct pdf "/CropBox" page.Pdfpage.rest with
             | Some (Pdf.Array [a; b; c; d]) ->
                 Pdf.getnum a, Pdf.getnum b, Pdf.getnum c, Pdf.getnum d
             | _ -> m_minx, m_miny, m_maxx, m_maxy
           in
             let getotherbox name =
               match Pdf.lookup_direct pdf name page.Pdfpage.rest with
                 | Some (Pdf.Array [a; b; c; d]) ->
                     Pdf.getnum a, Pdf.getnum b, Pdf.getnum c, Pdf.getnum d
                 | _ -> c_minx, c_miny, c_maxx, c_maxy
             in
             let t_minx, t_miny, t_maxx, t_maxy = getotherbox "/TrimBox"
             in let a_minx, a_miny, a_maxx, a_maxy = getotherbox "/ArtBox"
             in let b_minx, b_miny, b_maxx, b_maxy = getotherbox "/BleedBox"
             in
               {pimediabox = {minx = m_minx; maxx = m_maxx; miny = m_miny; maxy = m_maxy};
                cropbox = {minx = c_minx; maxx = c_maxx; miny = c_miny; maxy = c_maxy};
                trimbox = {minx = t_minx; maxx = t_maxx; miny = t_miny; maxy = t_maxy};
                artbox = {minx = a_minx; maxx = a_maxx; miny = a_miny; maxy = a_maxy};
                bleedbox = {minx = b_minx; maxx = b_maxx; miny = b_miny; maxy = b_maxy}}
       )
       (Pdfpage.pages_of_pagetree pdf))

let getMediaBox pdf pagenumber =
  if !dbg then flprint "Cpdflib.getMediaBox\n";
  try 
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).pimediabox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getMediaBox" e; err_box

let getCropBox pdf pagenumber =
  if !dbg then flprint "Cpdflib.getCropBox\n";
  try
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).cropbox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getCropBox" e; err_box

let getTrimBox pdf pagenumber =
  if !dbg then flprint "Cpdflib.getTrimBox\n";
  try
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).trimbox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getTrimBox" e; err_box

let getArtBox pdf pagenumber =
  if !dbg then flprint "Cpdflib.getArtBox\n";
  try
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).artbox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getArtBox" e; err_box

let getBleedBox pdf pagenumber =
  if !dbg then flprint "Cpdflib.getBleedBox\n";
  try
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).bleedbox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getBleedBox" e; err_box

let setArtBox pdf range minx maxx miny maxy =
  if !dbg then flprint "Cpdflib.setArtBox\n";
  try
    update_pdf (Cpdf.setBox "/ArtBox" minx maxx miny maxy (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "setArtBox" e; err_unit

let setBleedBox pdf range minx maxx miny maxy =
  if !dbg then flprint "Cpdflib.setBleedBox\n";
  try
    update_pdf (Cpdf.setBox "/BleedBox" minx maxx miny maxy (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "setBleedBox" e; err_unit

let setTrimBox pdf range minx maxx miny maxy =
  if !dbg then flprint "Cpdflib.setTrimBox\n";
  try
    update_pdf (Cpdf.setBox "/TrimBox" minx maxx miny maxy (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "setTrimBox" e; err_unit

let setCropBox pdf range minx maxx miny maxy =
  if !dbg then flprint "Cpdflib.setCropBox\n";
  try
    update_pdf (Cpdf.setBox "/CropBox" minx maxx miny maxy (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "setCropBox" e; err_unit

let _ = Callback.register "getVersion" getVersion
let _ = Callback.register "getTitle" getTitle
let _ = Callback.register "getAuthor" getAuthor
let _ = Callback.register "getSubject" getSubject
let _ = Callback.register "getKeywords" getKeywords
let _ = Callback.register "getCreator" getCreator
let _ = Callback.register "getProducer" getProducer
let _ = Callback.register "getCreationDate" getCreationDate
let _ = Callback.register "getDateComponents" getDateComponents
let _ = Callback.register "dateStringOfComponents" dateStringOfComponents
let _ = Callback.register "getModificationDate" getModificationDate
let _ = Callback.register "setVersion" setVersion
let _ = Callback.register "setTitle" setTitle
let _ = Callback.register "setAuthor" setAuthor
let _ = Callback.register "setSubject" setSubject
let _ = Callback.register "setKeywords" setKeywords
let _ = Callback.register "setCreator" setCreator
let _ = Callback.register "setProducer" setProducer
let _ = Callback.register "setCreationDate" setCreationDate
let _ = Callback.register "setModificationDate" setModificationDate
let _ = Callback.register "markTrapped" markTrapped
let _ = Callback.register "markUntrapped" markUntrapped
let _ = Callback.register "setPageMode" setPageMode
let _ = Callback.register "setPageLayout" setPageLayout
let _ = Callback.register "hasBox" hasBox
let _ = Callback.register "getMediaBox" getMediaBox
let _ = Callback.register "getCropBox" getCropBox
let _ = Callback.register "getArtBox" getArtBox
let _ = Callback.register "getTrimBox" getTrimBox
let _ = Callback.register "getBleedBox" getBleedBox
let _ = Callback.register "setArtBox" setArtBox
let _ = Callback.register "setCropBox" setCropBox
let _ = Callback.register "setTrimBox" setTrimBox
let _ = Callback.register "setBleedBox" setBleedBox
let _ = Callback.register "hideToolbar" hideToolbar 
let _ = Callback.register "hideMenubar" hideMenubar
let _ = Callback.register "hideWindowUi" hideWindowUi
let _ = Callback.register "fitWindow" fitWindow
let _ = Callback.register "centerWindow" centerWindow
let _ = Callback.register "displayDocTitle" displayDocTitle
let _ = Callback.register "setMetadataFromFile" setMetadataFromFile
let _ = Callback.register "removeMetadata" removeMetadata
let _ = Callback.register "setMetadataFromByteArray" setMetadataFromByteArray
let _ = Callback.register "getMetadata" getMetadata

(* CHAPTER 12. File Attachments *)
let attachFile filename pdf =
  if !dbg then flprint "Cpdflib.attachFile\n";
  try
    update_pdf
      (Cpdf.attach_file false None (lookup_pdf pdf) filename)
      (lookup_pdf pdf);
  with
    e -> handle_error "attachFile" e; err_unit

let attachFileFromMemory rawbytes filename pdf =
  if !dbg then flprint "Cpdflib.attachFileFromMemory\n";
  try
    update_pdf
      (Cpdf.attach_file ~memory:(Pdfio.bytes_of_raw rawbytes) false None (lookup_pdf pdf) filename)
      (lookup_pdf pdf)
  with
    e -> handle_error "attachFileFromMemory" e; err_unit

let attachFileToPage filename pdf pagenumber =
  if !dbg then flprint "Cpdflib.attachFileToPage\n";
  try
    update_pdf
      (Cpdf.attach_file false (Some pagenumber) (lookup_pdf pdf) filename)
      (lookup_pdf pdf)
  with
    e -> handle_error "attachFileToPage" e; err_unit

let attachFileToPageFromMemory rawbytes filename pdf pagenumber =
  if !dbg then flprint "Cpdflib.attachFileToPageFromMemory\n";
  try
    update_pdf
      (Cpdf.attach_file ~memory:(Pdfio.bytes_of_raw rawbytes) false (Some pagenumber) (lookup_pdf pdf) filename)
      (lookup_pdf pdf)
  with
    e -> handle_error "attachFileToPageFromMemory" e; err_unit

let removeAttachedFiles pdf =
  if !dbg then flprint "Cpdflib.removeAttachedFiles\n";
  try
    update_pdf (Cpdf.remove_attached_files (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "removeAttachedFiles" e; err_unit

let attachments = ref []

let startGetAttachments pdf =
  if !dbg then flprint "Cpdflib.startGetAttachments\n";
  try
    attachments := Cpdf.list_attached_files (lookup_pdf pdf)
  with
    e -> handle_error "startGetAttachments" e; err_unit

let endGetAttachments () =
  if !dbg then flprint "Cpdflib.endGetAttachments\n";
  try attachments := [] with
    e -> handle_error "endGetAttachments" e; err_unit

let numberGetAttachments () =
  if !dbg then flprint "Cpdflib.numberGetAttachments\n";
  try length !attachments with e -> handle_error "numberGetAttachments" e; err_int

let getAttachmentName serial =
  if !dbg then flprint "Cpdflib.getAttachmentName\n";
  try
    (select (serial + 1) !attachments).Cpdf.name
  with e ->
    handle_error "getAttachmentName" e; err_string

let getAttachmentPage serial =
  if !dbg then flprint "Cpdflib.getAttachmentPage\n";
  try
    (select (serial + 1) !attachments).Cpdf.pagenumber
  with e ->
    handle_error "getAttachmentPage" e; err_int

let getAttachmentData serial =
  if !dbg then flprint "Cpdflib.getAttachmentData\n";
  try
    Pdfio.raw_of_bytes
      ((select (serial + 1) !attachments).Cpdf.data ())
  with e ->
    handle_error "getAttachmentData" e; err_data

let _ = Callback.register "attachFile" attachFile
let _ = Callback.register "attachFileToPage" attachFileToPage
let _ = Callback.register "attachFileFromMemory" attachFileFromMemory
let _ = Callback.register "attachFileToPageFromMemory" attachFileToPageFromMemory
let _ = Callback.register "removeAttachedFiles" removeAttachedFiles
let _ = Callback.register "startGetAttachments" startGetAttachments
let _ = Callback.register "endGetAttachments" endGetAttachments
let _ = Callback.register "numberGetAttachments" numberGetAttachments
let _ = Callback.register "getAttachmentName" getAttachmentName
let _ = Callback.register "getAttachmentPage" getAttachmentPage
let _ = Callback.register "getAttachmentData" getAttachmentData

(* CHAPTER 13. Miscellaneous *)
let draft pdf range boxes =
  if !dbg then flprint "Cpdflib.draft\n";
  try
    update_pdf (Cpdf.draft boxes (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "draft" e; err_unit

let blackText pdf range =
  if !dbg then flprint "Cpdflib.blackText\n";
  try
    update_pdf (Cpdf.blacktext (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "blackText" e; err_unit

let blackLines pdf range =
  if !dbg then flprint "Cpdflib.blackLines\n";
  try
    update_pdf (Cpdf.blacklines (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "blackLines" e; err_unit

let blackFills pdf range =
  if !dbg then flprint "Cpdflib.blackFills\n";
  try
    update_pdf (Cpdf.blackfills (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "blackFills" e; err_unit

let thinLines pdf range thickness =
  if !dbg then flprint "Cpdflib.thinLines\n";
  try
    update_pdf (Cpdf.thinlines (Array.to_list (lookup_range range)) thickness (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "thinLines" e; err_unit

let copyId from_pdf to_pdf =
  if !dbg then flprint "Cpdflib.copyId\n";
  try
    update_pdf (Cpdf.copy_id false (lookup_pdf from_pdf) (lookup_pdf to_pdf)) (lookup_pdf to_pdf)
  with
    e -> handle_error "copyId" e; err_unit

let _ = Callback.register "draft" draft
let _ = Callback.register "blackText" blackText
let _ = Callback.register "blackLines" blackLines
let _ = Callback.register "blackFills" blackFills
let _ = Callback.register "thinLines" thinLines
let _ = Callback.register "copyId" copyId

(* Add page labels of a given style, prefix and offset in a given range. *)
let addPageLabels pdf style prefix offset range =
  if !dbg then flprint "Cpdflib.addPageLabels\n";
  try
    let style =
      match style with
      | 0 -> Pdfpagelabels.DecimalArabic
      | 1 -> Pdfpagelabels.UppercaseRoman
      | 2 -> Pdfpagelabels.LowercaseRoman
      | 3 -> Pdfpagelabels.UppercaseLetters
      | 4 -> Pdfpagelabels.LowercaseLetters
      | _ -> failwith "Unknown page label style"
    and prefix =
      if prefix = "" then None else Some (Pdftext.pdfdocstring_of_utf8 prefix)
    in
      Cpdf.add_page_labels (lookup_pdf pdf) style prefix offset (Array.to_list (lookup_range range))
  with
    e -> handle_error "addPageLabels" e; err_unit

let _ = Callback.register "addPageLabels" addPageLabels

let onexit () =
  if !dbg then flprint "Cpdflib.onexit\n";
  Printf.printf "There are %i ranges on exit\n" (Hashtbl.length ranges);
  Printf.printf "There are %i PDFs on exit:\n" (Hashtbl.length pdfs);
  Hashtbl.iter (fun k v -> Printf.printf "%i, " k) pdfs;
  flprint "\n"

let _ = Callback.register "onexit" onexit

let squeeze userpw log_file file_in file_out =
  try
    Cpdfcommand.go_withargv
      [|"cpdf";
        file_in;
        "user=" ^ userpw;
        "-stay-on-error";
        "-squeeze-log-to"; log_file;
        "-squeeze";
        "-recrypt";
        "-o"; file_out|];
    0
  with
    Cpdfcommand.StayOnError -> 1

(* Look up the pdf, squeeze it with Cpdf.squeeze *)
let squeezeInMemory pdf =
  if !dbg then flprint "Cpdflib.squeezeInMemory\n";
  try
    Cpdf.squeeze ~logto:"nolog" (lookup_pdf pdf);
    update_pdf (lookup_pdf pdf) (lookup_pdf pdf)
  with
    e -> handle_error "squeezeInMemory" e; err_unit

let _ = Callback.register "squeeze" squeeze
let _ = Callback.register "squeezeInMemory" squeezeInMemory

let is_linearized filename =
  let ch = open_in_bin filename in
    let r = Pdfread.is_linearized (Pdfio.input_of_channel ch) in
      close_in ch;
      r

let _ = Callback.register "is_linearized" is_linearized

