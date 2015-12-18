package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p2a {
    
    public static int ribbon(String s){
        String[] dimStrings = s.split("x");

        int x = Integer.parseInt(dimStrings[0]);
        int y = Integer.parseInt(dimStrings[1]);
        int z = Integer.parseInt(dimStrings[2]);
        
        int total = x * y * z;
        
        if(x >= y && x >= z){
            total += 2*(y + z);
        }
        else if(y >= z){
            total += 2*(x + z);
        }
        else{
            total += 2*(x + y);
        }
        
        return total;
    }
    
    public static void main(String[] args) throws FileNotFoundException {
        int total = 0;
        Scanner s = new Scanner(new File("input"));
        
        while(s.hasNext()){
            total += ribbon(s.nextLine());
        }
        
        System.out.println("You will need " + total + " feet of ribbon.");
    }
}
