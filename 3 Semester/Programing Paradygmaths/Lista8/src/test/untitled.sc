def f(c: => Boolean)(e: Unit): Unit = if c then {
  e;
  f (c)(e)
}

var i=3

f(i<5){print(s"$i"); i+=1}

()