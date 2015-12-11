package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p2a {
    
    public static int move(String s){
        int total = 0;
        char[] characters = s.toCharArray();
        for(int i = 0; i < characters.length; i++){
            if(characters[i] == '('){
                total++;
            }
            else{
                total--;
                if(total < 0) {
                    return i + 1;
                }
            }
        }
        return -1;
    }
 
    public static void main(String[] args) throws FileNotFoundException {
        Scanner s = new Scanner(new File("input"));
    
        System.out.println("Santa moves into the basement at index " + move(s.next()) + ".");
    }
}
