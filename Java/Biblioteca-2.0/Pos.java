public class Pos extends Usuario{
	
	private String curso;

	//Construtor:
	Pos (String nome, String id, String curso){
		super(nome, id);
		this.curso = curso;
		limiteLivros = 3;
		limiteDias = 7;
	}
	
			//Getter
	public String getCurso(){
		return curso;
	}
	
	//Print info
	@Override
		public String toString(){
			return "------------------------\n"
			+ "Aluno de Pós Graduação:"
			+ "Curso de pós: " + this.getCurso()
			+ "\nNome: " + this.getNome()
			+ "\nRA: " + this.getId() 
			+ "\nLivros Pegos: " + this.livrosPegos 
			+ "\n------------------------\n";
		}
}
