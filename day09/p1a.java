package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class p1a{

    static String[] names = new String[8];
    static int[][] distances = new int[8][8];
    static ArrayList<String> paths = new ArrayList<>();
    static { generatePaths(); }

    public static int evaluatePaths(String s){
        String[] route = s.substring(1, s.length() - 1).split(", ");
        int[] calc = new int[route.length];

        int total = 0;

        for(int i = 0; i < route.length; i++){
            calc[i] = Integer.parseInt(route[i]);
        }
        for(int i = 0; i < calc.length - 1; i++){
            total += distances[calc[i]][calc[i + 1]];
        }

        return total;
    }

    public static void generatePaths(){
        char[] toAdd = new char[8];
        ArrayList<Integer> nodes = new ArrayList();
        int temp;

        for(int i = 0; i < 8; i++){
            nodes.add(i);
        }
        for(int i = 0; i < nodes.size(); i++){
            toAdd[0] = (char)(nodes.get(i) + 48);
            temp = nodes.get(i);
            nodes.remove(i);
            generatePaths(toAdd, nodes);
            nodes.add(i, temp);
        }
    }

    public static void generatePaths(char[] c, ArrayList<Integer> remaining){
        int temp;
        if(remaining.isEmpty()){
            paths.add(Arrays.toString(c));
        }
        else
        {
            for(int i = 0; i < remaining.size(); i++){
                c[8 - remaining.size()] = (char)(remaining.get(i) + 48);
                temp = remaining.get(i);
                remaining.remove(i);
                generatePaths(c, remaining);
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

    public static void reflectDistances(){
        for(int i = 0; i < distances.length; i++){
            for(int j = 0; j < distances.length; j++){
                if(distances[i][j] == 0 && distances[j][i] != 0){
                    distances[i][j] = distances[j][i];
                }
                else if(distances[j][i] == 0 && distances[i][j] != 0){
                    distances[j][i] = distances[i][j];
                }
            }
        }
    }

    public static void main(String[] args) throws FileNotFoundException{

        String[] route;
        int src;
        int dest;

        int distance;
        int min = Integer.MAX_VALUE;

        Scanner s = new Scanner(new File("input"));

        while(s.hasNext()){
            route = s.nextLine().split(" ");
            src = parseNodeName(route[0]);
            dest = parseNodeName(route[2]);
            distances[src][dest] = Integer.parseInt(route[4]);
        }

        reflectDistances();

        for(String path : paths){
            distance = evaluatePaths(path);
            if(distance < min){
                min = distance;
            }
        }

        System.out.println("The minimum distance is " + min +".");
    }
}
