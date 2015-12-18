package adventofcode;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import javax.xml.bind.DatatypeConverter;

public class p1a {
    
    static MessageDigest md5;

    static{
       try{
            md5 = MessageDigest.getInstance("MD5");
        }
        catch(NoSuchAlgorithmException e){
            System.out.println("Apparently MD5 doesn't exist.");
        }
    }
    
    public static String hash(String input, int answer){

        byte[] src = (input + answer).getBytes();
        String hex = DatatypeConverter.printHexBinary(md5.digest(src));

        return hex;
    }

    public static void main(String[] args){
        
        int answer = 1;
        String hash;
        
        while(true){
            hash = Solution.hash("ckczppom", answer);
            if(hash.startsWith("00000")){
                break;
            }
            answer++;
        }
        
        System.out.println("The answer is " + answer + ", producing hash " + hash + ".");
    }
}
