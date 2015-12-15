package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class p1a {

    static ArrayList<Integer[]> recipes = new ArrayList<>();
    static int[][] properties = new int[4][5];

    static{
        for(int a = 0; a <= 100; a++){
            for(int b = 0; b <= 100 - a; b++){
                for(int c = 0; c <= 100 - a - b; c++){
                    for(int d = 0; d <= 100 - a - b - c; d++){
                        recipes.add(new Integer[]{a, b, c, d});
                    }
                } 
            }
        }
    }

    static int calculateScore(Integer[] recipe){
        int capacity    = 0;
        int durability  = 0;
        int flavor      = 0;
        int texture     = 0;

        for(int i = 0; i < 4; i++){
            capacity    += recipe[i] * properties[i][0];
            durability  += recipe[i] * properties[i][1];
            flavor      += recipe[i] * properties[i][2];
            texture     += recipe[i] * properties[i][3];
        }

        if(capacity < 0 || durability < 0 || texture < 0 || flavor < 0){
            return 0;
        }
        else{
            return capacity * durability * texture * flavor;
        }
    }

    public static void main(String[] args) throws FileNotFoundException{

        Scanner s = new Scanner(new File("input"));

        String input;
        String[] params;

        for(int i = 0; i < 4; i++){
            input = s.nextLine();
            params = input.split(" ");
            properties[i][0] = Integer.parseInt(params[2].replace(",", ""));
            properties[i][1] = Integer.parseInt(params[4].replace(",", ""));
            properties[i][2] = Integer.parseInt(params[6].replace(",", ""));
            properties[i][3] = Integer.parseInt(params[8].replace(",", ""));
        }

        int best = 0;
        int score;

        for(Integer[] i : recipes){
            score = calculateScore(i);
            if(score > best){
                best = score;
            }
        }

        System.out.println("The best recipe has " + best +" points.");
    }
}
