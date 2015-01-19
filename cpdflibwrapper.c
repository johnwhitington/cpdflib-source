#include <stdio.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/alloc.h>
#include <caml/bigarray.h>

/* CHAPTER 0. Preliminaries */

void cpdf_startup(char ** argv)
{
  caml_startup(argv);
  return;
}

int cpdf_lastError = 0;
char* cpdf_lastErrorString = "";

/* Get the latest error from OCaml and replicate it here in C. Also update the
 * lastErrorString, This function is not exposed in the interface */
void updateLastError (void)
{
  CAMLparam0();
  CAMLlocal3(getLastError_v, unit_v, result_v);
  CAMLlocal2(getLastErrorString_v, string_result_v);
  getLastError_v = *caml_named_value("getLastError");
  unit_v = Val_unit;
  result_v = caml_callback(getLastError_v, unit_v);
  cpdf_lastError = Int_val(result_v);
  getLastErrorString_v = *caml_named_value("getLastErrorString");
  string_result_v = caml_callback(getLastErrorString_v, unit_v);
  cpdf_lastErrorString = String_val(string_result_v);
  CAMLreturn0;
}

void cpdf_setDemo(int b)
{
  CAMLparam0 ();
  CAMLlocal3(setdemo_v, int_v, result_v);
  setdemo_v = *caml_named_value("setdemo");
  int_v = Val_int(b);
  result_v = caml_callback(setdemo_v, int_v);
  updateLastError();
  CAMLreturn0;
}

/*Clear the error in the Ocaml bit, and here in C*/
void cpdf_clearError (void)
{
  CAMLparam0 ();
  CAMLlocal3(clearError_v, unit_v, result_v);
  clearError_v = *caml_named_value("clearError");
  unit_v = Val_unit;
  result_v = caml_callback(clearError_v, unit_v);
  cpdf_lastError = 0;
  CAMLreturn0;
}

void cpdf_onExit (void)
{
  CAMLparam0();
  CAMLlocal2(fn_v, out_v);
  fn_v = *caml_named_value("onexit");
  out_v = caml_callback(fn_v, Val_unit);
  CAMLreturn0;
}

void cpdf_deletePdf(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(deletePdf, int_in, unit_out);
  deletePdf = *caml_named_value("deletePdf");
  int_in = Val_int(pdf);
  unit_out = caml_callback(deletePdf, int_in);
  updateLastError();
  CAMLreturn0;
}

void cpdf_replacePdf(int o, int n)
{
  CAMLparam0 ();
  CAMLlocal4(replacePdf, o_v, n_v, unit_out);
  replacePdf = *caml_named_value("replacePdf");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(replacePdf, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}

int cpdf_startEnumeratePDFs(void)
{
  CAMLparam0 ();
  CAMLlocal3(enumeratePDFs_v, unit_v, int_v);
  enumeratePDFs_v = *caml_named_value("startEnumeratePDFs");
  unit_v = Val_unit;
  int_v = caml_callback(enumeratePDFs_v, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(int_v));
}

int cpdf_enumeratePDFsKey(int key)
{
  CAMLparam0 ();
  CAMLlocal3(enumeratePDFsKey, key_v, out_v);
  enumeratePDFsKey = *caml_named_value("enumeratePDFsKey");
  key_v = Val_int(key);
  out_v = caml_callback(enumeratePDFsKey, key_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

char* cpdf_enumeratePDFsInfo(int key)
{
  CAMLparam0 ();
  CAMLlocal3(enumeratePDFsInfo, key_v, out_v);
  enumeratePDFsInfo = *caml_named_value("enumeratePDFsInfo");
  key_v = Val_int(key);
  out_v = caml_callback(enumeratePDFsInfo, key_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out_v));
}

void cpdf_endEnumeratePDFs(void)
{
  CAMLparam0 ();
  CAMLlocal3(endEnumeratePDFs, unit_v, out_v);
  endEnumeratePDFs = *caml_named_value("endEnumeratePDFs");
  unit_v = Val_unit;
  out_v = caml_callback(endEnumeratePDFs, unit_v);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 1. Basics */
double cpdf_ptOfCm (double f)
{
  CAMLparam0 ();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("ptOfCm");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}

double cpdf_ptOfMm (double f)
{
  CAMLparam0 ();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("ptOfMm");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}

double cpdf_ptOfIn (double f)
{
  CAMLparam0 ();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("ptOfIn");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}

double cpdf_cmOfPt (double f)
{
  CAMLparam0 ();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("cmOfPt");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}

double cpdf_mmOfPt (double f)
{
  CAMLparam0 ();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("mmOfPt");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}

double cpdf_inOfPt (double f)
{
  CAMLparam0 ();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("inOfPt");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}

int cpdf_parsePagespec(int pdf, char* str)
{
  CAMLparam0 ();
  CAMLlocal4 (fn, inpdf, instr, out);
  fn = *caml_named_value("parsePagespec");
  inpdf = Val_int(pdf);
  instr = caml_copy_string(str);
  out = caml_callback2(fn, inpdf, instr);
  updateLastError ();
  CAMLreturnT(int, Int_val(out));
}

int cpdf_validatePagespec(char* str)
{
  CAMLparam0();
  CAMLlocal3(fn, instr, out);
  fn = *caml_named_value("validatePagespec");
  instr = caml_copy_string(str);
  out = caml_callback(fn, instr);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

char* cpdf_stringOfPagespec(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4(fn, inpdf, inrange, out);
  fn = *caml_named_value("stringOfPagespec");
  inpdf = Val_int(pdf);
  inrange = Val_int(range);
  out = caml_callback2(fn, inpdf, inrange);
  updateLastError();
  CAMLreturnT(char*, String_val(out));
}

int cpdf_blankRange(void)
{
  CAMLparam0 ();
  CAMLlocal3(fn, unitin, rangeout);
  fn = *caml_named_value("blankrange");
  unitin = Val_unit;
  rangeout = caml_callback(fn, unitin);
  updateLastError();
  CAMLreturnT(int, Int_val(rangeout));
}

void cpdf_deleteRange(int range)
{
  CAMLparam0 ();
  CAMLlocal3(fn, range_v, out_v);
  fn = *caml_named_value("deleterange");
  range_v = Val_int(range);
  out_v = caml_callback(fn, range_v);
  updateLastError();
  CAMLreturn0;
}

int cpdf_range(int a, int b)
{
  CAMLparam0 ();
  CAMLlocal4(fn, range, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("range");
  range = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT (int, Int_val(range));
}

int cpdf_even(int r)
{
  CAMLparam0 ();
  CAMLlocal3(fn, r_v, out_v);
  fn = *caml_named_value("even");
  r_v = Val_int(r);
  out_v = caml_callback(fn, r_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_odd(int r)
{
  CAMLparam0 ();
  CAMLlocal3(fn, r_v, out_v);
  fn = *caml_named_value("odd");
  r_v = Val_int(r);
  out_v = caml_callback(fn, r_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_rangeUnion(int a, int b)
{
  CAMLparam0 ();
  CAMLlocal4(fn, a_v, b_v, out_v);
  a_v = Val_int(a);
  b_v = Val_int(b);
  fn = *caml_named_value("range_union");
  out_v = caml_callback2(fn, a_v, b_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_difference(int a, int b)
{
  CAMLparam0 ();
  CAMLlocal4(fn, a_v, b_v, out_v);
  a_v = Val_int(a);
  b_v = Val_int(b);
  fn = *caml_named_value("difference");
  out_v = caml_callback2(fn, a_v, b_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_removeDuplicates(int r)
{
  CAMLparam0 ();
  CAMLlocal3(fn, r_v, out_v);
  fn = *caml_named_value("removeDuplicates");
  r_v = Val_int(r);
  out_v = caml_callback(fn, r_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_rangeLength(int r)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, r_v, out_v);
  fn = *caml_named_value("lengthrange");
  r_v = Val_int(r);
  out_v = caml_callback(fn, r_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_rangeGet(int r, int pos)
{
  CAMLparam0 ();
  CAMLlocal4 (fn, r_v, pos_v, out_v);
  fn = *caml_named_value("readrange");
  r_v = Val_int(r);
  pos_v = Val_int(pos);
  out_v = caml_callback2(fn, r_v, pos_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_rangeAdd(int r, int n)
{
  CAMLparam0 ();
  CAMLlocal4 (fn, r_v, n_v, out_v);
  fn = *caml_named_value("addtorange");
  r_v = Val_int(r);
  n_v = Val_int(n);
  out_v = caml_callback2(fn, r_v, n_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_isInRange(int r, int i)
{
  CAMLparam0 ();
  CAMLlocal4 (fn, r_v, i_v, out_v);
  fn = *caml_named_value("isInRange");
  r_v = Val_int(r);
  i_v = Val_int(i);
  out_v = caml_callback2(fn, r_v, i_v);
  updateLastError ();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_fromFile(char* filename, char* userpw)
{
  CAMLparam0 ();
  CAMLlocal4(fromfile_v, filename_v, userpw_v, result_v);
  fromfile_v = *caml_named_value("fromFile");
  filename_v = caml_copy_string(filename);
  userpw_v = caml_copy_string(userpw);
  result_v = caml_callback2(fromfile_v, filename_v, userpw_v);
  updateLastError ();
  CAMLreturnT(int, Int_val(result_v));
}

int cpdf_fromFileLazy(char* filename, char* userpw)
{
  CAMLparam0 ();
  CAMLlocal4(fromfile_v, filename_v, userpw_v, result_v);
  fromfile_v = *caml_named_value("fromFileLazy");
  filename_v = caml_copy_string(filename);
  userpw_v = caml_copy_string(userpw);
  result_v = caml_callback2(fromfile_v, filename_v, userpw_v);
  updateLastError();
  CAMLreturnT(int, Int_val(result_v));
}

int cpdf_blankDocument(double width, double height, int pages)
{
  CAMLparam0 ();
  CAMLlocal5(fn, width_v, height_v, pages_v, out);
  fn = *caml_named_value("blankDocument");
  width_v = caml_copy_double(width);
  height_v = caml_copy_double(height);
  pages_v = Val_int(pages);
  out = caml_callback3(fn, width_v, height_v, pages_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

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

int cpdf_blankDocumentPaper(enum cpdf_papersize papersize, int pages)
{
  CAMLparam0 ();
  CAMLlocal4(fn, papersize_v, pages_v, out);
  fn = *caml_named_value("blankDocumentPaper");
  papersize_v = Val_int(papersize);
  pages_v = Val_int(pages);
  out = caml_callback2(fn, papersize_v, pages_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

int cpdf_pages(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(fn, pdf_v, out);
  fn = *caml_named_value("pages");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

int cpdf_pagesFast(char* password, char* filename)
{
  CAMLparam0 ();
  CAMLlocal4(pagesFast_v, filename_v, password_v, result_v);
  pagesFast_v = *caml_named_value("pagesFast");
  filename_v = caml_copy_string(filename);
  password_v = caml_copy_string(password);
  result_v = caml_callback2(pagesFast_v, password_v, filename_v);
  updateLastError();
  CAMLreturnT(int, Int_val(result_v));
}

void cpdf_toFile(int pdf, char* filename, int linearize, int make_id)
{
  CAMLparam0 ();
  CAMLlocal2(fn, unit);
  CAMLlocalN (args, 4);
  args[0] = Val_int(pdf);
  args[1] = caml_copy_string(filename);
  args[2] = Val_int(linearize);
  args[3] = Val_int(make_id);
  fn = *caml_named_value("toFile");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}

int cpdf_all(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(out_v, fn, pdf_v);
  fn = *caml_named_value("all");
  pdf_v = Val_int(pdf);
  out_v = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_isEncrypted(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(fn, pdf_v, out);
  fn = *caml_named_value("isEncrypted");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

void cpdf_decryptPdf(int pdf, char* password)
{
  CAMLparam0 ();
  CAMLlocal4(unit, fn, pdf_v, password_v);
  fn = *caml_named_value("decryptPdf");
  pdf_v = Val_int(pdf);
  password_v = caml_copy_string(password);
  unit = caml_callback2(fn, pdf_v, password_v);
  updateLastError ();
  CAMLreturn0;
}

void cpdf_decryptPdfOwner(int pdf, char* password)
{
  CAMLparam0 ();
  CAMLlocal4(unit, fn, pdf_v, password_v);
  fn = *caml_named_value("decryptPdfOwner");
  pdf_v = Val_int(pdf);
  password_v = caml_copy_string(password);
  unit = caml_callback2(fn, pdf_v, password_v);
  updateLastError ();
  CAMLreturn0;
}

enum cpdf_permission
  {cpdf_noEdit,
   cpdf_noPrint,
   cpdf_noCopy,
   cpdf_noAnnot,
   cpdf_noForms,
   cpdf_noExtract,
   cpdf_noAssemble,
   cpdf_noHqPrint};

enum cpdf_encryptionMethod
  {cpdf_pdf40bit,
   cpdf_pdf218bit,
   cpdf_aes128bitfalse,
   cpdf_aes128bittrue,
   cpdf_aes256bitfalse,
   cpdf_aes256bittrue,
   cpdf_aes256bitisofalse,
   cpdf_aes256bitisotrue};

void cpdf_toFileEncrypted
  (int pdf,
   int e,
   int* ps,
   int len,
   char* owner,
   char* user,
   int linearize,
   int makeid,
   char* filename)
{
  CAMLparam0 ();
  CAMLlocal4(unit, fn, temp, permissions);
  CAMLlocalN (args, 8);
  /* Build ocaml permission array */
  permissions = caml_alloc(len, 0);
  int x;
  for(x = 0; x < len; x++)
    {
      temp = Val_int(ps[x]);
      Store_field(permissions, x, temp);
    };
  /* Do Callback */
  args[0] = Val_int(pdf);
  args[1] = Val_int(e);
  args[2] = permissions;
  args[3] = caml_copy_string(owner);
  args[4] = caml_copy_string(user);
  args[5] = Val_int(linearize);
  args[6] = Val_int(makeid);
  args[7] = caml_copy_string(filename);
  fn = *caml_named_value("toFileEncrypted");
  unit = caml_callbackN(fn, 8, args);
  updateLastError();
  /* Return */
  CAMLreturn0;
}

void cpdf_toFileRecrypting(int original, int decrypted_and_modified, char* userpw, char* filename)
{
  CAMLparam0 ();
  CAMLlocal2 (unit, fn);
  CAMLlocalN (args, 4);
  fn = *caml_named_value("toFileRecrypting");
  args[0] = Val_int(original);
  args[1] = Val_int(decrypted_and_modified);
  args[2] = caml_copy_string(userpw);
  args[3] = caml_copy_string(filename);
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}

int cpdf_hasPermission(int pdf, enum cpdf_permission tocheck)
{
  CAMLparam0 ();
  CAMLlocal4(fn_v, pdf_v, tocheck_v, out_v);
  fn_v = *caml_named_value("hasPermission");
  pdf_v = Val_int(pdf);
  tocheck_v = Val_int(tocheck);
  out_v = caml_callback2(fn_v, pdf_v, tocheck_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

enum cpdf_encryptionMethod cpdf_encryptionKind(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn_v, pdf_v, out_v);
  fn_v = *caml_named_value("encryptionKind");
  pdf_v = Val_int(pdf);
  out_v = caml_callback(fn_v, pdf_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

/* CHAPTER 2. Merging and Splitting */

int cpdf_mergeSimple(int* pdfs, int len)
{ 
  CAMLparam0 ();
  CAMLlocal4(fn, array, temp, out);
  array = caml_alloc(len, 0);
  int x;
  for(x = 0; x < len; x++)
  { 
    temp = Val_int(pdfs[x]);
    Store_field(array, x, temp);
  };
  fn = *caml_named_value("mergeSimple");
  out = caml_callback(fn, array);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

int cpdf_merge(int* pdfs, int len, int retain_numbering, int remove_duplicate_fonts)
{
  CAMLparam0();
  CAMLlocal5(fn, array, temp, len_v, retain_numbering_v);
  CAMLlocal2(remove_duplicate_fonts_v, out);
  array = caml_alloc(len, 0);
  int x;
  for(x = 0; x < len; x++)
  {
    temp = Val_int(pdfs[x]);
    Store_field(array, x, temp);
  };
  fn = *caml_named_value("merge");
  retain_numbering_v = Val_int(retain_numbering);
  remove_duplicate_fonts_v = Val_int(remove_duplicate_fonts);
  out = caml_callback3(fn, array, retain_numbering_v, remove_duplicate_fonts_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

int cpdf_mergeSame(int* pdfs, int len, int retain_numbering, int remove_duplicate_fonts, int* ranges)
{
  CAMLparam0();
  CAMLlocal3(array, rangearray, fn);
  CAMLlocal2(temp, out);
  CAMLlocalN(args, 4);
  array = caml_alloc(len, 0);
  rangearray = caml_alloc(len, 0);
  int x;
  for(x = 0; x < len; x++)
  {
    temp = Val_int(pdfs[x]);
    Store_field(array, x, temp);
  };
  for(x = 0; x < len; x++)
  {
    temp = Val_int(ranges[x]);
    Store_field(rangearray, x, temp);
  };
  fn = *caml_named_value("mergeSame");
  args[0] = array;
  args[1] = Val_int(retain_numbering);
  args[2] = Val_int(remove_duplicate_fonts);
  args[3] = rangearray;
  out = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

int cpdf_selectPages(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4(fn, pdf_v, range_v, out);
  fn = *caml_named_value("selectPages");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  out = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

/* CHAPTER 3. Pages */

void cpdf_scalePages(int pdf, int range, double sx, double sy)
{
  CAMLparam0 ();
  CAMLlocal2 (fn, unit);
  CAMLlocalN (args, 4);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(sx);
  args[3] = caml_copy_double(sy);
  fn = *caml_named_value("scalePages");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_scaleToFit(int pdf, int range, double w, double h)
{
  CAMLparam0 ();
  CAMLlocalN (args, 4);
  CAMLlocal2 (fn, unit);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(w);
  args[3] = caml_copy_double(h);
  fn = *caml_named_value("scaleToFit");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_scaleToFitPaper(int pdf, int range, int papersize)
{
  CAMLparam0 ();
  CAMLlocalN (args, 3);
  CAMLlocal2 (unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = Val_int(papersize);
  fn = *caml_named_value("scaleToFitPaper");
  unit = caml_callbackN(fn, 3, args);
  updateLastError();
  CAMLreturn0;
}

enum cpdf_anchor
  {cpdf_posCentre,
   cpdf_posLeft,
   cpdf_posRight,
   cpdf_top,
   cpdf_topLeft,
   cpdf_topRight,
   cpdf_left,
   cpdf_bottomLeft,
   cpdf_bottom,
   cpdf_bottomRight,
   cpdf_right,
   cpdf_diagonal,
   cpdf_reversediagonal};

struct cpdf_position {
  int cpdf_anchor;
  double cpdf_coord1;
  double cpdf_coord2;
};

void cpdf_scaleContents(int pdf, int range, struct cpdf_position pos, double scale)
{
  CAMLparam0 ();
  CAMLlocalN (args, 6);
  CAMLlocal3 (unit, camlpos, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = Val_int(pos.cpdf_anchor);
  args[3] = caml_copy_double(pos.cpdf_coord1);
  args[4] = caml_copy_double(pos.cpdf_coord2);
  args[5] = caml_copy_double(scale);
  fn = *caml_named_value("scaleContents");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_shiftContents(int pdf, int range, double dx, double dy)
{
  CAMLparam0 ();
  CAMLlocalN (args, 4);
  CAMLlocal2 (fn, unit);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(dx);
  args[3] = caml_copy_double(dy);
  fn = *caml_named_value("shiftContents");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_rotate(int pdf, int range, int angle)
{
  CAMLparam0 ();
  CAMLlocal5 (unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("rotate");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_rotateBy(int pdf, int range, int angle)
{
  CAMLparam0 ();
  CAMLlocal5 (unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("rotateBy");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_rotateContents(int pdf, int range, double angle)
{
  CAMLparam0 ();
  CAMLlocal5 (unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("rotateContents");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = caml_copy_double(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_upright(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4(unit, fn, pdf_v, range_v);
  fn = *caml_named_value("upright");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_hFlip(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4(unit, fn, pdf_v, range_v);
  fn = *caml_named_value("hFlip");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_vFlip(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4(unit, fn, pdf_v, range_v);
  fn = *caml_named_value("vFlip");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_crop(int pdf, int range, double x, double y, double w, double h)
{
  CAMLparam0 ();
  CAMLlocalN (args, 6);
  CAMLlocal2 (unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(x);
  args[3] = caml_copy_double(y);
  args[4] = caml_copy_double(w);
  args[5] = caml_copy_double(h);
  fn = *caml_named_value("crop");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_removeCrop(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, range_v);
  fn = *caml_named_value("removeCrop");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_removeTrim(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, range_v);
  fn = *caml_named_value("removeTrim");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_removeArt(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, range_v);
  fn = *caml_named_value("removeArt");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_removeBleed(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, range_v);
  fn = *caml_named_value("removeBleed");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 5. Compression */
void cpdf_compress(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (unit, fn, pdf_v);
  fn = *caml_named_value("compress");
  pdf_v = Val_int(pdf);
  unit = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_decompress(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (unit, fn, pdf_v);
  fn = *caml_named_value("decompress");
  pdf_v = Val_int(pdf);
  unit = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 6. Bookmarks */
void cpdf_startGetBookmarkInfo (int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(fn_v, pdf_v, out_v);
  fn_v = *caml_named_value("startGetBookmarkInfo");
  pdf_v = Val_int(pdf);
  out_v = caml_callback(fn_v, pdf_v);
  updateLastError();
  CAMLreturn0;
}

int cpdf_numberBookmarks(void)
{
  CAMLparam0 ();
  CAMLlocal3 (fn_v, out_v, unit_v);
  fn_v = *caml_named_value("numberBookmarks");
  unit_v = Val_unit;
  out_v = caml_callback(fn_v, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_getBookmarkLevel(int serial)
{
  CAMLparam0 ();
  CAMLlocal3 (serial_v, fn_v, out_v);
  fn_v = *caml_named_value("getBookmarkLevel");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn_v, serial_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_getBookmarkPage(int pdf, int serial)
{
  CAMLparam0 ();
  CAMLlocal4 (serial_v, fn_v, out_v, pdf_v);
  fn_v = *caml_named_value("getBookmarkPage");
  serial_v = Val_int(serial);
  pdf_v = Val_int(pdf);
  out_v = caml_callback2(fn_v, pdf_v, serial_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

char* cpdf_getBookmarkText(int serial)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, serial_v, out_v);
  fn = *caml_named_value("getBookmarkText");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn, serial_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out_v)); 
}

void cpdf_endGetBookmarkInfo (void)
{
  CAMLparam0 ();
  CAMLlocal3(fn_v, unit_v, out_v);
  fn_v = *caml_named_value("endGetBookmarkInfo");
  unit_v = Val_unit;
  out_v = caml_callback(fn_v, unit_v);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 7. Presentations */

/* CHAPTER 8. Logos, Watermarks and Stamps */

void cpdf_stampOn(int pdf, int pdf2, int range)
{
  CAMLparam0 ();
  CAMLlocal5 (fn, pdf_v, pdf2_v, range_v, unit);
  fn = *caml_named_value("stampOn");
  pdf_v = Val_int(pdf);
  pdf2_v = Val_int(pdf2);
  range_v = Val_int(range);
  unit = caml_callback3(fn, pdf_v, pdf2_v, range_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_stampUnder(int pdf, int pdf2, int range)
{
  CAMLparam0 ();
  CAMLlocal5 (unit, fn, pdf_v, pdf2_v, range_v);
  fn = *caml_named_value("stampUnder");
  pdf_v = Val_int(pdf);
  pdf2_v = Val_int(pdf2);
  range_v = Val_int(range);
  unit = caml_callback3(fn, pdf_v, pdf2_v, range_v);
  updateLastError();
  CAMLreturn0;
}

int cpdf_combinePages(int pdf, int pdf2)
{
  CAMLparam0 ();
  CAMLlocal4 (fn, pdf_v, pdf2_v, pdfout);
  fn = *caml_named_value("combinePages");
  pdf_v = Val_int(pdf);
  pdf2_v = Val_int(pdf2);
  pdfout = caml_callback2(fn, pdf_v, pdf2_v);
  updateLastError();
  CAMLreturnT(int, Int_val(pdfout));
}

void cpdf_addText
(int metrics,
 int pdf,
 int range,
 char* text,
 struct cpdf_position pos,
 double linespacing,
 int bates,
 int font,
 double fontsize,
 double r,
 double g,
 double b,
 int underneath,
 int cropbox,
 int outline,
 double opacity,
 int justification,
 int midline,
 char* filename)
{
  CAMLparam0 ();
  CAMLlocal2(fn, unit);
  CAMLlocalN (args, 21);
  fn = *caml_named_value("addText");
  args[0] = Val_int(metrics);
  args[1] = Val_int(pdf);
  args[2] = Val_int(range);
  args[3] = caml_copy_string(text);
  args[4] = Val_int(pos.cpdf_anchor);
  args[5] = caml_copy_double(pos.cpdf_coord1);
  args[6] = caml_copy_double(pos.cpdf_coord2);
  args[7] = caml_copy_double(linespacing);
  args[8] = Val_int(bates);
  args[9] = Val_int(font);
  args[10] = caml_copy_double(fontsize);
  args[11] = caml_copy_double(r);
  args[12] = caml_copy_double(g);
  args[13] = caml_copy_double(b);
  args[14] = Val_int(underneath);
  args[15] = Val_int(cropbox);
  args[16] = Val_int(outline);
  args[17] = caml_copy_double(opacity);
  args[18] = Val_int(justification);
  args[19] = Val_int(midline);
  args[20] = caml_copy_string(filename);
  unit = caml_callbackN(fn, 21, args);
  updateLastError();
  CAMLreturn0;
}

int cpdf_addTextHowMany(void)
{
  CAMLparam0();
  CAMLlocal3(fn, unit, out_v);
  fn = *caml_named_value("addTextHowMany");
  unit = Val_unit;
  out_v = caml_callback(fn, unit);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

char* cpdf_addTextReturnText(int serial)
{
  CAMLparam0();
  CAMLlocal3(fn, serial_v, out_v);
  fn = *caml_named_value("addTextReturnText");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn, serial_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out_v));
}

double cpdf_addTextReturnX(int serial)
{
  CAMLparam0();
  CAMLlocal3(fn, serial_v, out_v);
  fn = *caml_named_value("addTextReturnX");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn, serial_v);
  updateLastError();
  CAMLreturnT(double, Double_val(out_v));
}

double cpdf_addTextReturnY(int serial)
{
  CAMLparam0();
  CAMLlocal3(fn, serial_v, out_v);
  fn = *caml_named_value("addTextReturnY");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn, serial_v);
  updateLastError();
  CAMLreturnT(double, Double_val(out_v));
}

double cpdf_addTextReturnRotation(int serial)
{
  CAMLparam0();
  CAMLlocal3(fn, serial_v, out_v);
  fn = *caml_named_value("addTextReturnRotation");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn, serial_v);
  updateLastError();
  CAMLreturnT(double, Double_val(out_v));
}

double cpdf_addTextReturnBaselineAdjustment(void)
{
  CAMLparam0();
  CAMLlocal2(fn, out_v);
  fn = *caml_named_value("addTextReturnBaselineAdjustment");
  out_v = caml_callback(fn, Val_unit);
  updateLastError();
  CAMLreturnT(double, Double_val(out_v));
}

void cpdf_removeText(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4 (fn, unit, pdf_v, range_v);
  fn = *caml_named_value("removeText");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}



int cpdf_textWidth(int font, char* text)
{
  CAMLparam0 ();
  CAMLlocal2 (fn, out_v);
  CAMLlocal2 (font_v, text_v);
  font_v = Val_int(font);
  text_v = caml_copy_string(text);
  fn = *caml_named_value("textWidth");
  out_v = caml_callback2(fn, font_v, text_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v)); 
}

/* CHAPTER 9. Multipage facilities */

void cpdf_twoUp(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(unit, fn, pdf_v);
  fn = *caml_named_value("twoUp");
  pdf_v = Val_int(pdf);
  unit = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_padBefore(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4(unit, pdf_v, range_v, fn);
  fn = *caml_named_value("padBefore");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_padAfter(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4(unit, pdf_v, range_v, fn);
  fn = *caml_named_value("padAfter");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 10. Annotations */

/* CHAPTER 11. Document Information and Metadata */

void cpdf_startGetFontInfo (int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(fn_v, pdf_v, out_v);
  fn_v = *caml_named_value("startGetFontInfo");
  pdf_v = Val_int(pdf);
  out_v = caml_callback(fn_v, pdf_v);
  updateLastError();
  CAMLreturn0;
}
int cpdf_numberFonts(void)
{
  CAMLparam0 ();
  CAMLlocal3 (fn_v, out_v, unit_v);
  fn_v = *caml_named_value("numberFonts");
  unit_v = Val_unit;
  out_v = caml_callback(fn_v, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_getFontPage(int serial)
{
  CAMLparam0 ();
  CAMLlocal3 (serial_v, fn_v, out_v);
  fn_v = *caml_named_value("getFontPage");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn_v, serial_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

char* cpdf_getFontName(int serial)
{
  CAMLparam0 ();
  CAMLlocal3 (serial_v, fn_v, out_v);
  fn_v = *caml_named_value("getFontName");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn_v, serial_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out_v));
}

char* cpdf_getFontType(int serial)
{
  CAMLparam0 ();
  CAMLlocal3 (serial_v, fn_v, out_v);
  fn_v = *caml_named_value("getFontType");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn_v, serial_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out_v));
}

char* cpdf_getFontEncoding(int serial)
{
  CAMLparam0 ();
  CAMLlocal3 (serial_v, fn_v, out_v);
  fn_v = *caml_named_value("getFontEncoding");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn_v, serial_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out_v));
}

void cpdf_endGetFontInfo (void)
{
  CAMLparam0 ();
  CAMLlocal3(fn_v, unit_v, out_v);
  fn_v = *caml_named_value("endGetFontInfo");
  unit_v = Val_unit;
  out_v = caml_callback(fn_v, unit_v);
  updateLastError();
  CAMLreturn0;
}

int cpdf_isLinearized(char* filename)
{
  CAMLparam0 ();
  CAMLlocal3 (fn_v, filename_v, out_v);
  fn_v = *caml_named_value("isLinearized");
  filename_v = caml_copy_string(filename);
  out_v = caml_callback(fn_v, filename_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_getVersion(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out);
  fn = *caml_named_value("getVersion");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

char* cpdf_getTitle(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out);
  fn = *caml_named_value("getTitle");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out));
}

char* cpdf_getAuthor(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out);
  fn = *caml_named_value("getAuthor");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out));
}

char* cpdf_getSubject(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out);
  fn = *caml_named_value("getSubject");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out));
}

char* cpdf_getKeywords(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out);
  fn = *caml_named_value("getKeywords");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out));
}

char* cpdf_getCreator(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out);
  fn = *caml_named_value("getCreator");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out));
}

char* cpdf_getProducer(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out);
  fn = *caml_named_value("getProducer");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out));
}

char* cpdf_getCreationDate(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out);
  fn = *caml_named_value("getCreationDate");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out));
}

char* cpdf_getModificationDate(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out);
  fn = *caml_named_value("getModificationDate");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out));
}

void cpdf_getDateComponents
(char* date,
 int* year,
 int* month,
 int* day,
 int* hour,
 int* minute,
 int* second,
 int* hour_offset,
 int* minute_offset)
{
  CAMLparam0 ();
  CAMLlocal5(fn, str_v, out_v, year_v, month_v);
  CAMLlocal5(day_v, hour_v, minute_v, second_v, hour_offset_v);
  CAMLlocal1(minute_offset_v);
  fn = *caml_named_value("getDateComponents");
  str_v = caml_copy_string(date);
  out_v = caml_callback(fn, str_v);
  updateLastError();
  year_v = Field(out_v, 0);
  month_v = Field(out_v, 1);
  day_v = Field(out_v, 2);
  hour_v = Field(out_v, 3);
  minute_v = Field(out_v, 4);
  second_v = Field(out_v, 5);
  hour_offset_v = Field(out_v, 6);
  minute_offset_v = Field(out_v, 7);
  *year = Int_val(year_v);
  *month = Int_val(month_v);
  *day = Int_val(day_v);
  *hour = Int_val(hour_v);
  *minute = Int_val(minute_v);
  *second = Int_val(second_v);
  *hour_offset = Int_val(hour_offset_v);
  *minute_offset = Int_val(minute_offset_v);
  CAMLreturn0;
}

char* cpdf_dateStringOfComponents(int year, int month, int day, int hour, int minute, int second, int hour_offset, int minute_offset)
{
  CAMLparam0 ();
  CAMLlocalN(args, 8);
  CAMLlocal2 (fn, string_out);
  args[0] = Val_int(year);
  args[1] = Val_int(month);
  args[2] = Val_int(day);
  args[3] = Val_int(hour);
  args[4] = Val_int(minute);
  args[5] = Val_int(second);
  args[6] = Val_int(hour_offset);
  args[7] = Val_int(minute_offset);
  fn = *caml_named_value("dateStringOfComponents");
  string_out = caml_callbackN(fn, 8, args);
  updateLastError();
  CAMLreturnT(char *, String_val(string_out));
}

int cpdf_hasBox(int pdf, int pagenumber, char* boxname)
{
  CAMLparam0 ();
  CAMLlocal4(fn, pdf_v, pagenumber_v, boxname_v);
  CAMLlocal1(out_v);
  fn = *caml_named_value("hasBox");
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  boxname_v = caml_copy_string(boxname);
  out_v = caml_callback3(fn, pdf_v, pagenumber_v, boxname_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v)); 
}

void cpdf_getMediaBox(int pdf, int pagenumber, double *minx, double* maxx, double* miny, double* maxy)
{
  CAMLparam0 ();
  CAMLlocal5(fn, pdf_v, pagenumber_v, tuple_v, minx_v);
  CAMLlocal3(maxx_v, miny_v, maxy_v);
  fn = *caml_named_value("getMediaBox");
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  tuple_v = caml_callback2(fn, pdf_v, pagenumber_v);
  updateLastError();
  minx_v = Field(tuple_v, 0);
  maxx_v = Field(tuple_v, 1);
  miny_v = Field(tuple_v, 2);
  maxy_v = Field(tuple_v, 3);
  *minx = Double_val(minx_v);
  *maxx = Double_val(maxx_v);
  *miny = Double_val(miny_v);
  *maxy = Double_val(maxy_v);
  CAMLreturn0;
}

void cpdf_setMediabox(int pdf, int range, double minx, double maxx, double miny, double maxy)
{
  CAMLparam0 ();
  CAMLlocalN (args, 6);
  CAMLlocal2 (unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("setMediabox");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_getCropBox(int pdf, int pagenumber, double *minx, double* maxx, double* miny, double* maxy)
{
  CAMLparam0 ();
  CAMLlocal5(fn, pdf_v, pagenumber_v, tuple_v, minx_v);
  CAMLlocal3(maxx_v, miny_v, maxy_v);
  fn = *caml_named_value("getCropBox");
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  tuple_v = caml_callback2(fn, pdf_v, pagenumber_v);
  updateLastError();
  minx_v = Field(tuple_v, 0);
  maxx_v = Field(tuple_v, 1);
  miny_v = Field(tuple_v, 2);
  maxy_v = Field(tuple_v, 3);
  *minx = Double_val(minx_v);
  *maxx = Double_val(maxx_v);
  *miny = Double_val(miny_v);
  *maxy = Double_val(maxy_v);
  CAMLreturn0;
}

void cpdf_setCropBox(int pdf, int range, double minx, double maxx, double miny, double maxy)
{
  CAMLparam0 ();
  CAMLlocal2(fn, out_v);
  CAMLlocalN(args, 6);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("setCropBox");
  out_v = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_getTrimBox(int pdf, int pagenumber, double *minx, double* maxx, double* miny, double* maxy)
{
  CAMLparam0 ();
  CAMLlocal5(fn, pdf_v, pagenumber_v, tuple_v, minx_v);
  CAMLlocal3(maxx_v, miny_v, maxy_v);
  fn = *caml_named_value("getTrimBox");
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  tuple_v = caml_callback2(fn, pdf_v, pagenumber_v);
  updateLastError();
  minx_v = Field(tuple_v, 0);
  maxx_v = Field(tuple_v, 1);
  miny_v = Field(tuple_v, 2);
  maxy_v = Field(tuple_v, 3);
  *minx = Double_val(minx_v);
  *maxx = Double_val(maxx_v);
  *miny = Double_val(miny_v);
  *maxy = Double_val(maxy_v);
  CAMLreturn0;
}

void cpdf_setTrimBox(int pdf, int range, double minx, double maxx, double miny, double maxy)
{
  CAMLparam0 ();
  CAMLlocal2(fn, out_v);
  CAMLlocalN(args, 6);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("setTrimBox");
  out_v = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_getArtBox(int pdf, int pagenumber, double *minx, double* maxx, double* miny, double* maxy)
{
  CAMLparam0 ();
  CAMLlocal5(fn, pdf_v, pagenumber_v, tuple_v, minx_v);
  CAMLlocal3(maxx_v, miny_v, maxy_v);
  fn = *caml_named_value("getArtBox");
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  tuple_v = caml_callback2(fn, pdf_v, pagenumber_v);
  updateLastError();
  minx_v = Field(tuple_v, 0);
  maxx_v = Field(tuple_v, 1);
  miny_v = Field(tuple_v, 2);
  maxy_v = Field(tuple_v, 3);
  *minx = Double_val(minx_v);
  *maxx = Double_val(maxx_v);
  *miny = Double_val(miny_v);
  *maxy = Double_val(maxy_v);
  CAMLreturn0;
}

void cpdf_setArtBox(int pdf, int range, double minx, double maxx, double miny, double maxy)
{
  CAMLparam0 ();
  CAMLlocal2(fn, out_v);
  CAMLlocalN(args, 6);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("setArtBox");
  out_v = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_getBleedBox(int pdf, int pagenumber, double *minx, double* maxx, double* miny, double* maxy)
{
  CAMLparam0 ();
  CAMLlocal5(fn, pdf_v, pagenumber_v, tuple_v, minx_v);
  CAMLlocal3(maxx_v, miny_v, maxy_v);
  fn = *caml_named_value("getBleedBox");
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  tuple_v = caml_callback2(fn, pdf_v, pagenumber_v);
  updateLastError();
  minx_v = Field(tuple_v, 0);
  maxx_v = Field(tuple_v, 1);
  miny_v = Field(tuple_v, 2);
  maxy_v = Field(tuple_v, 3);
  *minx = Double_val(minx_v);
  *maxx = Double_val(maxx_v);
  *miny = Double_val(miny_v);
  *maxy = Double_val(maxy_v);
  CAMLreturn0;
}

void cpdf_setBleedBox(int pdf, int range, double minx, double maxx, double miny, double maxy)
{
  CAMLparam0 ();
  CAMLlocal2(fn, out_v);
  CAMLlocalN(args, 6);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("setBleedBox");
  out_v = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_markTrapped(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(unit, fn, pdf_v);
  fn = *caml_named_value("markTrapped");
  pdf_v = Val_int(pdf);
  unit = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_markUntrapped(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(unit, fn, pdf_v);
  fn = *caml_named_value("markUntrapped");
  pdf_v = Val_int(pdf);
  unit = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setVersion(int pdf, int version)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, version_v);
  fn = *caml_named_value("setVersion");
  pdf_v = Val_int(pdf);
  version_v = Val_int(version);
  unit = caml_callback2(fn, pdf_v, version_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setTitle(int pdf, char* str)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, str_v);
  fn = *caml_named_value("setTitle");
  pdf_v = Val_int(pdf);
  str_v = caml_copy_string(str);
  unit = caml_callback2(fn, pdf_v, str_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setAuthor(int pdf, char* str)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, str_v);
  fn = *caml_named_value("setAuthor");
  pdf_v = Val_int(pdf);
  str_v = caml_copy_string(str);
  unit = caml_callback2(fn, pdf_v, str_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setSubject(int pdf, char* str)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, str_v);
  fn = *caml_named_value("setSubject");
  pdf_v = Val_int(pdf);
  str_v = caml_copy_string(str);
  unit = caml_callback2(fn, pdf_v, str_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setKeywords(int pdf, char* str)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, str_v);
  fn = *caml_named_value("setKeywords");
  pdf_v = Val_int(pdf);
  str_v = caml_copy_string(str);
  unit = caml_callback2(fn, pdf_v, str_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setCreator(int pdf, char* str)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, str_v);
  fn = *caml_named_value("setCreator");
  pdf_v = Val_int(pdf);
  str_v = caml_copy_string(str);
  unit = caml_callback2(fn, pdf_v, str_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setProducer(int pdf, char* str)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, str_v);
  fn = *caml_named_value("setProducer");
  pdf_v = Val_int(pdf);
  str_v = caml_copy_string(str);
  unit = caml_callback2(fn, pdf_v, str_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setCreationDate(int pdf, char* str)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, str_v);
  fn = *caml_named_value("setCreationDate");
  pdf_v = Val_int(pdf);
  str_v = caml_copy_string(str);
  unit = caml_callback2(fn, pdf_v, str_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setModificationDate(int pdf, char* str)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, str_v);
  fn = *caml_named_value("setModificationDate");
  pdf_v = Val_int(pdf);
  str_v = caml_copy_string(str);
  unit = caml_callback2(fn, pdf_v, str_v);
  updateLastError();
  CAMLreturn0;
}

enum cpdf_layout
  {cpdf_singlePage,
   cpdf_oneColumn,
   cpdf_twoColumnLeft,
   cpdf_twoColumnRight,
   cpdf_twoPageLeft,
   cpdf_twoPageRight};

void cpdf_setPageLayout(int pdf, enum cpdf_layout layout)
{
  CAMLparam0 ();
  CAMLlocal4(fn, unit, pdf_v, layout_v);
  fn = *caml_named_value("setPageLayout");
  pdf_v = Val_int(pdf);
  layout_v = Val_int(layout);
  unit = caml_callback2(fn, pdf_v, layout_v);
  updateLastError();
  CAMLreturn0;
}

enum cpdf_pageMode
  {cpdf_useNone,
   cpdf_useOutlines,
   cpdf_useThumbs,
   cpdf_useOC,
   cpdf_useAttachments};

void cpdf_setPageMode(int pdf, enum cpdf_pageMode mode)
{
  CAMLparam0 ();
  CAMLlocal4(fn, unit, pdf_v, mode_v);
  fn = *caml_named_value("setPageMode");
  pdf_v = Val_int(pdf);
  mode_v = Val_int(mode);
  unit = caml_callback2(fn, pdf_v, mode_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_hideToolbar(int pdf, int flag)
{
  CAMLparam0 ();
  CAMLlocal4(unit, pdf_v, flag_v, fn);
  fn = *caml_named_value("hideToolbar");
  pdf_v = Val_int(pdf);
  flag_v = Val_int(flag);
  unit = caml_callback2(fn, pdf_v, flag_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_hideMenubar(int pdf, int flag)
{
  CAMLparam0 ();
  CAMLlocal4(unit, pdf_v, flag_v, fn);
  fn = *caml_named_value("hideMenubar");
  pdf_v = Val_int(pdf);
  flag_v = Val_int(flag);
  unit = caml_callback2(fn, pdf_v, flag_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_hideWindowUi(int pdf, int flag)
{
  CAMLparam0 ();
  CAMLlocal4(unit, pdf_v, flag_v, fn);
  fn = *caml_named_value("hideWindowUi");
  pdf_v = Val_int(pdf);
  flag_v = Val_int(flag);
  unit = caml_callback2(fn, pdf_v, flag_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_fitWindow(int pdf, int flag)
{
  CAMLparam0 ();
  CAMLlocal4(unit, pdf_v, flag_v, fn);
  fn = *caml_named_value("fitWindow");
  pdf_v = Val_int(pdf);
  flag_v = Val_int(flag);
  unit = caml_callback2(fn, pdf_v, flag_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_centerWindow(int pdf, int flag)
{
  CAMLparam0 ();
  CAMLlocal4(unit, pdf_v, flag_v, fn);
  fn = *caml_named_value("centerWindow");
  pdf_v = Val_int(pdf);
  flag_v = Val_int(flag);
  unit = caml_callback2(fn, pdf_v, flag_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_displayDocTitle(int pdf, int flag)
{
  CAMLparam0 ();
  CAMLlocal4(unit, pdf_v, flag_v, fn);
  fn = *caml_named_value("displayDocTitle");
  pdf_v = Val_int(pdf);
  flag_v = Val_int(flag);
  unit = caml_callback2(fn, pdf_v, flag_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setMetadataFromFile(int pdf, char* filename)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, filename_v);
  fn = *caml_named_value("setMetadataFromFile");
  pdf_v = Val_int(pdf);
  filename_v = caml_copy_string(filename);
  unit = caml_callback2(fn, pdf_v, filename_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_setMetadataFromByteArray(int pdf, void* data, int len)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, bytestream, setMetadataFromByteArray, valpdf);
  bytestream = alloc_bigarray_dims(BIGARRAY_UINT8 | BIGARRAY_C_LAYOUT, 1, data, len);
  setMetadataFromByteArray = *caml_named_value("setMetadataFromByteArray");
  valpdf = Val_int(pdf);
  unit = caml_callback2(setMetadataFromByteArray, valpdf, bytestream); 
  updateLastError();
  CAMLreturn0;
}

void* cpdf_getMetadata(int pdf, int *retlen)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, bytestream, pdf_v);
  fn = *caml_named_value("getMetadata");
  pdf_v = Val_int(pdf);
  bytestream = caml_callback(fn, pdf_v);
  updateLastError();
  char* memory = NULL;
  int size = Bigarray_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) printf("getMetadata: failed");
  if (size > 0)
  {
    int x;
    char* indata = Data_bigarray_val(bytestream);
    for (x = 0; x < size; x++) { memory[x] = indata[x]; };
  }
  *retlen = size;
  CAMLreturnT(void*, memory);
}

void cpdf_removeMetadata(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (unit, fn, pdf_v);
  pdf_v = Val_int(pdf);
  fn = *caml_named_value("removeMetadata");
  unit = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 12. File Attachments */
void cpdf_attachFile(char* filename, int pdf)
{
  CAMLparam0 ();
  CAMLlocal4(unit, fn, filename_v, pdf_v);
  fn = *caml_named_value("attachFile");
  filename_v = caml_copy_string(filename);
  pdf_v = Val_int(pdf);
  unit = caml_callback2(fn, filename_v, pdf_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_attachFileToPage(char* filename, int pdf, int pagenumber)
{
  CAMLparam0 ();
  CAMLlocal5(unit, fn, filename_v, pdf_v, pagenumber_v);
  fn = *caml_named_value("attachFileToPage");
  filename_v = caml_copy_string(filename);
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  unit = caml_callback3(fn, filename_v, pdf_v, pagenumber_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_removeAttachedFiles(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(removeAttachedFiles, valpdf, unit);
  removeAttachedFiles = *caml_named_value("removeAttachedFiles");
  valpdf = Val_int(pdf);
  unit = caml_callback(removeAttachedFiles, valpdf);
  updateLastError();
  CAMLreturn0;
}

void cpdf_startGetAttachments (int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out_v);
  fn = *caml_named_value("startGetAttachments");
  pdf_v = Val_int(pdf);
  out_v = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturn0;
}

int cpdf_numberGetAttachments (void)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, unit_v, out_v);
  fn = *caml_named_value("numberGetAttachments");
  unit_v = Val_unit;
  out_v = caml_callback(fn, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

char* cpdf_getAttachmentName(int serial)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, serial_v, out_v);
  fn = *caml_named_value("getAttachmentName");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn, serial_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out_v));
}

void cpdf_endGetAttachments (void)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, unit_v, out_v);
  fn = *caml_named_value("endGetAttachments");
  unit_v = Val_unit;
  out_v = caml_callback(fn, unit_v);
  updateLastError();
  CAMLreturn0;
}


/* CHAPTER 13. Miscellaneous */
void cpdf_draft(int pdf, int range, int boxes)
{
  CAMLparam0 ();
  CAMLlocal5(unit, pdf_v, range_v, boxes_v, fn);
  fn = *caml_named_value("draft");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  boxes_v = Val_int(boxes);
  unit = caml_callback3(fn, pdf_v, range_v, boxes_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_blackText(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, range_v);
  fn = *caml_named_value("blackText");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_blackLines(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, range_v);
  fn = *caml_named_value("blackLines");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_blackFills(int pdf, int range)
{
  CAMLparam0 ();
  CAMLlocal4 (unit, fn, pdf_v, range_v);
  fn = *caml_named_value("blackFills");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  unit = caml_callback2(fn, pdf_v, range_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_thinLines(int pdf, int range, double minwidth)
{
  CAMLparam0 ();
  CAMLlocal5(unit, fn, pdf_v, range_v, minwidth_v);
  fn = *caml_named_value("thinLines");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  minwidth_v = caml_copy_double(minwidth);
  unit = caml_callback3(fn, pdf_v, range_v, minwidth_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_copyId(int pdf, int pdf2)
{
  CAMLparam0 ();
  CAMLlocal4(unit, fn, pdf_v, pdf2_v);
  fn = *caml_named_value("copyId");
  pdf_v = Val_int(pdf);
  pdf2_v = Val_int(pdf2);
  unit = caml_callback2(fn, pdf_v, pdf2_v);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 14. Page labels */

enum cpdf_pageLabelStyle
  {cpdf_decimalArabic,
   cpdf_uppercaseRoman,
   cpdf_lowercaseRoman,
   cpdf_uppercaseLetters,
   cpdf_lowercaseLetters};

void cpdf_addPageLabels
(int pdf,
 enum cpdf_pageLabelStyle style,
 char* prefix,
 int offset,
 int range
)
{
  CAMLparam0 ();
  CAMLlocal2(fn, out_v);
  fn = *caml_named_value("addPageLabels");
  CAMLlocalN(args, 5);
  args[0] = Val_int(pdf);
  args[1] = Val_int(style);
  args[2] = caml_copy_string(prefix);
  args[3] = Val_int(offset);
  args[4] = Val_int(range);
  out_v = caml_callbackN(fn, 5, args);
  updateLastError();
  CAMLreturn0;
}

/* Special functionality 1. Encryption and Permission status */

enum cpdf_pdfStatus
  {cpdf_notEncrypted,
   cpdf_encrypted,
   cpdf_wasDecryptedWithUser,
   cpdf_wasDecryptedWithOwner};

enum cpdf_pdfStatus cpdf_lookupPdfStatus(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3(fn, pdf_v, out);
  fn = *caml_named_value("lookupPdfStatus");
  pdf_v = Val_int(pdf);
  out = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}


int cpdf_hasPermissionStatus(int pdf, enum cpdf_permission tocheck)
{
  CAMLparam0 ();
  CAMLlocal4 (fn, pdf_v, tocheck_v, out_v);
  fn = *caml_named_value("hasPermissionStatus");
  pdf_v = Val_int(pdf);
  tocheck_v = Val_int(tocheck);
  out_v = caml_callback2(fn, pdf_v, tocheck_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_lookupPdfEncryption(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out_v);
  fn = *caml_named_value("lookupPdfEncryption");
  pdf_v = Val_int(pdf);
  out_v = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

char* cpdf_lookupPdfUserPassword(int pdf)
{
  CAMLparam0 ();
  CAMLlocal3 (fn, pdf_v, out_v);
  fn = *caml_named_value("lookupPdfUserPassword");
  pdf_v = Val_int(pdf);
  out_v = caml_callback(fn, pdf_v);
  updateLastError();
  CAMLreturnT(char*, String_val(out_v)); 
}

/* Special functionality 2. Undo */
int cpdf_undo(int i)
{
  CAMLparam0 ();
  CAMLlocal3(undo_v, int_v, out_v);
  undo_v = *caml_named_value("undo");
  int_v = Val_int(i);
  out_v = caml_callback(undo_v, int_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

int cpdf_redo(int i)
{
  CAMLparam0 ();
  CAMLlocal3(redo_v, int_v, out_v);
  redo_v = *caml_named_value("redo");
  int_v = Val_int(i);
  out_v = caml_callback(redo_v, int_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

void cpdf_aboutToUpdate(int i)
{
  CAMLparam0 ();
  CAMLlocal3(about_to_update_v, int_v, unit_v);
  about_to_update_v = *caml_named_value("aboutToUpdate");
  int_v = Val_int(i);
  unit_v = caml_callback(about_to_update_v, int_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_aboutToUpdateDeep(int i)
{
  CAMLparam0 ();
  CAMLlocal3(about_to_update_v, int_v, unit_v);
  about_to_update_v = *caml_named_value("aboutToUpdateDeep");
  int_v = Val_int(i);
  unit_v = caml_callback(about_to_update_v, int_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_abortUpdate(int i)
{
  CAMLparam0 ();
  CAMLlocal3(abort_update_v, int_v, unit_v);
  abort_update_v = *caml_named_value("abortUpdate");
  int_v = Val_int(i);
  unit_v = caml_callback(abort_update_v, int_v);
  updateLastError();
  CAMLreturn0;
}

int cpdf_squeeze(char* userpw, char* logfile, char* infile, char* outfile)
{
  CAMLparam0 ();
  CAMLlocal2 (fn, out);
  CAMLlocalN(args, 4);
  fn = *caml_named_value("squeeze");
  args[0] = caml_copy_string(userpw);
  args[1] = caml_copy_string(logfile);
  args[2] = caml_copy_string(infile);
  args[3] = caml_copy_string(outfile);
  out = caml_callbackN(fn, 4, args);
  updateLastError ();
  CAMLreturnT(int, Int_val(out));
}

int is_linearized(char* filename)
{
  CAMLparam0 ();
  CAMLlocal3 (filename_v, fn, out_v);
  filename_v = caml_copy_string(filename);
  fn = *caml_named_value("is_linearized");
  out_v = caml_callback(fn, filename_v);
  CAMLreturnT(int, Int_val(out_v));
}

