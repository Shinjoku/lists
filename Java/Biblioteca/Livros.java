import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;

public class Livros{
//Erro de nomenclatura, deveria ser "Livro";

	private String nome;
	private int qntd;
	
	Livros(String nome, int qntd){
		this.nome = nome;
		this.qntd = qntd;
	}
	
							//Getters e Setters:
	//Nome:
	public void setNome(String nome){
		this.nome = nome;
	}
	
	public String getNome(){
		return nome;
	}
	
	//Quantidade de Livros:
	public void setQntd(int qntd){
		this.qntd = qntd;
	}
	
	public int getQntd(){
		return qntd;
	}
	//------>Incrementar e Decrementar:
	public void incQntd(){
		qntd++;
	}
	
	public void decQntd(){
		qntd--;
	}
	
	@Override
		public String toString(){
			return "------------------------\n" + "Título: " + this.getNome() + "\nQuantidade: " + this.getQntd() + "\n------------------------\n";
		}
}
