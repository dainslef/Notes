/*
 * 代码完成时间： 2014-12-19 23:51 AM
 * 单数组方式实现八皇后问题
 * java语言实现
 */


/**
 *
 * @author dainslef
 */

public class queen {

	public static void main(String[] args) {
		GetQueen q = new GetQueen();
		q.queen(0);
		System.out.println("\n共找到了" + q.getCount() + "种解法。");
	}

}

class GetQueen
{
	private final int QUEEN_SIZE = 8;
	private int count = 0;
	private int[] chessBoard = new int[QUEEN_SIZE];

	int getCount() {
		return count;
	}

	void queen(int row) {
		if (row == QUEEN_SIZE) {
			count++;
			System.out.println("\n找到了第" + count + "种方法：");
			show();
		}
		else {
			for (int i = 0; i < QUEEN_SIZE; i++)
				if (find(row, i))
				{
					chessBoard[row] = i;
					queen(row + 1);
				}
		}
	}

	private boolean find(int row, int line) {
		for (int i = 0; i < row; i++)
			if (line == chessBoard[i] || Math.abs(chessBoard[i] - line) == Math.abs(i - row))
				return false;
		return true;
	}

	private void show() {
		for (int i = 0; i < QUEEN_SIZE; i++)
			for (int p = 0; p < QUEEN_SIZE; p++) {
				if (p == chessBoard[i])
					System.out.print("X  ");
				else
					System.out.print("_  ");
				if (p == QUEEN_SIZE - 1)
					System.out.println();
			}
	}
}
