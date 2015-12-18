package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p2a {

    public static boolean isNice(String s){
        char[] tester = s.toCharArray();
        
        boolean sandwich = false;
        boolean pairSequence = false;
        
        for(int i = 0; i < tester.length - 2; i++){
            if(tester[i] == tester[i + 2]){
                sandwich = true;
            }
            if(s.substring(i + 2).contains(s.substring(i, i + 2))){
                pairSequence = true;
            }
        }
        return sandwich && pairSequence;
    }
    
    public static void main(String[] args) throws FileNotFoundException {
        
        int count = 0;
        
        Scanner s = new Scanner(new File("input"));
        
        while(s.hasNext()){
            if(isNice(s.nextLine())){
                count++;
            }
        }
        
        System.out.println("There are " + count + " nice strings.");
    }
}
