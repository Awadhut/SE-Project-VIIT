/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cg;
import java.awt.*;
import javax.swing.*;
import java.lang.*;
import java.util.*;
/**
 *
 * @author Rohit
 */
public class transformation extends JFrame{
    static int size = 3;
    static int [][] vert = new int[size][3];
    static int x_off = 960;
    static int y_off = 540;
    static int [][] t_mat = new int[3][3];
    static int [][] s_mat = new int[3][3];
    static double [][] r_mat = new double[3][3];
    static int [][] c = new int[size][3];
    
    public void delay()
    {
        try
        {
            Thread.sleep(2000);
        }
        catch(Throwable e)
                {
                    System.out.println(e.getMessage());
                }
    }
    
    public void clear(Graphics g)
    {
        g.clearRect(0, 0, 1920, 1080);
    }
    
    public static  void mat_mul(int a[][],int b[][])
    {
        for(int i=0;i<size;i++)
        {    
            for(int j=0;j<3;j++)
            {    
                c[i][j]=0;      
                for(int k=0;k<size;k++)      
                {      
                    c[i][j]+=a[i][k]*b[k][j];      
                }
                //System.out.print(" "+c[i][j]);
            }
            System.out.println();
        }
    }
    
    public static  void mat_mul(int a[][],double b[][])
    {
        for(int i=0;i<size;i++)
        {    
            for(int j=0;j<3;j++)
            {    
                c[i][j]=0;      
                for(int k=0;k<size;k++)      
                {      
                    c[i][j]+=a[i][k]*b[k][j];      
                }
                //System.out.print(" "+c[i][j]);
            }
            System.out.println();
        }
    }
    
    public void drawAxis(Graphics g)
    {
        g.setColor(Color.RED);
        g.drawLine(960, 0, 960, 1000);
        g.drawLine(50, 540, 1900, 540);
    }
    
    public void paint(Graphics g)
    {
        
        drawAxis(g);
        vert[0][0] = 10;
        vert[0][1] = -10;
        vert[0][2] = 1;
        vert[1][0] = 110;
        vert[1][1] = -10;
        vert[1][2] = 1;
        vert[2][0] = 60;
        vert[2][1] = -60;
        vert[2][2] = 1;
        
        t_mat[0][0] = 1;
        t_mat[0][1] = 0;
        t_mat[0][2] = 0;
        t_mat[1][0] = 0;
        t_mat[1][1] = 1;
        t_mat[1][2] = 0;
        t_mat[2][0] = 400;
        t_mat[2][1] = 0;
        t_mat[2][2] = 1;
        
        s_mat[0][0] = 2;
        s_mat[0][1] = 0;
        s_mat[0][2] = 0;
        s_mat[1][0] = 0;
        s_mat[1][1] = 2;
        s_mat[1][2] = 0;
        s_mat[2][0] = 0;
        s_mat[2][1] = 0;
        s_mat[2][2] = 1;
        
        r_mat[0][0] = Math.cos(Math.PI/3);
        r_mat[0][1] = -Math.sin(Math.PI/3);;
        r_mat[0][2] = 0;
        r_mat[1][0] = Math.sin(Math.PI/3);;
        r_mat[1][1] = Math.cos(Math.PI/3);;
        r_mat[1][2] = 0;
        r_mat[2][0] = 0;
        r_mat[2][1] = 0;
        r_mat[2][2] = 1;
        
        
        g.setColor(Color.BLUE);
        int i;
        for(i=0;i<size;i++)
        {
            g.drawLine(vert[i%size][0]+x_off, vert[i%size][1]+y_off, vert[(i+1)%size][0]+x_off, vert[(i+1)%size][1]+y_off);
        }
        int choice=0;
        do
        {
            System.out.println("Press 1 for Trnslation");
            System.out.println("Press 2 for Scaling");
            System.out.println("Press 3 for Rotation");
            Scanner s = new Scanner(System.in);

            choice = s.nextInt();
            if(choice == 1)
            {
                mat_mul(vert,t_mat);
                dr(g);
            }
            if(choice==2)
            {
                mat_mul(vert,s_mat);
                dr(g);
            }
            if(choice==3)
            {
                mat_mul(vert,r_mat);
                dr(g);
            }
        }while(choice!=0);
        
    }
    public static void dr(Graphics g)
    {
        g.setColor(Color.MAGENTA);
        int i;
        
        for(i=0;i<size;i++)
        {
            g.drawLine(c[i%size][0]+x_off, c[i%size][1]+y_off, c[(i+1)%size][0]+x_off, c[(i+1)%size][1]+y_off);
        }
    }
    
    public static void main(String[] args) {
        transformation obj = new transformation();
        
        obj.setTitle("Scan Fill");
        obj.setSize(1920, 1080);
        System.out.println("");
            obj.setVisible(true);    
    }
    
}
