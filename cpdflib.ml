(* CHAPTER 1. Basics *)
open Pdfutil

(* We need to poke Cpdfcommand to get its module initialisation to run, to get
the mutual recursion between Cpdfdrawcontrol and Cpdfcommand done. *)
let () = Cpdfcommand.null ()

let fast = ref false

let embed_std14 = ref false
let embed_std14_dir = ref ""

let json_utf8 = ref false

let setFast () =
  fast := true

let setSlow () =
  fast := false

let embedStd14 b =
  embed_std14 := b

let embedStd14Dir dir =
  embed_std14_dir := dir

let jsonUTF8 b =
  json_utf8 := b

let _ = Callback.register "setFast" setFast
let _ = Callback.register "setSlow" setSlow
let _ = Callback.register "embedStd14" embedStd14
let _ = Callback.register "embedStd14Dir" embedStd14Dir
let _ = Callback.register "JSONUTF8" jsonUTF8

let version = "2.6.1"

let _ = Callback.register "version" version

let ppstub f n p = (f n p, n, Pdftransform.i_matrix)

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
  lastError := noerror;
  lastErrorString := ""

(* Used within all functions to wrap the error up *)
let handle_error fn e =
  let errstr = Printf.sprintf "ERROR: %s: %s" fn (Printexc.to_string e) in
    prerr_endline errstr;
    flush stderr;
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
  try Pdfunits.points x Pdfunits.Centimetre with e ->
    handle_error "ptOfCm" e; err_float

let ptOfMm x =
  try Pdfunits.points x Pdfunits.Millimetre with e ->
    handle_error "ptOfMm" e; err_float

let ptOfIn x =
  try Pdfunits.points x Pdfunits.Inch with e ->
    handle_error "ptOfIn" e; err_float

let cmOfPt x =
  try Pdfunits.centimetres x Pdfunits.PdfPoint with e ->
    handle_error "cmOfPt" e; err_float

let mmOfPt x =
  try Pdfunits.millimetres x Pdfunits.PdfPoint with e ->
    handle_error "mmOfPt" e; err_float

let inOfPt x =
  try Pdfunits.inches x Pdfunits.PdfPoint with e ->
    handle_error "inOfPt" e; err_float

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
  try new_range (Array.make 0 0) with e -> handle_error "blankrange" e; err_int

let writerange r p n =
  try Array.set (lookup_range r) p n with e -> handle_error "writerange" e; err_unit

let makerange len =
  try new_range (Array.make len 0) with e -> handle_error "makerange" e; err_int

let lengthrange r =
  try Array.length (lookup_range r) with e -> handle_error "lengthrange" e; err_int

let readrange r p =
  try (lookup_range r).(p) with e -> handle_error "readrange" e; err_int

let addtorange r p =
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
  try Hashtbl.remove ranges r with e -> handle_error "deleterange" e; err_unit

let _ = Callback.register "blankRange" blankrange
let _ = Callback.register "rangeLength" lengthrange
let _ = Callback.register "rangeGet" readrange
let _ = Callback.register "rangeAdd" addtorange
let _ = Callback.register "deleteRange" deleterange
 
type pdfdoc = Pdf.t

type range_arr = int array

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
  try new_range (range a b) with e -> handle_error "range" e; err_int

let even r =
  try new_range (even (lookup_range r)) with e -> handle_error "even" e; err_int

let odd r =
  try new_range (odd (lookup_range r)) with e -> handle_error "odd" e; err_int

let union a b =
  try new_range (union (lookup_range a) (lookup_range b)) with e -> handle_error "union" e; err_int

let difference a b =
  try new_range (difference (lookup_range a) (lookup_range b)) with e -> handle_error "difference" e; err_int

let removeDuplicates r =
  try new_range (removeDuplicates (lookup_range r)) with e -> handle_error "removeDuplicated" e; err_int

let isInRange r i =
  try mem i (Array.to_list (lookup_range r)) with e -> handle_error "isInRange" e; err_bool

let _ = Callback.register "range" range
let _ = Callback.register "even" even
let _ = Callback.register "odd" odd
let _ = Callback.register "rangeUnion" union
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
  if Pdfcrypt.is_encrypted pdf then Encrypted else NotEncrypted

(* Store the PDF and return the integer key *)
let pdfs = null_hash ()

let pdfkey = ref 0

let new_pdf ?channel pdf =
  incr pdfkey;
  Hashtbl.add pdfs !pdfkey ([], (pdf, initial_encryption_status pdf, channel), []);
  !pdfkey

let lookup_pdf i =
  match Hashtbl.find pdfs i with
  | (_, (pdf, _, _), _) -> pdf
  | exception Not_found -> failwith "lookup_pdf: not found"

let number_of_encryption_status = function
  | NotEncrypted -> 0
  | Encrypted -> 1
  | WasDecryptedWithUser _ -> 2
  | WasDecryptedWithOwner _ -> 3

let lookup_pdf_status i =
  match Hashtbl.find pdfs i with (_, (_, enc, _), _) -> enc

let lookupPdfStatus i =
  try
    number_of_encryption_status (lookup_pdf_status i)
  with
    e -> handle_error "lookupPdfStatus" e; err_int

let set_pdf_status i status =
  let l, (pdf, _, channel), r = Hashtbl.find pdfs i in
    Hashtbl.replace pdfs i (l, (pdf, status, channel), r) 

let delete_pdf i =
  begin try
    begin match Hashtbl.find pdfs i with
    | (_, (_, _, Some ch), _) -> close_in ch
    | _ -> ()
    end
  with
    _ -> ()
  end;
  Hashtbl.remove pdfs i

let replace_pdf i pdf =
  let l, (_, enc, channel), r = Hashtbl.find pdfs i in
    Hashtbl.replace pdfs i (l, (pdf, enc, None), r)

let enumeratePairs = ref []

let info_of_pdf _ = "info"

let list_pdfs () =
  Printf.printf "PDFs in memory\n";
  Hashtbl.iter (fun i _ -> Printf.printf "%i " i) pdfs;
  flprint "\n"

let startEnumeratePDFs () =
  try
    Hashtbl.iter
      (fun k v -> enumeratePairs := (k, info_of_pdf v)::!enumeratePairs)
      pdfs;
    length !enumeratePairs
  with
    e -> handle_error "startEnumeratePDFs" e; err_int

let enumeratePDFsKey i =
  try fst (select (i + 1) !enumeratePairs) with e -> handle_error "enumeratePDFsKey" e; err_int

let enumeratePDFsInfo i =
  try snd (select (i + 1) !enumeratePairs) with e -> handle_error "enumeratePDFsInfo" e; err_string

let endEnumeratePDFs () =
  try enumeratePairs := [] with e -> handle_error "endEnumeratePDFs" e; err_unit

let deletePdf i =
  try delete_pdf i with e -> handle_error "deletePdf" e; err_unit

let replacePdf x y =
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

let _ = Callback.register "startEnumeratePDFs" startEnumeratePDFs
let _ = Callback.register "enumeratePDFsKey" enumeratePDFsKey
let _ = Callback.register "enumeratePDFsInfo" enumeratePDFsInfo
let _ = Callback.register "endEnumeratePDFs" endEnumeratePDFs
let _ = Callback.register "deletePdf" deletePdf
let _ = Callback.register "replacePdf" replacePdf

let parsePagespec pdf str =
  try
    new_range (Array.of_list (Cpdfpagespec.parse_pagespec (lookup_pdf pdf) str))
  with
    e -> handle_error "parsePagespec" e; err_int

let stringOfPagespec pdf range =
  try
    Cpdfpagespec.string_of_pagespec (lookup_pdf pdf) (Array.to_list (lookup_range range))
  with
    e -> handle_error "stringOfPagespec" e; err_string

let validatePagespec spec =
  try
    Cpdfpagespec.validate_pagespec spec
  with
    e -> handle_error "validatePagespec" e; err_bool

let _ = Callback.register "parsePagespec" parsePagespec
let _ = Callback.register "stringOfPagespec" stringOfPagespec
let _ = Callback.register "validatePagespec" validatePagespec

(* Read a file, no attempt at decryption, unless it's the blank user password. *)
let fromFile filename userpw =
  try
    new_pdf (Pdfread.pdf_of_file (Some userpw) None filename)
  with
    e -> handle_error "fromFile" e; err_int

let fromMemory rawbytes userpw =
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
  try
    let fh = open_in_bin filename in
      try
        new_pdf ~channel:fh (Pdfread.pdf_of_channel_lazy (Some userpw) None fh)
      with
        _ -> close_in fh; raise Exit
  with
    e -> handle_error "fromFileLazy" e; err_int

let fromMemoryLazy rawbytes userpw =
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
  try
    let pdf = lookup_pdf pdf in
      Pdf.remove_unreferenced pdf;
      Pdfwrite.pdf_to_file_options None make_id pdf filename
  with
    e -> handle_error "toFile" e; err_unit

let toFileExt
  pdf filename linearize make_id preserve_objstm generate_objstm compress_objstm
=
  try
    let pdf = lookup_pdf pdf in
      Pdf.remove_unreferenced pdf;
      Pdfwrite.pdf_to_file_options
        ~preserve_objstm ~generate_objstm ~compress_objstm
        None make_id pdf filename
  with
    e -> handle_error "toFileExt" e; err_unit

(* Write to memory. *)
let toFileMemory pdf linearize make_id =
  try
    let pdf = lookup_pdf pdf in
      Pdf.remove_unreferenced pdf;
      let o, bytes = Pdfio.input_output_of_bytes (100 * 1024) in
        Pdfwrite.pdf_to_output None make_id pdf o;
        Pdfio.raw_of_bytes
          (Pdfio.extract_bytes_from_input_output o bytes)
  with
    e -> handle_error "toFileMemory" e; err_data

let toFileMemoryExt
  pdf linearize make_id preserve_objstm generate_objstm compress_objstm
=
  try
    let pdf = lookup_pdf pdf in
      Pdf.remove_unreferenced pdf;
      let o, bytes = Pdfio.input_output_of_bytes (100 * 1024) in
        Pdfwrite.pdf_to_output
          ~preserve_objstm ~generate_objstm ~compress_objstm
          None make_id pdf o;
        Pdfio.raw_of_bytes
          (Pdfio.extract_bytes_from_input_output o bytes)
  with
    e -> handle_error "toFileMemoryExt" e; err_data

(* Number of pages in a PDF *)
let pages i =
  try Pdfpage.endpage (lookup_pdf i) with
    e -> handle_error "pages" e; err_int

(* Get the number of pages in file. Doesn't need decryption. *)
let endpage_io ?revision i user_pw owner_pw =
  let pdf = Pdfread.pdf_of_input_lazy ?revision user_pw owner_pw i in
    Pdfpage.endpage pdf

let pagesFast password filename =
  try
    let channel = open_in_bin filename in
      try
        let r = endpage_io (Pdfio.input_of_channel channel) (Some password) None in
          close_in channel;
          r
      with
        _ -> close_in channel; raise Exit
  with
    e -> handle_error "pagesfast" e; err_int

let pagesFastMemory password rawbytes =
  try
    let i = Pdfio.input_of_bytes (Pdfio.bytes_of_raw rawbytes) in
    let r = endpage_io i (Some password) None in
      r
  with
    e -> handle_error "pagesfast" e; err_int

(* The full range with all pages. *)
let all pdf =
  Array.of_list (ilist 1 (pages pdf))

let all i =
  try new_range (all i) with
    e -> handle_error "all" e; err_int

let isEncrypted i =
  try Pdfcrypt.is_encrypted (lookup_pdf i) with
    e -> handle_error "isEncrypted" e; err_bool

let hasPermission pdf tocheck =
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
  try
    flatten_encryptionKind (Pdfread.what_encryption (lookup_pdf pdf))
  with
    e -> handle_error "encryptionKind" e; err_int

let _ = Callback.register "hasPermission" hasPermission
let _ = Callback.register "encryptionKind" encryptionKind

(* If marked as encrypted, and we successfully decrypt, mark as
WasDecryptedWithUser, otherwise leave as is. *)
let decryptPdf i p =
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
  try
    let encryption =
      {Pdfwrite.encryption_method = encryption_method;
       Pdfwrite.permissions = Array.to_list permissions;
       Pdfwrite.owner_password = owner_password;
       Pdfwrite.user_password = user_password}
    in
      Pdfwrite.pdf_to_file_options (Some encryption) makeid pdf filename
  with
    e -> handle_error "toFileEncryptedInner" e; err_unit

let toFileMemoryEncrypted_inner
  ?(preserve_objstm = true) ?(generate_objstm = false)
  ?(compress_objstm = true)
  pdf encryption_method permissions owner_password user_password linearize makeid o
=
  try
    let encryption =
      {Pdfwrite.encryption_method = encryption_method;
       Pdfwrite.permissions = Array.to_list permissions;
       Pdfwrite.owner_password = owner_password;
       Pdfwrite.user_password = user_password}
    in
      Pdfwrite.pdf_to_output (Some encryption) makeid pdf o
  with
    e -> handle_error "toFileEncryptedInner" e; err_unit

let read_method = function
  | 0 -> Pdfwrite.PDF40bit
  | 1 -> Pdfwrite.PDF128bit
  | 2 -> Pdfwrite.AES128bit false
  | 3 -> Pdfwrite.AES128bit true
  | 4 -> Pdfwrite.AES256bit false
  | 5 -> Pdfwrite.AES256bit true
  | 6 -> Pdfwrite.AES256bitISO false
  | 7 -> Pdfwrite.AES256bitISO true
  | _ -> failwith "bad encryption method"

let read_perms perms =
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

let toFileEncrypted i mthd perms user owner linearize makeid filename =
  try
    Pdf.remove_unreferenced (lookup_pdf i);
    toFileEncrypted_inner
      (lookup_pdf i) (read_method mthd) (read_perms perms) user owner linearize makeid filename
  with
    e -> handle_error "toFileEncrypted" e; err_unit

let toFileMemoryEncrypted i mthd perms user owner linearize makeid =
  try
    let pdf = lookup_pdf i in
      Pdf.remove_unreferenced pdf;
      let o, bytes = Pdfio.input_output_of_bytes (100 * 1024) in
        toFileMemoryEncrypted_inner
          (lookup_pdf i) (read_method mthd) (read_perms perms) user owner linearize makeid o;
        Pdfio.raw_of_bytes
          (Pdfio.extract_bytes_from_input_output o bytes)
  with
    e -> handle_error "toFileMemory" e; err_data

let toFileEncryptedExt
  i mthd perms user owner linearize makeid
  preserve_objstm generate_objstm compress_objstm filename
=
  try
    Pdf.remove_unreferenced (lookup_pdf i);
    toFileEncrypted_inner
      ~preserve_objstm ~generate_objstm ~compress_objstm
      (lookup_pdf i) (read_method mthd) (read_perms perms) user owner linearize makeid filename
  with
    e -> handle_error "toFileEncryptedExt" e; err_unit

let toFileMemoryEncryptedExt
  i mthd perms user owner linearize makeid 
  preserve_objstm generate_objstm compress_objstm
=
  try
    let pdf = lookup_pdf i in
      Pdf.remove_unreferenced pdf;
      let o, bytes = Pdfio.input_output_of_bytes (100 * 1024) in
        toFileMemoryEncrypted_inner
          ~preserve_objstm ~generate_objstm ~compress_objstm
          (lookup_pdf i) (read_method mthd) (read_perms perms) user owner linearize makeid o;
        Pdfio.raw_of_bytes
          (Pdfio.extract_bytes_from_input_output o bytes)
  with
    e -> handle_error "toFileMemory" e; err_data

let _ = Callback.register "fromFile" fromFile
let _ = Callback.register "fromFileLazy" fromFileLazy
let _ = Callback.register "fromMemory" fromMemory
let _ = Callback.register "fromMemoryLazy" fromMemoryLazy
let _ = Callback.register "decryptPdf" decryptPdf
let _ = Callback.register "decryptPdfOwner" decryptPdfOwner
let _ = Callback.register "toFile" toFile
let _ = Callback.register "toFileExt" toFileExt
let _ = Callback.register "toFileMemory" toFileMemory
let _ = Callback.register "toFileMemoryExt" toFileMemoryExt
let _ = Callback.register "toFileMemoryEncrypted" toFileMemoryEncrypted
let _ = Callback.register "toFileMemoryEncryptedExt" toFileMemoryEncryptedExt
let _ = Callback.register "pages" pages
let _ = Callback.register "pagesFast" pagesFast
let _ = Callback.register "pagesFastMemory" pagesFastMemory
let _ = Callback.register "all" all
let _ = Callback.register "isEncrypted" isEncrypted
let _ = Callback.register "toFileEncrypted" toFileEncrypted
let _ = Callback.register "toFileEncryptedExt" toFileEncryptedExt

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
  try
    new_pdf (Pdfpage.pdf_of_pages ~retain_numbering:true (lookup_pdf pdf) (Array.to_list (lookup_range range)))
  with
    e -> handle_error "selectPages" e; err_int

let _ = Callback.register "mergeSimple" mergeSimple
let _ = Callback.register "merge" merge
let _ = Callback.register "mergeSame" mergeSame
let _ = Callback.register "selectPages" selectPages

(* CHAPTER 3. Pages *)
let read_position f1 f2 = function
  | 0 -> Cpdfposition.PosCentre (f1, f2)
  | 1 -> Cpdfposition.PosLeft (f1, f2)
  | 2 -> Cpdfposition.PosRight (f1, f2)
  | 3 -> Cpdfposition.Top f1
  | 4 -> Cpdfposition.TopLeft (f1, f1)
  | 5 -> Cpdfposition.TopRight (f1, f1)
  | 6 -> Cpdfposition.Left f1
  | 7 -> Cpdfposition.BottomLeft (f1, f1)
  | 8 -> Cpdfposition.Bottom f1
  | 9 -> Cpdfposition.BottomRight (f1, f1)
  | 10 -> Cpdfposition.Right f1
  | 11 -> Cpdfposition.Diagonal
  | 12 -> Cpdfposition.ReverseDiagonal
  | n -> failwith ("read_position" ^ string_of_int n)

let bl0_1, bl0_2, bl0_3 = 0., 0., 7

(* For turning functions which return a new PDF into ones which update the given
pdf. The PDF which is newly created should be thrown away. *)
let update_pdf (copyfrom : Pdf.t) (copyto : Pdf.t) =
  copyto.Pdf.major <- copyfrom.Pdf.major;
  copyto.Pdf.minor <- copyfrom.Pdf.minor;
  copyto.Pdf.root <- copyfrom.Pdf.root;
  copyto.Pdf.objects <- copyfrom.Pdf.objects;
  copyto.Pdf.trailerdict <- copyfrom.Pdf.trailerdict

let scalePages i range sx sy =
  try
    let sxsylist = many (sx, sy) (pages i) in
      update_pdf (Cpdfpage.scale_pdf ~fast:!fast sxsylist (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "scalePages" e; err_unit

let scaleToFit i range w h scale =
  try
    let whlist = many (w, h) (pages i) in
      update_pdf (Cpdfpage.scale_to_fit_pdf ~fast:!fast (Cpdfposition.BottomLeft (0., 0.)) scale whlist () (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "scaleToFit" e; err_unit

let points_of_papersize p =
  let u = Pdfpaper.unit p in
  let w = Pdfunits.points (Pdfpaper.width p) u in
  let h = Pdfunits.points (Pdfpaper.height p) u in
    w, h

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

let scaleToFitPaper i range papersize scale =
  try
    let w, h = points_of_papersize (papersize_of_int papersize) in
    let whlist = many (w, h) (pages i) in
      update_pdf (Cpdfpage.scale_to_fit_pdf (Cpdfposition.BottomLeft (0., 0.)) scale whlist () (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "scaleToFitPaper" e; err_unit

let shiftContents i range dx dy =
  try
    let dxdylist = many (dx, dy) (pages i) in
    update_pdf (Cpdfpage.shift_pdf ~fast:!fast dxdylist (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "shiftContents" e; err_unit

let shiftBoxes i range dx dy =
  try
    let dxdylist = many (dx, dy) (pages i) in
    update_pdf (Cpdfpage.shift_boxes dxdylist (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "shiftBoxes" e; err_unit

let scaleContents pdf range pos f1 f2 factor =
  try
    update_pdf (Cpdfpage.scale_contents ~fast:!fast (read_position f1 f2 pos) factor (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "scaleContents" e; err_unit

let rotate i range angle =
  try
    update_pdf (Cpdfpage.rotate_pdf angle (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "rotate" e; err_unit

let rotateBy i range angle =
  try
    update_pdf (Cpdfpage.rotate_pdf_by angle (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "rotateBy" e; err_unit

let rotateContents i range angle =
  try
    update_pdf (Cpdfpage.rotate_contents ~fast:!fast angle (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "rotateContents" e; err_unit

let upright i range =
  try
    update_pdf (Cpdfpage.upright ~fast:!fast (Array.to_list (lookup_range range)) (lookup_pdf i)) (lookup_pdf i)
  with
    e -> handle_error "upright" e; err_unit

let hFlip i range =
  try
    update_pdf (Cpdfpage.hflip_pdf ~fast:!fast (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "hFlip" e; err_unit

let vFlip i range =
  try
    update_pdf (Cpdfpage.vflip_pdf ~fast:!fast (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "vFlip" e; err_unit

let crop i range x y w h =
  try
    let xywhlist = many (x, y, w, h) (pages i) in
    update_pdf (Cpdfpage.crop_pdf xywhlist (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "crop" e; err_unit

let removeCrop i range =
  try
    update_pdf (Cpdfpage.remove_cropping_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "removeCrop" e; err_unit

let removeTrim i range =
  try
    update_pdf (Cpdfpage.remove_trim_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "removeTrim" e; err_unit

let removeArt i range =
  try
    update_pdf (Cpdfpage.remove_art_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "removeArt" e; err_unit

let removeBleed i range =
  try
    update_pdf (Cpdfpage.remove_bleed_pdf (lookup_pdf i) (Array.to_list (lookup_range range))) (lookup_pdf i)
  with
    e -> handle_error "removeBleed" e; err_unit

let setMediabox i range minx maxx miny maxy =
  try
    let lst = many (minx, miny, maxx -. minx, maxy -. miny) (pages i) in
    update_pdf
      (Cpdfpage.set_mediabox lst (lookup_pdf i) (Array.to_list (lookup_range range))) 
      (lookup_pdf i)
  with
    e -> handle_error "setMediaBox" e; err_unit

let trimMarks i range =
  try
    update_pdf
      (Cpdfpage.trim_marks (lookup_pdf i) (Array.to_list (lookup_range range)))
      (lookup_pdf i)
  with
    e -> handle_error "trimMarks" e; err_unit

let showBoxes i range =
  try
    update_pdf
      (Cpdfpage.show_boxes (lookup_pdf i) (Array.to_list (lookup_range range)))
      (lookup_pdf i)
  with
    e -> handle_error "showBoxes" e; err_unit

let hardBox i range box =
  try
    update_pdf
      (Cpdfpage.hard_box (lookup_pdf i) (Array.to_list (lookup_range range)) box false !fast)
      (lookup_pdf i)
  with
    e -> handle_error "hardBox" e; err_unit

let _ = Callback.register "scalePages" scalePages
let _ = Callback.register "scaleToFit" scaleToFit
let _ = Callback.register "scaleToFitPaper" scaleToFitPaper
let _ = Callback.register "shiftContents" shiftContents
let _ = Callback.register "shiftBoxes" shiftBoxes
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
let _ = Callback.register "trimMarks" trimMarks
let _ = Callback.register "showBoxes" showBoxes
let _ = Callback.register "hardBox" hardBox

(* CHAPTER 5. Compression *)
let compress pdf =
  try update_pdf (Cpdfsqueeze.recompress_pdf (lookup_pdf pdf)) (lookup_pdf pdf) with
    e -> handle_error "compress" e; err_unit

let decompress pdf =
  try update_pdf (Cpdfsqueeze.decompress_pdf (lookup_pdf pdf)) (lookup_pdf pdf) with
    e -> handle_error "decompress" e; err_unit

let _ = Callback.register "compress" compress
let _ = Callback.register "decompress" decompress

(* CHAPTER 6. Bookmarks *)
let bookmarkinfo = ref [||]

let startGetBookmarkInfo pdf =
  try
    bookmarkinfo := Array.of_list (Pdfmarks.read_bookmarks (lookup_pdf pdf))
  with
    e -> handle_error "startGetBookmarkInfo" e; err_unit

let endGetBookmarkInfo () =
  try
    bookmarkinfo := [||]
  with
    e -> handle_error "endGetBookmarkInfo" e; err_unit

let numberBookmarks () =
  try Array.length !bookmarkinfo with 
    e -> handle_error "numberBookmarks" e; err_int 

let getBookmarkPage pdf serial =
  try
    let page =
      Pdfpage.pagenumber_of_target (lookup_pdf pdf) !bookmarkinfo.(serial).Pdfmarks.target
    in
      page
  with
    e -> handle_error "getBookmarkPage" e; err_int

let getBookmarkLevel serial =
  try !bookmarkinfo.(serial).Pdfmarks.level with
    e -> handle_error "getBookmarkLevel" e; err_int

let getBookmarkText serial =
  try Pdftext.utf8_of_pdfdocstring !bookmarkinfo.(serial).Pdfmarks.text with
    e -> handle_error "getBookmarkText" e; err_string

let getBookmarkOpenStatus serial =
  try !bookmarkinfo.(serial).Pdfmarks.isopen with
    e -> handle_error "getBookmarkOpenStatus" e; err_bool

type mut_pdfmarks =
  {mutable mut_level : int;
   mutable mut_text : string;
   mutable mut_target : Pdfdest.t;
   mutable mut_isopen : bool}
                    
let setbookmarkinfo = ref [||]

let debug_setbookmarkinfo () =
  Printf.printf "debug_setbookmarkinfo: %i %s %s %b\n"
  !setbookmarkinfo.(0).mut_level
  !setbookmarkinfo.(0).mut_text
  (Pdfwrite.string_of_pdf (Pdfdest.pdfobject_of_destination !setbookmarkinfo.(0).mut_target))
  !setbookmarkinfo.(0).mut_isopen

let startSetBookmarkInfo num_bookmarks =
  setbookmarkinfo :=
    Array.init
      num_bookmarks
      (fun _ -> {mut_level = 0;
                 mut_text = "";
                 mut_target = Pdfdest.NullDestination;
                 mut_isopen = false})

let setBookmarkPage pdf serial pagenum =
  try
    !setbookmarkinfo.(serial).mut_target <-
      Pdfpage.target_of_pagenumber (lookup_pdf pdf) pagenum 
  with
    e -> handle_error "setBookmarkPage" e; err_unit

let setBookmarkLevel serial level =
  try
    !setbookmarkinfo.(serial).mut_level <- level
  with
    e -> handle_error "setBookmarkLevel" e; err_unit

let setBookmarkOpenStatus serial isopen =
  try
    !setbookmarkinfo.(serial).mut_isopen <- isopen
  with
    e -> handle_error "setBookmarkOpenStatus" e; err_unit

(* copied from cpdf.ml *)
let rec fixup_characters prev = function
  | [] -> rev prev
  | '\\'::'\\'::t -> fixup_characters ('\\'::prev) t
  | '\\'::'"'::t -> fixup_characters ('"'::prev) t
  | '\\'::'n'::t -> fixup_characters ('\n'::prev) t
  | h::t -> fixup_characters (h::prev) t

let setBookmarkText serial str =
  try
    !setbookmarkinfo.(serial).mut_text <-
      Pdftext.pdfdocstring_of_utf8 (implode (fixup_characters [] (explode str)))
  with
    e -> handle_error "setBookmarkText" e; err_unit

let endSetBookmarkInfo pdf =
  let convert {mut_level; mut_text; mut_target; mut_isopen} =
    {Pdfmarks.level = mut_level;
     Pdfmarks.text = mut_text;
     Pdfmarks.target = mut_target;
     Pdfmarks.isopen = mut_isopen}
  in
    try
      update_pdf (Pdfmarks.add_bookmarks (map convert (Array.to_list !setbookmarkinfo)) (lookup_pdf pdf)) (lookup_pdf pdf);
      setbookmarkinfo := [||]
    with
      e -> handle_error "endSetBookmarkInfo" e; err_unit

let getBookmarksJSON pdf =
  try
    Pdfio.raw_of_bytes (Cpdfbookmarks.get_bookmarks_json (lookup_pdf pdf))
  with
    e -> handle_error "getBookmarksJSON" e; err_data

let setBookmarksJSON pdf data =
  try
    let i = Pdfio.input_of_bytes (Pdfio.bytes_of_raw data) in
      update_pdf (Cpdfbookmarks.add_bookmarks ~json:true false i (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setBookmarksJSON" e; err_unit

let tableOfContents pdf font fontsize title bookmark =
  try
    let font = Cpdfembed.PreMadeFontPack (Cpdfembed.fontpack_of_standardfont (Pdftext.StandardFont (font, Pdftext.WinAnsiEncoding))) in
      update_pdf
        (Cpdftoc.typeset_table_of_contents ~font ~fontsize ~title ~bookmark (lookup_pdf pdf))
        (lookup_pdf pdf)
  with
    e -> handle_error "tableOfContents" e; err_unit

let _ = Callback.register "startGetBookmarkInfo" startGetBookmarkInfo
let _ = Callback.register "endGetBookmarkInfo" endGetBookmarkInfo
let _ = Callback.register "numberBookmarks" numberBookmarks
let _ = Callback.register "getBookmarkPage" getBookmarkPage
let _ = Callback.register "getBookmarkLevel" getBookmarkLevel
let _ = Callback.register "getBookmarkText" getBookmarkText
let _ = Callback.register "getBookmarkOpenStatus" getBookmarkOpenStatus
let _ = Callback.register "startSetBookmarkInfo" startSetBookmarkInfo
let _ = Callback.register "endSetBookmarkInfo" endSetBookmarkInfo
let _ = Callback.register "setBookmarkPage" setBookmarkPage
let _ = Callback.register "setBookmarkLevel" setBookmarkLevel
let _ = Callback.register "setBookmarkText" setBookmarkText
let _ = Callback.register "setBookmarkOpenStatus" setBookmarkOpenStatus
let _ = Callback.register "getBookmarksJSON" getBookmarksJSON
let _ = Callback.register "setBookmarksJSON" setBookmarksJSON
let _ = Callback.register "tableOfContents" tableOfContents

(* CHAPTER 8. Logos, Watermarks and Stamps *)
let stampExtended pdf pdf2 range isover scale_stamp_to_fit pos1 pos2 pos3 relative_to_cropbox =
  try
    update_pdf
      (Cpdfpage.stamp
         relative_to_cropbox
         (read_position pos1 pos2 pos3)
         false
         false
         !fast
         scale_stamp_to_fit
         isover
         (Array.to_list (lookup_range range))
         (lookup_pdf pdf)
         (lookup_pdf pdf2))
      (lookup_pdf pdf2)
  with
    e -> handle_error "stampExtended" e; err_unit

let stampOn pdf pdf2 range =
  stampExtended pdf pdf2 range true false bl0_1 bl0_2 bl0_3 false

let stampUnder pdf pdf2 range =
  stampExtended pdf pdf2 range false false bl0_1 bl0_2 bl0_3 false

let combinePages pdf pdf2 =
  try
    new_pdf (Cpdfpage.combine_pages !fast (lookup_pdf pdf2) (lookup_pdf pdf) false false true)
  with
    e -> handle_error "combinePages" e; err_int

let removeText pdf range =
  try
    update_pdf (Cpdfremovetext.removetext (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
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

let addText_inner
  metrics pdf range text position linespacing bates font fontsize color underneath cropbox outline opacity justification midline topline filename linewidth embed_fonts
=
  let fontname = Pdftext.string_of_standard_font font in
    let newpdf =
      (Cpdfaddtext.addtexts
         linewidth (* linewidth *)
         outline (* outline *)
         !fast (* fast *)
         fontname (* font name *)
         (Cpdfembed.PreMadeFontPack (Cpdfembed.fontpack_of_standardfont (Pdftext.StandardFont (font, Pdftext.WinAnsiEncoding)))) (* font *)
         bates (* bates number *)
         None (* pad bates *)
         (Cpdfaddtext.RGB (color.r, color.g, color.b)) (* colour *)
         position (* position *)
         linespacing (* line spacing *)
         fontsize (* font size *)
         underneath (* underneath *)
         text (* text *)
         (Array.to_list range) (* page range *)
         cropbox (* relative to cropbox *)
         opacity (* opacity *)
         justification (* justification *)
         midline (* relative to midline *)
         topline (* relative to topline *)
         filename (* file name *)
         None (* extract text font size *)
         ~raw:false
         "0 0" (* shift *)
         pdf (* pdf *))
    in
      if not metrics then
        begin
          pdf.Pdf.root <- newpdf.Pdf.root;
          pdf.Pdf.objects <- newpdf.Pdf.objects;
          pdf.Pdf.trailerdict <- newpdf.Pdf.trailerdict
        end

let addText
  metrics pdf range text pos f1 f2 linespace bates font size r g b
  underneath cropbox outline opacity justification midline topline filename linewidth embed_fonts
=
  try
    addText_inner metrics (lookup_pdf pdf) (lookup_range range) text (read_position f1 f2 pos)
    linespace bates font size (rgb r g b) underneath cropbox outline opacity justification midline topline filename linewidth embed_fonts
  with
    e -> handle_error "addText" e; err_unit

let textWidth font text =
  try
    Pdfstandard14.textwidth false Pdftext.StandardEncoding font text
  with
    e -> handle_error "textWidth" e; err_int

let _ = Callback.register "stampOn" stampOn
let _ = Callback.register "stampUnder" stampUnder
let _ = Callback.register "stampExtended" stampExtended
let _ = Callback.register "combinePages" combinePages
let _ = Callback.register "removeText" removeText
let _ = Callback.register "addText" addText
let _ = Callback.register "textWidth" textWidth

let addContent s before pdf range =
  try
    update_pdf (Cpdftweak.append_page_content s before !fast (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "addContent" e; err_unit

let _ = Callback.register "addContent" addContent

let stampAsXObject pdf range stamp_pdf =
  try
     let pdf', name = Cpdfxobject.stamp_as_xobject (lookup_pdf pdf) (Array.to_list (lookup_range range)) (lookup_pdf stamp_pdf) in
     update_pdf pdf' (lookup_pdf pdf);
     name
  with
    e -> handle_error "stampAsXObject" e; err_string

let _ = Callback.register "stampAsXObject" stampAsXObject

(* CHAPTER 9. Multipage facilities *)
let impose pdf x y fit columns rtl btt center margin spacing linewidth =
  try
    update_pdf (Cpdfimpose.impose ~x ~y ~fit ~columns ~rtl ~btt ~center ~margin ~spacing ~linewidth ~fast:!fast (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "impose" e; err_unit

let twoUp pdf =
  try
    update_pdf (Cpdfimpose.twoup !fast (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "twoUp" e; err_unit

let twoUpStack pdf =
  try
    update_pdf (Cpdfimpose.twoup_stack !fast (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "twoUpStack" e; err_unit

let padBefore pdf range =
  try
    update_pdf (Cpdfpad.padbefore (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "padBefore" e; err_unit
 
let padAfter pdf range =
  try
    update_pdf (Cpdfpad.padafter (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "padAfter" e; err_unit

let padEvery pdf n =
  try
    let pdf = lookup_pdf pdf in
    let range =
      match keep (function m -> m mod n = 0) (ilist 1 (Pdfpage.endpage pdf)) with
      | [] -> []
      | l -> if last l = Pdfpage.endpage pdf then all_but_last l else l
    in
      update_pdf (Cpdfpad.padafter range pdf) pdf
  with
    e -> handle_error "padEvery" e; err_unit

let padMultiple pdf n =
  try
    update_pdf (Cpdfpad.padmultiple n (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "padMultiple" e; err_unit

let padMultipleBefore pdf n =
  try
    update_pdf (Cpdfpad.padmultiple (-n) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "padMultipleBefore" e; err_unit

let _ = Callback.register "twoUp" twoUp
let _ = Callback.register "twoUpStack" twoUpStack
let _ = Callback.register "impose" impose
let _ = Callback.register "padBefore" padBefore
let _ = Callback.register "padAfter" padAfter
let _ = Callback.register "padEvery" padEvery
let _ = Callback.register "padMultiple" padMultiple
let _ = Callback.register "padMultipleBefore" padMultipleBefore

(* CHAPTER 10. Annotations *)
let annotationsJSON pdf =
  try
    Pdfio.raw_of_bytes (Cpdfannot.get_annotations_json (lookup_pdf pdf) (Array.to_list (lookup_range (all pdf))))
  with
    e -> handle_error "annotationsJSON" e; err_data

let removeAnnotations pdf range =
  try
    update_pdf (Cpdfannot.remove_annotations (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "removeAnnotations" e; err_unit

let setAnnotationsJSON pdf data =
  try
    let i = Pdfio.input_of_bytes (Pdfio.bytes_of_raw data) in
      Cpdfannot.set_annotations_json (lookup_pdf pdf) i
  with
    e -> handle_error "setAnnotationsJSON" e; err_unit

let _ = Callback.register "annotationsJSON" annotationsJSON
let _ = Callback.register "removeAnnotations" removeAnnotations
let _ = Callback.register "setAnnotationsJSON" setAnnotationsJSON

(* CHAPTER 11. Document Information and Metadata *)

let isLinearized string =
  try
    let ch = open_in_bin string in
      try
        Pdfread.is_linearized (Pdfio.input_of_channel ch)
      with
        _ -> close_in ch; raise Exit
  with
    e -> handle_error "isLinearized" e; err_bool

let isLinearizedMemory rawbytes =
  try
    Pdfread.is_linearized (Pdfio.input_of_bytes (Pdfio.bytes_of_raw rawbytes))
  with
    e -> handle_error "isLinearizedMemory" e; err_bool

let _ = Callback.register "isLinearized" isLinearized
let _ = Callback.register "isLinearizedMemory" isLinearizedMemory

let fontinfo = ref [||]

(* Actually get the font info and store in an array. *)
let startGetFontInfo pdf =
  try
    fontinfo := Array.of_list (Cpdffont.list_fonts (lookup_pdf pdf) (ilist 1 (Pdfpage.endpage (lookup_pdf pdf))))
  with
    e -> handle_error "startGetFontInfo" e; err_unit

(* Throw the information away. *)
let endGetFontInfo () =
  try fontinfo := [||] with e -> handle_error "endGetFontInfo" e; err_unit

let numberFonts () =
  try Array.length !fontinfo with e -> handle_error "numberFonts" e; err_int

let getFontPage serial =
  try let x, _, _, _, _ = !fontinfo.(serial) in x with e -> handle_error "getFontPage" e; err_int

let getFontName serial =
  try let _, _, _, x, _ = !fontinfo.(serial) in x with e -> handle_error "getFontName" e; err_string

let getFontType serial =
  try let _, _, x, _, _ = !fontinfo.(serial) in x with e -> handle_error "getFontType" e; err_string

let getFontEncoding serial =
  try let _, _, _, _, x = !fontinfo.(serial) in x with e -> handle_error "getFontEncoding" e; err_string

let fontsJSON pdf =
  try
    Pdfio.raw_of_bytes (Pdfio.bytes_of_string (Cpdfyojson.Safe.pretty_to_string (Cpdffont.json_fonts (lookup_pdf pdf) (ilist 1 (Pdfpage.endpage (lookup_pdf pdf))))))
  with
    e -> handle_error "fontsJSON" e; err_data

let _ = Callback.register "numberFonts" numberFonts
let _ = Callback.register "getFontPage" getFontPage
let _ = Callback.register "getFontName" getFontName
let _ = Callback.register "getFontType" getFontType
let _ = Callback.register "getFontEncoding" getFontEncoding
let _ = Callback.register "startGetFontInfo" startGetFontInfo
let _ = Callback.register "endGetFontInfo" endGetFontInfo
let _ = Callback.register "fontsJSON" fontsJSON

let removeFonts pdf = ()
let copyFont pdf_from pdf_to range page name = ()

let _ = Callback.register "removeFonts" removeFonts
let _ = Callback.register "copyFont" copyFont

let getVersion pdf =
  try (lookup_pdf pdf).Pdf.minor with e -> handle_error "getVersion" e; err_int

let getMajorVersion pdf =
  try (lookup_pdf pdf).Pdf.major with e -> handle_error "getMajorVersion" e; err_int

let getTitle pdf =
  try
    Cpdfmetadata.get_info_utf8 (lookup_pdf pdf) "/Title"
  with
    e -> handle_error "getTitle" e; err_string

let getAuthor pdf =
  try
    Cpdfmetadata.get_info_utf8 (lookup_pdf pdf) "/Author"
  with
    e -> handle_error "getAuthor" e; err_string

let getSubject pdf =
  try
    Cpdfmetadata.get_info_utf8 (lookup_pdf pdf) "/Subject"
  with
    e -> handle_error "getSubject" e; err_string

let getKeywords pdf =
  try
    Cpdfmetadata.get_info_utf8 (lookup_pdf pdf) "/Keywords"
  with
    e -> handle_error "getKeywords" e; err_string

let getCreator pdf =
  try
    Cpdfmetadata.get_info_utf8 (lookup_pdf pdf) "/Creator"
  with
    e -> handle_error "getCreator" e; err_string

let getProducer pdf =
  try
    Cpdfmetadata.get_info_utf8 (lookup_pdf pdf) "/Producer"
  with
    e -> handle_error "getProducer" e; err_string

let getCreationDate pdf =
  try
    Cpdfmetadata.get_info_utf8 (lookup_pdf pdf) "/CreationDate"
  with
    e -> handle_error "getCreationDate" e; err_string

let getModificationDate pdf =
  try
    Cpdfmetadata.get_info_utf8 (lookup_pdf pdf) "/ModDate"
  with
    e -> handle_error "getModificationDate" e; err_string

let getTitleXMP pdf =
  try
    Cpdfmetadata.get_info_utf8 (lookup_pdf pdf) "/Title"
  with
    e -> handle_error "getTitleXMP" e; err_string

let getAuthorXMP pdf =
  try
    Cpdfmetadata.get_xmp_info (lookup_pdf pdf) "/Author"
  with
    e -> handle_error "getAuthorXMP" e; err_string

let getSubjectXMP pdf =
  try
    Cpdfmetadata.get_xmp_info (lookup_pdf pdf) "/Subject"
  with
    e -> handle_error "getSubjectXMP" e; err_string

let getKeywordsXMP pdf =
  try
    Cpdfmetadata.get_xmp_info (lookup_pdf pdf) "/Keywords"
  with
    e -> handle_error "getKeywordsXMP" e; err_string

let getCreatorXMP pdf =
  try
    Cpdfmetadata.get_xmp_info (lookup_pdf pdf) "/Creator"
  with
    e -> handle_error "getCreatorXMP" e; err_string

let getProducerXMP pdf =
  try
    Cpdfmetadata.get_xmp_info (lookup_pdf pdf) "/Producer"
  with
    e -> handle_error "getProducerXMP" e; err_string

let getCreationDateXMP pdf =
  try
    Cpdfmetadata.get_xmp_info (lookup_pdf pdf) "/CreationDate"
  with
    e -> handle_error "getCreationDateXMP" e; err_string

let getModificationDateXMP pdf =
  try
    Cpdfmetadata.get_xmp_info (lookup_pdf pdf) "/ModDate"
  with
    e -> handle_error "getModificationDateXMP" e; err_string

let getDateComponents str =
  try Pdfdate.date_of_string str with
    e -> handle_error "getDateComponents" e; err_date

let dateStringOfComponents year month day hour minute second hour_offset minute_offset =
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
  try
    (lookup_pdf pdf).Pdf.minor <- version
  with
    e -> handle_error "setVersion" e; err_unit

let setFullVersion pdf major minor =
  try
    (lookup_pdf pdf).Pdf.major <- major;
    (lookup_pdf pdf).Pdf.minor <- minor
  with
    e -> handle_error "setFullVersion" e; err_unit

let setTitle pdf title =
  try
    let title = Pdftext.pdfdocstring_of_utf8 title in
      update_pdf (Cpdfmetadata.set_pdf_info ("/Title", Pdf.String title, 1) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setTitle" e; err_unit

let setAuthor pdf author =
  try
    let author = Pdftext.pdfdocstring_of_utf8 author in
      update_pdf (Cpdfmetadata.set_pdf_info ("/Author", Pdf.String author, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setAuthor" e; err_unit

let setSubject pdf subject =
  try
    let subject = Pdftext.pdfdocstring_of_utf8 subject in
      update_pdf (Cpdfmetadata.set_pdf_info ("/Subject", Pdf.String subject, 1) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setSubject" e; err_unit

let setKeywords pdf keywords =
  try
    let keywords = Pdftext.pdfdocstring_of_utf8 keywords in
      update_pdf (Cpdfmetadata.set_pdf_info ("/Keywords", Pdf.String keywords, 1) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setKeywords" e; err_unit

let setCreator pdf creator =
  try
    let creator = Pdftext.pdfdocstring_of_utf8 creator in
      update_pdf (Cpdfmetadata.set_pdf_info ("/Creator", Pdf.String creator, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "SetCreator" e; err_unit

let setProducer pdf producer =
  try      
    let producer = Pdftext.pdfdocstring_of_utf8 producer in
      update_pdf (Cpdfmetadata.set_pdf_info ("/Producer", Pdf.String producer, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setProducer" e; err_unit

let setCreationDate pdf date =
  try
    let date = Pdftext.pdfdocstring_of_utf8 date in
      update_pdf (Cpdfmetadata.set_pdf_info ("/CreationDate", Pdf.String (Cpdfmetadata.expand_date date), 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setCreationDate" e; err_unit

let setModificationDate pdf date =
  try
    let date = Pdftext.pdfdocstring_of_utf8 date in
      update_pdf (Cpdfmetadata.set_pdf_info ("/ModDate", Pdf.String (Cpdfmetadata.expand_date date), 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setModificationDate" e; err_unit

let markTrapped pdf =
  try
    update_pdf (Cpdfmetadata.set_pdf_info ("/Trapped", Pdf.Boolean true, 3) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "markTrapped" e; err_unit

let markUntrapped pdf =
  try
    update_pdf (Cpdfmetadata.set_pdf_info ("/Trapped", Pdf.Boolean false, 3) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "markUntrapped" e; err_unit

let setTitleXMP pdf title =
  try
    let title = Pdftext.pdfdocstring_of_utf8 title in
      update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/Title", Pdf.String title, 1) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setTitle" e; err_unit

let setAuthorXMP pdf author =
  try
    let author = Pdftext.pdfdocstring_of_utf8 author in
      update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/Author", Pdf.String author, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setAuthor" e; err_unit

let setSubjectXMP pdf subject =
  try
    let subject = Pdftext.pdfdocstring_of_utf8 subject in
      update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/Subject", Pdf.String subject, 1) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setSubject" e; err_unit

let setKeywordsXMP pdf keywords =
  try
    let keywords = Pdftext.pdfdocstring_of_utf8 keywords in
      update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/Keywords", Pdf.String keywords, 1) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setKeywords" e; err_unit

let setCreatorXMP pdf creator =
  try
    let creator = Pdftext.pdfdocstring_of_utf8 creator in
      update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/Creator", Pdf.String creator, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "SetCreator" e; err_unit

let setProducerXMP pdf producer =
  try      
    let producer = Pdftext.pdfdocstring_of_utf8 producer in
      update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/Producer", Pdf.String producer, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setProducer" e; err_unit

let setCreationDateXMP pdf date =
  try
    let date = Pdftext.pdfdocstring_of_utf8 date in
      update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/CreationDate", Pdf.String (Cpdfmetadata.expand_date date), 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setCreationDate" e; err_unit

let setModificationDateXMP pdf date =
  try
    let date = Pdftext.pdfdocstring_of_utf8 date in
      update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/ModDate", Pdf.String (Cpdfmetadata.expand_date date), 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setModificationDate" e; err_unit

let markTrappedXMP pdf =
  try
    update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/Trapped", Pdf.Boolean true, 3) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "markTrapped" e; err_unit

let markUntrappedXMP pdf =
  try
    update_pdf (Cpdfmetadata.set_pdf_info ~xmp_just_set:true ("/Trapped", Pdf.Boolean false, 3) (lookup_pdf pdf)) (lookup_pdf pdf)
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

let getPageLayout pdf =
  try
    match Cpdfmetadata.get_catalog_item "/PageLayout" (lookup_pdf pdf) with
    | "SinglePage" -> 0
    | "OneColumn" -> 1
    | "TwoColumnLeft" -> 2
    | "TwoColumnRight" -> 3
    | "TwoPageLeft" -> 4
    | "TwoPageRight" -> 5
    | _ -> 0
  with
    e -> handle_error "getPageLayout" e; err_int

let setPageLayout pdf layout =
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
      update_pdf (Cpdfmetadata.set_page_layout (lookup_pdf pdf) (string_of_layout layout)) (lookup_pdf pdf)
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

let getPageMode pdf =
  try
    match Cpdfmetadata.get_catalog_item "/PageMode" (lookup_pdf pdf) with
    | "UseNone" -> 0
    | "UseOutlines" -> 1
    | "UseThumbs" -> 2
    | "FullScreen" -> 3
    | "UseOC" -> 4
    | "UseAttachments" -> 5
    | _ -> 0
  with
    e -> handle_error "getPageMode" e; err_int

let setPageMode pdf mode =
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
      update_pdf (Cpdfmetadata.set_page_mode (lookup_pdf pdf) (string_of_mode mode)) (lookup_pdf pdf)
  with
    e -> handle_error "setPageMode" e; err_unit

let hideToolbar pdf b =
  try
    update_pdf (Cpdfmetadata.set_viewer_preference ("/HideToolbar", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "hideToolbar" e; err_unit

let getHideToolbar pdf =
  try
    match Cpdfmetadata.get_viewer_pref_item "/HideToolbar" (lookup_pdf pdf) with
    | "true" -> true
    | _ -> false
  with
    e -> handle_error "getHideToolbar" e; err_bool

let hideMenubar pdf b =
  try
    update_pdf (Cpdfmetadata.set_viewer_preference ("/HideMenubar", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "hideMenubar" e; err_unit

let getHideMenubar pdf =
  try
    match Cpdfmetadata.get_viewer_pref_item "/HideMenubar" (lookup_pdf pdf) with
    | "true" -> true
    | _ -> false
  with
    e -> handle_error "getHideMenubar" e; err_bool

let hideWindowUi pdf b =
  try
    update_pdf (Cpdfmetadata.set_viewer_preference ("/HideWindowUI", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "hideWindowUi" e; err_unit

let getHideWindowUi pdf =
  try
    match Cpdfmetadata.get_viewer_pref_item "/HideWindowUI" (lookup_pdf pdf) with
    | "true" -> true
    | _ -> false
  with
    e -> handle_error "getHideWindowUi" e; err_bool

let fitWindow pdf b =
  try
    update_pdf (Cpdfmetadata.set_viewer_preference ("/FitWindow", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "fitWindow" e; err_unit

let getFitWindow pdf =
  try
    match Cpdfmetadata.get_viewer_pref_item "/FitWindow" (lookup_pdf pdf) with
    | "true" -> true
    | _ -> false
  with
    e -> handle_error "getFitWindow" e; err_bool

let centerWindow pdf b =
  try
    update_pdf (Cpdfmetadata.set_viewer_preference ("/CenterWindow", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "centerWindow" e; err_unit

let getCenterWindow pdf =
  try
    match Cpdfmetadata.get_viewer_pref_item "/CenterWindow" (lookup_pdf pdf) with
    | "true" -> true
    | _ -> false
  with
    e -> handle_error "getCenterWindow" e; err_bool

let displayDocTitle pdf b =
  try
    update_pdf (Cpdfmetadata.set_viewer_preference ("/DisplayDocTitle", Pdf.Boolean b, 0) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "displayDocTitle" e; err_unit

let getDisplayDocTitle pdf =
  try
    match Cpdfmetadata.get_viewer_pref_item "/DisplayDocTitle" (lookup_pdf pdf) with
    | "true" -> true
    | _ -> false
  with
    e -> handle_error "getDisplayDocTitle" e; err_bool

let getNonFullScreenPageMode pdf =
  try
    match Cpdfmetadata.get_viewer_pref_item "/NonFullScreenPageMode" (lookup_pdf pdf) with
    | "UseNone" -> 0
    | "UseOutlines" -> 1
    | "UseThumbs" -> 2
    | "UseOC" -> 4
    | "UseAttachments" -> 5
    | _ -> 0
  with
    e -> handle_error "getNonFullScreenPageMode" e; err_int

let nonFullScreenPageMode pdf mode =
  try
    let mode =
      match mode with
      | 0 -> UseNone
      | 1 -> UseOutlines
      | 2 -> UseThumbs
      | 3 -> FullScreen
      | 4 -> UseOC
      | 5 -> UseAttachments
      | _ -> UseNone
    in
      update_pdf (Cpdfmetadata.set_non_full_screen_page_mode (lookup_pdf pdf) (string_of_mode mode)) (lookup_pdf pdf)
  with
    e -> handle_error "nonFullScreenPageMode" e; err_unit

let openAtPage pdf fit pagenum =
  try
    update_pdf (Cpdfmetadata.set_open_action (lookup_pdf pdf) fit pagenum) (lookup_pdf pdf)
  with
    e -> handle_error "openAtPage" e; err_unit

let openAtPageCustom pdf dest =
  try
    update_pdf (Cpdfmetadata.set_open_action ~dest (lookup_pdf pdf) false 1) (lookup_pdf pdf)
  with
    e -> handle_error "openAtPageCustom" e; err_unit

let setMetadataFromFile pdf filename =
  try
    update_pdf (Cpdfmetadata.set_metadata false filename (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setMetadataFromFile" e; err_unit

let setMetadataFromByteArray pdf bytes =
  try
    update_pdf (Cpdfmetadata.set_metadata_from_bytes false (Pdfio.copybytes (Pdfio.bytes_of_raw bytes)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "setMetadataFromByteArray" e; err_unit

let getMetadata pdf =
  try
    match Cpdfmetadata.get_metadata (lookup_pdf pdf) with
      None -> err_data
    | Some data -> Pdfio.raw_of_bytes data
  with
    e -> handle_error "getMetadata" e; err_data

let removeMetadata pdf =
  try
    update_pdf (Cpdfmetadata.remove_metadata (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "removeMetadata" e; err_unit

let createMetadata pdf =
  try
    update_pdf (Cpdfmetadata.create_metadata (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "createMetadata" e; err_unit

let setMetadataDate pdf date =
  try
    update_pdf (Cpdfmetadata.set_metadata_date (lookup_pdf pdf) date) (lookup_pdf pdf)
  with
    e -> handle_error "setMetadataDate" e; err_unit

let hasBox pdf pagenumber boxname =
  try Cpdfpage.hasbox (lookup_pdf pdf) pagenumber boxname with
    e -> handle_error "hasBox" e; err_bool

let getPageRotation pdf pagenumber =
  try 
    let pages = Pdfpage.pages_of_pagetree (lookup_pdf pdf) in
      Pdfpage.int_of_rotation (List.nth pages (pagenumber - 1)).Pdfpage.rotate
  with
    e -> handle_error "getPageRotation" e; err_int

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
               Pdf.getnum pdf a, Pdf.getnum pdf b, Pdf.getnum pdf c, Pdf.getnum pdf d
           | _ -> 0., 0., 0., 0.
         in
           let c_minx, c_miny, c_maxx, c_maxy =
             match Pdf.lookup_direct pdf "/CropBox" page.Pdfpage.rest with
             | Some (Pdf.Array [a; b; c; d]) ->
                 Pdf.getnum pdf a, Pdf.getnum pdf b, Pdf.getnum pdf c, Pdf.getnum pdf d
             | _ -> m_minx, m_miny, m_maxx, m_maxy
           in
             let getotherbox name =
               match Pdf.lookup_direct pdf name page.Pdfpage.rest with
                 | Some (Pdf.Array [a; b; c; d]) ->
                     Pdf.getnum pdf a, Pdf.getnum pdf b, Pdf.getnum pdf c, Pdf.getnum pdf d
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
  try 
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).pimediabox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getMediaBox" e; err_box

let getCropBox pdf pagenumber =
  try
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).cropbox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getCropBox" e; err_box

let getTrimBox pdf pagenumber =
  try
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).trimbox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getTrimBox" e; err_box

let getArtBox pdf pagenumber =
  try
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).artbox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getArtBox" e; err_box

let getBleedBox pdf pagenumber =
  try
    let box =
      (getPageInfo (lookup_pdf pdf)).(pagenumber - 1).bleedbox
    in
      box.minx, box.maxx, box.miny, box.maxy
  with
    e -> handle_error "getBleedBox" e; err_box

let setArtBox pdf range minx maxx miny maxy =
  try
    update_pdf (Cpdfpage.setBox "/ArtBox" minx maxx miny maxy (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "setArtBox" e; err_unit

let setBleedBox pdf range minx maxx miny maxy =
  try
    update_pdf (Cpdfpage.setBox "/BleedBox" minx maxx miny maxy (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "setBleedBox" e; err_unit

let setTrimBox pdf range minx maxx miny maxy =
  try
    update_pdf (Cpdfpage.setBox "/TrimBox" minx maxx miny maxy (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "setTrimBox" e; err_unit

let setCropBox pdf range minx maxx miny maxy =
  try
    update_pdf (Cpdfpage.setBox "/CropBox" minx maxx miny maxy (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "setCropBox" e; err_unit

(* FIXME not fonts *)
let pageInfoJSON pdf =
  try
    Pdfio.raw_of_bytes (Pdfio.bytes_of_string (Cpdfyojson.Safe.pretty_to_string (Cpdffont.json_fonts (lookup_pdf pdf) (ilist 1 (Pdfpage.endpage (lookup_pdf pdf))))))
  with
    e -> handle_error "pageInfoJSON" e; err_data

let compositionJSON filesize pdf =
  try
    Pdfio.raw_of_bytes (Cpdfcomposition.show_composition_json_blob filesize (lookup_pdf pdf))
  with
    e -> handle_error "compositionJSON" e; err_data

let _ = Callback.register "getVersion" getVersion
let _ = Callback.register "getMajorVersion" getMajorVersion
let _ = Callback.register "getTitle" getTitle
let _ = Callback.register "getAuthor" getAuthor
let _ = Callback.register "getSubject" getSubject
let _ = Callback.register "getKeywords" getKeywords
let _ = Callback.register "getCreator" getCreator
let _ = Callback.register "getProducer" getProducer
let _ = Callback.register "getCreationDate" getCreationDate
let _ = Callback.register "getModificationDate" getModificationDate
let _ = Callback.register "getTitleXMP" getTitleXMP
let _ = Callback.register "getAuthorXMP" getAuthorXMP
let _ = Callback.register "getSubjectXMP" getSubjectXMP
let _ = Callback.register "getKeywordsXMP" getKeywordsXMP
let _ = Callback.register "getCreatorXMP" getCreatorXMP
let _ = Callback.register "getProducerXMP" getProducerXMP
let _ = Callback.register "getCreationDateXMP" getCreationDateXMP
let _ = Callback.register "getModificationDateXMP" getModificationDateXMP
let _ = Callback.register "getDateComponents" getDateComponents
let _ = Callback.register "dateStringOfComponents" dateStringOfComponents
let _ = Callback.register "setVersion" setVersion
let _ = Callback.register "setFullVersion" setFullVersion
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
let _ = Callback.register "setTitleXMP" setTitleXMP
let _ = Callback.register "setAuthorXMP" setAuthorXMP
let _ = Callback.register "setSubjectXMP" setSubjectXMP
let _ = Callback.register "setKeywordsXMP" setKeywordsXMP
let _ = Callback.register "setCreatorXMP" setCreatorXMP
let _ = Callback.register "setProducerXMP" setProducerXMP
let _ = Callback.register "setCreationDateXMP" setCreationDateXMP
let _ = Callback.register "setModificationDateXMP" setModificationDateXMP
let _ = Callback.register "markTrappedXMP" markTrappedXMP
let _ = Callback.register "markUntrappedXMP" markUntrappedXMP
let _ = Callback.register "getPageMode" getPageMode
let _ = Callback.register "setPageMode" setPageMode
let _ = Callback.register "getPageLayout" getPageLayout
let _ = Callback.register "setPageLayout" setPageLayout
let _ = Callback.register "hasBox" hasBox
let _ = Callback.register "getPageRotation" getPageRotation
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
let _ = Callback.register "getHideToolbar" getHideToolbar
let _ = Callback.register "hideMenubar" hideMenubar
let _ = Callback.register "getHideMenubar" getHideMenubar
let _ = Callback.register "hideWindowUi" hideWindowUi
let _ = Callback.register "getHideWindowUi" getHideWindowUi
let _ = Callback.register "fitWindow" fitWindow
let _ = Callback.register "getFitWindow" getFitWindow
let _ = Callback.register "centerWindow" centerWindow
let _ = Callback.register "getCenterWindow" getCenterWindow
let _ = Callback.register "displayDocTitle" displayDocTitle
let _ = Callback.register "getDisplayDocTitle" getDisplayDocTitle
let _ = Callback.register "nonFullScreenPageMode" nonFullScreenPageMode
let _ = Callback.register "getNonFullScreenPageMode" getNonFullScreenPageMode
let _ = Callback.register "openAtPage" openAtPage
let _ = Callback.register "openAtPageCustom" openAtPageCustom
let _ = Callback.register "setMetadataFromFile" setMetadataFromFile
let _ = Callback.register "removeMetadata" removeMetadata
let _ = Callback.register "createMetadata" createMetadata
let _ = Callback.register "setMetadataDate" setMetadataDate
let _ = Callback.register "setMetadataFromByteArray" setMetadataFromByteArray
let _ = Callback.register "getMetadata" getMetadata
let _ = Callback.register "compositionJSON" compositionJSON

(* CHAPTER 12. File Attachments *)
let attachFile filename pdf =
  try
    update_pdf
      (Cpdfattach.attach_file false None (lookup_pdf pdf) filename)
      (lookup_pdf pdf);
  with
    e -> handle_error "attachFile" e; err_unit

let attachFileFromMemory rawbytes filename pdf =
  try
    update_pdf
      (Cpdfattach.attach_file ~memory:(Pdfio.bytes_of_raw rawbytes) false None (lookup_pdf pdf) filename)
      (lookup_pdf pdf)
  with
    e -> handle_error "attachFileFromMemory" e; err_unit

let attachFileToPage filename pdf pagenumber =
  try
    update_pdf
      (Cpdfattach.attach_file false (Some pagenumber) (lookup_pdf pdf) filename)
      (lookup_pdf pdf)
  with
    e -> handle_error "attachFileToPage" e; err_unit

let attachFileToPageFromMemory rawbytes filename pdf pagenumber =
  try
    update_pdf
      (Cpdfattach.attach_file ~memory:(Pdfio.bytes_of_raw rawbytes) false (Some pagenumber) (lookup_pdf pdf) filename)
      (lookup_pdf pdf)
  with
    e -> handle_error "attachFileToPageFromMemory" e; err_unit

let removeAttachedFiles pdf =
  try
    update_pdf (Cpdfattach.remove_attached_files (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "removeAttachedFiles" e; err_unit

let attachments = ref []

let startGetAttachments pdf =
  try
    attachments := Cpdfattach.list_attached_files (lookup_pdf pdf)
  with
    e -> handle_error "startGetAttachments" e; err_unit

let endGetAttachments () =
  try attachments := [] with
    e -> handle_error "endGetAttachments" e; err_unit

let numberGetAttachments () =
  try length !attachments with e -> handle_error "numberGetAttachments" e; err_int

let getAttachmentName serial =
  try
    (select (serial + 1) !attachments).Cpdfattach.name
  with e ->
    handle_error "getAttachmentName" e; err_string

let getAttachmentPage serial =
  try
    (select (serial + 1) !attachments).Cpdfattach.pagenumber
  with e ->
    handle_error "getAttachmentPage" e; err_int

let getAttachmentData serial =
  try
    Pdfio.raw_of_bytes
      ((select (serial + 1) !attachments).Cpdfattach.data ())
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

(* CHAPTER 13. Images *)
let images = ref [||]

let startGetImageResolution pdf res = 
  images :=
    Array.of_list
      (Cpdfimage.image_resolution (lookup_pdf pdf) (ilist 1 (Pdfpage.endpage (lookup_pdf pdf))) res);
  Array.length !images

let endGetImageResolution () =
  images := [||]

let getImageResolutionPageNumber serial =
  try
    begin match !images.(serial) with r, _, _, _, _, _, _ -> r end
  with e ->
    handle_error "getImageResolutionPageNumber" e; err_int

let getImageResolutionImageName serial =
  try
    begin match !images.(serial) with _, r, _, _, _, _, _ -> r end
  with e ->
    handle_error "getImageResolutionImageName" e; err_string

let getImageResolutionXPixels serial =
  try
    begin match !images.(serial) with _, _, r, _, _, _, _ -> r end
  with e ->
    handle_error "getImageResolutionXPixels" e; err_int

let getImageResolutionYPixels serial =
  try
    begin match !images.(serial) with _, _, _, r, _, _, _ -> r end
  with e ->
    handle_error "getImageResolutionYPixels" e; err_int

let getImageResolutionXRes serial =
  try
    begin match !images.(serial) with _, _, _, _, r, _, _ -> r end
  with e ->
    handle_error "getImageResolutionXRes" e; err_float

let getImageResolutionYRes serial =
  try
    begin match !images.(serial) with _, _, _, _, _, r, _ -> r end
  with e ->
    handle_error "getImageResolutionYRes" e; err_float

let getImageResolutionObjNum serial =
  try
    begin match !images.(serial) with _, _, _, _, _, _, r -> r end
  with e ->
    handle_error "getImageResolutionObjNum" e; err_int

let imageResolutionJSON pdf res =
  try
    Pdfio.raw_of_bytes (Cpdfimage.image_resolution_json (lookup_pdf pdf) (ilist 1 (Pdfpage.endpage (lookup_pdf pdf))) res)
  with
    e -> handle_error "imageResolutionJSON" e; err_data

let imagesJSON pdf =
  try
    Pdfio.raw_of_bytes (Pdfio.bytes_of_string (Cpdfyojson.Safe.pretty_to_string (Cpdfimage.images (lookup_pdf pdf) (ilist 1 (Pdfpage.endpage (lookup_pdf pdf))))))
  with
    e -> handle_error "imagesJSON" e; err_data

let _ = Callback.register "startGetImageResolution" startGetImageResolution
let _ = Callback.register "endGetImageResolution" endGetImageResolution
let _ = Callback.register "getImageResolutionPageNumber" getImageResolutionPageNumber
let _ = Callback.register "getImageResolutionImageName" getImageResolutionImageName
let _ = Callback.register "getImageResolutionXPixels" getImageResolutionXPixels
let _ = Callback.register "getImageResolutionYPixels" getImageResolutionYPixels
let _ = Callback.register "getImageResolutionXRes" getImageResolutionXRes
let _ = Callback.register "getImageResolutionYRes" getImageResolutionYRes
let _ = Callback.register "getImageResolutionObjNum" getImageResolutionObjNum
let _ = Callback.register "imageResolutionJSON" imageResolutionJSON
let _ = Callback.register "imagesJSON" imagesJSON

(* Add page labels of a given style, prefix and offset in a given range. *)
let addPageLabels pdf style prefix offset range progress =
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
      Cpdfpagelabels.add_page_labels (lookup_pdf pdf) progress style prefix offset (Array.to_list (lookup_range range))
  with
    e -> handle_error "addPageLabels" e; err_unit

let removePageLabels pdf =
  try
    Pdfpagelabels.remove (lookup_pdf pdf)
  with
    e -> handle_error "removePageLabels\n" e; err_unit

let labels = ref [||]

let startGetPageLabels pdf =
  try
    labels := Array.of_list (Pdfpagelabels.read (lookup_pdf pdf));
    Array.length !labels
  with
    e -> handle_error "startGetPageLabels\n" e; err_int

let int_of_labelstyle = function
  | Pdfpagelabels.DecimalArabic -> 0
  | Pdfpagelabels.UppercaseRoman -> 1
  | Pdfpagelabels.LowercaseRoman -> 2
  | Pdfpagelabels.UppercaseLetters -> 3
  | Pdfpagelabels.LowercaseLetters -> 4
  | Pdfpagelabels.NoLabelPrefixOnly -> 5

let getPageLabelStyle n =
  try
    int_of_labelstyle (!labels.(n).Pdfpagelabels.labelstyle)
  with
    e -> handle_error "getPageLabelStyle\n" e; err_int

let getPageLabelPrefix n =
  try
    match !labels.(n).Pdfpagelabels.labelprefix with
    | None -> ""
    | Some x -> Pdftext.utf8_of_pdfdocstring x
  with
    e -> handle_error "getPageLabelPrefix\n" e; err_string

let getPageLabelOffset n =
  try
    !labels.(n).Pdfpagelabels.startpage
  with
    e -> handle_error "getPageLabelOffset\n" e; err_int

let getPageLabelRange n =
  try
    !labels.(n).Pdfpagelabels.startvalue
  with
    e -> handle_error "getPageLabelRange\n" e; err_int

let endGetPageLabels () =
  labels := [||]

let getPageLabelStringForPage pdf n =
  let labels = Pdfpagelabels.read (lookup_pdf pdf) in
  try
    begin try Pdfpagelabels.pagelabeltext_of_pagenumber n labels with Not_found -> "" end
  with
    e -> handle_error "getPageLabelStringForPage\n" e; err_string

let _ = Callback.register "addPageLabels" addPageLabels
let _ = Callback.register "removePageLabels" removePageLabels
let _ = Callback.register "startGetPageLabels" startGetPageLabels
let _ = Callback.register "getPageLabelStyle" getPageLabelStyle
let _ = Callback.register "getPageLabelPrefix" getPageLabelPrefix
let _ = Callback.register "getPageLabelOffset" getPageLabelOffset
let _ = Callback.register "getPageLabelRange" getPageLabelRange
let _ = Callback.register "endGetPageLabels" endGetPageLabels
let _ = Callback.register "getPageLabelStringForPage" getPageLabelStringForPage

(* Look up the pdf, squeeze it with Cpdf.squeeze *)
let squeezeInMemory pdf =
  try
    Cpdfsqueeze.squeeze ~logto:"nolog" (lookup_pdf pdf);
    update_pdf (lookup_pdf pdf) (lookup_pdf pdf)
  with
    e -> handle_error "squeezeInMemory" e; err_unit

let _ = Callback.register "squeezeInMemory" squeezeInMemory

(* CHAPTER 15. PDF and JSON *)
let outputJSON filename parse_content no_stream_data decompress_streams pdf =
  try
    let handle = open_out_bin filename in
      Cpdfjson.to_output
        (Pdfio.output_of_channel handle) ~utf8:!json_utf8 ~parse_content ~no_stream_data ~decompress_streams (lookup_pdf pdf);
      close_out handle
  with
    e -> handle_error "outputJSON" e; err_unit

let outputJSONMemory parse_content no_stream_data decompress_streams pdf =
  try
    let o, bytes = Pdfio.input_output_of_bytes (100 * 1024) in
      Cpdfjson.to_output o ~utf8:!json_utf8 ~parse_content ~no_stream_data ~decompress_streams (lookup_pdf pdf);
      Pdfio.raw_of_bytes (Pdfio.extract_bytes_from_input_output o bytes)
  with
    e -> handle_error "outputJSONMemory" e; err_data

let _ = Callback.register "outputJSON" outputJSON
let _ = Callback.register "outputJSONMemory" outputJSONMemory

let fromJSON filename =
  try
    let fh = open_in_bin filename in
      try
        let pdf = Cpdfjson.of_input (Pdfio.input_of_channel fh) in
          close_in fh;
          new_pdf pdf
      with
        _ -> close_in fh; raise Exit
  with
    e -> handle_error "fromJSON" e; err_int

let fromJSONMemory rawbytes =
  try
    new_pdf (Cpdfjson.of_input (Pdfio.input_of_bytes (Pdfio.bytes_of_raw rawbytes)))
  with
    e -> handle_error "fromJSONMemory" e; err_int

let _ = Callback.register "fromJSON" fromJSON
let _ = Callback.register "fromJSONMemory" fromJSONMemory

(* CHAPTER 16. Optional Content Groups *)
let ocgnamelist = ref [||]

let startGetOCGList pdf =
  try
    ocgnamelist := Array.of_list (Cpdfocg.ocg_get_list (lookup_pdf pdf));
    Array.length !ocgnamelist;
  with
    e -> handle_error "startGetOCGList" e; err_int

let ocgListEntry n =
  try
    Array.get !ocgnamelist n
  with
    e -> handle_error "ocgListEntry" e; err_string

let endGetOCGList () =
  try
    ocgnamelist := [||]
  with
    e -> handle_error "endGetOCGList" e; err_unit

let _ = Callback.register "startGetOCGList" startGetOCGList
let _ = Callback.register "OCGListEntry" ocgListEntry
let _ = Callback.register "endGetOCGList" endGetOCGList

let ocgCoalesce pdf =
  try
    Cpdfocg.ocg_coalesce (lookup_pdf pdf)
  with
    e -> handle_error "ocgCoalesce" e; err_unit

let _ = Callback.register "OCGCoalesce" ocgCoalesce

let ocgRename pdf f t =
  try
    Cpdfocg.ocg_rename f t (lookup_pdf pdf) 
  with
    e -> handle_error "ocgRename" e; err_unit

let _ = Callback.register "OCGRename" ocgRename

let ocgOrderAll pdf =
  try
    Cpdfocg.ocg_order_all (lookup_pdf pdf)
  with
    e -> handle_error "ocgOrderAll" e; err_unit

let _ = Callback.register "OCGOrderAll" ocgOrderAll

(* CHAPTER 17. Creating new PDFs *)
let blankDocument width height pages =
  try new_pdf (Cpdfcreate.blank_document width height pages) with
    e -> handle_error "blankDocument" e; err_int

let blankDocumentPaper papersize pages =
  try new_pdf (Cpdfcreate.blank_document_paper (papersize_of_int papersize) pages) with
    e -> handle_error "blankDocumentPaper" e; err_int

let contents_of_file filename =
  let ch = open_in_bin filename in
    try
      let s = really_input_string ch (in_channel_length ch) in
        close_in ch;
        (Pdfio.bytes_of_string s)
    with
      _ -> close_in ch; raise Exit

let textToPDF width height font fontsize filename =
  try
    new_pdf
      (Cpdftexttopdf.typeset
         ~papersize:(Pdfpaper.make Pdfunits.PdfPoint width height)
         ~font:(Cpdfembed.PreMadeFontPack (Cpdfembed.fontpack_of_standardfont (Pdftext.StandardFont (font, Pdftext.WinAnsiEncoding))))
         ~fontsize (contents_of_file filename))
  with
    e -> handle_error "textToPDF" e; err_int

let textToPDFPaper papersize font fontsize filename =
  try
    new_pdf
      (Cpdftexttopdf.typeset
         ~papersize:(papersize_of_int papersize)
         ~font:(Cpdfembed.PreMadeFontPack (Cpdfembed.fontpack_of_standardfont (Pdftext.StandardFont (font, Pdftext.WinAnsiEncoding))))
         ~fontsize (contents_of_file filename)) with
    e -> handle_error "textToPDFPaper" e; err_int

let textToPDFMemory width height font fontsize rawbytes =
  try
    new_pdf
      (Cpdftexttopdf.typeset
         ~papersize:(Pdfpaper.make Pdfunits.PdfPoint width height)
         ~font:(Cpdfembed.PreMadeFontPack (Cpdfembed.fontpack_of_standardfont (Pdftext.StandardFont (font, Pdftext.WinAnsiEncoding))))
         ~fontsize (Pdfio.bytes_of_raw rawbytes)) with
    e -> handle_error "textToPDFMemory" e; err_int

let textToPDFPaperMemory papersize font fontsize rawbytes =
  try
    new_pdf
      (Cpdftexttopdf.typeset
         ~papersize:(papersize_of_int papersize)
         ~font:(Cpdfembed.PreMadeFontPack (Cpdfembed.fontpack_of_standardfont (Pdftext.StandardFont (font, Pdftext.WinAnsiEncoding))))
         ~fontsize (Pdfio.bytes_of_raw rawbytes)) with
    e -> handle_error "textToPDFPaperMemory" e; err_int

let fromJPEGMemory rawbytes =
  try
    new_pdf
      (Cpdfimage.image_of_input (fun () -> Cpdfimage.obj_of_jpeg_data) (Pdfio.input_of_bytes (Pdfio.bytes_of_raw rawbytes)))
  with
    e -> handle_error "fromJPEGMemory" e; err_int

let fromPNGMemory rawbytes =
  try
    new_pdf
      (Cpdfimage.image_of_input (fun () -> Cpdfimage.obj_of_png_data) (Pdfio.input_of_bytes (Pdfio.bytes_of_raw rawbytes)))
  with
    e -> handle_error "fromPNGMemory" e; err_int

let fromJPEG filename =
  try
    let input = Pdfio.input_of_bytes (contents_of_file filename) in
      new_pdf (Cpdfimage.image_of_input (fun () -> Cpdfimage.obj_of_jpeg_data) input)
  with
    e -> handle_error "fromJPEG" e; err_int

let fromPNG filename =
  try
    let input = Pdfio.input_of_bytes (contents_of_file filename) in
      new_pdf (Cpdfimage.image_of_input (fun () -> Cpdfimage.obj_of_png_data) input)
  with
    e -> handle_error "fromPNG" e; err_int

let _ = Callback.register "blankDocument" blankDocument
let _ = Callback.register "blankDocumentPaper" blankDocumentPaper
let _ = Callback.register "textToPDF" textToPDF
let _ = Callback.register "textToPDFPaper" textToPDFPaper
let _ = Callback.register "textToPDFMemory" textToPDFMemory
let _ = Callback.register "textToPDFPaperMemory" textToPDFPaperMemory
let _ = Callback.register "fromJPEG" fromJPEG
let _ = Callback.register "fromPNG" fromPNG
let _ = Callback.register "fromJPEGMemory" fromJPEGMemory
let _ = Callback.register "fromPNGMemory" fromPNGMemory

(* CHAPTER 18. Drawing on PDFs *)
let drawBegin () =
  try
    Cpdfdrawcontrol.drawops := [("_MAIN", [])];
    !Cpdfdrawcontrol.setdrawing ();
    !Cpdfdrawcontrol.setembedstd14 !embed_std14 !embed_std14_dir;
  with
    e -> handle_error "drawBegin" e; err_unit

let drawEnd pdf range =
  try
    match !Cpdfdrawcontrol.drawops with
    | [("_MAIN", ops)] ->
        update_pdf
          (Cpdfdraw.draw ~fast:!fast ~underneath:false ~filename:"" ~bates:0 ~batespad:None (Array.to_list (lookup_range range)) (lookup_pdf pdf) (rev ops))
          (lookup_pdf pdf)
    | _ -> failwith "not enough -end-xobj or -et"
  with
    e -> handle_error "drawEnd" e; err_unit

let drawEndExtended pdf range underneath bates filename =
  try
    match !Cpdfdrawcontrol.drawops with
    | [("_MAIN", ops)] ->
        update_pdf
          (Cpdfdraw.draw ~fast:!fast ~underneath ~filename ~bates ~batespad:None (Array.to_list (lookup_range range)) (lookup_pdf pdf) (rev ops))
          (lookup_pdf pdf)
    | _ -> failwith "not enough -end-xobj or -et"
  with
    e -> handle_error "drawEnd" e; err_unit

let one = Printf.sprintf "%f"
let two = Printf.sprintf "%f %f"
let three = Printf.sprintf "%f %f %f"
let four = Printf.sprintf "%f %f %f %f"
let five = Printf.sprintf "%f %f %f %f %f"
let six = Printf.sprintf "%f %f %f %f %f %f"

let drawTo a b =
  try Cpdfdrawcontrol.addto (two a b) with
    e -> handle_error "drawTo" e; err_unit

let drawLine a b =
  try Cpdfdrawcontrol.addline (two a b) with
    e -> handle_error "drawLine" e; err_unit

let drawStroke () =
  try Cpdfdrawcontrol.stroke () with
    e -> handle_error "drawStroke" e; err_unit

let drawRect a b c d =
  try Cpdfdrawcontrol.addrect (four a b c d) with
    e -> handle_error "drawRect" e; err_unit

let drawBez a b c d e f =
  try Cpdfdrawcontrol.addbezier (six a b c d e f) with
    e -> handle_error "drawBez" e; err_unit

let drawBez23 a b c d =
  try Cpdfdrawcontrol.addbezier23 (four a b c d) with
    e -> handle_error "drawBez23" e; err_unit

let drawBez13 a b c d =
  try Cpdfdrawcontrol.addbezier13 (four a b c d) with
    e -> handle_error "drawBez13" e; err_unit

let drawCircle a b c =
  try Cpdfdrawcontrol.addcircle (three a b c) with
    e -> handle_error "drawCircle" e; err_unit

let drawStrokeColGrey a =
  try Cpdfdrawcontrol.setstroke (one a) with
    e -> handle_error "drawStrokeColGrey" e; err_unit

let drawStrokeColRGB a b c =
  try Cpdfdrawcontrol.setstroke (three a b c) with
    e -> handle_error "drawStrokeColRGB" e; err_unit

let drawStrokeColCYMK a b c d =
  try Cpdfdrawcontrol.setstroke (four a b c d) with
    e -> handle_error "drawStrokeColCYMK" e; err_unit

let drawFillColGrey a =
  try Cpdfdrawcontrol.setfill (one a) with
    e -> handle_error "drawFillColGrey" e; err_unit

let drawFillColRGB a b c =
  try Cpdfdrawcontrol.setfill (three a b c) with
    e -> handle_error "drawFillColRGB" e; err_unit

let drawFillColCYMK a b c d =
  try Cpdfdrawcontrol.setfill (four a b c d) with
    e -> handle_error "drawFillColCYMK" e; err_unit

let drawFill () =
  try Cpdfdrawcontrol.fill () with
    e -> handle_error "drawFill" e; err_unit

let drawFillEo () =
  try Cpdfdrawcontrol.fillevenodd () with
    e -> handle_error "drawFillEo" e; err_unit

let drawStrokeFill () =
  try Cpdfdrawcontrol.strokefill () with
    e -> handle_error "drawStrokeFill" e; err_unit

let drawStrokeFillEo () =
  try Cpdfdrawcontrol.strokefillevenodd () with
    e -> handle_error "drawStrokeFillEo" e; err_unit

let drawClose () =
  try Cpdfdrawcontrol.closepath () with
    e -> handle_error "drawClose" e; err_unit

let drawClip () =
  try Cpdfdrawcontrol.clip () with
    e -> handle_error "drawClip" e; err_unit

let drawClipEo () =
  try Cpdfdrawcontrol.clipevenodd () with
    e -> handle_error "drawClipEo" e; err_unit

let drawThick a =
  try Cpdfdrawcontrol.setthickness (one a) with
    e -> handle_error "drawThick" e; err_unit

let cap = function
  0 -> "butt"
| 1 -> "round"
| 2 -> "square"
| _ -> failwith "cap"

let drawCap a =
  try Cpdfdrawcontrol.setcap (cap a) with
    e -> handle_error "drawCap" e; err_unit

let join = function
   0 -> "miter"
 | 1 -> "round"
 | 2 -> "bevel"
 | _ -> failwith "join"

let drawJoin a =
  try Cpdfdrawcontrol.setjoin (join a) with
    e -> handle_error "drawJoin" e; err_unit

let drawMiter a =
  try Cpdfdrawcontrol.setmiter (one a) with
    e -> handle_error "drawMiter" e; err_unit

let drawDash a =
  try Cpdfdrawcontrol.setdash a with
    e -> handle_error "drawDash" e; err_unit

let drawPush () =
  try Cpdfdrawcontrol.push () with
    e -> handle_error "drawPush" e; err_unit

let drawPop () =
  try Cpdfdrawcontrol.pop () with
    e -> handle_error "drawPop" e; err_unit

let drawMatrix a b c d e f =
  try Cpdfdrawcontrol.setmatrix (six a b c d e f) with
    e -> handle_error "drawMatrix" e; err_unit

let drawMTrans a b =
  try Cpdfdrawcontrol.setmtranslate (two a b) with
    e -> handle_error "drawMTrans" e; err_unit

let drawMRot a b c =
  try Cpdfdrawcontrol.setmrotate (three a b c) with
    e -> handle_error "drawMRot" e; err_unit

let drawMScale a b c d =
  try Cpdfdrawcontrol.setmscale (four a b c d) with
    e -> handle_error "drawMScale" e; err_unit

let drawMShearX a b c =
  try Cpdfdrawcontrol.setmshearx (three a b c) with
    e -> handle_error "drawMShearX" e; err_unit

let drawMShearY a b c =
  try Cpdfdrawcontrol.setmsheary (three a b c) with
    e -> handle_error "drawMShearY" e; err_unit

let drawXObjBBox a b c d = 
  try Cpdfdrawcontrol.xobjbbox (four a b c d) with
    e -> handle_error "drawXObjBBox" e; err_unit

let drawXObj a =
  try Cpdfdrawcontrol.startxobj a with
    e -> handle_error "drawXObj" e; err_unit

let drawEndXObj () =
  try Cpdfdrawcontrol.endxobj () with
    e -> handle_error "drawEndXObj" e; err_unit

let drawUse a =
  try Cpdfdrawcontrol.usexobj a with
    e -> handle_error "drawUse" e; err_unit

let drawJPEG a b =
  try Cpdfdrawcontrol.addjpeg (Printf.sprintf "%s=%s" a b) with
    e -> handle_error "drawJPEG" e; err_unit

let drawPNG a b =
  try Cpdfdrawcontrol.addpng (Printf.sprintf "%s=%s" a b) with
    e -> handle_error "drawPNG" e; err_unit

let drawImage a =
  try Cpdfdrawcontrol.addimage a with
    e -> handle_error "drawImage" e; err_unit

let drawFillOpacity a =
  try Cpdfdrawcontrol.addopacity a with
    e -> handle_error "drawFillOpacity" e; err_unit

let drawStrokeOpacity a =
  try Cpdfdrawcontrol.addsopacity a with
    e -> handle_error "drawStrokeOpacity" e; err_unit

let drawBT a =
  try Cpdfdrawcontrol.addbt () with
    e -> handle_error "drawBT" e; err_unit

let drawET a =
  try Cpdfdrawcontrol.addet () with
    e -> handle_error "drawET" e; err_unit

let loadFont a b =
  try Cpdfdrawcontrol.loadttfseparate a b with
    e -> handle_error "loadFont" e; err_unit

let drawFont n =
  try !Cpdfdrawcontrol.setfontname n with
    e -> handle_error "drawFont" e; err_unit

let drawFontSize f =
  try !Cpdfdrawcontrol.setfontsize f with
    e -> handle_error "drawFontSize" e; err_unit

let drawText a =
  try Cpdfdrawcontrol.addtext a with
    e -> handle_error "drawText" e; err_unit

let drawSText a =
  try Cpdfdrawcontrol.addspecialtext a with
    e -> handle_error "drawSText" e; err_unit

let drawLeading a =
  try Cpdfdrawcontrol.addleading a with
    e -> handle_error "drawLeading" e; err_unit

let drawCharSpace a =
  try Cpdfdrawcontrol.addcharspace a with
    e -> handle_error "drawCharSpace" e; err_unit

let drawWordSpace a =
  try Cpdfdrawcontrol.addwordspace a with
    e -> handle_error "drawWordSpace" e; err_unit

let drawTextScale a =
  try Cpdfdrawcontrol.addtextscale a with
    e -> handle_error "drawTextScale" e; err_unit

let drawRenderMode a =
  try Cpdfdrawcontrol.addrendermode a with
    e -> handle_error "drawRenderMode" e; err_unit

let drawRise a = 
  try Cpdfdrawcontrol.addrise a with e -> handle_error "drawRise" e; err_unit

let drawNL a =
  try Cpdfdrawcontrol.addnewline () with
    e -> handle_error "drawNL" e; err_unit

let drawNewPage () =
  try Cpdfdrawcontrol.addnewpage ()
    with e -> handle_error "drawNewPage" e; err_unit

let _ = Callback.register "drawBegin" drawBegin
let _ = Callback.register "drawEnd" drawEnd
let _ = Callback.register "drawEndExtended" drawEndExtended
let _ = Callback.register "drawTo" drawTo
let _ = Callback.register "drawLine" drawLine
let _ = Callback.register "drawStroke" drawStroke
let _ = Callback.register "drawRect" drawRect
let _ = Callback.register "drawBez" drawBez
let _ = Callback.register "drawBez23" drawBez23
let _ = Callback.register "drawBez13" drawBez13
let _ = Callback.register "drawCircle" drawCircle
let _ = Callback.register "drawStrokeColGrey" drawStrokeColGrey
let _ = Callback.register "drawStrokeColRGB" drawStrokeColRGB
let _ = Callback.register "drawStrokeColCYMK" drawStrokeColCYMK
let _ = Callback.register "drawFillColGrey" drawFillColGrey
let _ = Callback.register "drawFillColRGB" drawFillColRGB
let _ = Callback.register "drawFillColCYMK" drawFillColCYMK
let _ = Callback.register "drawFill" drawFill
let _ = Callback.register "drawFillEo" drawFillEo
let _ = Callback.register "drawStrokeFill" drawStrokeFill
let _ = Callback.register "drawStrokeFillEo" drawStrokeFillEo
let _ = Callback.register "drawClose" drawClose
let _ = Callback.register "drawClip" drawClip
let _ = Callback.register "drawClipEo" drawClipEo
let _ = Callback.register "drawThick" drawThick
let _ = Callback.register "drawCap" drawCap
let _ = Callback.register "drawJoin" drawJoin
let _ = Callback.register "drawMiter" drawMiter
let _ = Callback.register "drawDash" drawDash
let _ = Callback.register "drawPush" drawPush
let _ = Callback.register "drawPop" drawPop
let _ = Callback.register "drawMatrix" drawMatrix
let _ = Callback.register "drawMTrans" drawMTrans
let _ = Callback.register "drawMRot" drawMRot
let _ = Callback.register "drawMScale" drawMScale
let _ = Callback.register "drawMShearX" drawMShearX
let _ = Callback.register "drawMShearY" drawMShearY
let _ = Callback.register "drawXObjBBox" drawXObjBBox
let _ = Callback.register "drawXObj" drawXObj
let _ = Callback.register "drawEndXObj" drawEndXObj
let _ = Callback.register "drawUse" drawUse
let _ = Callback.register "drawJPEG" drawJPEG
let _ = Callback.register "drawPNG" drawPNG
let _ = Callback.register "drawImage" drawImage
let _ = Callback.register "drawFillOpacity" drawFillOpacity
let _ = Callback.register "drawStrokeOpacity" drawStrokeOpacity
let _ = Callback.register "drawBT" drawBT
let _ = Callback.register "drawET" drawET
let _ = Callback.register "loadFont" loadFont
let _ = Callback.register "drawFont" drawFont
let _ = Callback.register "drawFontSize" drawFontSize
let _ = Callback.register "drawText" drawText
let _ = Callback.register "drawSText" drawSText
let _ = Callback.register "drawLeading" drawLeading
let _ = Callback.register "drawCharSpace" drawCharSpace
let _ = Callback.register "drawWordSpace" drawWordSpace  
let _ = Callback.register "drawTextScale" drawTextScale
let _ = Callback.register "drawRenderMode" drawRenderMode
let _ = Callback.register "drawRise" drawRise
let _ = Callback.register "drawNL" drawNL
let _ = Callback.register "drawNewPage" drawNewPage

(* CHAPTER 19. Miscellaneous *)
let draft pdf range boxes =
  try
    update_pdf (Cpdfdraft.draft None boxes (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "draft" e; err_unit

let blackText pdf range =
  try
    update_pdf (Cpdftweak.blacktext (Cpdfaddtext.RGB (0., 0., 0.)) (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "blackText" e; err_unit

let blackLines pdf range =
  try
    update_pdf (Cpdftweak.blacklines (Cpdfaddtext.RGB (0., 0., 0.)) (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "blackLines" e; err_unit

let blackFills pdf range =
  try
    update_pdf (Cpdftweak.blackfills (Cpdfaddtext.RGB (0., 0., 0.)) (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "blackFills" e; err_unit

let thinLines pdf range thickness =
  try
    update_pdf (Cpdftweak.thinlines (Array.to_list (lookup_range range)) thickness (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "thinLines" e; err_unit

let copyId from_pdf to_pdf =
  try
    update_pdf (Cpdfmetadata.copy_id false (lookup_pdf from_pdf) (lookup_pdf to_pdf)) (lookup_pdf to_pdf)
  with
    e -> handle_error "copyId" e; err_unit

let removeAllText pdf range =
  try
    update_pdf (Cpdfremovetext.remove_all_text (Array.to_list (lookup_range range)) (lookup_pdf pdf)) (lookup_pdf pdf)
  with
    e -> handle_error "removeAllText" e; err_unit

let removeId pdf =
  try
    (lookup_pdf pdf).Pdf.trailerdict <- Pdf.remove_dict_entry (lookup_pdf pdf).Pdf.trailerdict "/ID"
  with
    e -> handle_error "removeId" e; err_unit

let removeDictEntry pdf key =
  try
    Cpdftweak.remove_dict_entry (lookup_pdf pdf) key None
  with
    e -> handle_error "removeDictEntry" e; err_unit

let removeDictEntrySearch pdf key searchterm =
  try
    Cpdftweak.remove_dict_entry (lookup_pdf pdf) key (Some (Cpdfjson.object_of_json (Cpdfyojson.Safe.from_string searchterm)))
  with
    e -> handle_error "removeDictEntrySearch" e; err_unit

let replaceDictEntry pdf key value =
  try
    Cpdftweak.replace_dict_entry (lookup_pdf pdf) key (Cpdfjson.object_of_json (Cpdfyojson.Safe.from_string value)) None
  with
    e -> handle_error "replaceDictEntry" e; err_unit

let replaceDictEntrySearch pdf key value searchterm =
  try
    let a = lookup_pdf pdf in
    let b = (Cpdfjson.object_of_json (Cpdfyojson.Safe.from_string value)) in
    let c = (Some (Cpdfjson.object_of_json (Cpdfyojson.Safe.from_string searchterm))) in
    Cpdftweak.replace_dict_entry a key b c 
  with
    e -> handle_error "replaceDictEntrySearch" e; err_unit

let getDictEntries pdf key =
  try
    Pdfio.raw_of_bytes (Cpdftweak.get_dict_entries ~utf8:!json_utf8 (lookup_pdf pdf) key)
  with
    e -> handle_error "getDictEntries" e; err_data

let removeClipping pdf range =
  try
    update_pdf (Cpdftweak.remove_clipping (lookup_pdf pdf) (Array.to_list (lookup_range range))) (lookup_pdf pdf)
  with
    e -> handle_error "removeClipping" e; err_unit

let _ = Callback.register "draft" draft
let _ = Callback.register "blackText" blackText
let _ = Callback.register "blackLines" blackLines
let _ = Callback.register "blackFills" blackFills
let _ = Callback.register "thinLines" thinLines
let _ = Callback.register "copyId" copyId
let _ = Callback.register "removeAllText" removeAllText
let _ = Callback.register "removeId" removeId
let _ = Callback.register "removeDictEntry" removeDictEntry
let _ = Callback.register "removeDictEntrySearch" removeDictEntrySearch
let _ = Callback.register "replaceDictEntry" replaceDictEntry
let _ = Callback.register "replaceDictEntrySearch" replaceDictEntrySearch
let _ = Callback.register "getDictEntries" getDictEntries
let _ = Callback.register "removeClipping" removeClipping


let onexit () =
  Printf.printf "There are %i ranges on exit\n" (Hashtbl.length ranges);
  Printf.printf "There are %i PDFs on exit:\n" (Hashtbl.length pdfs);
  Hashtbl.iter (fun k v -> Printf.printf "%i, " k) pdfs;
  print_string "\n";
  flush stdout

let _ = Callback.register "onexit" onexit
