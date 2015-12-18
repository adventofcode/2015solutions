package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p2a {
    
    static boolean[][] quad1 = new boolean[2048][2048];
    static boolean[][] quad2 = new boolean[2048][2048];
    static boolean[][] quad3 = new boolean[2048][2048];
    static boolean[][] quad4 = new boolean[2048][2048];
    static int x1 = 0;
    static int y1 = 0;
    static int x2 = 0;
    static int y2 = 0;

    public static boolean moveSanta(String direction){
        switch(direction){
            case "^":
                y1++;
                break;
            case ">":
                x1++;
                break;
            case "<":
                x1--;
                break;
            case "v":
                y1--;
                break;
        }
        if(x1 > -1 && y1 > -1){
            if(!quad1[x1][y1]){
                quad1[x1][y1] = true;
                return true;
            }
        }
        else if(x1 > -1 && y1 < 0){
            if(!quad2[x1][-y1]){
                quad2[x1][-y1] = true;
                return true;
            }
        }
        else if(x1 < 0 && y1 < 0){
            if(!quad3[-x1][-y1]){
                quad3[-x1][-y1] = true;
                return true;
            }
        }
        else if(x1 < 0 && y1 > -1){
            if(!quad4[-x1][y1]){
                quad4[-x1][y1] = true;
                return true;
            }
        }
        else{
            System.out.println("Unhandled case: x = " + x1 + ", y = " + y1);
        }
        return false;
    }
    
    public static boolean moveRoboSanta(String direction){
        switch(direction){
            case "^":
                y2++;
                break;
            case ">":
                x2++;
                break;
            case "<":
                x2--;
                break;
            case "v":
                y2--;
                break;
        }
        if(x2 > -1 && y2 > -1){
            if(!quad1[x2][y2]){
                quad1[x2][y2] = true;
                return true;
            }
        }
        else if(x2 > -1 && y2 < 0){
            if(!quad2[x2][-y2]){
                quad2[x2][-y2] = true;
                return true;
            }
        }
        else if(x2 < 0 && y2 < 0){
            if(!quad3[-x2][-y2]){
                quad3[-x2][-y2] = true;
                return true;
            }
        }
        else if(x2 < 0 && y2 > -1){
            if(!quad4[-x2][y2]){
                quad4[-x2][y2] = true;
                return true;
            }
        }
        else{
            System.out.println("Unhandled case: x = " + x2 + ", y = " + y2);
        }
        return false;
    }
    
    public static void main(String[] args) throws FileNotFoundException{
        int total = 1;
        quad1[0][0] = true;
        boolean roboSanta = false;
        
        Scanner s = new Scanner(new File("input"));
        s.useDelimiter("");
        
        while(s.hasNext()){
            if(roboSanta){
                if(moveRoboSanta(s.next())){
                    total++;
                }
            }
            else{
                if(moveSanta(s.next())){
                    total++;
                }
            }
            roboSanta = !roboSanta;
        }

        System.out.println("Total number of houses visited: " + total);
    }
}
