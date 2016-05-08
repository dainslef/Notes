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
	private final int queen = 8;
	private int count = 0;
	private int[] map = new int[queen];

	int getCount() {
		return count;
	}

	void queen(int row) {
		if (row == queen) {
			count++;
			System.out.println("\n找到了第" + count + "种方法：");
			show();
		}
		else {
			for (int i = 0; i < queen; i++)
				if (find(row, i))
				{
					map[row] = i;
					queen(row + 1);
				}
		}
	}

	private boolean find(int row, int line) {
		for (int i = 0; i < row; i++)
			if (line == map[i] || Math.abs(map[i] - line) == Math.abs(i - row))
				return false;
		return true;
	}

	private void show() {
		for (int i = 0; i < queen; i++)
			for (int p = 0; p < queen; p++) {
				if (p == map[i])
					System.out.print("X  ");
				else
					System.out.print("_  ");
				if (p == queen - 1)
					System.out.println();
			}
	}
}
