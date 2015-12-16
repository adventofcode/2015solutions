package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p2a {
    
    static int[] properties = {3, 7, 2, 3, 0, 0, 5, 3, 2, 1};

    static boolean identifyAunt(String input){
        String[] params = input.split(" ");
        int[] index = {indexProperties(params[2]), indexProperties(params[4]), indexProperties(params[6])};
        boolean isAunt = true;
        int[] values = {Integer.parseInt(params[3].substring(0, 1)), Integer.parseInt(params[5].substring(0, 1)), Integer.parseInt(params[7])};
        
        for(int i = 0; i < 3; i++){
            if(index[i] == 1 || index[i] == 7){
                if(!(properties[index[i]] < values[i])){
                    isAunt = false;
                }
            }
            else if(index[i] == 3 || index[i] == 6){
                if(!(properties[index[i]] > values[i])){
                    isAunt = false;
                }
            }
            else{
                if(!(properties[index[i]] == values[i])){
                    isAunt = false;
                }
            }
        }
        return isAunt;
    }
    
    static int indexProperties(String property){
        switch(property){
            case "children:":
                return 0;
            case "cats:":
                return 1;
            case "samoyeds:":
                return 2;
            case "pomeranians:":
                return 3;
            case "akitas:":
                return 4;
            case "vizslas:":
                return 5;
            case "goldfish:":
                return 6;
            case "trees:":
                return 7;
            case "cars:":
                return 8;
            case "perfumes:":
                return 9;
            default:
                return -1;
        }
    }

    public static void main(String[] args) throws FileNotFoundException{

        Scanner s = new Scanner(new File("input"));

        int aunt = 1;
        
        while(s.hasNext()){
            if(identifyAunt(s.nextLine())){
                break;
            }
            else{
                aunt++;
            }
        }

        System.out.println("Aunt Sue " + aunt + " sent you the gift.");
    }
}
