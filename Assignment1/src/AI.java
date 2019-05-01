import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
/* Dawit Tafesse CS-337
 */

public class AI {

	private static String FileName = "answers";
	
	public static void main(String[] args) throws IOException {
		Scanner scan = new Scanner(System.in);
		String []response;
	
		int j = 0;
		boolean Found = false;
		
		System.out.println("I am Eliza, cybertherapist. Anytime press Q to quit ");
		System.out.println("What troubles you?: ");
		String input = scan.nextLine();
		
		if(input.equalsIgnoreCase("q")){System.out.println("GoodBye");}
		else{
			response = askUser(input);
			
			ArrayList<ArrayList<String>> list = readText();
		
			do{
				for(int i = 0; i< list.size() && !Found; ++i){
					
					for(j = 0; j<= response.length-1 && !Found; ++j){
						if(response[j].equalsIgnoreCase(list.get(i).get(0))){
							int x = (int)(Math.random() * list.get(i).size()-1) + 1;
							System.out.println(list.get(i).get(x));
							Found = true;	
						}
					}
					
				}
				if(Found){
					String more = scan.nextLine();
					response = askUser(more);
					Found = false;
				}
				else{
					System.out.println("Tell me more: ");
					String more = scan.nextLine();
					response = askUser(more);
					Found = false;
				}
					
			}while(response!=null);	
		}
		scan.close();
	}
	/* Takes in user input and converts to string Array
	 * input: String
	 * output: String[]
	 */
	public static String[] askUser(String input)
	{
		if(!input.equalsIgnoreCase("q")){	
			String [] response = input.trim().split("[ ]+");//split string into substrings at a space
			return response;
		}
		return null;
	}
	/* Reads texts file and returns a String 2d ArrayList
	 * Input: none
	 * output: 2d String ArrayList
	 */
	public static ArrayList<ArrayList<String>> readText() throws IOException{
		BufferedReader in = new BufferedReader(new FileReader(FileName));//src/answers
		String str=null;
		ArrayList<String> lines = new ArrayList<String>();
		ArrayList<ArrayList<String>> list = new ArrayList<ArrayList<String>>();
		
		str = in.readLine();
		if(str != null){
			lines.add(str.substring(1));
		}
		while((str = in.readLine()) != null){  //add line by line
			if(str.charAt(0) != ':'){
				lines.add(str);
			}
			else{
				
				list.add(lines);
				lines = new ArrayList<String>();
				lines.add(str.substring(1));
			}
		}
		list.add(lines);
		in.close();
		return list;
	}
}
