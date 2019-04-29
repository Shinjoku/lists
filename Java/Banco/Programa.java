package banco;
import banco.Conta;

public class Programa {

	public static void main(String[] args) {
	    
	    //Criando o obj
		Conta minhaConta;
		minhaConta = new Conta();
		
		minhaConta.saldo = 100.25;
		minhaConta.dono = "José";
		
		System.out.println("Saldo = " + minhaConta.saldo);
		
		minhaConta.deposita(400.25);
		System.out.println("Novo Saldo = " + minhaConta.saldo);
	}
}
