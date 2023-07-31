#include <caml/alloc.h>
#include <caml/bigarray.h>
#include <caml/callback.h>
#include <caml/memory.h>
#include <stdio.h>

/* We define an AUTODEF for each ordinary type of function */

/* __AUTODEF unit->unit
void cpdf_~)() {
  CAMLparam0();
  CAMLlocal2(fn_v, unit_v);
  fn_v = *caml_named_value("~");
  unit_v = caml_callback(fn_v, Val_unit);
  CAMLreturn0;
} */

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
} */

/* CHAPTER 0. Preliminaries */

/* Functions which can't be created by AUTO are given explicitly, and simply copied. */

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

/* Now, we put an AUTO in for each function we want to create. */

/* __AUTO version unit->string */
/* __AUTO setFast unit->unit */
/* __AUTO setSlow unit->unit */
/* __AUTO onExit unit->unit */

/* CHAPTER 1. Basics */

/* __AUTO fromFile string->string->int */
/* __AUTO fromFileLazy string->string->int */
