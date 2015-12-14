package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class p2a {

    public static char[] killRed(char[] c){
        int level = 0;
        int index1 = 0;
        int index2 = 0;

        for(int i = 0; i < c.length; i++){
            if(c[i] == ':' && c[i+1] == '"' && c[i+2] == 'r'){
                for(int j = i; j > 0; j--){
                    if(c[j] == '}'){
                        level++;
                    }
                    else if(c[j] == '{' && level != 0){
                        level--;
                    }
                    else if(c[j] == '{' && level == 0){
                        index1 = j;
                        break;
                    }
                }
                for(int j = i; j < c.length; j++){
                    if(c[j] == '{'){
                        level++;
                    }
                    else if(c[j] == '}' && level != 0){
                        level--;
                    }
                    else if(c[j] == '}' && level == 0){
                        index2 = j;
                        break;
                    }
                }
                Arrays.fill(c, index1, index2 + 1, ' ');
            }
        }
        return c;
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner s = new Scanner(new File("input"));
        int output = 0;

        String input = s.nextLine();

        input = new String(killRed(input.toCharArray()));
        input = input.replaceAll("[\\[\\]\"{},:a-z]", " ");

        s = new Scanner(input);

        while(s.hasNext()){
            output += s.nextInt();
        }

        System.out.println("The sum is " + output + ".");
    }
}
