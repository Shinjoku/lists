import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;

public class Aluno{
	
	private String nome;
	private String ra;
	private int livrosEmprestados = 0;
	protected Map<String,String> livrosPegos = new HashMap<String,String>();

	//Construtor:
	Aluno(String nome, String ra){
		this.nome = nome;
		this.ra = ra;
	}
	
							//Getters & Setters:
	//Nome:
	public String getNome(){
		return nome;
	}
	public void setNome(String nome){
		this.nome = nome;
	}
	
	//RA:
	public String getRa(){
		return ra;
	}
	public void setRa(String ra){
		this.ra = ra;
	}
	
	//Livros Emprestados:
	public int getLivrosEmprestados(){
		return livrosEmprestados;
	}
	public void pegaLivro(String nomeLivro, String data){
			
		livrosEmprestados++;
		livrosPegos.put(nomeLivro, data);
	}
	
	public void alunoDevolveLivro(String nomeLivro){
		
		livrosEmprestados--;
		livrosPegos.remove(nomeLivro);
	}
	
	
	@Override
		public String toString(){
			return "------------------------\n" 
			+ "Nome: " + this.getNome()
			+ "\nRA: " + this.getRa() 
			+ "\nLivros Pegos: " + this.livrosPegos 
			+ "\n------------------------\n";
		}
}
