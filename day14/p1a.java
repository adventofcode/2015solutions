package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p1a {

    public static void main(String[] args) throws FileNotFoundException{
        int distance = 0;
        int record = 0;
        String input;
        int speed, stamina, rest;
        String[] params;
        Scanner s = new Scanner(new File("input"));

        while(s.hasNext()){
            input = s.nextLine();

            params = input.split(" ");

            speed = Integer.parseInt(params[3]);
            stamina = Integer.parseInt(params[6]);
            rest = Integer.parseInt(params[13]);

            distance += (2503 / (stamina + rest)) * speed * stamina;
            distance += (2503 % (stamina + rest)) > stamina ? speed * stamina : (2503 % (stamina + rest)) * speed;

            if(distance > record){
                record = distance;
            }

            distance = 0;
        }

        System.out.println("The maximum distance is " + record +".");
    }
}
