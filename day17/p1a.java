package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p1a {
    
    static int[] bottles = new int[20];
    static int total;
    
    public static void calculate(){
        for(int i = 0; i < (int)Math.pow(2, 20); i++){
            String unpadded = Integer.toBinaryString(i); 
            checkPermutation("00000000000000000000".substring(unpadded.length()) + unpadded);
        }
    }
    
    public static void checkPermutation(String s){
        char[] permutation = s.toCharArray();
        int capacity = 0;
        
        for(int i = 0; i < 20; i++){
            if(permutation[i] == '1'){
                capacity += bottles[i];
            }
        }
        if(capacity == 150){
            total++;
        }
    }
    
    public static void main(String[] args) throws FileNotFoundException {        
        Scanner s = new Scanner(new File("input"));
        
        for(int i = 0; i < 20; i++){
            bottles[i] = Integer.parseInt(s.nextLine());
        }
        
        calculate();
        
        System.out.println("There are " + total + " ways to fill the bottles.");
    }
}
