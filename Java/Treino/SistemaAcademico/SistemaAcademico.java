import java.util.Scanner;
import java.util.ArrayList;

public class SistemaAcademico{
	public static void main(String args[]){
		
		int i = 0;
		Scanner input = new Scanner(System.in);
		ArrayList<Aluno_t> alunos = new ArrayList<Aluno_t>();

								//Cadastro de alunos (Por enquanto só dois alunos):
		do {
			Aluno_t aluno = new Aluno_t(input.next(), input.nextInt());
			
			aluno.addMaterias(input.next());
			aluno.addMaterias(input.next());
			
			alunos.add(aluno);
			i++;
		} while(i != 2);
		
		System.out.println();
		
		for(Aluno_t d : alunos){
			System.out.println(d);
			System.out.println("Matérias:\n" + d.materias);
		}
	}
}

class Aluno_t{
	
	private String nome;
	private int matricula;
	ArrayList materias = new ArrayList();
	
	public Aluno_t(String name, int mat){
		nome = name;
		matricula = mat;
	}
	
											//Getters e Setters:
//Nome:
	public void setNome(String name){
		nome = name;
	}
	public String getNome(){
		return nome;
	}

//Matrícula:
	public void setMatricula(int mat){
		matricula = mat;
	}
	public int getMatricula(){
		return matricula;
	}
	
//Matérias:
	public void addMaterias(String disc){
		materias.add(disc);
	}
	public ArrayList getMaterias(){
	    return materias;
    }
   
   @Override
		public String toString() {
			return "\nNome:\n" + nome + "\nRA:\n" + matricula;
	}
}