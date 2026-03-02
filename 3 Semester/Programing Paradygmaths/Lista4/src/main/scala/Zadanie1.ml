type 'T lltree =
  | Empty
  | Leaf of 'T
  | Node of 'T * 'T lltree * 'T lltree
;;

let rec mapLLTree f tree =
  match tree with
  | Empty -> Empty
  | Leaf value -> Leaf (f value)
  | Node (value, lChild, rChild) -> Node (f value, mapLLTree f lChild, mapLLTree f rChild)
;;


let int_to_string x = "val:" ^ (string_of_int x);;

let input_tree = Node (100, Leaf 50, Node (25, Leaf 10, Empty) ) ;;

let test1_result = mapLLTree int_to_string Empty
let test2_result = mapLLTree int_to_string (Leaf 42)
let test3_result = mapLLTree int_to_string input_tree

