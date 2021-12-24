package cp213;

/**
 * @author Tommy Le 200298530
 * @version 2021-09-11
 */
public class Strings {
    // Constants
    public static final String VOWELS = "aeiouAEIOU";

    /**
     * Determines if string is a "palindrome": a word, verse, or sentence (such as "Able
     * was I ere I saw Elba") that reads the same backward or forward. Ignores case,
     * spaces, digits, and punctuation in the string parameter s.
     *
     * @param string a string
     * @return true if string is a palindrome, false otherwise
     */
    public static boolean isPalindrome(final String string) {

	// your code here
    	String newString = string.replaceAll("[^a-zA-Z0-9]", "");
	return newString.trim().equalsIgnoreCase( new StringBuilder(newString.trim()).reverse().toString() );
    }

    /**
     * Determines if name is a valid Java variable name. Variables names must start
     * with a letter or an underscore, but cannot be an underscore alone. The rest
     * of the variable name may consist of letters, numbers and underscores.
     *
     * @param name a string to test as a Java variable name
     * @return true if name is a valid Java variable name, false otherwise
     */
    public static boolean isValid(final String name) {

	// your code here
    	if (name.isEmpty()) {
            return false;
        }
        if (!Character.isJavaIdentifierStart(name.charAt(0))) {
            return false;
        }
        for (int i = 1; i < name.length(); i++) {
            if (!Character.isJavaIdentifierPart(name.charAt(i))) {
                return false;
            }
        }

	return true;
    }

    /**
     * Converts a word to Pig Latin. The conversion is:
     * <ul>
     * <li>if a word begins with a vowel, add "way" to the end of the word.</li>
     * <li>if the word begins with consonants, move the leading consonants to the
     * end of the word and add "ay" to the end of that. "y" is treated as a
     * consonant if it is the first character in the word, and as a vowel for
     * anywhere else in the word.</li>
     * </ul>
     * Preserve the case of the word - i.e. if the first character of word is
     * upper-case, then the new first character should also be upper case.
     *
     * @param word The string to convert to Pig Latin
     * @return the Pig Latin version of word
     */
    public static String pigLatin(String word) {

	// your code here
    	String piglatin = "";
        int flag = 0;
        for(int i = 0; i < word.length(); i++) {
            char x = word.charAt(i);
            if(x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u') {
            	if(i == 0) {
            		piglatin = word.substring(i) + word.substring(0, i) + "way";
    	            flag = 1;
    	            break;
            	}
            	piglatin = word.substring(i) + word.substring(0, i) + "ay";
	            flag = 1;
	            break;
            }
           
        }
        if(flag == 0) {
            piglatin = word + "ay";
        }
        return piglatin;
    }
    
}
    
    
    
