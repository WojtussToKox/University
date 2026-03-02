def isLeapYear(y:Int): Boolean = {
  (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)
}

def theVeryNextDay(day:Int, month:Int, year:Int): (Int, Int, Int) = {
  val daysInMonth = month match
    case 1 | 3 | 5 | 7 | 8 | 10 | 12 => 31
    case 4 | 6 | 9 | 11 => 30
    case 2 => if (isLeapYear(year)) 29 else 28
    case _ => throw new Exception(s"Podaj poprawny miesiac: ($month)")

  if(day <= 0 || day > daysInMonth) then
    throw new Exception(s"Podaj poprawny dzien: ($day)")
  else if(year < 0) then
    throw new Exception(s"Podaj poprawny rok: ($year)")

  else if(day < daysInMonth) then
    (day+1, month, year)
  else if (month == 12) then
    (1, 1, year+1)
  else
    (1, month+1, year)
}

theVeryNextDay(1,1,1)
theVeryNextDay(31,1,1)
theVeryNextDay(31,12,1)

theVeryNextDay(30,2,1)
theVeryNextDay(3,13,1)
theVeryNextDay(1,1,-1)

theVeryNextDay(29,2,2020)
theVeryNextDay(29,2,2021)