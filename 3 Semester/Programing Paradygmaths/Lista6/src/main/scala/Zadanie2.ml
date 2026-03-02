let pascalGiftI n r =
  let arr = Array.make n 1 in
  let i = ref 1 in
  while !i <= r do
    let j = ref 1 in
    while !j < n do
      arr.(!j) <- arr.(!j) + arr.(!j - 1);
      j := !j + 1
    done;
    i := !i + 1
  done;
  
  Array.to_list arr
;;
pascalGiftI 2 0;;
pascalGiftI 3 1;;
pascalGiftI 4 2;;
pascalGiftI 4 3;;
