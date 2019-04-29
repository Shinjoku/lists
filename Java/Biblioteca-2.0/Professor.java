public class Professor extends Usuario{
	

	//Construtor:
	Professor (String nome, String id){
		super(nome, id);
		limiteLivros = 5;
		limiteDias = 10;
	}
	
	//Print info
	@Override
		public String toString(){
			return "------------------------\n"
			+ "Professor:"
			+ "\nNome: " + this.getNome()
			+ "\nRP: " + this.getId() 
			+ "\nLivros Pegos: " + this.livrosPegos 
			+ "\n------------------------\n";
		}
}
