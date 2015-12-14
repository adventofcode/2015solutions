package adventofcode;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class p2a {
    
    public static String findPassword(String pass){
        char[] chars = pass.toCharArray();
        chars[7]++;
        
        for(char a = chars[0]; a <= 'z'; a++){
          chars[0] = a;
          if(a == 'i' || a == 'o' || a == 'l') a++;
          for(char b = chars[1]; b <= 'z'; b++){
            chars[1] = b;
            if(b == 'i' || b == 'o' || b == 'l') b++;
            for(char c = chars[2]; c <= 'z'; c++){
              chars[2] = c;
              if(c == 'i' || c == 'o' || c == 'l') c++;
              for(char d = chars[3]; d <= 'z'; d++){
                chars[3] = d;
                if(d == 'i' || d == 'o' || d == 'l') d++;
                for(char e = chars[4]; e <= 'z'; e++){
                  chars[4] = e;
                  if(e == 'i' || e == 'o' || e == 'l') e++;
                  for(char f = chars[5]; f <= 'z'; f++){
                    chars[5] = f;
                    if(f == 'i' || f == 'o' || f == 'l') f++;
                    for(char g = chars[6]; g <= 'z'; g++){
                      chars[6] = g;
                      if(g == 'i' || g == 'o' || g == 'l') g++;
                      for(char h = chars[7]; h <= 'z'; h++){
                        if(h == 'i' || h == 'o' || h == 'l') h++;
                        chars[7] = h;
                        if(checkPassword(chars)){
                          return new String(chars);
                        } 
                      }
                      chars[7] = 'a';
                    }
                    chars[6] = 'a';
                  }
                  chars[5] = 'a';
                }
                chars[4] = 'a';
              } 
              chars[3] = 'a';
            } 
            chars[2] = 'a';
          }
          chars[1] = 'a';
        }
        
        return "";
    }
    
    public static boolean checkPassword(char[] c){
        int doubles = 0;
        boolean consecutive = false;
        
        for(int i = 0; i < c.length - 2; i++){
            if(c[i] + 2 == c[i + 1] + 1 && c[i] + 2 == c[i+2]){
                consecutive = true;
            }
        }
        for(int i = 0; i < c.length - 1; i++){
            if(c[i] == c[i+1]){
                doubles++;
                i++;
            }
        }
        return doubles > 1 && consecutive;
    }
    
    public static void main(String[] args) throws FileNotFoundException {
        Scanner s = new Scanner(new File("input"));
        
        String password = findPassword(findPassword(s.nextLine()));
        
        System.out.println("Santa's new password is " + password + ".");
    }
}
