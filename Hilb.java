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
public class Hilb extends JFrame{
    
    private int level =2;
    private int dist0=512,dist=dist0;
    private int x=0,y=0;
     
    
    public void paint(Graphics g)
    {
        for (int i=level;i>0;i--)
        {
            dist = dist/2;
        }
        x = dist/2;
        y = dist/2;
        HilbertA(level,g);
    }
    
    private void HilbertA (int level,Graphics g) {
        if (level > 0) {
            
            HilbertB(level-1,g);
            lineRel(0,dist,g);
            HilbertA(level-1,g);    
            lineRel(dist,0,g);
            HilbertA(level-1,g);    
            lineRel(0,-dist,g);
            HilbertC(level-1,g);
        }
    }
    private void HilbertB (int level,Graphics g) {
        if (level > 0) {
            
            HilbertA(level-1,g);
            lineRel(dist,0,g);
            HilbertB(level-1,g);    
            lineRel(0,dist,g);
            HilbertB(level-1,g);    
            lineRel(-dist,0,g);
            HilbertD(level-1,g);
        }
    }
    private void HilbertC (int level,Graphics g) {
        if (level > 0) {
            
            HilbertD(level-1,g);
            lineRel(-dist,0,g);
            HilbertC(level-1,g);    
            lineRel(0,-dist,g);
            HilbertC(level-1,g);    
            lineRel(dist,0,g);
            HilbertA(level-1,g);
        }
    }
    private void HilbertD (int level,Graphics g) {
        if (level > 0) {
            
            HilbertC(level-1,g);
            lineRel(0,-dist,g);
            HilbertD(level-1,g);    
            lineRel(-dist,0,g);
            HilbertD(level-1,g);    
            lineRel(0,dist,g);
            HilbertB(level-1,g);
        }
    }
    
    public void lineRel(int delx, int dely,Graphics g) {
        g.drawLine ( x+50, y+50, x+delx+50, y+dely+50 );
        x += delx;    y += dely;
    }
    
    public static void main(String[] args) {
        Hilb obj = new Hilb();
        obj.setSize(1100, 1100);
        obj.setVisible(true);
        obj.setTitle("Hilbert Curve");
    }
    
}
