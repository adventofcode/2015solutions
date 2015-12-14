package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p2a {
    
    static int[][] distances = new int[8][2504];

    public static void main(String[] args) throws FileNotFoundException{
        
        Scanner s = new Scanner(new File("input"));
        
        String input;
        String[] params;
        int speed, stamina, rest;
        int counter;
        boolean flying;
        int distance;

        for(int c = 0; c < 8; c++){
            input = s.nextLine();

            params = input.split(" ");

            speed = Integer.parseInt(params[3]);
            stamina = Integer.parseInt(params[6]);
            rest = Integer.parseInt(params[13]);
            
            counter = 0;
            flying = true;
            distance = 0;
            
            for(int i = 1; i < 2504; i++){
                if(flying){
                    if(counter < stamina){
                        distance += speed;
                        counter++;
                    }
                    else if(counter >= stamina){
                        flying = false;
                        counter = 1;
                    }
                }
                else{
                    if(counter < rest){
                        counter++;
                    }
                    else if(counter >= rest){
                        flying = true;
                        distance += speed;
                        counter = 1;
                    }
                }
                distances[c][i] = distance;
            }
        }
        
        int record = 0;
        
        for(int i = 1; i < 2504; i++){
            for(int[] j : distances){
                if(j[i] > record){
                    record = j[i];
                }
            }
            for(int[] j : distances){
                if(j[i] == record){
                    j[0]++;
                }
            }
            record = 0;
        }
        
        for(int[] i : distances){
            if(i[0] > record){
                record = i[0];
            }
        }

        System.out.println("The winning reindeer has " + record +" points.");
    }
}
