package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p1a {

    public static boolean[][] lights = new boolean[1000][1000];
    
    public static void execute(String s){
        String[] instructions = s.split(" ");
        int startX;
        int startY;
        int endX;
        int endY;
        
        if(instructions[0].equals("toggle")){
            startX = Integer.parseInt(instructions[1].split(",")[0]);
            startY = Integer.parseInt(instructions[1].split(",")[1]);
            endX = Integer.parseInt(instructions[3].split(",")[0]);
            endY = Integer.parseInt(instructions[3].split(",")[1]);
            
            for(int i = startX; i <= endX; i++){
                for(int j = startY; j <= endY; j++){
                    lights[i][j] = !lights[i][j];
                }
            }            
        }
        else if(instructions[0].equals("turn")){
            startX = Integer.parseInt(instructions[2].split(",")[0]);
            startY = Integer.parseInt(instructions[2].split(",")[1]);
            endX = Integer.parseInt(instructions[4].split(",")[0]);
            endY = Integer.parseInt(instructions[4].split(",")[1]);
            
            if(instructions[1].equals("on")){
                for(int i = startX; i <= endX; i++){
                    for(int j = startY; j <= endY; j++){
                        lights[i][j] = true;
                    }
                }
            }
            else if(instructions[1].equals("off")){
                for(int i = startX; i <= endX; i++){
                    for(int j = startY; j <= endY; j++){
                        lights[i][j] = false;
                    }
                }
            }
        }
    }
    
    public static void main(String[] args) throws FileNotFoundException {
        
        int count = 0;
        
        Scanner s = new Scanner(new File("input"));
        
        while(s.hasNext()){
            execute(s.nextLine());
        }
        
        for(boolean[] b : lights){
            for(boolean c : b){
                if(c){
                    count++;
                }
            }
        }
        
        System.out.println("There are " + count + " lights on.");
    }
}
