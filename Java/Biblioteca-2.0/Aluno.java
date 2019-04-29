public class Aluno extends Usuario{
	

	//Construtor:
	Aluno (String nome, String id){
		super(nome, id);
		limiteLivros = 3;
		limiteDias = 5;
	}
	
	//Print info
	@Override
		public String toString(){
			return "------------------------\n" 
			+ "Aluno:"
			+ "\nNome: " + this.getNome()
			+ "\nRA: " + this.getId() 
			+ "\nLivros Pegos: " + this.livrosPegos 
			+ "\n------------------------\n";
		}
}
