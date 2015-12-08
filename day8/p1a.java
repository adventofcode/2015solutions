package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p1a {

    public static int evaluate(String s){
        char[] charArray = s.toCharArray();
        int subtract = 2;
        for(int i = 0; i < charArray.length - 1; i++){
            if(charArray[i] == '\\' && (charArray[i + 1] == '\\' || charArray[i + 1] == '\"')){
                subtract++;
                i++;
            }
            else if(charArray[i] == '\\' && charArray[i + 1] == 'x'){
                subtract += 3;
            }
        }

        return s.length() - subtract;
    }

    public static void main(String[] args) throws FileNotFoundException {

        int code = 0;
        int memory = 0;

        Scanner s = new Scanner(new File("input"));

        while(s.hasNext()){
            String str = s.nextLine();
            memory += evaluate(str);
            code += str.length();
        }

        System.out.println("The difference is " + (code - memory) + ".");
    }
}
