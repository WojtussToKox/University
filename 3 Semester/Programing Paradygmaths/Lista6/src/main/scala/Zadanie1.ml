let make_list n v = List.init n (fun _ -> v)

let next_row prev_row =
  let rec scan acc list =
    match list with
    | [] -> []
    | h :: t ->
        let new_val = h + acc in
        new_val :: scan new_val t
  in
  scan 0 prev_row
;;

let rec pascalGiftF n r =
  if r = 0 then make_list n 1
  else next_row (pascalGiftF n (r - 1))
;;

pascalGiftF 5 0;;
pascalGiftF 5 1;;
pascalGiftF 5 2;;
pascalGiftF 5 3;;