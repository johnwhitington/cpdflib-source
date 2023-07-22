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

let rec process a = function
  | [] -> rev a
  | h::t -> process (h::a) t (* Detect __AUTO and __AUTODEF *)

let go infile outfile compress =
  let indata = lines (contents_of_file infile) in
  let processed = process [] lines in
    contents_to_file outfile (implode processed)

let () =
  match Sys.argv with
  | [|_; infile; outfile|] -> go infile outfile false
  | [|_; infile; outfile; "compress"|] -> go infile outfile true
  | _ -> Printf.eprintf "compressor: unknown command line\n"
