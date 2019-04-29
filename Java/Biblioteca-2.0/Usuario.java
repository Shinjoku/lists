import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;

public class Usuario{
    
    protected String nome;
    protected String id;
	protected int livrosEmprestados = 0;
	protected int limiteLivros = 0;
	protected Map<String,String> livrosPegos = new HashMap<String,String>();
	protected int limiteDias;
	
		//Construtor:
	Usuario (String nome, String id){
		this.nome = nome;
		this.id = id;
	}
	
	//Getters e Setters:
		//Nome:
	public String getNome(){
		return nome;
	}
	public void setNome(String nome){
		this.nome = nome;
	}
	
		//ID:
	public String getId(){
		return id;
	}
	public void setId(String id){
		this.id = id;
	}
	
		//limiteLivros:
	public int getLimiteLivros(){
		return limiteLivros;
	}
	
		//limiteDias:
	public int getLimiteDias(){
		return limiteDias;
	}
	
		//Livros Emprestados:
	public int getLivrosEmprestados(){
		return livrosEmprestados;
	}
	public void pegaLivro(String nomeLivro, String data){
			
		livrosEmprestados++;
		livrosPegos.put(nomeLivro, data);
	}
	
	public void userDevolveLivro(String nomeLivro){
		
		livrosEmprestados--;
		livrosPegos.remove(nomeLivro);
	}
}