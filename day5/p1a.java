package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p1a {

    public static boolean isNice(String s){
        char[] tester = s.toCharArray();
        
        int vowels = 0;
        
        boolean threeVowels;
        boolean letterPair = false;
        
        for(int i = 0; i < tester.length; i++){
            if(tester[i] == 'a' || tester[i] == 'e' || tester[i] == 'i' || tester[i] == 'o' || tester[i] == 'u'){
                vowels++;
            }
            
            if(i < tester.length - 1){
                if(tester[i] == tester[i + 1]){
                    letterPair = true;
                }

                switch(tester[i]){
                    case 'a':
                        if(tester[i + 1] == 'b'){
                            return false;
                        }
                        break;
                    case 'c':
                        if(tester[i + 1] == 'd'){
                            return false;
                        }
                        break;
                    case 'p':
                        if(tester[i + 1] == 'q'){
                            return false;
                        }
                        break;
                    case 'x':
                        if(tester[i + 1] == 'y'){
                            return false;
                        }
                        break;
                }
            }
        }
        
        threeVowels = vowels > 2;
        
        return threeVowels && letterPair;
    }
    
    public static void main(String[] args) throws FileNotFoundException, InterruptedException{
        
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