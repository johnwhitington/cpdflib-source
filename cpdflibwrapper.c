#include <caml/alloc.h>
#include <caml/bigarray.h>
#include <caml/callback.h>
#include <caml/memory.h>
#include <stdio.h>

enum cpdf_papersize {
  cpdf_a0portrait,
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
  cpdf_uslegallandscape
};

enum cpdf_permission {
  cpdf_noEdit,
  cpdf_noPrint,
  cpdf_noCopy,
  cpdf_noAnnot,
  cpdf_noForms,
  cpdf_noExtract,
  cpdf_noAssemble,
  cpdf_noHqPrint
};

enum cpdf_encryptionMethod {
  cpdf_pdf40bit,
  cpdf_pdf218bit,
  cpdf_aes128bitfalse,
  cpdf_aes128bittrue,
  cpdf_aes256bitfalse,
  cpdf_aes256bittrue,
  cpdf_aes256bitisofalse,
  cpdf_aes256bitisotrue
};

enum cpdf_anchor {
  cpdf_posCentre,
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
  cpdf_reversediagonal
};

struct cpdf_position {
  int cpdf_anchor;
  double cpdf_coord1;
  double cpdf_coord2;
};

enum cpdf_font {
  cpdf_timesRoman,
  cpdf_timesBold,
  cpdf_timesItalic,
  cpdf_timesBoldItalic,
  cpdf_helvetica,
  cpdf_helveticaBold,
  cpdf_helveticaOblique,
  cpdf_helveticaBoldOblique,
  cpdf_courier,
  cpdf_courierBold,
  cpdf_courierOblique,
  cpdf_courierBoldOblique
};

enum cpdf_justification {
  cpdf_leftJustify,
  cpdf_CentreJustify,
  cpdf_RightJustify
};

enum cpdf_pageLabelStyle {
  cpdf_decimalArabic,
  cpdf_uppercaseRoman,
  cpdf_lowercaseRoman,
  cpdf_uppercaseLetters,
  cpdf_lowercaseLetters
};

enum cpdf_layout {
  cpdf_singlePage,
  cpdf_oneColumn,
  cpdf_twoColumnLeft,
  cpdf_twoColumnRight,
  cpdf_twoPageLeft,
  cpdf_twoPageRight
};

enum cpdf_pageMode {
  cpdf_useNone,
  cpdf_useOutlines,
  cpdf_useThumbs,
  cpdf_useOC,
  cpdf_useAttachments
};

/* CHAPTER 0. Preliminaries */

void cpdf_startup(char **argv) {
  caml_startup(argv);
  return;
}

int cpdf_lastError = 0;
char *cpdf_lastErrorString = "";

/* For .NET and Java, which can't access data in DLLs, only functions. */
int cpdf_fLastError(void) { return cpdf_lastError; }

char *cpdf_fLastErrorString(void) { return cpdf_lastErrorString; }

/* For .NET, expose the C free function */
void cpdf_free(void *ptr) { free(ptr); }

/*
 * Get the latest error from OCaml and replicate it here in C. Also update
 * the lastErrorString, This function is not exposed in the interface
 */
void updateLastError(void) {
  CAMLparam0();
  CAMLlocal3(getLastError_v, unit_v, result_v);
  CAMLlocal2(getLastErrorString_v, string_result_v);
  getLastError_v = *caml_named_value("getLastError");
  unit_v = Val_unit;
  result_v = caml_callback(getLastError_v, unit_v);
  cpdf_lastError = Int_val(result_v);
  getLastErrorString_v = *caml_named_value("getLastErrorString");
  string_result_v = caml_callback(getLastErrorString_v, unit_v);
  cpdf_lastErrorString = (char *)String_val(string_result_v);
  CAMLreturn0;
}

char *cpdf_version() {
  CAMLparam0();
  CAMLlocal1(version);
  version = *caml_named_value("version");
  char *str = (char *)String_val(version);
  CAMLreturnT(char *, str);
}

void cpdf_clearError(void) {
  CAMLparam0();
  CAMLlocal3(clearError_v, unit_v, result_v);
  clearError_v = *caml_named_value("clearError");
  unit_v = Val_unit;
  result_v = caml_callback(clearError_v, unit_v);
  cpdf_lastError = 0;
  cpdf_lastErrorString = "";
  CAMLreturn0;
}

void cpdf_setFast() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("setFast");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setSlow() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("setSlow");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}
void cpdf_onExit() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("onExit");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 1. Basics */

int cpdf_fromFile(char *one, char *two) {
  CAMLparam0();
  CAMLlocal4(fn_v, one_v, two_v, result_v);
  fn_v = *caml_named_value("fromFile");
  one_v = caml_copy_string(one);
  two_v = caml_copy_string(two);
  result_v = caml_callback2(fn_v, one_v, two_v);
  updateLastError();
  CAMLreturnT(int, Int_val(result_v));
}
int cpdf_fromFileLazy(char *one, char *two) {
  CAMLparam0();
  CAMLlocal4(fn_v, one_v, two_v, result_v);
  fn_v = *caml_named_value("fromFileLazy");
  one_v = caml_copy_string(one);
  two_v = caml_copy_string(two);
  result_v = caml_callback2(fn_v, one_v, two_v);
  updateLastError();
  CAMLreturnT(int, Int_val(result_v));
}
int cpdf_fromMemory(void *data, int len, char *userpw) {
  CAMLparam0();
  CAMLlocal4(pdf_v, bytestream, fn, userpw_v);
  bytestream =
      caml_ba_alloc_dims(CAML_BA_UINT8 | CAML_BA_C_LAYOUT, 1, data, len);
  fn = *caml_named_value("fromMemory");
  userpw_v = caml_copy_string(userpw);
  pdf_v = caml_callback2(fn, bytestream, userpw_v);
  updateLastError();
  CAMLreturnT(int, Int_val(pdf_v));
}
int cpdf_fromMemoryLazy(void *data, int len, char *userpw) {
  CAMLparam0();
  CAMLlocal4(pdf_v, bytestream, fn, userpw_v);
  bytestream =
      caml_ba_alloc_dims(CAML_BA_UINT8 | CAML_BA_C_LAYOUT, 1, data, len);
  fn = *caml_named_value("fromMemoryLazy");
  userpw_v = caml_copy_string(userpw);
  pdf_v = caml_callback2(fn, bytestream, userpw_v);
  updateLastError();
  CAMLreturnT(int, Int_val(pdf_v));
}
void cpdf_deletePdf(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("deletePdf");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_replacePdf(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("replacePdf");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
int cpdf_startEnumeratePDFs(void) {
  CAMLparam0();
  CAMLlocal3(f_v, unit_v, int_v);
  f_v = *caml_named_value("startEnumeratePDFs");
  unit_v = Val_unit;
  int_v = caml_callback(f_v, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(int_v));
}
int cpdf_enumeratePDFsKey(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("enumeratePDFsKey");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
char *cpdf_enumeratePDFsInfo(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("enumeratePDFsInfo");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
void cpdf_endEnumeratePDFs() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("endEnumeratePDFs");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}
double cpdf_ptOfCm(double f) {
  CAMLparam0();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("ptOfCm");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}
double cpdf_ptOfMm(double f) {
  CAMLparam0();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("ptOfMm");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}
double cpdf_ptOfIn(double f) {
  CAMLparam0();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("ptOfIn");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}
double cpdf_cmOfPt(double f) {
  CAMLparam0();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("cmOfPt");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}
double cpdf_mmOfPt(double f) {
  CAMLparam0();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("mmOfPt");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}
double cpdf_inOfPt(double f) {
  CAMLparam0();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("inOfPt");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}
int cpdf_parsePagespec(int i, char *str) {
  CAMLparam0();
  CAMLlocal4(fn, ini, instr, out);
  fn = *caml_named_value("parsePagespec");
  ini = Val_int(i);
  instr = caml_copy_string(str);
  out = caml_callback2(fn, ini, instr);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}
int cpdf_validatePagespec(char *str) {
  CAMLparam0();
  CAMLlocal3(fn, instr, out);
  fn = *caml_named_value("validatePagespec");
  instr = caml_copy_string(str);
  out = caml_callback(fn, instr);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}
char *cpdf_stringOfPagespec(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, a_v, b_v, out);
  fn = *caml_named_value("stringOfPagespec");
  a_v = Val_int(a);
  b_v = Val_int(a);
  out = caml_callback2(fn, a_v, b_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out));
}
int cpdf_blankRange(void) {
  CAMLparam0();
  CAMLlocal3(f_v, unit_v, int_v);
  f_v = *caml_named_value("blankRange");
  unit_v = Val_unit;
  int_v = caml_callback(f_v, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(int_v));
}
void cpdf_deleteRange(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("deleteRange");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
int cpdf_range(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("range");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_all(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("all");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_even(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("even");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_odd(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("odd");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_rangeUnion(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("rangeUnion");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_difference(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("difference");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_removeDuplicates(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("removeDuplicates");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_rangeLength(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("rangeLength");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_rangeGet(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("rangeGet");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_rangeAdd(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("rangeAdd");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_isInRange(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("isInRange");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_pages(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("pages");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_pagesFast(char *one, char *two) {
  CAMLparam0();
  CAMLlocal4(fn_v, one_v, two_v, result_v);
  fn_v = *caml_named_value("pagesFast");
  one_v = caml_copy_string(one);
  two_v = caml_copy_string(two);
  result_v = caml_callback2(fn_v, one_v, two_v);
  updateLastError();
  CAMLreturnT(int, Int_val(result_v));
}

void cpdf_toFile(int pdf, char *filename, int linearize, int make_id) {
  CAMLparam0();
  CAMLlocal2(fn, unit);
  CAMLlocalN(args, 4);
  args[0] = Val_int(pdf);
  args[1] = caml_copy_string(filename);
  args[2] = Val_int(linearize);
  args[3] = Val_int(make_id);
  fn = *caml_named_value("toFile");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_toFileExt(int pdf, char *filename, int linearize, int make_id,
                    int preserve_objstm, int create_objstm,
                    int compress_objstm) {
  CAMLparam0();
  CAMLlocal2(fn, unit);
  CAMLlocalN(args, 7);
  fn = *caml_named_value("toFileExt");
  args[0] = Val_int(pdf);
  args[1] = caml_copy_string(filename);
  args[2] = Val_int(linearize);
  args[3] = Val_int(make_id);
  args[4] = Val_bool(preserve_objstm);
  args[5] = Val_bool(create_objstm);
  args[6] = Val_bool(compress_objstm);
  unit = caml_callbackN(fn, 7, args);
  updateLastError();
  CAMLreturn0;
}

void *cpdf_toMemory(int pdf, int linearize, int make_id, int *retlen) {
  CAMLparam0();
  CAMLlocal5(fn, bytestream, pdf_v, linearize_v, make_id_v);
  fn = *caml_named_value("toFileMemory");
  pdf_v = Val_int(pdf);
  linearize_v = Val_bool(linearize);
  make_id_v = Val_bool(make_id);
  bytestream = caml_callback3(fn, pdf_v, linearize_v, make_id_v);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "toMemory: failed");
  if (size > 0) {
    int x;
    char *indata = Caml_ba_data_val(bytestream);
    for (x = 0; x < size; x++) {
      memory[x] = indata[x];
    };
  }
  *retlen = size;
  CAMLreturnT(void *, memory);
}

int cpdf_isEncrypted(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("isEncrypted");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
void cpdf_decryptPdf(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("decryptPdf");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_decryptPdfOwner(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("decryptPdfOwner");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_toFileEncrypted(int pdf, int e, int *ps, int len, char *owner,
                          char *user, int linearize, int makeid,
                          char *filename) {
  CAMLparam0();
  CAMLlocal4(unit, fn, temp, permissions);
  CAMLlocalN(args, 8);
  permissions = caml_alloc(len, 0);
  int x;
  for (x = 0; x < len; x++) {
    temp = Val_int(ps[x]);
    Store_field(permissions, x, temp);
  };
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
  CAMLreturn0;
}

/* FIXME: Extend for recrypting at some point? */
void cpdf_toFileEncryptedExt(int pdf, int e, int *ps, int len, char *owner,
                             char *user, int linearize, int makeid,
                             int preserve_objstm, int generate_objstm,
                             int compress_objstm, char *filename) {
  CAMLparam0();
  CAMLlocal4(unit, fn, temp, permissions);
  CAMLlocalN(args, 11);
  permissions = caml_alloc(len, 0);
  int x;
  for (x = 0; x < len; x++) {
    temp = Val_int(ps[x]);
    Store_field(permissions, x, temp);
  };
  args[0] = Val_int(pdf);
  args[1] = Val_int(e);
  args[2] = permissions;
  args[3] = caml_copy_string(owner);
  args[4] = caml_copy_string(user);
  args[5] = Val_int(linearize);
  args[6] = Val_int(makeid);
  args[7] = Val_bool(preserve_objstm);
  args[8] = Val_bool(generate_objstm);
  args[9] = Val_bool(compress_objstm);
  args[10] = caml_copy_string(filename);
  fn = *caml_named_value("toFileEncryptedExt");
  unit = caml_callbackN(fn, 11, args);
  updateLastError();
  CAMLreturn0;
}

int cpdf_hasPermission(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("hasPermission");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_encryptionKind(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("encryptionKind");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

/* CHAPTER 2. Merging and Splitting */

int cpdf_mergeSimple(int *pdfs, int len) {
  CAMLparam0();
  CAMLlocal4(fn, array, temp, out);
  array = caml_alloc(len, 0);
  int x;
  for (x = 0; x < len; x++) {
    temp = Val_int(pdfs[x]);
    Store_field(array, x, temp);
  };
  fn = *caml_named_value("mergeSimple");
  out = caml_callback(fn, array);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

int cpdf_merge(int *pdfs, int len, int retain_numbering,
               int remove_duplicate_fonts) {
  CAMLparam0();
  CAMLlocal5(fn, array, temp, len_v, retain_numbering_v);
  CAMLlocal2(remove_duplicate_fonts_v, out);
  array = caml_alloc(len, 0);
  int x;
  for (x = 0; x < len; x++) {
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

int cpdf_mergeSame(int *pdfs, int len, int retain_numbering,
                   int remove_duplicate_fonts, int *ranges) {
  CAMLparam0();
  CAMLlocal3(array, rangearray, fn);
  CAMLlocal2(temp, out);
  CAMLlocalN(args, 4);
  array = caml_alloc(len, 0);
  rangearray = caml_alloc(len, 0);
  int x;
  for (x = 0; x < len; x++) {
    temp = Val_int(pdfs[x]);
    Store_field(array, x, temp);
  };
  for (x = 0; x < len; x++) {
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

int cpdf_selectPages(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("selectPages");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

/* CHAPTER 3. Pages */

void cpdf_scalePages(int pdf, int range, double sx, double sy) {
  CAMLparam0();
  CAMLlocal2(fn, unit);
  CAMLlocalN(args, 4);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(sx);
  args[3] = caml_copy_double(sy);
  fn = *caml_named_value("scalePages");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}
void cpdf_scaleToFit(int pdf, int range, double w, double h, double scale) {
  CAMLparam0();
  CAMLlocalN(args, 5);
  CAMLlocal2(fn, unit);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(w);
  args[3] = caml_copy_double(h);
  args[4] = caml_copy_double(scale);
  fn = *caml_named_value("scaleToFit");
  unit = caml_callbackN(fn, 5, args);
  updateLastError();
  CAMLreturn0;
}
void cpdf_scaleToFitPaper(int pdf, int range, int papersize, double scale) {
  CAMLparam0();
  CAMLlocalN(args, 4);
  CAMLlocal2(unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = Val_int(papersize);
  args[3] = caml_copy_double(scale);
  fn = *caml_named_value("scaleToFitPaper");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_scaleContents(int pdf, int range, struct cpdf_position pos,
                        double scale) {
  CAMLparam0();
  CAMLlocalN(args, 6);
  CAMLlocal3(unit, camlpos, fn);
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

void cpdf_shiftContents(int pdf, int range, double sx, double sy) {
  CAMLparam0();
  CAMLlocal2(fn, unit);
  CAMLlocalN(args, 4);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(sx);
  args[3] = caml_copy_double(sy);
  fn = *caml_named_value("shiftContents");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}
void cpdf_rotate(int pdf, int range, int angle) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("rotate");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_rotateBy(int pdf, int range, int angle) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("rotateBy");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_rotateContents(int pdf, int range, double minwidth) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, minwidth_v);
  fn = *caml_named_value("rotateContents");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  minwidth_v = caml_copy_double(minwidth);
  unit = caml_callback3(fn, pdf_v, range_v, minwidth_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_upright(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("upright");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_hFlip(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("hFlip");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_vFlip(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("vFlip");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_crop(int pdf, int range, double minx, double maxx, double miny,
                      double maxy) {
  CAMLparam0();
  CAMLlocalN(args, 6);
  CAMLlocal2(unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("crop");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removeCrop(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("removeCrop");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removeTrim(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("removeTrim");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removeArt(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("removeArt");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removeBleed(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("removeBleed");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_trimMarks(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("trimMarks");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_showBoxes(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("showBoxes");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_hardBox(int pdf, int range, char *box) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, box_v);
  fn = *caml_named_value("hardBox");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  box_v = caml_copy_string(box);
  unit = caml_callback3(fn, pdf_v, range_v, box_v);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 5. Compression */

void cpdf_compress(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("compress");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_decompress(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("decompress");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_squeezeInMemory(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("squeezeInMemory");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 6. Bookmarks */

int cpdf_startGetBookmarkInfo(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("startGetBookmarkInfo");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_numberBookmarks(void) {
  CAMLparam0();
  CAMLlocal3(f_v, unit_v, int_v);
  f_v = *caml_named_value("numberBookmarks");
  unit_v = Val_unit;
  int_v = caml_callback(f_v, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(int_v));
}
int cpdf_getBookmarkLevel(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getBookmarkLevel");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_getBookmarkPage(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("getBookmarkPage");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
char *cpdf_getBookmarkText(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getBookmarkText");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
int cpdf_getBookmarkOpenStatus(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getBookmarkOpenStatus");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
void cpdf_endGetBookmarkInfo() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("endGetBookmarkInfo");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}
void cpdf_startSetBookmarkInfo(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("startSetBookmarkInfo");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setBookmarkLevel(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("setBookmarkLevel");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setBookmarkPage(int pdf, int range, int angle) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("setBookmarkPage");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setBookmarkOpenStatus(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("setBookmarkOpenStatus");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setBookmarkText(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setBookmarkText");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_endSetBookmarkInfo(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("endSetBookmarkInfo");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void *cpdf_getBookmarksJSON(int pdf, int *retlen) {
  CAMLparam0();
  CAMLlocal3(fn, bytestream, pdf_v);
  fn = *caml_named_value("getBookmarksJSON");
  pdf_v = Val_int(pdf);
  bytestream = caml_callback(fn, pdf_v);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "getBookmarksJSON: failed");
  if (size > 0) {
    int x;
    char *indata = Caml_ba_data_val(bytestream);
    for (x = 0; x < size; x++) {
      memory[x] = indata[x];
    };
  }
  *retlen = size;
  CAMLreturnT(void *, memory);
}
void cpdf_setBookmarksJSON(int pdf, void *data, int len) {
  CAMLparam0();
  CAMLlocal4(unit, bytestream, fn, valpdf);
  bytestream =
      caml_ba_alloc_dims(CAML_BA_UINT8 | CAML_BA_C_LAYOUT, 1, data, len);
  fn = *caml_named_value("setBookmarksJSON");
  valpdf = Val_int(pdf);
  unit = caml_callback2(fn, valpdf, bytestream);
  updateLastError();
  CAMLreturn0;
}
void cpdf_tableOfContents(int pdf, int font, double fontsize, char *title,
                          int bookmark) {
  CAMLparam0();
  CAMLlocalN(args, 5);
  args[0] = Val_int(pdf);
  args[1] = Val_int(font);
  args[2] = caml_copy_double(fontsize);
  args[3] = caml_copy_string(title);
  args[4] = Val_int(bookmark);
  CAMLlocal2(fn_v, out_v);
  fn_v = *caml_named_value("tableOfContents");
  out_v = caml_callbackN(fn_v, 5, args);
  CAMLreturn0;
}

/* CHAPTER 7. Presentations */

/* Not included in the library version */

/* CHAPTER 8. Logos, Watermarks and Stamps */

void cpdf_stampOn(int pdf, int range, int angle) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("stampOn");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_stampUnder(int pdf, int range, int angle) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("stampUnder");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_stampExtended(int pdf, int pdf2, int range, int isover,
                        int scale_stamp_to_fit, struct cpdf_position pos,
                        int relative_to_cropbox) {
  CAMLparam0();
  CAMLlocal2(fn, unit);
  CAMLlocalN(args, 9);
  fn = *caml_named_value("stampExtended");
  args[0] = Val_int(pdf);
  args[1] = Val_int(pdf2);
  args[2] = Val_int(range);
  args[3] = Val_int(isover);
  args[4] = Val_int(scale_stamp_to_fit);
  args[5] = caml_copy_double(pos.cpdf_coord1);
  args[6] = caml_copy_double(pos.cpdf_coord2);
  args[7] = Val_int(pos.cpdf_anchor);
  args[8] = Val_int(relative_to_cropbox);
  unit = caml_callbackN(fn, 9, args);
  updateLastError();
  CAMLreturn0;
}

int cpdf_combinePages(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("combinePages");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}

void cpdf_addText(int metrics, int pdf, int range, char *text,
                  struct cpdf_position pos, double linespacing, int bates,
                  enum cpdf_font font, double fontsize, double r, double g,
                  double b, int underneath, int cropbox, int outline,
                  double opacity, enum cpdf_justification justification,
                  int midline, int topline, char *filename, double linewidth,
                  int embed_fonts) {
  CAMLparam0();
  CAMLlocal2(fn, unit);
  CAMLlocalN(args, 24);
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
  args[20] = Val_int(topline);
  args[21] = caml_copy_string(filename);
  args[22] = caml_copy_double(linewidth);
  args[23] = Val_int(embed_fonts);
  unit = caml_callbackN(fn, 24, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_addTextSimple(int pdf, int range, char *text,
                        struct cpdf_position pos, enum cpdf_font font,
                        double fontsize) {
  CAMLparam0();
  char s[] = "";
  cpdf_addText(0,
               /* Do not collect metrics, but add text */
               pdf, range, text, pos, 1.0,
               /* Normal line spacing */
               0,
               /* Starting bates number */
               font, fontsize, 0,
               /* r = 0 */
               0,
               /* g = 0 */
               0,
               /* b = 0 */
               0,
               /* Text not underneath */
               0,
               /* Text not relative to crop box */
               0,
               /* Text not outlined */
               1.0,
               /* Opaque */
               cpdf_leftJustify, 0,
               /* baseline not midline */
               0,
               /* baseline not topline */
               s,
               /* file name */
               0.0,
               /* line width */
               0
               /* don't embed fonts */
  );
  CAMLreturn0;
}

int cpdf_removeText(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("removeText");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_textWidth(int i, char *str) {
  CAMLparam0();
  CAMLlocal4(fn, ini, instr, out);
  fn = *caml_named_value("textWidth");
  ini = Val_int(i);
  instr = caml_copy_string(str);
  out = caml_callback2(fn, ini, instr);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}
void cpdf_addContent(char *s, int before, int pdf, int range) {
  CAMLparam0();
  CAMLlocal2(fn, out);
  CAMLlocalN(args, 4);
  args[0] = caml_copy_string(s);
  args[1] = Val_int(before);
  args[2] = Val_int(pdf);
  args[3] = Val_int(range);
  fn = *caml_named_value("addContent");
  out = caml_callbackN(fn, 4, args);
  CAMLreturn0;
}
char *cpdf_stampAsXObject(int pdf, int range, int stamp_pdf) {
  CAMLparam0();
  CAMLlocal5(pdf_v, range_v, stamp_pdf_v, fn, name_v);
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  stamp_pdf_v = Val_int(stamp_pdf);
  fn = *caml_named_value("stampAsXObject");
  name_v = caml_callback3(fn, pdf_v, range_v, stamp_pdf_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(name_v));
}

/* CHAPTER 9. Multipage facilities */

void cpdf_impose(int pdf, double x, double y, int fit, int columns, int rtl,
                 int btt, int center, double margin, double spacing,
                 double linewidth) {
  CAMLparam0();
  CAMLlocalN(args, 11);
  args[0] = Val_int(pdf);
  args[1] = caml_copy_double(x);
  args[2] = caml_copy_double(y);
  args[3] = Val_bool(fit);
  args[4] = Val_bool(columns);
  args[5] = Val_bool(rtl);
  args[6] = Val_bool(btt);
  args[7] = Val_bool(center);
  args[8] = caml_copy_double(margin);
  args[9] = caml_copy_double(spacing);
  args[10] = caml_copy_double(linewidth);
  CAMLlocal2(fn, out_v);
  fn = *caml_named_value("impose");
  out_v = caml_callbackN(fn, 11, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_twoUp(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("twoUp");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_twoUpStack(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("twoUpStack");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_padBefore(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("padBefore");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_padAfter(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("padAfter");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_padEvery(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("padEvery");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_padMultiple(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("padMultiple");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_padMultipleBefore(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("padMultipleBefore");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 10. Annotations */
void *cpdf_annotationsJSON(int pdf, int *retlen) {
  CAMLparam0();
  CAMLlocal3(fn, bytestream, pdf_v);
  fn = *caml_named_value("annotationsJSON");
  pdf_v = Val_int(pdf);
  bytestream = caml_callback(fn, pdf_v);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "annotationsJSON: failed");
  if (size > 0) {
    int x;
    char *indata = Caml_ba_data_val(bytestream);
    for (x = 0; x < size; x++) {
      memory[x] = indata[x];
    };
  }
  *retlen = size;
  CAMLreturnT(void *, memory);
}

/* CHAPTER 11. Document Information and Metadata */

int cpdf_isLinearized(char *str) {
  CAMLparam0();
  CAMLlocal3(fn, instr, out);
  fn = *caml_named_value("isLinearized");
  instr = caml_copy_string(str);
  out = caml_callback(fn, instr);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}
int cpdf_getVersion(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getVersion");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_getMajorVersion(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getMajorVersion");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
char *cpdf_getTitle(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getTitle");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getAuthor(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getAuthor");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getSubject(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getSubject");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getKeywords(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getKeywords");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getCreator(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getCreator");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getProducer(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getProducer");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getCreationDate(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getCreationDate");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getModificationDate(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getModificationDate");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getTitleXMP(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getTitleXMP");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getAuthorXMP(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getAuthorXMP");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getSubjectXMP(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getSubjectXMP");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getKeywordsXMP(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getKeywordsXMP");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getCreatorXMP(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getCreatorXMP");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getProducerXMP(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getProducerXMP");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getCreationDateXMP(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getCreationDateXMP");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getModificationDateXMP(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getModificationDateXMP");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
void cpdf_setTitle(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setTitle");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setAuthor(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setAuthor");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setSubject(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setSubject");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setKeywords(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setKeywords");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setCreator(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setCreator");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setProducer(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setProducer");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setCreationDate(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setCreationDate");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setModificationDate(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setModificationDate");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setTitleXMP(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setTitleXMP");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setAuthorXMP(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setAuthorXMP");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setSubjectXMP(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setSubjectXMP");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setKeywordsXMP(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setKeywordsXMP");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setCreatorXMP(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setCreatorXMP");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setProducerXMP(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setProducerXMP");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setCreationDateXMP(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setCreationDateXMP");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setModificationDateXMP(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setModificationDateXMP");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_getDateComponents(char *date, int *year, int *month, int *day,
                            int *hour, int *minute, int *second,
                            int *hour_offset, int *minute_offset) {
  CAMLparam0();
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

char *cpdf_dateStringOfComponents(int year, int month, int day, int hour,
                                  int minute, int second, int hour_offset,
                                  int minute_offset) {
  CAMLparam0();
  CAMLlocalN(args, 8);
  CAMLlocal2(fn, string_out);
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
  CAMLreturnT(char *, (char *)String_val(string_out));
}

int cpdf_getPageRotation(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("getPageRotation");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_hasBox(int pdf, int pagenumber, char *boxname) {
  CAMLparam0();
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
void cpdf_getMediaBox(int pdf, int pagenumber, double *minx, double *maxx,
                      double *miny, double *maxy) {
  CAMLparam0();
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
void cpdf_getCropBox(int pdf, int pagenumber, double *minx, double *maxx,
                      double *miny, double *maxy) {
  CAMLparam0();
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
void cpdf_getTrimBox(int pdf, int pagenumber, double *minx, double *maxx,
                      double *miny, double *maxy) {
  CAMLparam0();
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
void cpdf_getArtBox(int pdf, int pagenumber, double *minx, double *maxx,
                      double *miny, double *maxy) {
  CAMLparam0();
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
void cpdf_getBleedBox(int pdf, int pagenumber, double *minx, double *maxx,
                      double *miny, double *maxy) {
  CAMLparam0();
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
void cpdf_setMediabox(int pdf, int range, double minx, double maxx, double miny,
                      double maxy) {
  CAMLparam0();
  CAMLlocalN(args, 6);
  CAMLlocal2(unit, fn);
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
void cpdf_setCropBox(int pdf, int range, double minx, double maxx, double miny,
                      double maxy) {
  CAMLparam0();
  CAMLlocalN(args, 6);
  CAMLlocal2(unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("setCropBox");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setTrimBox(int pdf, int range, double minx, double maxx, double miny,
                      double maxy) {
  CAMLparam0();
  CAMLlocalN(args, 6);
  CAMLlocal2(unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("setTrimBox");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setArtBox(int pdf, int range, double minx, double maxx, double miny,
                      double maxy) {
  CAMLparam0();
  CAMLlocalN(args, 6);
  CAMLlocal2(unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("setArtBox");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setBleedBox(int pdf, int range, double minx, double maxx, double miny,
                      double maxy) {
  CAMLparam0();
  CAMLlocalN(args, 6);
  CAMLlocal2(unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(minx);
  args[3] = caml_copy_double(maxx);
  args[4] = caml_copy_double(miny);
  args[5] = caml_copy_double(maxy);
  fn = *caml_named_value("setBleedBox");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}
void cpdf_markTrapped(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("markTrapped");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_markUntrapped(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("markUntrapped");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_markTrappedXMP(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("markTrappedXMP");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_markUntrappedXMP(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("markUntrappedXMP");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setPageLayout(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("setPageLayout");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setPageMode(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("setPageMode");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_hideToolbar(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("hideToolbar");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_hideMenubar(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("hideMenubar");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_hideWindowUi(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("hideWindowUi");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_fitWindow(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("fitWindow");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_centerWindow(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("centerWindow");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_displayDocTitle(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("displayDocTitle");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_openAtPage(int pdf, int range, int angle) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("openAtPage");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setMetadataFromFile(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setMetadataFromFile");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setMetadataFromByteArray(int pdf, void *data, int len) {
  CAMLparam0();
  CAMLlocal4(unit, bytestream, fn, valpdf);
  bytestream =
      caml_ba_alloc_dims(CAML_BA_UINT8 | CAML_BA_C_LAYOUT, 1, data, len);
  fn = *caml_named_value("setMetadataFromByteArray");
  valpdf = Val_int(pdf);
  unit = caml_callback2(fn, valpdf, bytestream);
  updateLastError();
  CAMLreturn0;
}
void *cpdf_getMetadata(int pdf, int *retlen) {
  CAMLparam0();
  CAMLlocal3(fn, bytestream, pdf_v);
  fn = *caml_named_value("getMetadata");
  pdf_v = Val_int(pdf);
  bytestream = caml_callback(fn, pdf_v);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "getMetadata: failed");
  if (size > 0) {
    int x;
    char *indata = Caml_ba_data_val(bytestream);
    for (x = 0; x < size; x++) {
      memory[x] = indata[x];
    };
  }
  *retlen = size;
  CAMLreturnT(void *, memory);
}
void cpdf_removeMetadata(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("removeMetadata");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_createMetadata(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("createMetadata");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setMetadataDate(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("setMetadataDate");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_addPageLabels(int pdf, enum cpdf_pageLabelStyle style, char *prefix,
                        int offset, int range, int progress) {
  CAMLparam0();
  CAMLlocal2(fn, out_v);
  fn = *caml_named_value("addPageLabels");
  CAMLlocalN(args, 6);
  args[0] = Val_int(pdf);
  args[1] = Val_int(style);
  args[2] = caml_copy_string(prefix);
  args[3] = Val_int(offset);
  args[4] = Val_int(range);
  args[5] = Val_int(progress);
  out_v = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removePageLabels(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("removePageLabels");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
int cpdf_startGetPageLabels(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("startGetPageLabels");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
void cpdf_endGetPageLabels() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("endGetPageLabels");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}
int cpdf_getPageLabelOffset(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getPageLabelOffset");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_getPageLabelStyle(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getPageLabelStyle");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_getPageLabelRange(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getPageLabelRange");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
char *cpdf_getPageLabelPrefix(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getPageLabelPrefix");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getPageLabelStringForPage(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, a_v, b_v, out);
  fn = *caml_named_value("getPageLabelStringForPage");
  a_v = Val_int(a);
  b_v = Val_int(a);
  out = caml_callback2(fn, a_v, b_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out));
}

/* CHAPTER 12. File Attachments */

void cpdf_attachFile(char *filename, int pdf) {
  CAMLparam0();
  CAMLlocal4(unit, fn, filename_v, pdf_v);
  fn = *caml_named_value("attachFile");
  filename_v = caml_copy_string(filename);
  pdf_v = Val_int(pdf);
  unit = caml_callback2(fn, filename_v, pdf_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_attachFileToPage(char *filename, int pdf, int pagenumber) {
  CAMLparam0();
  CAMLlocal5(unit, fn, filename_v, pdf_v, pagenumber_v);
  fn = *caml_named_value("attachFileToPage");
  filename_v = caml_copy_string(filename);
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  unit = caml_callback3(fn, filename_v, pdf_v, pagenumber_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_attachFileFromMemory(void *data, int length, char *filename,
                               int pdf) {
  CAMLparam0();
  CAMLlocal5(unit_v, fn, filename_v, bytestream_v, pdf_v);
  fn = *caml_named_value("attachFileFromMemory");
  bytestream_v =
      caml_ba_alloc_dims(CAML_BA_UINT8 | CAML_BA_C_LAYOUT, 1, data, length);
  filename_v = caml_copy_string(filename);
  pdf_v = Val_int(pdf);
  unit_v = caml_callback3(fn, bytestream_v, filename_v, pdf_v);
  updateLastError();
  CAMLreturn0;
}

void cpdf_attachFileToPageFromMemory(void *data, int length, char *filename,
                                     int pdf, int page) {
  CAMLparam0();
  CAMLlocal3(unit_v, fn, filename_v);
  CAMLlocal3(bytestream_v, pdf_v, page_v);
  CAMLlocalN(args, 4);
  fn = *caml_named_value("attachFileToPageFromMemory");
  args[0] = bytestream_v =
      caml_ba_alloc_dims(CAML_BA_UINT8 | CAML_BA_C_LAYOUT, 1, data, length);
  args[1] = filename_v = caml_copy_string(filename);
  args[2] = Val_int(pdf);
  args[3] = Val_int(page);
  unit_v = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}

void cpdf_removeAttachedFiles(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("removeAttachedFiles");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_startGetAttachments(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("startGetAttachments");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
int cpdf_numberGetAttachments(void) {
  CAMLparam0();
  CAMLlocal3(f_v, unit_v, int_v);
  f_v = *caml_named_value("numberGetAttachments");
  unit_v = Val_unit;
  int_v = caml_callback(f_v, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(int_v));
}
char *cpdf_getAttachmentName(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getAttachmentName");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
int cpdf_getAttachmentPage(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getAttachmentPage");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
void *cpdf_getAttachmentData(int pdf, int *retlen) {
  CAMLparam0();
  CAMLlocal3(fn, bytestream, pdf_v);
  fn = *caml_named_value("getAttachmentData");
  pdf_v = Val_int(pdf);
  bytestream = caml_callback(fn, pdf_v);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "getAttachmentData: failed");
  if (size > 0) {
    int x;
    char *indata = Caml_ba_data_val(bytestream);
    for (x = 0; x < size; x++) {
      memory[x] = indata[x];
    };
  }
  *retlen = size;
  CAMLreturnT(void *, memory);
}
void cpdf_endGetAttachments() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("endGetAttachments");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 13. Images */

int cpdf_startGetImageResolution(int pdf, double res) {
  CAMLparam0();
  CAMLlocal4(fn, pdf_v, out_v, res_v);
  fn = *caml_named_value("startGetImageResolution");
  pdf_v = Val_int(pdf);
  res_v = caml_copy_double(res);
  out_v = caml_callback2(fn, pdf_v, res_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_getImageResolutionPageNumber(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getImageResolutionPageNumber");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
char *cpdf_getImageResolutionImageName(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getImageResolutionImageName");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
int cpdf_getImageResolutionXPixels(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getImageResolutionXPixels");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_getImageResolutionYPixels(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getImageResolutionYPixels");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
double cpdf_getImageResolutionXRes(int serial) {
  CAMLparam0();
  CAMLlocal3(fn, serial_v, out_v);
  fn = *caml_named_value("getImageResolutionXRes");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn, serial_v);
  updateLastError();
  CAMLreturnT(int, Double_val(out_v));
}
double cpdf_getImageResolutionYRes(int serial) {
  CAMLparam0();
  CAMLlocal3(fn, serial_v, out_v);
  fn = *caml_named_value("getImageResolutionYRes");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn, serial_v);
  updateLastError();
  CAMLreturnT(int, Double_val(out_v));
}
void cpdf_endGetImageResolution() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("endGetImageResolution");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 14. Fonts */

void cpdf_startGetFontInfo(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("startGetFontInfo");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
int cpdf_numberFonts(void) {
  CAMLparam0();
  CAMLlocal3(f_v, unit_v, int_v);
  f_v = *caml_named_value("numberFonts");
  unit_v = Val_unit;
  int_v = caml_callback(f_v, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(int_v));
}
int cpdf_getFontPage(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("getFontPage");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
char *cpdf_getFontName(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getFontName");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getFontType(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getFontType");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
char *cpdf_getFontEncoding(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("getFontEncoding");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
void cpdf_endGetFontInfo() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("endGetFontInfo");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removeFonts(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("removeFonts");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_copyFont(int from_pdf, int to_pdf, int range, int pagenumber,
                   char *fontname) {
  CAMLparam0();
  CAMLlocal2(fn_v, out_v);
  fn_v = *caml_named_value("copyFont");
  CAMLlocalN(args, 5);
  args[0] = Val_int(from_pdf);
  args[1] = Val_int(to_pdf);
  args[2] = Val_int(range);
  args[3] = Val_int(pagenumber);
  args[4] = caml_copy_string(fontname);
  out_v = caml_callbackN(fn_v, 5, args);
  updateLastError();
  CAMLreturn0;
}

/* CHAPTER 15. PDF and JSON */

void cpdf_outputJSON(char *filename, int parse_content, int no_stream_data,
                     int decompress_streams, int pdf) {
  CAMLparam0();
  CAMLlocal2(fn, out);
  CAMLlocalN(args, 5);
  args[0] = caml_copy_string(filename);
  args[1] = Val_int(parse_content);
  args[2] = Val_int(no_stream_data);
  args[3] = Val_int(decompress_streams);
  args[4] = Val_int(pdf);
  fn = *caml_named_value("outputJSON");
  out = caml_callbackN(fn, 5, args);
  CAMLreturn0;
}

void *cpdf_outputJSONMemory(int pdf, int parse_content, int no_stream_data,
                            int decompress_streams, int *retlen) {
  CAMLparam0();
  CAMLlocal2(fn, bytestream);
  CAMLlocalN(args, 4);
  args[0] = Val_int(parse_content);
  args[1] = Val_int(no_stream_data);
  args[2] = Val_int(decompress_streams);
  args[3] = Val_int(pdf);
  fn = *caml_named_value("outputJSONMemory");
  bytestream = caml_callbackN(fn, 4, args);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "outputJSONMemory: failed");
  if (size > 0) {
    int x;
    char *indata = Caml_ba_data_val(bytestream);
    for (x = 0; x < size; x++) {
      memory[x] = indata[x];
    };
  }
  *retlen = size;
  CAMLreturnT(void *, memory);
}

int cpdf_fromJSON(char *str) {
  CAMLparam0();
  CAMLlocal3(fn, instr, out);
  fn = *caml_named_value("fromJSON");
  instr = caml_copy_string(str);
  out = caml_callback(fn, instr);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}

int cpdf_fromJSONMemory(void *data, int len) {
  CAMLparam0();
  CAMLlocal3(pdf_v, bytestream, fn);
  bytestream =
      caml_ba_alloc_dims(CAML_BA_UINT8 | CAML_BA_C_LAYOUT, 1, data, len);
  fn = *caml_named_value("fromJSONMemory");
  pdf_v = caml_callback(fn, bytestream);
  updateLastError();
  CAMLreturnT(int, Int_val(pdf_v));
}

/* CHAPTER 16. Optional Content Groups */

int cpdf_startGetOCGList(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("startGetOCGList");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
char *cpdf_OCGListEntry(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  f = *caml_named_value("OCGListEntry");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
void cpdf_endGetOCGList() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("endGetOCGList");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}
int cpdf_OCGCoalesce(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("OCGCoalesce");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
void cpdf_OCGRename(int pdf, char *f, char *t) {
  CAMLparam0();
  CAMLlocal5(pdf_v, unit_v, fn, f_v, t_v);
  pdf_v = Val_int(pdf);
  fn = *caml_named_value("OCGRename");
  f_v = caml_copy_string(f);
  t_v = caml_copy_string(t);
  unit_v = caml_callback3(fn, pdf_v, f_v, t_v);
  CAMLreturn0;
}
void cpdf_OCGOrderAll(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("OCGOrderAll");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}


/* CHAPTER 17. Creating New PDFs */

int cpdf_blankDocument(double width, double height, int pages) {
  CAMLparam0();
  CAMLlocal5(fn, width_v, height_v, pages_v, out);
  fn = *caml_named_value("blankDocument");
  width_v = caml_copy_double(width);
  height_v = caml_copy_double(height);
  pages_v = Val_int(pages);
  out = caml_callback3(fn, width_v, height_v, pages_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}
int cpdf_blankDocumentPaper(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("blankDocumentPaper");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_textToPDF(double w, double h, int font, double fontsize,
                   char *filename) {
  CAMLparam0();
  CAMLlocal2(fn_v, out_v);
  CAMLlocalN(args, 5);
  args[0] = caml_copy_double(w);
  args[1] = caml_copy_double(h);
  args[2] = Val_int(font);
  args[3] = caml_copy_double(fontsize);
  args[4] = caml_copy_string(filename);
  fn_v = *caml_named_value("textToPDF");
  out_v = caml_callbackN(fn_v, 5, args);
  CAMLreturnT(int, Int_val(out_v));
}
int cpdf_textToPDFPaper(int papersize, int font, double fontsize,
                        char *filename) {
  CAMLparam0();
  CAMLlocal2(fn_v, out_v);
  CAMLlocalN(args, 4);
  fn_v = *caml_named_value("textToPDFPaper");
  args[0] = Val_int(papersize);
  args[1] = Val_int(font);
  args[2] = caml_copy_double(fontsize);
  args[3] = caml_copy_string(filename);
  out_v = caml_callbackN(fn_v, 4, args);
  CAMLreturnT(int, Int_val(out_v));
}


/* CHAPTER 18. Miscellaneous */

void cpdf_draft(int pdf, int range, int angle) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("draft");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removeAllText(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("removeAllText");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_blackText(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("blackText");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_blackLines(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("blackLines");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_blackFills(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("blackFills");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_thinLines(int pdf, int range, double minwidth) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, minwidth_v);
  fn = *caml_named_value("thinLines");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  minwidth_v = caml_copy_double(minwidth);
  unit = caml_callback3(fn, pdf_v, range_v, minwidth_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_copyId(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("copyId");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removeId(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("removeId");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setVersion(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("setVersion");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_setFullVersion(int pdf, int range, int angle) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("setFullVersion");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removeDictEntry(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("removeDictEntry");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
void cpdf_removeDictEntrySearch(int pdf, char *f, char *t) {
  CAMLparam0();
  CAMLlocal5(pdf_v, unit_v, fn, f_v, t_v);
  pdf_v = Val_int(pdf);
  fn = *caml_named_value("removeDictEntrySearch");
  f_v = caml_copy_string(f);
  t_v = caml_copy_string(t);
  unit_v = caml_callback3(fn, pdf_v, f_v, t_v);
  CAMLreturn0;
}
void cpdf_replaceDictEntry(int pdf, char *f, char *t) {
  CAMLparam0();
  CAMLlocal5(pdf_v, unit_v, fn, f_v, t_v);
  pdf_v = Val_int(pdf);
  fn = *caml_named_value("replaceDictEntry");
  f_v = caml_copy_string(f);
  t_v = caml_copy_string(t);
  unit_v = caml_callback3(fn, pdf_v, f_v, t_v);
  CAMLreturn0;
}
void cpdf_replaceDictEntrySearch(int pdf, char *key, char *newvalue,
                                 char *searchterm) {
  CAMLparam0();
  CAMLlocal2(fn_v, out_v);
  CAMLlocalN(args, 4);
  fn_v = *caml_named_value("replaceDictEntrySearch");
  args[0] = Val_int(pdf);
  args[1] = caml_copy_string(key);
  args[2] = caml_copy_string(newvalue);
  args[3] = caml_copy_string(searchterm);
  out_v = caml_callbackN(fn_v, 4, args);
  updateLastError();
  CAMLreturn0;
}

void *cpdf_getDictEntries(int pdf, char *key, int *retlen) {
  CAMLparam0();
  CAMLlocal4(fn, bytestream, pdf_v, key_v);
  fn = *caml_named_value("getDictEntries");
  pdf_v = Val_int(pdf);
  key_v = caml_copy_string(key);
  bytestream = caml_callback2(fn, pdf_v, key_v);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "getDictEntries: failed");
  if (size > 0) {
    int x;
    char *indata = Caml_ba_data_val(bytestream);
    for (x = 0; x < size; x++) {
      memory[x] = indata[x];
    };
  }
  *retlen = size;
  CAMLreturnT(void *, memory);
}

void cpdf_removeClipping(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("removeClipping");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
