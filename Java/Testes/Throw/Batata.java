public class Batata{
	public static void main(String args[]){
		
		int i = 15;
		
		try{
			
			excecao(i);
			
		}catch (DivisaoZero e){
			
			System.out.println("Batata");
			
		}
	}
	
	public static void excecao(int i) throws DivisaoZero{
		
		System.out.println(i/0);
		
		throw new DivisaoZero();
	}
	
}