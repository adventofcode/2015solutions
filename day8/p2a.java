package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p2a {

    public static int evaluate(String s){
        char[] charArray = s.toCharArray();
        int add = 2;
        for(int i = 0; i < charArray.length; i++){
            if(charArray[i] == '\\' || charArray[i] == '\"'){
                add++;
            }
        }

        return s.length() + add;
    }

    public static void main(String[] args) throws FileNotFoundException {

        int str_rep = 0;
        int str_length = 0;

        Scanner s = new Scanner(new File("input"));

        while(s.hasNext()){
            String str = s.nextLine();
            str_rep += evaluate(str);
            str_length += str.length();
        }

        System.out.println("The difference is " + (str_rep - str_length) + ".");
    }
}
