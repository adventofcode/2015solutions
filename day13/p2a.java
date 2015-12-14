package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class p2a {

    static String[] names = new String[9];
    static int[][] opinions = new int[9][9];
    static ArrayList<String> paths = new ArrayList<>();
    static { generateSeats(); }

    public static int evaluateHappiness(String s){
        String[] route = s.substring(1, s.length() - 1).split(", ");
        int[] calc = new int[route.length];

        int total = 0;

        for(int i = 0; i < route.length; i++){
            calc[i] = Integer.parseInt(route[i]);
        }
        
        total += opinions[calc[0]][calc[1]];
        total += opinions[calc[0]][calc[8]];
        for(int i = 1; i < calc.length - 1; i++){
            total += opinions[calc[i]][calc[i + 1]];
            total += opinions[calc[i]][calc[i - 1]];
        }
        total += opinions[calc[8]][calc[0]];
        total += opinions[calc[8]][calc[7]];

        return total;
    }

    public static void generateSeats(){
        char[] toAdd = new char[9];
        ArrayList<Integer> nodes = new ArrayList();
        int temp;

        for(int i = 0; i < 9; i++){
            nodes.add(i);
        }
        for(int i = 0; i < nodes.size(); i++){
            toAdd[0] = (char)(nodes.get(i) + 48);
            temp = nodes.get(i);
            nodes.remove(i);
            Solution.generateSeats(toAdd, nodes);
            nodes.add(i, temp);
        }
    }

    public static void generateSeats(char[] c, ArrayList<Integer> remaining){
        int temp;
        if(remaining.isEmpty()){
            paths.add(Arrays.toString(c));
        }
        else
        {
            for(int i = 0; i < remaining.size(); i++){
                c[9 - remaining.size()] = (char)(remaining.get(i) + 48);
                temp = remaining.get(i);
                remaining.remove(i);
                Solution.generateSeats(c, remaining);
                remaining.add(i, temp);
            }
        }
    }

    public static int parseNodeName(String s){
        for(int i = 0; i < names.length; i++){
            if(names[i] != null){
                if(s.equals(names[i])){
                    return i;
                }
            }
            else{
                names[i] = s;
                return i;
            }
        }
        return -1;
    }

    public static void main(String[] args) throws FileNotFoundException{

        String[] route;
        String input;
        int src;
        int dest;
        int sign;

        int distance;
        int max = 0;

        Scanner s = new Scanner(new File("input"));

        while(s.hasNext()){
            input = s.nextLine();
            route = input.substring(0, input.length() - 1).split(" ");
            src = parseNodeName(route[0]);
            dest = parseNodeName(route[10]);
            sign = route[2].equals("gain") ? 1 : -1;
            opinions[src][dest] = Integer.parseInt(route[3]) * sign;
        }
        
        Arrays.fill(opinions[8], 0);
        
        for(int[] i : opinions){
            i[8] = 0;
        }

        for(String path : paths){
            distance = evaluateHappiness(path);
            if(distance > max){
                max = distance;
            }
        }

        System.out.println("The maximum happiness is " + max +".");
    }
}
