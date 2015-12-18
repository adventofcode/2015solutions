package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p1a {
    
    static boolean[][] quad1 = new boolean[2048][2048];
    static boolean[][] quad2 = new boolean[2048][2048];
    static boolean[][] quad3 = new boolean[2048][2048];
    static boolean[][] quad4 = new boolean[2048][2048];
    static int x = 0;
    static int y = 0;

    public static boolean moveSanta(String direction){
        switch(direction){
            case "^":
                y++;
                break;
            case ">":
                x++;
                break;
            case "<":
                x--;
                break;
            case "v":
                y--;
                break;
        }
        if(x > -1 && y > -1){
            if(!quad1[x][y]){
                quad1[x][y] = true;
                return true;
            }
        }
        else if(x > -1 && y < 0){
            if(!quad2[x][-y]){
                quad2[x][-y] = true;
                return true;
            }
        }
        else if(x < 0 && y < 0){
            if(!quad3[-x][-y]){
                quad3[-x][-y] = true;
                return true;
            }
        }
        else if(x < 0 && y > -1){
            if(!quad4[-x][y]){
                quad4[-x][y] = true;
                return true;
            }
        }
        else{
            System.out.println("Unhandled case: x = " + x + ", y = " + y);
        }
        return false;
    }
    
    public static void main(String[] args) throws FileNotFoundException{
        int total = 1;
        quad1[0][0] = true;
        
        Scanner s = new Scanner(new File("input"));
        s.useDelimiter("");
        
        while(s.hasNext()){
            if(moveSanta(s.next())){
                total++;
            }
        }

        System.out.println("Total number of houses visited: " + total);
    }
}
