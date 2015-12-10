package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class p1a {
        
    public static ArrayList<Integer> evaluate(ArrayList<Integer> list){
        ArrayList<Integer> output = new ArrayList<>();
        
        int currentNum = list.get(0);
        int count = 1;
        for(int i = 1; i < list.size(); i++){
            if(list.get(i) != currentNum){
                output.add(count);
                output.add(currentNum);
                currentNum = list.get(i);
                count = 1;
            }
            else{
                count++;
            }
        }
        output.add(count);
        output.add(currentNum);
        return output;
    }
    
    public static void main(String[] args) throws FileNotFoundException {
        ArrayList<Integer> input = new ArrayList<>();
        
        Scanner s = new Scanner(new File("input10.txt"));
        s.useDelimiter("");
        
        while(s.hasNext()){
            input.add(s.nextInt());
        }
        
        for(int i = 0; i < 40; i++){
            input = evaluate(input);
        }
        
        System.out.println("The value is " + input.size() + ".");
    }
}
