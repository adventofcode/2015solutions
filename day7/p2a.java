package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p2a {
    
    static String[] commands = new String[339];
    static int[] wires = new int[339];
    
    public static int evaluate(String wire){
        
        try{
            return Integer.parseInt(wire);
        }
        catch(NumberFormatException e){}
        
        int position = getPosition(wire);
        
        if(wires[position] != 0){
            return wires[position];
        }
        
        else{
            String command = commands[position];
            String[] commandParts = command.split(" ");
            
            if(command.contains(" AND ")){
                wires[position] = evaluate(commandParts[0]) & evaluate(commandParts[2]);
            }
            else if(command.contains(" OR ")){
                wires[position] = evaluate(commandParts[0]) | evaluate(commandParts[2]);
            }
            else if(command.contains(" LSHIFT ")){
                wires[position] = evaluate(commandParts[0]) << Integer.parseInt(commandParts[2]);
            }
            else if(command.contains(" RSHIFT ")){
                wires[position] = evaluate(commandParts[0]) >> Integer.parseInt(commandParts[2]);
            }
            else if(command.contains("NOT ")){
                wires[position] = ~evaluate(commandParts[1]);
            }
            else{
                wires[position] = evaluate(commandParts[0]);
            }
            return wires[position];
        }
    }
    
    public static int getPosition(String wire){
        char[] twoChars = wire.toCharArray();
        int multiplier;
        int additive;
        
        if(twoChars.length == 2){
            multiplier = twoChars[0] == ' ' ? 0 : (byte)twoChars[0] - 96;
            additive = (byte)twoChars[1] - 97;
            return 26 * multiplier + additive;
        }
        else{
            return (byte)twoChars[0] - 97;
        }
    }
 
    public static void main(String[] args) throws FileNotFoundException {

        Scanner s = new Scanner(new File("input.txt"));
    
        while(s.hasNext()){
            String command = s.nextLine();
            int position = getPosition(command.substring(command.length() - 2));
            commands[position] = command;
        }
        
        int b = evaluate("a");
        wires = new int[339];
        wires[1] = b;
        
        System.out.println("The value is " + evaluate("a") + ".");
    }
}