type 'a llist = LNil | LCons of 'a * 'a llist Lazy.t;;

let rec lfrom k = LCons (k, lazy (lfrom (k+1)));;

let rec ltake (n, lxs) =
  match (n, lxs) with
  | (0, _) -> []
  | (_, LNil) -> []
  | (n, LCons(x, lazy xs)) -> x :: ltake(n-1, xs);;


let rec lcombine f l1 l2 =
  match (l1, l2) with
  | (LCons(x, lazy t1), LCons(y, lazy t2)) ->
      LCons (f x y, lazy (lcombine f t1 t2))
  | _ -> LNil;;



let l1 = lfrom 1;;
let l2 = lfrom 10;;

let sumy = lcombine (+) l1 l2;;
ltake(3, sumy);;


let iloczyny = lcombine ( * ) l1 l2;;
ltake(3, iloczyny);; 