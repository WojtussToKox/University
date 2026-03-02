let find_tail list value =
  let rec find_rec current_list index acc =
    match current_list with
    | [] -> acc
    | head :: tail when head = value ->
        find_rec tail (index + 1) (index :: acc)
    | _ :: tail ->
        find_rec tail (index + 1) acc
  in
  find_rec list 0 []


let find list value =
  let rec find_rec current_list index =
    match current_list with
    | [] -> []
    | head :: tail when head = value ->
        index :: find_rec tail (index + 1)
    | _ :: tail ->
        find_rec tail (index + 1)
  in
  find_rec list 0


let test_list = [1; 2; 3; 1; 5; 3]
let test_list2 = [1; 2; 3; 3; 2; 1]
let test_list3 = ["A"; "B"; "C"; "B"; "B"]


let find_in_numbers_tail = find_tail test_list
let find_in_123_tail = find_tail test_list2
let find_in_letters_tail = find_tail test_list3


let find_in_numbers = find test_list
let find_in_123 = find test_list2
let find_in_letters = find test_list3


let result1 = find_in_numbers_tail 3
let result2 = find_in_123_tail 3
let result3 = find_in_letters_tail "B"
let result4 = find_in_numbers 3
let result5 = find_in_123 3
let result6 = find_in_letters "B"

=========================================
=========================================
=========================================
=========================================
=========================================


let rec split_n_rec (list : 'a list) (n : int) : 'a list list =
  if n <= 0 then
    failwith "N must be greater than 0";

  (* stworz n pustych list *)
  let rec create_empty_lists n_lists =
    if n_lists = 0 then [] else [] :: create_empty_lists (n_lists - 1)
  in

  let rec add_to_list act_list_index input_lists element current_index =
    match input_lists with
    (*gdy dojdziemy na koniec wyjdz z rekurencji*)
    | [] -> []

    | h_list :: t_lists ->
      (* wchodzimy do konca listyList i szukamy indexu do ktorego ma trafic element *)
        let rest_of_lists = add_to_list (act_list_index + 1) t_lists element current_index in

      (* jezeli znaleziono doloz go do listy i doklej pozostale listy *)
        if act_list_index = current_index then
          (element :: h_list) :: rest_of_lists
        else
          h_list :: rest_of_lists
  in

  (* Najpierw podziel na elementy, i gdy nie bedzie juz zadnej listy
     Czyli beda same elementy stworz mi puste listy *)
  let rec split list_to_split n_total current_index =
    match list_to_split with
    | [] -> create_empty_lists n_total

    | h :: t ->
        let next_index = (current_index + 1) mod n_total in

      (* przy dzieleniu na elementy przekaz do ktorego indexu listy ma trafic dany element *)
        let sub_lists = split t n_total next_index in

      (* zacznij od subLists[0] i dodaj glowe pozostalej listy na dany index *)
        add_to_list 0 sub_lists h current_index
  in

  split list n 0

let test = [0; 1; 2; 3; 4; 5; 6; 7; 8; 9; 10; 11; 12; 13]

let result = split_n_rec test 4

=========================================
=========================================
=========================================
=========================================
=========================================


let split_n_tail_rec (list : 'a list) (n : int) : 'a list list =
  if n <= 0 then
    failwith "N must be greater than 0";
  
  let rec create_empty_lists n_lists acc =
    if n_lists = 0 then acc else create_empty_lists (n_lists - 1) ([] :: acc)
  in

  let initial_lists = create_empty_lists n [] in

  let rec insert_element act_index target_index element acc_lists =
    match acc_lists with
    | [] -> []

    | h_list :: t_lists ->
        let rest = insert_element (act_index + 1) target_index element t_lists in
        if act_index = target_index then
          (element :: h_list) :: rest (* Dodaj element na głowę podlisty *)
        else
          h_list :: rest (* Pozostaw inne podlisty bez zmian *)
  in

  
  let rec split remaining_list acc current_index =
    match remaining_list with
    | [] -> acc

    | h :: t ->
        let next_index = (current_index + 1) mod n in

      (* The list manipulation step that is not tail-recursive: *)
        let new_acc = insert_element 0 current_index h acc in
      
        split t new_acc next_index 
  in

  (* The sublists are built by prepending elements, so they must be reversed 
     to maintain the original order of elements within the sublists. *)
  split list initial_lists 0




let test = [0; 1; 2; 3; 4; 5; 6; 7; 8; 9; 10; 11; 12; 13]

let result = split_n_tail_rec test 4
    
    =========================================
    =========================================
    =========================================
    =========================================
    =========================================

let split_n_tail_rec (list : 'a list) (n : int) : 'a list list =
  if n <= 0 then
    failwith "N must be greater than 0";

  (* tworzy n pustych list *)
  let rec create_empty_lists n_lists acc =
    if n_lists = 0 then acc else create_empty_lists (n_lists - 1) ([] :: acc)
  in

  let initial_lists = create_empty_lists n [] in

  (* dodaje element do listy o indeksie wantedIndex *) 
  let rec find_sublist_and_add acc wanted_index value pos new_acc =
    match acc with
    (* BEZ UZYCIA REVERSE TUTAJ SIE TAK SYPIE PROGRAM ŻE NIE MAM POJĘCIA O CO CHODZI *)
    | [] -> new_acc
    | h :: t ->
        if pos = wanted_index then
          find_sublist_and_add t wanted_index value (pos + 1) ((value :: h) :: new_acc)
        else
          find_sublist_and_add t wanted_index value (pos + 1) (h :: new_acc)
  in

  (* główna funkcja dzieląca listę na n podlist *)
  let rec split remaining_list acc current_index =
    match remaining_list with
    | [] -> acc
    | h :: t ->
        let new_acc = find_sublist_and_add acc current_index h 0 [] in
        let next_index = (current_index + 1) mod n in
        split t new_acc next_index
  in

  (split list initial_lists 0)

    
let test = [0; 1; 2; 3; 4; 5; 6; 7; 8; 9; 10; 11; 12; 13]

let result = split_n_tail_rec test 5
    