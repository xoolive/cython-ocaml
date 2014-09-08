let factorial =
  let rec fact cumul = function
    0 -> cumul
  | n -> fact (n*cumul) (n-1) in
  fact 1

let _ =
  Callback.register "factorial" factorial

