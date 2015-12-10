package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p1a {

    public static int paper(String s){
        String[] dimStrings = s.split("x");

        int x = Integer.parseInt(dimStrings[0]);
        int y = Integer.parseInt(dimStrings[1]);
        int z = Integer.parseInt(dimStrings[2]);
        
        int dim1 = x * y;
        int dim2 = y * z;
        int dim3 = x * z;
        
        int total = 2*dim1 + 2*dim2 + 2*dim3;
        
        if(dim1 <= dim2 && dim1 <= dim3){
            total += dim1;
        }
        else if(dim2 <= dim3){
            total += dim2;
        }
        else{
            total += dim3;
        }
        
        return total;
    }
    
    public static void main(String[] args) throws FileNotFoundException {
        int total = 0;
        Scanner s = new Scanner(new File("input"));
        
        while(s.hasNext()){
            total += paper(s.nextLine());
        }
        
        System.out.println("You will need " + total + " square feet of paper.");
    }
}