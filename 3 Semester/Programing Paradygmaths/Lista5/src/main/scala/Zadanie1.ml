type 'a llist = LNil | LCons of 'a * (unit -> 'a llist);;

let rec lfrom k = LCons (k, function () -> lfrom (k+1));;

let rec ltake (n, lxs) =
  match (n, lxs) with
  | (0, _) -> []
  | (_, LNil) -> []
  | (n, LCons(x,xf)) -> x :: ltake(n-1, xf());;

let lsplit lxs =
  let rec take_even l =
    match l with
    | LNil -> LNil
    | LCons(x, xf) -> LCons(x, function () -> take_odd (xf()))

  and take_odd l =
    match l with
    | LNil -> LNil
    | LCons(_, xf) -> take_even (xf())
  in
  (take_even lxs, take_odd lxs);;



let naturalne = lfrom 0;;

let (indeksy_parzyste, indeksy_nieparzyste) = lsplit naturalne;;


ltake(4, indeksy_parzyste);;

ltake(4, indeksy_nieparzyste);;