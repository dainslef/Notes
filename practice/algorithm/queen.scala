/*
 * 代码完成时间： 2016-6-17 17:29
 * 单数组方式实现八皇后问题
 * Scala语言版本，单数组Lambda内部递归实现
 */


/**
 *
 * @author dainslef
 */

object Queen extends App {

  implicit class Self(in: Self => Int => Unit) {
    def apply(self: Self) = in(self)
  }

  val QUEEN_SIZE = 8
  val chessBoard = new Array[Int](QUEEN_SIZE)

  var count = 0

  import java.lang.Math.abs

  // 使用Lambda内部自递归
  ((x: Self) => x(x)) ((queen: Self) =>
    (row: Int) =>
      if (row == QUEEN_SIZE) {
        count += 1
        println(s"\n找到了第 $count 种方法：")
        for {
          row <- 0 until QUEEN_SIZE
          line <- 0 until QUEEN_SIZE
        } {
          print(s"${if (line == chessBoard(row)) 'X' else '_'} ")
          if (line == QUEEN_SIZE - 1) println
        }
      } else
        for {
          line <- 0 until QUEEN_SIZE
          if 0 until row filter { i =>
            chessBoard(i) == line || abs(chessBoard(i) - line) == abs(i - row)
          } isEmpty
        } {
          chessBoard(row) = line
          queen(queen)(row + 1)
        }
  )(0)

  println(s"\n共找到了 $count 种解法。")

}