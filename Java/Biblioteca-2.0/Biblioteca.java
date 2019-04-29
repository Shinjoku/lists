import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;

class Biblioteca{
	
	private List<Usuario> usuarios = new ArrayList<Usuario>();
	private List<Livro> livros = new ArrayList<Livro>();
	Scanner input = new Scanner(System.in);
	private String data;
	
	Biblioteca (){
		System.out.printf("Digite a data (dd/mm/aaaa): ");
		data = input.nextLine();
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
		
		System.out.printf("Digite o nome do usuário: ");
		input.nextLine();
		String nome = input.nextLine();
		
		System.out.printf("Digite o ID do usuário: ");
		String id = input.next();
		
		System.out.printf("Digite o código de cadastro.\n1 - Professor\n2 - Aluno\n3 - Aluno de Pós-Graduação\n");
		int choice = input.nextInt();
		
		for(Usuario i : usuarios){						//Verifica se já existe o aluno no Banco de Dados	
			if(id.equals(i.getId())){
				insere = false;
				System.out.println("O usuário já existe! O cadastro falhou.");
			}
		}
		
		if(insere == true){
			if(choice == 1){
				
				usuarios.add(new Professor(nome, id));
			}
			else if (choice == 2){ 
				
				usuarios.add(new Aluno(nome, id));
			}
			else if (choice == 3) {
				
				System.out.printf("Digite o curso que o aluno de pós está cursando: ");
				String curso = input.nextLine();
				usuarios.add(new Pos(nome, id, curso));
			}
			System.out.println("Usuário adicionado com sucesso!");
		}
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
		
		
		for(Livro i : livros)						//Verifica se já existe o livro no Banco de Dados	
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
			Livro livroX = new Livro(titulo, qntd);		//Pega dados do livro
			livros.add(livroX);
			System.out.println("Livro adicionado com sucesso!");
		}
	}

//3 - Done;
	public void emprestarLivro(String data){
		
		boolean confId = false, confLivro = false;
		boolean confIdLivros = false, confLivroExemplares = false;
		Usuario auxUser = null;
		Livro auxLivro = null;
		
		System.out.println("Digite o ID do usuário:");
		input.nextLine();
		String idUser = input.nextLine();

		System.out.println("Digite o nome do livro:");
		String nomeLivro = input.nextLine();
		
		try{
			auxUser = buscaUsuario(idUser);

			try{
				auxLivro = buscaLivro(nomeLivro);
				
				if(auxUser.getLivrosEmprestados() < auxUser.getLimiteLivros())
					confIdLivros = true;
				else
					System.out.println("O aluno já tem o máximo de livros permitidos! Tente novamente.");
					
				
				
				if(auxLivro.getQntd() != 0)
					confLivroExemplares = true;
				else
					System.out.println("Não existem exemplares disponíveis desse livro! Tente novamente.");
				
				if(confIdLivros && confLivroExemplares){
					
					auxUser.pegaLivro(auxLivro.getNome(), converteData(data, auxUser.getLimiteDias()));
					auxLivro.decQntd();
				} 
				
			} catch (LivroNaoEncontradoException e){
				
				System.out.println("O livro não foi cadastrado! Tente novamente.");
				System.out.println("O cadastro falhou.");
				menu();
			}
			
		} catch (UsuarioNaoEncontradoException e){
			
			System.out.println("O aluno não está cadastrado! Tente novamente.");
			System.out.println("O cadastro falhou.");
			menu();
		}


		
		
		System.out.println("Data de devolução: " + converteData(data, auxUser.getLimiteDias()));
	}
	
	//4 - Done;
	public int devolverLivro(){
		
		boolean confId = false, confLivro = false;
		Usuario auxUser = null;
		Livro auxLivro = null;
		String dataDevolucao;
		
		System.out.println("Digite a data de devolução:");
		input.nextLine();
		String data =  input.nextLine();
		
		System.out.println("Digite o ID do usuário:");
		String idUser = input.nextLine();
		
		System.out.println("Digite o nome do livro:");
		String nomeLivro = input.nextLine();
		
		try{
			auxUser = buscaUsuario(idUser);

			try{
				auxLivro = buscaLivro(nomeLivro);
					
					dataDevolucao = auxUser.livrosPegos.get(auxLivro.getNome());
					auxUser.userDevolveLivro(auxLivro.getNome());
					auxLivro.incQntd();
					//System.out.println("Data de devolução: " + dataDevolucao);
					if(converteDia(dataDevolucao) <= converteDia(data)){
						System.out.println("O livro foi devolvido com atraso.");
						
					} else{
						System.out.println("O livro foi devolvido com sucesso.");
						return 0;
					}
			} catch (LivroNaoEncontradoException e){
				
				System.out.println("O livro não foi cadastrado! Tente novamente.");
				menu();
			}
			
		} catch (UsuarioNaoEncontradoException e){
			
			System.out.println("O aluno não está cadastrado! Tente novamente.");
			menu();
		}

		System.out.println("A devolução falhou.");
		return 0;
	}
	
	//5 - Done;
	public void consultaLivroTitulo(){
		
		boolean confLivro = false;
		Livro auxLivro = null;
		
		System.out.println("Digite o nome do livro:");
		input.nextLine();
		String nomeLivro = input.nextLine();
		
		for(Livro l : livros){
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
		Usuario auxUser = null;
		
		System.out.println("Digite o nome do usuário:");
		input.nextLine();
		String nomeUser = input.nextLine();
		
		for(Usuario i : usuarios){
			if(nomeUser.equals(i.getNome())){
				confNome = true;
				auxUser = i;
				break;
			}
		}
		
		if(!confNome)
			System.out.println("O usuário não está cadastrado! Tente novamente.");
		else{
			System.out.println(auxUser);
		}
	}
	
	//7	- Done;
	public void alunosAtrasados(){
		
		String dataDevolucao;
		input.nextLine();
		
		//Não tem no projeto enviado:
		dataDevolucao = input.nextLine();
		//---------------------------
		
		System.out.println("Alunos que estão em atraso: ");
		
		for(Usuario i : usuarios){
			for(Livro j : livros){
				dataDevolucao = i.livrosPegos.get(j.getNome());
				if(converteDia(dataDevolucao) <= converteDia(data)){
					System.out.println("------------------------\n" 
					+ "Nome: \n" + i.getNome() 
					+"\nRA:" + i.getId() + "\n------------------------\n");
				}
			}
		}
	}

//8	- Done;
	public void consultaLivros(){
		for(Livro i : livros)
			System.out.println(i);
	}
//9	- Done;
	public void consultaAlunos(){
		for(Usuario i : usuarios)
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
	
	public String converteData(String data, int limiteDias){
		
		int manip;
		String novaData;
		int i;
		
		manip = converteDia(data);	
		manip += limiteDias;										// Adiciona 7 dias
		
		novaData = String.valueOf(manip);				// Transforma em string o dia de devolução				
		
		for(i = 2; i < data.length(); i++){					//Passa para novaData o resto da data inicial
			novaData += data.charAt(i);
		}
		
		return novaData;
	}
	
	public Usuario buscaUsuario(String idUser) throws UsuarioNaoEncontradoException {

		for(Usuario i : usuarios){
			if(idUser.equals(i.getId())){
				return i;
			}
		}
		
		throw new UsuarioNaoEncontradoException();
	}
	
	public Livro buscaLivro(String nomeLivro) throws LivroNaoEncontradoException {
		
		for(Livro l : livros){
			if(nomeLivro.equals(l.getNome())){
				return l;
			}
		}
		
		throw new LivroNaoEncontradoException();
	}
	
}
