#include <caml/alloc.h>
#include <caml/bigarray.h>
#include <caml/callback.h>
#include <caml/memory.h>
#include <stdio.h>

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
/* -__AUTO fromMemory data->int->string->int */
/* -__AUTO fromMemoryLazy data->int->string->int */
/* -__AUTO deletePdf int->unit */
/* -__AUTO replacePdf int->int->unit */
/* -__AUTO startEnumeratePDFs unit->int */
/* -__AUTO enumeratePDFsKey int->int */
/* -__AUTO enumeratePDFsInfo int->string */
/* __AUTO endEnumeratePDFs unit->unit */
/* -__AUTO ptOfCm float->float */
/* -__AUTO ptOfMm float->float */
/* -__AUTO ptOfIn float->float */
/* -__AUTO cmOfPt float->float */
/* -__AUTO mmOfPt float->float */
/* -__AUTO inOfPt float->float */
/* -__AUTO parsePagespec int->string->int */
/* -__AUTO validatePagespec string->int */
/* -__AUTO stringOfPagespec int->int->string */
/* -__AUTO blankRange void->int */
/* __AUTO deleteRange unit->unit */
/* -__AUTO range int->int->int */
/* -__AUTO all int->int */
/* -__AUTO even int->int */
/* -__AUTO odd int->int */
/* -__AUTO rangeUnion int->int */
/* -__AUTO difference int->int->int */
/* -__AUTO removeDuplicates int->int */
/* -__AUTO rangeLength int->int */
/* -__AUTO rangeGet int->int->int */
/* -__AUTO rangeAdd int->int->int */
/* -__AUTO isInrange int->int->int */
/* -__AUTO pages int->int */
/* __AUTO pagesFast string->string->int */
/* -__AUTO toFile int->string->int->int->void */
/* toFileExt special */
/* -__AUTO toMemory int->int->int->int*->void* */
/* -__AUTO isEncrypted int->int */
/* -__AUTO decryptPdf int->string->unit */
/* -__AUTO decryptPdfOwner int->string->unit */
/* toFileEncrypted special */
/* toFileEncryptedExt special */
/* -__AUTO hasPermission int->int->int */
/* -__AUTO encryptionKind int->int */
