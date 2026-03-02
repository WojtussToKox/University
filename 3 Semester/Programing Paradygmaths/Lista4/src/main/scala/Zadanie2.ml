type productUnit =
  | Kilogram
  | Piece
;;

type product = {
  code: string;
  name: string;
  price: float;
  unit: productUnit;
} ;;

type productDataBase = product list ;;



type receiptItem = (string * float) ;;

type fullReceipt = receiptItem list ;;

type receiptDataBase = fullReceipt list;;



let rec findProduct code dataBase =
  match dataBase with
  | [] -> None
  | currentProduct :: restOfDataBase ->
      if currentProduct.code = code then
        Some currentProduct
      else
        findProduct code restOfDataBase
;;

let formatUnit unit =
  match unit with
  | Kilogram -> "per Kilo"
  | Piece -> "per Piece"
;;



let prettyPrint receipt dataBase =

  let processProduct (code, quantity) =
    let productOption = findProduct code dataBase in
    match productOption with
    | None -> None
    | Some product ->
        let name = product.name in
        let price = product.price in
        let unitInfo = formatUnit product.unit in
        let totalValue = price *. quantity in

        Some (name, unitInfo, quantity, price, totalValue)
  in

  List.filter_map processProduct receipt ;;


let test_db: productDataBase = [
  { code = "101"; name = "Banan"; price = 4.50; unit = Kilogram };
  { code = "202"; name = "Czekolada"; price = 5.25; unit = Piece };
  { code = "303"; name = "Chleb"; price = 3.80; unit = Piece };
]

let test_paragon_1: fullReceipt = [
  ("101", 1.5);
  ("202", 3.0);
  ("999", 1.0);
]

let test_paragon_2: fullReceipt = []

let test_paragon_3: fullReceipt = [ ("303", 2.0) ]

let pusta_baza: productDataBase = []


let wynik1 = prettyPrint test_paragon_1 test_db


let wynik2 = prettyPrint test_paragon_2 test_db


let wynik3 = prettyPrint test_paragon_3 pusta_baza























