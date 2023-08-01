#include <caml/alloc.h>
#include <caml/bigarray.h>
#include <caml/callback.h>
#include <caml/memory.h>
#include <stdio.h>

/* FIXME check enums/int */

/* __AUTODEF unit->unit
void cpdf_~() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("~");
  unit_v = caml_callback(fn_v, Val_unit);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF string->string->int
int cpdf_~(char *one, char *two) {
  CAMLparam0();
  CAMLlocal4(fn_v, one_v, two_v, result_v);
  fn_v = *caml_named_value("~");
  one_v = caml_copy_string(one);
  two_v = caml_copy_string(two);
  result_v = caml_callback2(fn_v, one_v, two_v);
  updateLastError();
  CAMLreturnT(int, Int_val(result_v));
}
*/

/* __AUTODEF float->float
double cpdf_~(double f) {
  CAMLparam0();
  CAMLlocal3(fn, in, out);
  fn = *caml_named_value("~");
  in = caml_copy_double(f);
  out = caml_callback(fn, in);
  updateLastError();
  CAMLreturnT(double, Double_val(out));
}
*/

/* __AUTODEF int->int
int cpdf_~(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, in_v, out_v);
  fn = *caml_named_value("~");
  in_v = Val_int(pdf);
  out_v = caml_callback(fn, in_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
*/

/* __AUTODEF int->int->int
int cpdf_~(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, out_v, av, bv);
  av = Val_int(a);
  bv = Val_int(b);
  fn = *caml_named_value("~");
  out_v = caml_callback2(fn, av, bv);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
*/

/* __AUTODEF int->unit
void cpdf_~(int pdf) {
  CAMLparam0();
  CAMLlocal3(fn, int_in, unit_out);
  fn = *caml_named_value("~");
  int_in = Val_int(pdf);
  unit_out = caml_callback(fn, int_in);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->string->unit
void cpdf_~(int pdf, char *s) {
  CAMLparam0();
  CAMLlocal4(unit, fn, pdf_v, s_v);
  fn = *caml_named_value("~");
  pdf_v = Val_int(pdf);
  s_v = caml_copy_string(s);
  unit = caml_callback2(fn, pdf_v, s_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->int->unit
void cpdf_~(int o, int n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("~");
  o_v = Val_int(o);
  n_v = Val_int(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF unit->int
int cpdf_~(void) {
  CAMLparam0();
  CAMLlocal3(f_v, unit_v, int_v);
  f_v = *caml_named_value("~");
  unit_v = Val_unit;
  int_v = caml_callback(f_v, unit_v);
  updateLastError();
  CAMLreturnT(int, Int_val(int_v));
}
*/

/* __AUTODEF int->string
char *cpdf_~(int key) {
  CAMLparam0();
  CAMLlocal3(f, key_v, out_v);
  enumeratePDFsInfo = *caml_named_value("~");
  key_v = Val_int(key);
  out_v = caml_callback(f, key_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out_v));
}
*/

/* __AUTODEF string->int
int cpdf_~(char *str) {
  CAMLparam0();
  CAMLlocal3(fn, instr, out);
  fn = *caml_named_value("~");
  instr = caml_copy_string(str);
  out = caml_callback(fn, instr);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}
*/

/* __AUTODEF int->string->int
int cpdf_~(int i, char *str) {
  CAMLparam0();
  CAMLlocal4(fn, ini, instr, out);
  fn = *caml_named_value("~");
  ini = Val_int(i);
  instr = caml_copy_string(str);
  out = caml_callback2(fn, ini, instr);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}
*/

/* __AUTODEF int->int->string
char *cpdf_~(int a, int b) {
  CAMLparam0();
  CAMLlocal4(fn, a_v, b_v, out);
  fn = *caml_named_value("~");
  a_v = Val_int(a);
  b_v = Val_int(a);
  out = caml_callback2(fn, a_v, b_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(out));
}
*/

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

/* __AUTO setFast unit->unit */
/* __AUTO setSlow unit->unit */
/* __AUTO onExit unit->unit */

/* CHAPTER 1. Basics */

/* __AUTO fromFile string->string->int */
/* __AUTO fromFileLazy string->string->int */

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
/* __AUTO deletePdf int->unit */
/* __AUTO replacePdf int->int->unit */
/* __AUTO startEnumeratePDFs unit->int */
/* __AUTO enumeratePDFsKey int->int */
/* __AUTO enumeratePDFsInfo int->string */
/* __AUTO endEnumeratePDFs unit->unit */
/* __AUTO ptOfCm float->float */
/* __AUTO ptOfMm float->float */
/* __AUTO ptOfIn float->float */
/* __AUTO cmOfPt float->float */
/* __AUTO mmOfPt float->float */
/* __AUTO inOfPt float->float */
/* __AUTO parsePagespec int->string->int */
/* __AUTO validatePagespec string->int */
/* __AUTO stringOfPagespec int->int->string */
/* __AUTO blankRange unit->int */
/* __AUTO deleteRange unit->unit */
/* __AUTO range int->int->int */
/* __AUTO all int->int */
/* __AUTO even int->int */
/* __AUTO odd int->int */
/* __AUTO rangeUnion int->int */
/* __AUTO difference int->int->int */
/* __AUTO removeDuplicates int->int */
/* __AUTO rangeLength int->int */
/* __AUTO rangeGet int->int->int */
/* __AUTO rangeAdd int->int->int */
/* __AUTO isInrange int->int->int */
/* __AUTO pages int->int */
/* __AUTO pagesFast string->string->int */
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
/* __AUTO isEncrypted int->int */
/* __AUTO decryptPdf int->string->unit */
/* __AUTO decryptPdfOwner int->string->unit */
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
/* __AUTO hasPermission int->int->int */
/* __AUTO encryptionKind int->int */
