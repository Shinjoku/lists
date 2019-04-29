import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;

class Biblioteca{
	
	private List<Aluno> alunos = new ArrayList<Aluno>();
	private List<Livros> livros = new ArrayList<Livros>();
	Scanner input = new Scanner(System.in);
	private String data;
	
	Biblioteca(){
		menu();
	}
	
//Métodos:
	public int escolhaUsuario(){
		
		int escolha;
		
		escolha = input.nextInt();
		
		switch(escolha){
			case 1:
				cadastraAluno();
				break;
			case 2:
				cadastraLivro();
				break;
			case 3:
				emprestarLivro(data);
				break;
			case 4:
				devolverLivro();
				break;
			case 5:
				consultaLivroTitulo();
				break;
			case 6:
				consultaUsuarioNome();
				break;
			case 7:
				alunosAtrasados();
				break;
			case 8:
				consultaLivros();
				break;
			case 9:
				consultaAlunos();
				break;
			case 10:
				System.out.println("Programa finalizado.");
				break;
			default:
				System.out.println("Insira um número válido.");
		}
	
		return escolha;
		
	}
	
	public void menu(){
		
		System.out.printf("Digite a data (dd/mm/aaaa): ");
		data = input.nextLine();
		
		do {
			System.out.println("Digite o número referente à escolha:");
			System.out.println("1 - Cadastrar Aluno;");
			System.out.println("2 - Cadastrar Livro;");
			System.out.println("3 - Emprestar Livro;");
			System.out.println("4 - Devolver Livro;");
			System.out.println("5 - Consultar Livro (Por Título);");
			System.out.println("6 - Consultar Usuário (Por Nome);");
			System.out.println("7 - Consultar Alunos Com Devolução Em Atraso;");
			System.out.println("8 - Consultar Livros (Todos Cadastrados Até o Momento);");
			System.out.println("9 - Consultar Alunos (Todos Cadastrados Até o Momento);");
			System.out.println("10 - Finalizar Programa;");
						
		} while (escolhaUsuario() != 10);
	}
//1	- Done;
	public void cadastraAluno(){
		
		boolean insere = true;
		
		System.out.printf("Digite o nome do aluno: ");
		input.nextLine();
		String nome = input.nextLine();
		
		System.out.printf("Digite o RA do aluno: ");
		String ra = input.next();
		
		for(Aluno i : alunos){						//Verifica se já existe o aluno no Banco de Dados	
			if(ra.equals(i.getRa())){
				insere = false;
				System.out.println("O Aluno já existe! O cadastro falhou.");
			}
		}
		
		if(insere == true){
			Aluno alunoX = new Aluno(nome, ra);
			alunos.add(alunoX);
			System.out.println("Aluno adicionado com sucesso!");
		}
		
		insere = true;
	}
//2 - Done;
	public void cadastraLivro(){
		
		boolean insere = true;
		
		String titulo;
		int qntd;
		
		do{
			System.out.println("Digite o título do livro:");
			input.nextLine();
			titulo = input.nextLine();
			
			System.out.println("Digite a quantidade de exemplares:");
			qntd = input.nextInt();
		
			if(qntd > 5)
				System.out.println("O número máximo de exemplares é 5! Tente novamente com um número válido.");
				
		} while (qntd > 5);
		
		
		for(Livros i : livros)						//Verifica se já existe o livro no Banco de Dados	
			if(titulo.equals(i.getNome())){
				insere = false;
				if(i.getQntd() < 5){
					i.incQntd();
					System.out.println("O livro já existe! Por isso, sua quantidade foi aumentada em 1.");
				}
				else
					System.out.println("O livro já existe e já existem 5 exemplares! O cadastro falhou");
			}
				
		if(insere == true){
			Livros livroX = new Livros(titulo, qntd);		//Pega dados do livro
			livros.add(livroX);
			System.out.println("Livro adicionado com sucesso!");
		}
		
		insere = true;
	}
//3 - Done;
	public void emprestarLivro(String data){
		
		boolean confRa = false, confLivro = false;
		boolean confRaLivros = false, confLivroExemplares = false;
		Aluno auxAluno = null;
		Livros auxLivro = null;
		
		System.out.println("Digite o RA do aluno:");
		input.nextLine();
		String raUser = input.nextLine();

		System.out.println("Digite o nome do livro:");
		String nomeLivro = input.nextLine();
		
		for(Aluno i : alunos){
			if(raUser.equals(i.getRa())){
				confRa = true;
				auxAluno = i;
				break;
			}
		}
		if(!confRa)
			System.out.println("O aluno não está cadastrado! Tente novamente.");
		
		if(auxAluno.getLivrosEmprestados() < 3)
			confRaLivros = true;
		else
			System.out.println("O aluno já tem o máximo de livros permitidos! Tente novamente.");
			
		
		for(Livros l : livros){
			if(nomeLivro.equals(l.getNome())){
				confLivro = true;
				auxLivro = l;
				break;
			}
		}
		if(!confLivro)
			System.out.println("O livro não foi cadastrado! Tente novamente.");
		
		if(auxLivro.getQntd() != 0)
			confLivroExemplares = true;
		else
			System.out.println("Não existem exemplares disponíveis desse livro! Tente novamente.");
		
		if(confRa && confLivro && confRaLivros && confLivroExemplares){
			
			auxAluno.pegaLivro(auxLivro.getNome(), converteData(data));
			auxLivro.decQntd();
			
		} 
		else
			System.out.println("O cadastro falhou.");
		
		
		System.out.println("Data de devolução: " + converteData(data));
		
	}
//4 - Done;
	public void devolverLivro(){
		
		boolean confRa = false, confLivro = false;
		Aluno auxAluno = null;
		Livros auxLivro = null;
		String dataDevolucao;
		
		System.out.println("Digite a data de devolução:");
		input.nextLine();
		String data =  input.nextLine();
		
		System.out.println("Digite o RA do aluno:");
		String raUser = input.nextLine();
		
		System.out.println("Digite o nome do livro:");
		String nomeLivro = input.nextLine();
		
		for(Aluno i : alunos){
			if(raUser.equals(i.getRa())){
				confRa = true;
				auxAluno = i;
				break;
			}
		}
		
		if(!confRa)
			System.out.println("O aluno não está cadastrado! Tente novamente.");
		
		
		for(Livros l : livros){
			if(nomeLivro.equals(l.getNome())){
				confLivro = true;
				auxLivro = l;
				break;
			}
		}
		
		if(!confLivro)
			System.out.println("O livro não foi cadastrado! Tente novamente.");
		
		if(confRa && confLivro){
			
			dataDevolucao = auxAluno.livrosPegos.get(auxLivro.getNome());
			auxAluno.alunoDevolveLivro(auxLivro.getNome());
			auxLivro.incQntd();
			//System.out.println("Data de devolução: " + dataDevolucao);
			if(converteDia(dataDevolucao) <= converteDia(data)){
				System.out.println("O livro foi devolvido com atraso.");
				
			} else
				System.out.println("O livro foi devolvido com sucesso.");
				
		} 
		else
			System.out.println("A devolução falhou.");
	}
//5 - Done;
	public void consultaLivroTitulo(){
		
		boolean confLivro = false;
		Livros auxLivro = null;
		
		System.out.println("Digite o nome do livro:");
		input.nextLine();
		String nomeLivro = input.nextLine();
		
		for(Livros l : livros){
			if(nomeLivro.equals(l.getNome())){
				confLivro = true;
				auxLivro = l;
				break;
			}
		}
		
		if(!confLivro)
			System.out.println("O livro não foi cadastrado! Tente novamente.");
		else
			System.out.println(auxLivro);
		
	}
//6	- Done;
	public void consultaUsuarioNome(){
		
		boolean confNome = false;
		Aluno auxAluno = null;
		
		System.out.println("Digite o nome do aluno:");
		input.nextLine();
		String nomeUser = input.nextLine();
		
		for(Aluno i : alunos){
			if(nomeUser.equals(i.getNome())){
				confNome = true;
				auxAluno = i;
				break;
			}
		}
		
		if(!confNome)
			System.out.println("O aluno não está cadastrado! Tente novamente.");
		else{
			System.out.println(auxAluno);
		}
	}
//7	- Done;
	public void alunosAtrasados(){
		
		String dataDevolucao;
		input.nextLine();
		
		System.out.println("Alunos que estão em atraso: ");
		
		for(Aluno i : alunos){
			for(Livros j : livros){
				dataDevolucao = i.livrosPegos.get(j.getNome());
				if(converteDia(dataDevolucao) <= converteDia(data)){
					System.out.println("------------------------\n" 
					+ "Nome: \n" + i.getNome() 
					+"\nRA:" + i.getRa() + "\n------------------------\n");
				}
			}
		}
	}
//8	- Done;
	public void consultaLivros(){
		for(Livros i : livros)
			System.out.println(i);
	}
//9	- Done;
	public void consultaAlunos(){
		for(Aluno i : alunos)
			System.out.println(i);
	}
	
//Funções auxilliares:
	public int converteDia(String data){
		
		String dia = "";
		int i = 0;
		int manip;
		
		while (data.charAt(i) != '/' && i < data.length()){			// Procura / e vai dando append em "dia"
			dia += data.charAt(i);
			i++;
		}
		
		manip = Integer.parseInt(dia); 					// Transforma dia (string) em inteiro
		return manip;									/// Retorna o dia em int
	}
	
	public String converteData(String data){
		
		int manip;
		String novaData;
		int i;
		
		manip = converteDia(data);	
		manip += 7;										// Adiciona 7 dias
		
		novaData = String.valueOf(manip);				// Transforma em string o dia de devolução				
		
		for(i = 2; i < data.length(); i++){					//Passa para novaData o resto da data inicial
			novaData += data.charAt(i);
		}
		
		return novaData;
	}
	

}
