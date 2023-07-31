(* AUTO *)
open Pdfutil

let contents_of_file filename =
  let ch = open_in_bin filename in
  let s = really_input_string ch (in_channel_length ch) in
    close_in ch;
    s

let contents_to_file filename contents =
  let ch = open_out_bin filename in
    output_string ch contents;
    close_out ch

let lines contents =
  map implode (split_around (eq '\n') (explode contents))

let rec return_lines_until a s = function
  | [] -> (rev a, [])
  | h::t when h = s -> (rev a, t)
  | h::t -> return_lines_until (h::a) s t 

let autos = null_hash ()

let store_auto h t =
  let typ = implode (drop (explode h) 13) in
  let autodef, more = return_lines_until [] "" t in
    Hashtbl.add autos typ (rev (tl (rev autodef)));
    more

let use_auto h =
  let name, typ =
    let both = drop (explode h) 10 in
      let name, more = cleavewhile (neq ' ') both in
        let typ, _ = cleavewhile (neq ' ') (tl more) in
          implode name, implode typ
  in
    map (string_replace_all "~" name) (Hashtbl.find autos typ)

let rec process a = function
  | [] -> rev (map (fun x -> x ^ "\n") a)
  | h::t ->
      if starts_with "/* __AUTODEF" h then
        let t = store_auto h t in
          process a t
      else if starts_with "/* __AUTO" h then
        let auto = use_auto h in
          process (rev auto @ a) t
      else process (h::a) t

let go infile outfile =
  let indata = lines (contents_of_file infile) in
  let processed = process [] indata in
    contents_to_file outfile (fold_left ( ^ ) "" processed)

let () = go "cpdflibwrapper.auto.c" "cpdflibwrapper.c"
