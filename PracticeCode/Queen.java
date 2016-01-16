/*
 * 代码完成时间： 2014-12-19 23:51 AM
 * 单数组方式实现八皇后问题
 * java语言实现
 */


/**
 *
 * @author dainslef
 */

public class Queen {

	public static void main(String[] args) {
		GetQueen Q = new GetQueen();
		Q.Queen(0);
		System.out.println("共找到了" + Q.count + "种解法。");
	}
		
}

class GetQueen
{
	final int queen = 8;
	int count = 0;
	int[] Map = new int[queen];
	
	void Queen(int row) {
		if (row == queen) {
			count++;
			System.out.println("找到了第" + count + "种方法：");
			show();
		}
		else {
			for (int i = 0; i < queen; i++)
				if (find(row, i))
				{
					Map[row] = i;
					Queen(row + 1);
				}
		}
	}
	
	boolean find(int row, int line) {
		for (int i = 0; i < row; i++)
			if (line == Map[i] || Math.abs(Map[i] - line) == Math.abs(i - row))
				return false;
		return true;
	}
	
	void show() {
		for (int i = 0; i < queen; i++)
			for (int p = 0; p < queen; p++) {
				if (p == Map[i])
					System.out.print("X  ");
				else
					System.out.print("_  ");
				if (p == queen - 1)
					System.out.println();
			}
	}	
}