package L3;

import java.util.Scanner;
import java.util.Random;
import java.util.Date;

public class L3 
{
	public static void main (String args[])
	{
		System.out.print("Please, enter n, the size of the array: ");
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		in.close();
		
		Random myRand = new Random((new Date()).getTime());
		int myArr[][] = new int [n][n];
		System.out.println("The generated array:" );
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				myArr[i][j] = myRand.nextInt(2 * n) - n;
				System.out.print(myArr[i][j] + " ");
			}
			System.out.println();
		}
		
		int numLocalMins = 0;
		boolean minFlag = false;
		int xSnifts[] = {-1, -1, 0, 1, 1, 1, 0, -1};
		int ySnifts[] = {0, -1, -1, -1, 0, 1, 1, 1};
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int numMins = 0;
				int numNeigh = 0;
				for (int k = 0; k < 8; k++)
				{		
					if (i + xSnifts[k] >= 0 && i + xSnifts[k] < n && j + ySnifts[k] >= 0 && j + ySnifts[k] < n)
					{
						numNeigh++;
						if (myArr[i][j] < myArr[i + xSnifts[k]][j + ySnifts[k]])
							numMins++;
					}
				}
				if (numNeigh == numMins)
					numLocalMins++;
			}
		}
		System.out.println("There are local minimums: " + numLocalMins);
		}
	}
	