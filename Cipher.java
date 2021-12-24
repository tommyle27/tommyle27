package cp213;

/**
 * @author Tommy Le 200298530
 * @version 2021-09-11
 */
public class Cipher {
    // Constants
    public static final String ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    public static final int ALPHA_LENGTH = ALPHA.length();

    /**
     * Encipher a string using a shift cipher. Each letter is replaced by a letter
     * 'n' letters to the right of the original. Thus for example, all shift values
     * evenly divisible by 26 (the length of the English alphabet) replace a letter
     * with itself. Non-letters are left unchanged.
     *
     * @param s string to encipher
     * @param n the number of letters to shift
     * @return the enciphered string
     */
    public static String shift(final String s, final int n) {

	// your code here
    	String newString = "";
        int len = s.length();
        for(int x = 0; x < len; x++){
            char c = (char)(s.charAt(x) + n);
            if (c > 'Z')
                newString += (char)(s.charAt(x) - (26-n));
            else
                newString += (char)(s.charAt(x) + n);
        }
        
    return newString;
    }

    /**
     * Encipher a string using the letter positions in ciphertext. Each letter is
     * replaced by the letter in the same ordinal position in the ciphertext.
     * Non-letters are left unchanged. Ex:
     *
     * <pre>
    Alphabet:   ABCDEFGHIJKLMNOPQRSTUVWXYZ
    Ciphertext: AVIBROWNZCEFGHJKLMPQSTUXYD
     * </pre>
     *
     * A is replaced by A, B by V, C by I, D by B, E by R, and so on. Non-letters
     * are ignored.
     *
     * @param s          string to encipher
     * @param ciphertext ciphertext alphabet
     * @return the enciphered string
     */
    public static String substitute(final String s, final String ciphertext) {

	// your code here
    	String newString = "";
    	int len = s.length();
    	for (int x = 0; x < len; x++) {
    		char Let = (char)(s.charAt(x));
    		if(Let == 'A')
    			newString += 'A';
    		else if(Let == 'B')
    			newString += 'V';
    		else if(Let == 'C')
    			newString += 'I';
    		else if(Let == 'D')
    			newString += 'B';
    		else if(Let == 'E')
    			newString += 'R';
    		else if(Let == 'F')
    			newString += 'O';
    		else if(Let == 'G')
    			newString += 'W';
    		else if(Let == 'H')
    			newString += 'N';
    		else if(Let == 'I')
    			newString += 'Z';
    		else if(Let == 'J')
    			newString += 'C';
    		else if(Let == 'K')
    			newString += 'E';
    		else if(Let == 'L')
    			newString += 'F';
    		else if(Let == 'M')
    			newString += 'G';
    		else if(Let == 'N')
    			newString += 'H';
    		else if(Let == 'O')
    			newString += 'J';
    		else if(Let == 'P')
    			newString += 'K';
    		else if(Let == 'Q')
    			newString += 'L';
    		else if(Let == 'R')
    			newString += 'M';
    		else if(Let == 'S')
    			newString += 'P';
    		else if(Let == 'T')
    			newString += 'Q';
    		else if(Let == 'U')
    			newString += 'S';
    		else if(Let == 'V')
    			newString += 'T';
    		else if(Let == 'W')
    			newString += 'U';
    		else if(Let == 'X')
    			newString += 'X';
    		else if(Let == 'Y')
    			newString += 'Y';
    		else if(Let == 'Z')
    			newString += 'D';
    	}
    	
	return newString;
    }

}
