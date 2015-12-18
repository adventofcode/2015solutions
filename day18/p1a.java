package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p1a {

    static boolean[][] lights = new boolean[100][100];

    static boolean[][] step(boolean[][] input){
        int neighbors = 0;
        boolean[][] output = new boolean[100][100];

        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j++){
                if((i == 0 || i == 99) && (j == 0 || j == 99)){
                    if(lights[i == 0 ? i+1 : i-1][j]){
                        neighbors++;
                    }
                    if(lights[i == 0 ? i+1 : i-1][j == 0 ? j+1 : j-1]){
                        neighbors++;
                    }
                    if(lights[i][j == 0 ? j+1 : j-1]){
                        neighbors++;
                    }
                }
                else if(i == 0 || i == 99){
                    if(lights[i][j-1]){
                        neighbors++;
                    }
                    if(lights[i][j+1]){
                        neighbors++;
                    }
                    if(lights[i == 0 ? i+1 : i-1][j-1]){
                        neighbors++;
                    }
                    if(lights[i == 0 ? i+1 : i-1][j]){
                        neighbors++;
                    }
                    if(lights[i == 0 ? i+1 : i-1][j+1]){
                        neighbors++;
                    }
                }
                else if(j == 0 || j == 99){
                    if(lights[i-1][j]){
                        neighbors++;
                    }
                    if(lights[i+1][j]){
                        neighbors++;
                    }
                    if(lights[i-1][j == 0 ? j+1 : j-1]){
                        neighbors++;
                    }
                    if(lights[i][j == 0 ? j+1 : j-1]){
                        neighbors++;
                    }
                    if(lights[i+1][j == 0 ? j+1 : j-1]){
                        neighbors++;
                    }
                }
                else{
                    if(lights[i-1][j-1]){
                        neighbors++;
                    }
                    if(lights[i-1][j]){
                        neighbors++;
                    }
                    if(lights[i-1][j+1]){
                        neighbors++;
                    }
                    if(lights[i][j-1]){
                        neighbors++;
                    }
                    if(lights[i][j+1]){
                        neighbors++;
                    }
                    if(lights[i+1][j-1]){
                        neighbors++;
                    }
                    if(lights[i+1][j]){
                        neighbors++;
                    }
                    if(lights[i+1][j+1]){
                        neighbors++;
                    }
                }
                if(lights[i][j]){
                    output[i][j] = !(neighbors > 3 || neighbors < 2);
                }
                else if(!lights[i][j]){
                    output[i][j] = neighbors == 3;
                }
                neighbors = 0;
            }
        }
        return output;
    }

    public static void main(String[] args) throws FileNotFoundException {        
        Scanner s = new Scanner(new File("input"));

        int total = 0;
        char[] input;
        for(int i = 0; i < 100; i++){
            input = s.nextLine().toCharArray();
            for(int j = 0; j < 100; j++){
                lights[i][j] = input[j] == '#';
            }
        }

        for(int i = 0; i < 100; i++){
            lights = step(lights);
        }

        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j++){
                if(lights[i][j]){
                    total++;
                }
            }
        }

        System.out.println("There are " + total + " lights on.");
    }
}
