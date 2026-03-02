def f(c: => Boolean)(e: Unit): Unit = if c then {
  print("CHUJ");
  f (c)(e)
}

var i=3

f(i<5){}
