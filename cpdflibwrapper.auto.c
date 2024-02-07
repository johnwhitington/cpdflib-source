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

/* __AUTODEF float->unit
void cpdf_~(double o) {
  CAMLparam0();
  CAMLlocal3(fn, o_v, unit_out);
  fn = *caml_named_value("~");
  o_v = caml_copy_double(o);
  unit_out = caml_callback(fn, o_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF float->float->unit
void cpdf_~(double o, double n) {
  CAMLparam0();
  CAMLlocal4(fn, o_v, n_v, unit_out);
  fn = *caml_named_value("~");
  o_v = caml_copy_double(o);
  n_v = caml_copy_double(n);
  unit_out = caml_callback2(fn, o_v, n_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF float->float->float->unit
void cpdf_~(double o, double n, double m) {
  CAMLparam0();
  CAMLlocal5(fn, o_v, n_v, m_v, unit_out);
  fn = *caml_named_value("~");
  o_v = caml_copy_double(o);
  n_v = caml_copy_double(n);
  m_v = caml_copy_double(m);
  unit_out = caml_callback3(fn, o_v, n_v, m_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF float->float->float->float->unit
void cpdf_~(double o, double n, double m, double p) {
  CAMLparam0();
  CAMLlocal2(fn, unit_out);
  CAMLlocalN(args, 4);
  fn = *caml_named_value("~");
  args[0] = caml_copy_double(o);
  args[1] = caml_copy_double(n);
  args[2] = caml_copy_double(m);
  args[3] = caml_copy_double(p);
  unit_out = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF float->float->float->float->float->float->unit
void cpdf_~(double o, double n, double m, double p, double q, double r) {
  CAMLparam0();
  CAMLlocal2(fn, unit_out);
  CAMLlocalN(args, 6);
  fn = *caml_named_value("~");
  args[0] = caml_copy_double(o);
  args[1] = caml_copy_double(n);
  args[2] = caml_copy_double(m);
  args[3] = caml_copy_double(p);
  args[4] = caml_copy_double(q);
  args[5] = caml_copy_double(r);
  unit_out = caml_callbackN(fn, 6, args);
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
  f = *caml_named_value("~");
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

/* __AUTODEF string->unit
void cpdf_~(char *str) {
  CAMLparam0();
  CAMLlocal3(fn, instr, out);
  fn = *caml_named_value("~");
  instr = caml_copy_string(str);
  out = caml_callback(fn, instr);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF string->string->unit
void cpdf_~(char *str, char* str2) {
  CAMLparam0();
  CAMLlocal4(fn, instr, instr2, out);
  fn = *caml_named_value("~");
  instr = caml_copy_string(str);
  instr2 = caml_copy_string(str2);
  out = caml_callback2(fn, instr, instr2);
  updateLastError();
  CAMLreturn0;
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

/* __AUTODEF int->int->int->unit
void cpdf_~(int pdf, int range, int angle) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, angle_v);
  fn = *caml_named_value("~");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  angle_v = Val_int(angle);
  unit = caml_callback3(fn, pdf_v, range_v, angle_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->float
double cpdf_~(int serial) {
  CAMLparam0();
  CAMLlocal3(fn, serial_v, out_v);
  fn = *caml_named_value("~");
  serial_v = Val_int(serial);
  out_v = caml_callback(fn, serial_v);
  updateLastError();
  CAMLreturnT(int, Double_val(out_v));
}
*/

/* __AUTODEF int->int->float->float->unit
void cpdf_~(int pdf, int range, double sx, double sy) {
  CAMLparam0();
  CAMLlocal2(fn, unit);
  CAMLlocalN(args, 4);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(sx);
  args[3] = caml_copy_double(sy);
  fn = *caml_named_value("~");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->int->float->float->float->unit
void cpdf_~(int pdf, int range, double w, double h, double scale) {
  CAMLparam0();
  CAMLlocalN(args, 5);
  CAMLlocal2(fn, unit);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(w);
  args[3] = caml_copy_double(h);
  args[4] = caml_copy_double(scale);
  fn = *caml_named_value("~");
  unit = caml_callbackN(fn, 5, args);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->int->int->float->unit
void cpdf_~(int pdf, int range, int papersize, double scale) {
  CAMLparam0();
  CAMLlocalN(args, 4);
  CAMLlocal2(unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = Val_int(papersize);
  args[3] = caml_copy_double(scale);
  fn = *caml_named_value("~");
  unit = caml_callbackN(fn, 4, args);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->int->float->float->float->float->unit
void cpdf_~(int pdf, int range, double x, double y, double w, double h) {
  CAMLparam0();
  CAMLlocalN(args, 6);
  CAMLlocal2(unit, fn);
  args[0] = Val_int(pdf);
  args[1] = Val_int(range);
  args[2] = caml_copy_double(x);
  args[3] = caml_copy_double(y);
  args[4] = caml_copy_double(w);
  args[5] = caml_copy_double(h);
  fn = *caml_named_value("~");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->int->string->unit
void cpdf_~(int pdf, int range, char *box) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, box_v);
  fn = *caml_named_value("~");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  box_v = caml_copy_string(box);
  unit = caml_callback3(fn, pdf_v, range_v, box_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->int->float->string->int->unit
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
*/

/* __AUTODEF string->int->int->int->unit
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
*/

/* __AUTODEF int->int->int->string
char *cpdf_~(int pdf, int range, int stamp_pdf) {
  CAMLparam0();
  CAMLlocal5(pdf_v, range_v, stamp_pdf_v, fn, name_v);
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  stamp_pdf_v = Val_int(stamp_pdf);
  fn = *caml_named_value("~");
  name_v = caml_callback3(fn, pdf_v, range_v, stamp_pdf_v);
  updateLastError();
  CAMLreturnT(char *, (char *)String_val(name_v));
}
*/

/* __AUTODEF int->int->string->int
int cpdf_~(int pdf, int pagenumber, char *boxname) {
  CAMLparam0();
  CAMLlocal4(fn, pdf_v, pagenumber_v, boxname_v);
  CAMLlocal1(out_v);
  fn = *caml_named_value("~");
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  boxname_v = caml_copy_string(boxname);
  out_v = caml_callback3(fn, pdf_v, pagenumber_v, boxname_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
*/

/* __AUTODEF int->int->float*->float*->float*->float*->unit
void cpdf_~(int pdf, int pagenumber, double *minx, double *maxx,
                      double *miny, double *maxy) {
  CAMLparam0();
  CAMLlocal5(fn, pdf_v, pagenumber_v, tuple_v, minx_v);
  CAMLlocal3(maxx_v, miny_v, maxy_v);
  fn = *caml_named_value("~");
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
*/

/* __AUTODEF int->int->float->float->float->float->unit
void cpdf_~(int pdf, int range, double minx, double maxx, double miny,
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
  fn = *caml_named_value("~");
  unit = caml_callbackN(fn, 6, args);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->int->string->int->int->int->unit
void cpdf_~(int pdf, enum cpdf_pageLabelStyle style, char *prefix,
                        int offset, int range, int progress) {
  CAMLparam0();
  CAMLlocal2(fn, out_v);
  fn = *caml_named_value("~");
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
*/

/* __AUTODEF string->int->unit
void cpdf_~(char *filename, int pdf) {
  CAMLparam0();
  CAMLlocal4(unit, fn, filename_v, pdf_v);
  fn = *caml_named_value("~");
  filename_v = caml_copy_string(filename);
  pdf_v = Val_int(pdf);
  unit = caml_callback2(fn, filename_v, pdf_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF string->int->int->unit
void cpdf_~(char *filename, int pdf, int pagenumber) {
  CAMLparam0();
  CAMLlocal5(unit, fn, filename_v, pdf_v, pagenumber_v);
  fn = *caml_named_value("~");
  filename_v = caml_copy_string(filename);
  pdf_v = Val_int(pdf);
  pagenumber_v = Val_int(pagenumber);
  unit = caml_callback3(fn, filename_v, pdf_v, pagenumber_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->float->int
int cpdf_~(int pdf, double res) {
  CAMLparam0();
  CAMLlocal4(fn, pdf_v, out_v, res_v);
  fn = *caml_named_value("~");
  pdf_v = Val_int(pdf);
  res_v = caml_copy_double(res);
  out_v = caml_callback2(fn, pdf_v, res_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out_v));
}
*/

/* __AUTODEF int->int->int->int->string->unit
void cpdf_~(int from_pdf, int to_pdf, int range, int pagenumber,
                   char *fontname) {
  CAMLparam0();
  CAMLlocal2(fn_v, out_v);
  fn_v = *caml_named_value("~");
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
*/

/* __AUTODEF int->string->string->unit
void cpdf_~(int pdf, char *f, char *t) {
  CAMLparam0();
  CAMLlocal5(pdf_v, unit_v, fn, f_v, t_v);
  pdf_v = Val_int(pdf);
  fn = *caml_named_value("~");
  f_v = caml_copy_string(f);
  t_v = caml_copy_string(t);
  unit_v = caml_callback3(fn, pdf_v, f_v, t_v);
  CAMLreturn0;
}
*/

/* __AUTODEF float->float->int->int
int cpdf_~(double width, double height, int pages) {
  CAMLparam0();
  CAMLlocal5(fn, width_v, height_v, pages_v, out);
  fn = *caml_named_value("~");
  width_v = caml_copy_double(width);
  height_v = caml_copy_double(height);
  pages_v = Val_int(pages);
  out = caml_callback3(fn, width_v, height_v, pages_v);
  updateLastError();
  CAMLreturnT(int, Int_val(out));
}
*/

/* __AUTODEF float->float->int->float->string->int
int cpdf_~(double w, double h, int font, double fontsize,
                   char *filename) {
  CAMLparam0();
  CAMLlocal2(fn_v, out_v);
  CAMLlocalN(args, 5);
  args[0] = caml_copy_double(w);
  args[1] = caml_copy_double(h);
  args[2] = Val_int(font);
  args[3] = caml_copy_double(fontsize);
  args[4] = caml_copy_string(filename);
  fn_v = *caml_named_value("~");
  out_v = caml_callbackN(fn_v, 5, args);
  CAMLreturnT(int, Int_val(out_v));
}
*/

/* __AUTODEF int->int->float->string->int
int cpdf_~(int papersize, int font, double fontsize,
                        char *filename) {
  CAMLparam0();
  CAMLlocal2(fn_v, out_v);
  CAMLlocalN(args, 4);
  fn_v = *caml_named_value("~");
  args[0] = Val_int(papersize);
  args[1] = Val_int(font);
  args[2] = caml_copy_double(fontsize);
  args[3] = caml_copy_string(filename);
  out_v = caml_callbackN(fn_v, 4, args);
  CAMLreturnT(int, Int_val(out_v));
}
*/

/* __AUTODEF int->int->float->unit
void cpdf_~(int pdf, int range, double minwidth) {
  CAMLparam0();
  CAMLlocal5(unit, fn, pdf_v, range_v, minwidth_v);
  fn = *caml_named_value("~");
  pdf_v = Val_int(pdf);
  range_v = Val_int(range);
  minwidth_v = caml_copy_double(minwidth);
  unit = caml_callback3(fn, pdf_v, range_v, minwidth_v);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF int->string->string->string->unit
void cpdf_~(int pdf, char *key, char *newvalue,
                                 char *searchterm) {
  CAMLparam0();
  CAMLlocal2(fn_v, out_v);
  CAMLlocalN(args, 4);
  fn_v = *caml_named_value("~");
  args[0] = Val_int(pdf);
  args[1] = caml_copy_string(key);
  args[2] = caml_copy_string(newvalue);
  args[3] = caml_copy_string(searchterm);
  out_v = caml_callbackN(fn_v, 4, args);
  updateLastError();
  CAMLreturn0;
}
*/

/* __AUTODEF void*->int->string->int
int cpdf_~(void *data, int len, char *userpw) {
  CAMLparam0();
  CAMLlocal4(pdf_v, bytestream, fn, userpw_v);
  bytestream =
      caml_ba_alloc_dims(CAML_BA_UINT8 | CAML_BA_C_LAYOUT, 1, data, len);
  fn = *caml_named_value("~");
  userpw_v = caml_copy_string(userpw);
  pdf_v = caml_callback2(fn, bytestream, userpw_v);
  updateLastError();
  CAMLreturnT(int, Int_val(pdf_v));
}
*/

/* __AUTODEF int->int*->void*
void *cpdf_~(int pdf, int *retlen) {
  CAMLparam0();
  CAMLlocal3(fn, bytestream, pdf_v);
  fn = *caml_named_value("~");
  pdf_v = Val_int(pdf);
  bytestream = caml_callback(fn, pdf_v);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "~: failed");
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
*/

/* __AUTODEF int->int*->float->void*
void *cpdf_~(int pdf, int *retlen, double f) {
  CAMLparam0();
  CAMLlocal4(fn, bytestream, pdf_v, f_v);
  fn = *caml_named_value("~");
  pdf_v = Val_int(pdf);
  f_v = caml_copy_double(f);
  bytestream = caml_callback2(fn, pdf_v, f_v);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "~: failed");
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
*/

/* __AUTODEF int->int->int*->void*
void *cpdf_~(int filesize, int pdf, int *retlen) {
  CAMLparam0();
  CAMLlocal4(fn, filesize_v, bytestream, pdf_v);
  fn = *caml_named_value("~");
  pdf_v = Val_int(pdf);
  filesize_v = Val_int(filesize);
  bytestream = caml_callback2(fn, filesize_v, pdf_v);
  updateLastError();
  char *memory = NULL;
  int size = Caml_ba_array_val(bytestream)->dim[0];
  memory = calloc(size, sizeof(char));
  if (memory == NULL && size > 0) fprintf(stderr, "~: failed");
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
*/

/* __AUTODEF int->void*->int->unit
void cpdf_~(int pdf, void *data, int len) {
  CAMLparam0();
  CAMLlocal4(unit, bytestream, fn, valpdf);
  bytestream =
      caml_ba_alloc_dims(CAML_BA_UINT8 | CAML_BA_C_LAYOUT, 1, data, len);
  fn = *caml_named_value("~");
  valpdf = Val_int(pdf);
  unit = caml_callback2(fn, valpdf, bytestream);
  updateLastError();
  CAMLreturn0;
}
*/

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

enum cpdf_cap {
  cpdf_capButt,
  cpdf_capRound,
  cpdf_capSquare
};

enum cpdf_join {
  cpdf_joinMiter,
  cpdf_joinRound,
  cpdf_joinBevel
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

/* __AUTO setFast unit->unit */
/* __AUTO setSlow unit->unit */
/* __AUTO embedStd14 int->unit */
/* __AUTO embedStd14Dir string->unit */
/* __AUTO onExit unit->unit */

/* CHAPTER 1. Basics */

/* __AUTO fromFile string->string->int */
/* __AUTO fromFileLazy string->string->int */
/* __AUTO fromMemory void*->int->string->int */
/* __AUTO fromMemoryLazy void*->int->string->int */
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
/* __AUTO deleteRange int->unit */
/* __AUTO range int->int->int */
/* __AUTO all int->int */
/* __AUTO even int->int */
/* __AUTO odd int->int */
/* __AUTO rangeUnion int->int->int */
/* __AUTO difference int->int->int */
/* __AUTO removeDuplicates int->int */
/* __AUTO rangeLength int->int */
/* __AUTO rangeGet int->int->int */
/* __AUTO rangeAdd int->int->int */
/* __AUTO isInRange int->int->int */
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

/* __AUTO selectPages int->int->int */

/* CHAPTER 3. Pages */

/* __AUTO scalePages int->int->float->float->unit */
/* __AUTO scaleToFit int->int->float->float->float->unit */
/* __AUTO scaleToFitPaper int->int->int->float->unit */

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

/* __AUTO shiftContents int->int->float->float->unit */
/* __AUTO rotate int->int->int->unit */
/* __AUTO rotateBy int->int->int->unit */
/* __AUTO rotateContents int->int->float->unit */
/* __AUTO upright int->int->unit */
/* __AUTO hFlip int->int->unit */
/* __AUTO vFlip int->int->unit */
/* __AUTO crop int->int->float->float->float->float->unit */
/* __AUTO removeCrop int->int->unit */
/* __AUTO removeTrim int->int->unit */
/* __AUTO removeArt int->int->unit */
/* __AUTO removeBleed int->int->unit */
/* __AUTO trimMarks int->int->unit */
/* __AUTO showBoxes int->int->unit */
/* __AUTO hardBox int->int->string->unit */

/* CHAPTER 5. Compression */

/* __AUTO compress int->unit */
/* __AUTO decompress int->unit */
/* __AUTO squeezeInMemory int->unit */

/* CHAPTER 6. Bookmarks */

/* __AUTO startGetBookmarkInfo int->int */
/* __AUTO numberBookmarks unit->int */
/* __AUTO getBookmarkLevel int->int */
/* __AUTO getBookmarkPage int->int->int */
/* __AUTO getBookmarkText int->string */
/* __AUTO getBookmarkOpenStatus int->int */
/* __AUTO endGetBookmarkInfo unit->unit */
/* __AUTO startSetBookmarkInfo int->unit */
/* __AUTO setBookmarkLevel int->int->unit */
/* __AUTO setBookmarkPage int->int->int->unit */
/* __AUTO setBookmarkOpenStatus int->int->unit */
/* __AUTO setBookmarkText int->string->unit */
/* __AUTO endSetBookmarkInfo int->unit */
/* __AUTO getBookmarksJSON int->int*->void* */
/* __AUTO setBookmarksJSON int->void*->int->unit */
/* __AUTO tableOfContents int->int->float->string->int->unit */

/* CHAPTER 7. Presentations */

/* Not included in the library version */

/* CHAPTER 8. Logos, Watermarks and Stamps */

/* __AUTO stampOn int->int->int->unit */
/* __AUTO stampUnder int->int->int->unit */

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

/* __AUTO combinePages int->int->int */

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

/* __AUTO removeText int->int->int */
/* __AUTO textWidth int->string->int */
/* __AUTO addContent string->int->int->int->unit */
/* __AUTO stampAsXObject int->int->int->string */

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

/* __AUTO twoUp int->unit */
/* __AUTO twoUpStack int->unit */
/* __AUTO padBefore int->int->unit */
/* __AUTO padAfter int->int->unit */
/* __AUTO padEvery int->int->unit */
/* __AUTO padMultiple int->int->unit */
/* __AUTO padMultipleBefore int->int->unit */

/* CHAPTER 10. Annotations */

/* __AUTO annotationsJSON int->int*->void* */
/* __AUTO removeAnnotations int->int->unit */
/* __AUTO setAnnotationsJSON int->void*->int->unit */

/* CHAPTER 11. Document Information and Metadata */

/* __AUTO isLinearized string->int */
/* __AUTO getVersion int->int */
/* __AUTO getMajorVersion int->int */
/* __AUTO getTitle int->string */
/* __AUTO getAuthor int->string */
/* __AUTO getSubject int->string */
/* __AUTO getKeywords int->string */
/* __AUTO getCreator int->string */
/* __AUTO getProducer int->string */
/* __AUTO getCreationDate int->string */
/* __AUTO getModificationDate int->string */
/* __AUTO getTitleXMP int->string */
/* __AUTO getAuthorXMP int->string */
/* __AUTO getSubjectXMP int->string */
/* __AUTO getKeywordsXMP int->string */
/* __AUTO getCreatorXMP int->string */
/* __AUTO getProducerXMP int->string */
/* __AUTO getCreationDateXMP int->string */
/* __AUTO getModificationDateXMP int->string */
/* __AUTO setTitle int->string->unit */
/* __AUTO setAuthor int->string->unit */
/* __AUTO setSubject int->string->unit */
/* __AUTO setKeywords int->string->unit */
/* __AUTO setCreator int->string->unit */
/* __AUTO setProducer int->string->unit */
/* __AUTO setCreationDate int->string->unit */
/* __AUTO setModificationDate int->string->unit */
/* __AUTO setTitleXMP int->string->unit */
/* __AUTO setAuthorXMP int->string->unit */
/* __AUTO setSubjectXMP int->string->unit */
/* __AUTO setKeywordsXMP int->string->unit */
/* __AUTO setCreatorXMP int->string->unit */
/* __AUTO setProducerXMP int->string->unit */
/* __AUTO setCreationDateXMP int->string->unit */
/* __AUTO setModificationDateXMP int->string->unit */

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

/* __AUTO getPageRotation int->int->int */
/* __AUTO hasBox int->int->string->int */
/* __AUTO getMediaBox int->int->float*->float*->float*->float*->unit */
/* __AUTO getCropBox int->int->float*->float*->float*->float*->unit */
/* __AUTO getTrimBox int->int->float*->float*->float*->float*->unit */
/* __AUTO getArtBox int->int->float*->float*->float*->float*->unit */
/* __AUTO getBleedBox int->int->float*->float*->float*->float*->unit */
/* __AUTO setMediabox int->int->float->float->float->float->unit */
/* __AUTO setCropBox int->int->float->float->float->float->unit */
/* __AUTO setTrimBox int->int->float->float->float->float->unit */
/* __AUTO setArtBox int->int->float->float->float->float->unit */
/* __AUTO setBleedBox int->int->float->float->float->float->unit */
/* __AUTO markTrapped int->unit */
/* __AUTO markUntrapped int->unit */
/* __AUTO markTrappedXMP int->unit */
/* __AUTO markUntrappedXMP int->unit */
/* __AUTO setPageLayout int->int->unit */
/* __AUTO getPageLayout int->int */
/* __AUTO setPageMode int->int->unit */
/* __AUTO getPageMode int->int */
/* __AUTO getHideToolbar int->int */
/* __AUTO hideToolbar int->int->unit */
/* __AUTO getHideMenubar int->int */
/* __AUTO hideMenubar int->int->unit */
/* __AUTO getHideWindowUi int->int */
/* __AUTO hideWindowUi int->int->unit */
/* __AUTO getFitWindow int->int */
/* __AUTO fitWindow int->int->unit */
/* __AUTO getCenterWindow int->int */
/* __AUTO centerWindow int->int->unit */
/* __AUTO getDisplayDocTitle int->int */
/* __AUTO displayDocTitle int->int->unit */
/* __AUTO openAtPage int->int->int->unit */
/* __AUTO openAtPageCustom int->string->unit */
/* __AUTO getNonFullScreenPageMode int->int */
/* __AUTO nonFullScreenPageMode int->int->unit */
/* __AUTO setMetadataFromFile int->string->unit */
/* __AUTO setMetadataFromByteArray int->void*->int->unit */
/* __AUTO getMetadata int->int*->void* */
/* __AUTO removeMetadata int->unit */
/* __AUTO createMetadata int->unit */
/* __AUTO setMetadataDate int->string->unit */
/* __AUTO addPageLabels int->int->string->int->int->int->unit */
/* __AUTO removePageLabels int->unit */
/* __AUTO startGetPageLabels int->int */
/* __AUTO endGetPageLabels unit->unit */
/* __AUTO getPageLabelOffset int->int */
/* __AUTO getPageLabelStyle int->int */
/* __AUTO getPageLabelRange int->int */
/* __AUTO getPageLabelPrefix int->string */
/* __AUTO getPageLabelStringForPage int->int->string */
/* __AUTO compositionJSON int->int->int*->void* */

/* CHAPTER 12. File Attachments */

/* __AUTO attachFile string->int->unit */
/* __AUTO attachFileToPage string->int->int->unit */

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

/* __AUTO removeAttachedFiles int->unit */
/* __AUTO startGetAttachments int->unit */
/* __AUTO numberGetAttachments unit->int */
/* __AUTO getAttachmentName int->string */
/* __AUTO getAttachmentPage int->int */
/* __AUTO getAttachmentData int->int*->void* */
/* __AUTO endGetAttachments unit->unit */

/* CHAPTER 13. Images */

/* __AUTO startGetImageResolution int->float->int */
/* __AUTO getImageResolutionPageNumber int->int */
/* __AUTO getImageResolutionImageName int->string */
/* __AUTO getImageResolutionXPixels int->int */
/* __AUTO getImageResolutionYPixels int->int */
/* __AUTO getImageResolutionXRes int->float */
/* __AUTO getImageResolutionYRes int->float */
/* __AUTO endGetImageResolution unit->unit */
/* __AUTO imageResolutionJSON int->int*->float->void* */

/* CHAPTER 14. Fonts */

/* __AUTO startGetFontInfo int->unit */
/* __AUTO numberFonts unit->int */
/* __AUTO getFontPage int->int */
/* __AUTO getFontName int->string */
/* __AUTO getFontType int->string */
/* __AUTO getFontEncoding int->string */
/* __AUTO endGetFontInfo unit->unit */
/* __AUTO removeFonts int->unit */
/* __AUTO copyFont int->int->int->int->string->unit */

/* CHAPTER 15. PDF and JSON */

/* __AUTO JSONUTF8 int->unit */

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

/* __AUTO fromJSON string->int */

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

/* __AUTO startGetOCGList int->int */
/* __AUTO OCGListEntry int->string */
/* __AUTO endGetOCGList unit->unit */
/* __AUTO OCGCoalesce int->int */
/* __AUTO OCGRename int->string->string->unit */
/* __AUTO OCGOrderAll int->unit */


/* CHAPTER 17. Creating New PDFs */

/* __AUTO blankDocument float->float->int->int */
/* __AUTO blankDocumentPaper int->int->int */
/* __AUTO textToPDF float->float->int->float->string->int */
/* __AUTO textToPDFPaper int->int->float->string->int */
/* __AUTO fromPNG string->int */
/* __AUTO fromJPEG string->int */

/* CHAPTER 18. Drawing on PDFs */

/* __AUTO drawBegin unit->unit */
/* __AUTO drawEnd int->int->unit */
/* __AUTO drawEndExtended int->int->int->int->string->unit */
/* __AUTO drawRect float->float->float->float->unit */
/* __AUTO drawTo float->float->unit */
/* __AUTO drawLine float->float->unit */
/* __AUTO drawBez float->float->float->float->float->float->unit */
/* __AUTO drawBez23 float->float->float->float->unit */
/* __AUTO drawBez13 float->float->float->float->unit */
/* __AUTO drawCircle float->float->float->unit */
/* __AUTO drawStrokeColGrey float->unit */
/* __AUTO drawStrokeColRGB float->float->float->unit */
/* __AUTO drawStrokeColCYMK float->float->float->float->unit */
/* __AUTO drawFillColGrey float->unit */
/* __AUTO drawFillColRGB float->float->float->unit */
/* __AUTO drawFillColCYMK float->float->float->float->unit */
/* __AUTO drawStroke unit->unit */
/* __AUTO drawFill unit->unit */
/* __AUTO drawFillEo unit->unit */
/* __AUTO drawStrokeFill unit->unit */
/* __AUTO drawStrokeFillEo unit->unit */
/* __AUTO drawClose unit->unit */
/* __AUTO drawClip unit->unit */
/* __AUTO drawClipEo unit->unit */
/* __AUTO drawThick float->unit */
/* __AUTO drawCap int->unit */
/* __AUTO drawJoin int->unit */
/* __AUTO drawMiter float->unit */
/* __AUTO drawDash string->unit */
/* __AUTO drawPush unit->unit */
/* __AUTO drawPop unit->unit */
/* __AUTO drawMatrix float->float->float->float->float->float->unit */
/* __AUTO drawMTrans float->float->unit */
/* __AUTO drawMRot float->float->float->unit */
/* __AUTO drawMScale float->float->float->float->unit */
/* __AUTO drawMShearX float->float->float->unit */
/* __AUTO drawMShearY float->float->float->unit */
/* __AUTO drawXObjBBox float->float->float->float->unit */
/* __AUTO drawXObj string->unit */
/* __AUTO drawEndXObj unit->unit */
/* __AUTO drawUse string->unit */
/* __AUTO drawJPEG string->string->unit */
/* __AUTO drawPNG string->string->unit */
/* __AUTO drawImage string->unit */
/* __AUTO drawFillOpacity float->unit */
/* __AUTO drawStrokeOpacity float->unit */
/* __AUTO drawBT unit->unit */
/* __AUTO drawET unit->unit */
/* __AUTO loadFont string->string->unit */
/* __AUTO drawFont string->unit */
/* __AUTO drawFontSize float->unit */
/* __AUTO drawText string->unit */
/* __AUTO drawSText string->unit */
/* __AUTO drawLeading float->unit */
/* __AUTO drawCharSpace float->unit */
/* __AUTO drawWordSpace float->unit */
/* __AUTO drawTextScale float->unit */
/* __AUTO drawRenderMode int->unit */
/* __AUTO drawRise float->unit */
/* __AUTO drawNL unit->unit */
/* __AUTO drawNewPage unit->unit */

/* CHAPTER 19. Miscellaneous */

/* __AUTO draft int->int->int->unit */
/* __AUTO removeAllText int->int->unit */
/* __AUTO blackText int->int->unit */
/* __AUTO blackLines int->int->unit */
/* __AUTO blackFills int->int->unit */
/* __AUTO thinLines int->int->float->unit */
/* __AUTO copyId int->int->unit */
/* __AUTO removeId int->unit */
/* __AUTO setVersion int->int->unit */
/* __AUTO setFullVersion int->int->int->unit */
/* __AUTO removeDictEntry int->string->unit */
/* __AUTO removeDictEntrySearch int->string->string->unit */
/* __AUTO replaceDictEntry int->string->string->unit */
/* __AUTO replaceDictEntrySearch int->string->string->string->unit */

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

/* __AUTO removeClipping int->int->unit */
