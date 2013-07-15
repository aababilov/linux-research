import javax.swing.*;
import java.io.*;
import java.util.Scanner;

public class matr 
{
	public static void main(String[] args) {
Scanner in = new Scanner (System.in);
System.out.println("Insert dimension");
int p = in.nextInt();
	int [][] a = new int[p][p];

System.out.println("Insert array");

/* for (int element: a)
element = in.nextInt();*/
	
for (int i = 0; i < p; i++)
	for (int j = 0; j < p; j++)
a[i][j] = in.nextInt();


int f = 0;
int h = 0;
int e = 0;
int i = 0;
int j = 0;
while (f != p / 2 + 1) 
	//&& (h != p / 2 + 1)
{
	
	if (e == 0)
	for (j = h; j < p - h ; j++ )
	{   
		System.out.print(a[i][j] + " ");
	}
	if (e == 1)
	for (i = f; i < p - f ; i++ )
	{
		System.out.print(a[i][j] + " ");	
	}
	if (e == 2)	
	for (j = p - h; j > h ; j-- )
	{   
		System.out.print(a[i][j] + " ");
	}
	if (e == 3)
	for (i = p - f; i > f ; i-- )
	{
		System.out.print(a[i][j] + " ");	
	}

	System.out.println();	
    if (e % 2 == 0) h++;
    else f++;
    e = (e+1) % 4;
}
}
	}