package banco;

public class Conta {
	
	//Atributos:
	int numConta;
	String dono;
	double saldo;
	double limite;
	
	//Métodos
	void deposita(double quant){
		this.saldo += quant;
	}
	
	void saca(double quant){
	    this.saldo -= quant;
	}
	
}
