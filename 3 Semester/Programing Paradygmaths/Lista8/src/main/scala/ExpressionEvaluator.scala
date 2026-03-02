object ExpressionEvaluator {

  def evaluate[T](expr: Node[T], vars: Map[String, Any]): T = {
    expr match {
      case Const(value) => value

      case Variable(name) =>
        vars.get(name) match {
          case Some(value) => value.asInstanceOf[T]
          case None => throw new RuntimeException(s"Błąd: Nie znaleziono zmiennej '$name'!")
        }

      case UnaryOp(arg, op) =>
        val argValue = evaluate(arg, vars)
        op(argValue)

      case BinaryOp(left, right, op) =>
        val leftVal = evaluate(left, vars)
        val rightVal = evaluate(right, vars)
        op(leftVal, rightVal)
    }
  }
}
