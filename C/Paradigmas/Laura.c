#include <stdio.h>

typedef enum 
{
  SAIR=0, CADASTROALUNO, CADASTRODISCIPLINA, CADASTROPROF,
  MATRICULALUDIS, VINCPROFDIS, MATRICULALISTALUNOSLISTADISCIPLINAS,
  VINCLISTAPROFLISTADIS, EXIBEDISALUNO, EXIBEALUNODIS, EXIBEDISPROF, EXIBEPROFDIS, 
  CANCELARMATALUDISC, CANCELARVINCPROFDIS,
  CANCELARMATLISTALUNOSLISTADIS, CANCEARVINCLISTAPROFLISTADIS
} Menu;

typedef struct
{
  int ra;
  char nomealuno[30];
} Aluno;

typedef struct
{
  int codigo;
  char nomedisciplina[30];
} Disciplina;

typedef struct
{
  int ru;
  char nomeprofessor[30];
} Professor;

typedef struct
{
  Aluno student;
  Disciplina materia;
} Matricula;

typedef struct 
{
  Professor teacher;
  Disciplina materia;
} Vinculo;
int ValidaAluno(Aluno lista[],int ra, int tam)
{
  int d;
  for (d=0; d<tam; d++)
  {
    if (lista[d].ra == ra)
    {
      return d;
      break;
    }
  }
  return -1;
}

int ValidaDisciplina(Disciplina lista[], int codigo, int tam)
{
  int e;
  for (e=0; e<tam; e++)
  {
    if (lista[e].codigo == codigo)
    {
      return e;
    }
  }
  return -1;
}

int ValidaProfessor(Professor lista[], int ru, int tam)
{
  int l;
  for (l=0; l<tam; l++)
  {
    if (lista[l].ru == ru)
    {
      return l;
    }
  }
  return -1;
}

int ValidaMatricula (Matricula lista[], int ramat, int dismat, int tam)
{
  int n;
  for(n=0; n<tam; n++)
  {
    if (lista[n].student.ra == ramat && lista[n].materia.codigo == dismat)
    {
      return n;
    }
  }
  return -1;
}

int ValidaVinculo(Vinculo lista[], int ruvinc, int disvinc, int tam)
{
  int p;
  for (p=0; p<tam; p++)
  {
    if (lista[p].teacher.ru == ruvinc && lista[p].materia.codigo == disvinc)
    {
      return p;
    }
  }
  return -1;
}

void ExibeMenu()
{
  printf("1> Cadastrar Alunos (um por vez)\n");
  printf("2> Cadastrar Disciplinas (uma por vez)\n");
  printf("3> Cadastrar Professores (um por vez)\n");
  printf("4> Matricular Alunos-Disciplinas (um por vez)\n");
  printf("5> Vincular Professores-Disciplinas (um por vez)\n");
  printf("6> Matricular Lista de Alunos-Lista de Disciplinas\n");
  printf("7> Vincular Lista de Professores-Lista de Discilpinas\n");
  printf("8> Exibir as Disciplinas de um Aluno\n");
  printf("9> Exibir os Alunos de uma Disciplina\n");
  printf("10> Exibir as Disciplinas de um Professor\n");
  printf("11> Exibir os Professores de uma Disciplina\n");
  printf("12> Cancelar Matrícula Alunos-Disciplinas (uma por vez)\n");
  printf("13> Remover Vínculo Professores-Disciplinas (um por vez)\n");
  printf("14> Cancelar Matrícula Lista de Alunos-Lista de Disciplinas\n");
  printf("15> Cancelar Vínculo Lista de Professores-Lista de Disciplinas\n");
  printf("0> Sair\n");
  printf("Op: ");
}

int main()
{
  Aluno alu[30];
  Disciplina dis[30];
  Professor prof[30];
  Matricula mat[30];
  Vinculo vinc[30];
  int listalunos[30];
  int listadisciplinas[30];
  int listaprofessores[30];
  int listacancelalunos[30];
  int listacanceladisciplinas[30], listacanceladisciplinas1[30];
  int listacancelaprofessores[30];
  int a=0, b=0, c=0, f=0, j=0, k=0, m=0;
  int g, h, i, o, q, r, s, t;
  int z;
  int pegalu;
  Menu op;
  int ralu, codis, ruprof;
  int valalu, valdis, valprof, valmatri, valvinc;
  int raproc, codproc, ruproc;
  
  do
  {
    ExibeMenu();
    scanf("%u", &op);
    switch (op)
    {
      case SAIR:
	break;
      case CADASTROALUNO:
	printf("RA: ");
	scanf("%i", &alu[a].ra);
	printf("Nome do Aluno: ");
	__fpurge(stdin);
	fgets(alu[a].nomealuno, 30, stdin);
	a++;
	break;
      case CADASTRODISCIPLINA:
	printf("Código: ");
	scanf("%i", &dis[b].codigo);
	printf("Nome da Disciplina: ");
	__fpurge(stdin);
	fgets(dis[b].nomedisciplina, 30, stdin);
	b++;
	break;
      case CADASTROPROF:
	printf("RU: ");
	scanf("%i", &prof[c].ru);
	printf("Nome: ");
	__fpurge(stdin);
	fgets(prof[c].nomeprofessor, 30, stdin);
	c++;
	break;
      case MATRICULALUDIS:
	printf("RA: ");
	scanf("%i", &ralu);
	valalu = ValidaAluno(alu, ralu, a);
	if (valalu == -1)
	{
	  printf("RA não encontrado!!\n");
	}
	else
	{
	  printf("Código da disciplina: ");
	  scanf("%i", &codis);
	  valdis = ValidaDisciplina(dis, codis, b);
	  printf("%i\n", valdis);
	  if (valdis == -1)
	  {
	    printf("Disciplina não encontrada!!\n");
	  }
	  else
	  {
	    mat[f].student.ra = ralu;
	    mat[f].materia.codigo = codis;
	    f++;
	  }
	}
	break;
      case VINCPROFDIS:
	printf("RU: ");
	scanf("%i", &ruprof);
	valprof = ValidaProfessor(prof, ruprof, c);
	if (valprof == -1)
	{
	  printf("RU não encontrado!!\n");
	}
	else
	{
	  printf("Código da disciplina: ");
	  scanf("%i", &codis);
	  valdis = ValidaDisciplina(dis, codis, b);
	  printf("%i\n", valdis);
	  if (valdis == -1)
	  {
	    printf("Disciplina não encontrada!!\n");
	  }
	  else
	  {
	    vinc[m].teacher.ru = ruprof;
	    vinc[m].materia.codigo = codis;
	    m++;
	  }
	}
	break;
	case MATRICULALISTALUNOSLISTADISCIPLINAS:
	printf("Lista de Alunos: (Condição de parada: -1)\n");
	do
	{
	  scanf("%i", &listalunos[j]);
	  if (listalunos[j] != -1)
	  {
	    j++;
	  }
	} while (listalunos[j] != -1);
	printf("Lista de Disciplinas: (Condição de parada: -1)\n");
	do
	{
	  scanf("%i", &listadisciplinas[k]);
	  if (listadisciplinas[k] != -1)
	  {
	    k++;
	  }
	} while (listadisciplinas[k] != -1);
	for (g=0; g<j; g++)
	{
	  for (h=0; h<k; h++)
	  {
	    valalu = ValidaAluno(alu, listalunos[g], a);
	    if (valalu == -1)
	    {
	      printf("RA %i não cadastrado!!\n", listalunos[g]);
	    }
	    else
	    {
	      valdis = ValidaDisciplina(dis, listadisciplinas[h], b);
	      if (valdis == -1)
	      {
		printf("Disciplina %i não cadastrada!!\n", listadisciplinas[h]);
	      }
	      else
	      {
		mat[f].student.ra = listalunos[g];
		mat[f].materia.codigo = listadisciplinas[h];
		f++;
	      }
	    }
	  }
	}
	break;
      case VINCLISTAPROFLISTADIS:
	printf("Lista de Professores: (Condição de parada: -1)\n");
	do
	{
	  scanf("%i", &listaprofessores[j]);
	  if (listaprofessores[j] != -1)
	  {
	    j++;
	  }
	} while (listaprofessores[j] != -1);
	printf("Lista de Disciplinas: (Condição de parada: -1)\n");
	do
	{
	  scanf("%i", &listadisciplinas[k]);
	  if (listadisciplinas[k] != -1)
	  {
	    k++;
	  }
	} while (listadisciplinas[k] != -1);
	for (g=0; g < j; g++)
	{
	  for (h=0; h < k; h++)
	  {
	    valprof = ValidaProfessor(prof, listaprofessores[g], c);
	    if (valalu == -1)
	    {
	      printf("RU %i não cadastrado!!\n", listaprofessores[g]);
	    }
	    else
	    {
	      valdis = ValidaDisciplina(dis, listadisciplinas[h], b);
	      if (valdis == -1)
	      {
		printf("Disciplina %i não cadastrada!!\n", listadisciplinas[h]);
	      }
	      else
	      {
		vinc[m].teacher.ru = listaprofessores[g];
		vinc[m].materia.codigo = listadisciplinas[h];
		m++;
	      }
	    }
	  }
	}
	break;
      case EXIBEDISALUNO:
	printf("RA do aluno: ");
	scanf("%i", &ralu);
	valalu = ValidaAluno(alu, ralu, a);
	if (valalu == -1)
	{
	  printf("RA não encontrado!!\n");
	}
	else
	{
	  printf("Nome do Aluno: %s\n", alu[valalu].nomealuno);
	  for (h=0; h<f; h++)
	  {
	    if (mat[h].student.ra == ralu)
	    {
	      codproc = mat[h].materia.codigo;
	      valdis = ValidaDisciplina(dis, codproc, b);
	      if (valdis == -1)
	      {
		printf("Aluno não cadastrado em disciplinas!!\n");
	      }
	      else
	      {
		printf("Disciplina: %s\n", dis[valdis].nomedisciplina);
	      }
	    }
	  }
	}
	break;
      case EXIBEALUNODIS:
	printf("Código da disciplina: ");
	scanf("%i", &codis);
	valdis = ValidaDisciplina(dis, codis, b);
	if (valdis == -1)
	{
	  printf("Disciplina não encontrada!!\n");
	}
	else
	{
	  printf("Nome da disciplina: %s\n", dis[valdis].nomedisciplina);
	  for (i=0; i<f; i++)
	  {
	    if (mat[i].materia.codigo == codis)
	    {
	      raproc = mat[i].student.ra;
	      valalu = ValidaAluno(alu, raproc, a);
	      if (valalu == -1)
	      {
		printf("Não há alunos matriculados nesta disciplina!!\n");
	      }
	      else
	      {
		printf("Aluno: %s\n", alu[valalu].nomealuno);
	      }
	    }
	  }
	}
	break;
      case EXIBEDISPROF:
	printf("RU do professor: ");
	scanf("%i", &ruprof);
	valprof = ValidaProfessor(prof, ruprof, c);
	if (valprof == -1)
	{
	  printf("RU não encontrado!!\n");
	}
	else
	{
	  printf("Nome do Professor: %s\n", prof[valprof].nomeprofessor);
	  for (h=0; h<m; h++)
	  {
	    if (vinc[h].teacher.ru == ruprof)
	    {
	      codproc = vinc[h].materia.codigo;
	      valdis = ValidaDisciplina(dis, codproc, b);
	      if (valdis == -1)
	      {
		printf("Aluno não cadastrado em disciplinas!!\n");
	      }
	      else
	      {
		printf("Disciplina: %s\n", dis[valdis].nomedisciplina);
	      }
	    }
	  }
	}
	break;
      case EXIBEPROFDIS:
	printf("Código da disciplina: ");
	scanf("%i", &codis);
	valdis = ValidaDisciplina(dis, codis, b);
	if (valdis == -1)
	{
	  printf("Disciplina não encontrada!!\n");
	}
	else
	{
	  printf("Nome da disciplina: %s\n", dis[valdis].nomedisciplina);
	  for (i=0; i<m; i++)
	  {
	    if (vinc[i].materia.codigo == codis)
	    {
	      ruproc = vinc[i].teacher.ru;
	      valprof = ValidaProfessor(prof, ruproc, c);
	      if (valprof == -1)
	      {
		printf("Não há professores vinculados nesta disciplina!!\n");
	      }
	      else
	      {
		printf("Professor: %s\n", prof[valprof].nomeprofessor);
	      }
	    }
	  }
	}
	break;
      case CANCELARMATALUDISC:
	printf("RA do Aluno: ");
	scanf("%i", &raproc);
	printf("Código da Disciplina: ");
	scanf("%i", &codproc);
	valmatri = ValidaMatricula(mat, raproc, codproc, f);
	if (valmatri == -1)
	{
	  printf("Esta matrícula não foi realizada!!\n");
	}
	else
	{
	  for (o=valmatri; o<f; o++)
	  {
	    mat[o].student.ra = mat[o+1].student.ra;
	    mat[o].materia.codigo = mat[o+1].materia.codigo;
	  }
	  f--;
	}
	break;
      case CANCELARVINCPROFDIS:
	printf("RU do Professor: ");
	scanf("%i", &ruproc);
	printf("Código da Disciplina: ");
	scanf("%i", &codproc);
	valvinc = ValidaVinculo(vinc, ruproc, codproc, m);
	if (valvinc == -1)
	{
	  printf("Este vículo não foi realizado!!\n");
	}
	else
	{
	  for (q=valvinc; q<m; q++)
	  {
	    vinc[q].teacher.ru = vinc[q+1].teacher.ru;
	    vinc[q].materia.codigo = vinc[q+1].materia.codigo;
	  }
	  m--;
	}
	break;
      case CANCELARMATLISTALUNOSLISTADIS:
	printf("Lista de Alunos: (Condição de parada: -1)\n");
	do
	{
	  scanf("%i", &listacancelalunos[j]);
	  if (listacancelalunos[j] != -1)
	  {
	    j++;
	  }
	} while (listacancelalunos[j] != -1);
	printf("Lista de Disciplinas: (Condição de parada: -1)\n");
	do
	{
	  scanf("%i", &listacanceladisciplinas[k]);
	  if (listacanceladisciplinas[k] != -1)
	  {
	    k++;
	  }
	} while (listacanceladisciplinas[k] != -1);
	for (r=0; r<j; r++)
	{
	  for (s=0; s<k;s++)
	  {
	    valmatri = ValidaMatricula(mat, listacancelalunos[r], listacanceladisciplinas[s], f);
	    if (valmatri != -1)
	    {
	      for (t=valmatri; t<f; t++)
	      {
		mat[t].student.ra = mat[t+1].student.ra;
		mat[t].materia.codigo = mat[t+1].materia.codigo;
	      }
	    }
	  }
	}
	break;
      case CANCEARVINCLISTAPROFLISTADIS:
	printf("Lista de Professores: (Condição de parada: -1)\n");
	do
	{
	  scanf("%i", &listacancelaprofessores[j]);
	  if (listacancelaprofessores[j] != -1)
	  {
	    j++;
	  }
	} while (listacancelaprofessores[j] != -1);
	printf("Lista de Disciplinas: (Condição de parada: -1)\n");
	do
	{
	  scanf("%i", &listacanceladisciplinas1[k]);
	  if (listacanceladisciplinas1[k] != -1)
	  {
	    k++;
	  }
	} while (listacanceladisciplinas1[k] != -1);
	for (r=0; r<j; r++)
	{
	  for (s=0; s<k;s++)
	  {
	    valvinc = ValidaVinculo(vinc, listacancelaprofessores[r], listacanceladisciplinas1[s], m);
	    if (valvinc != -1)
	    {
	      for (t=valvinc; t<m; t++)
	      {
		vinc[t].teacher.ru = vinc[t+1].teacher.ru;
		vinc[t].materia.codigo = vinc[t+1].materia.codigo;
	      }
	    }
	  }
	}
	break;
      default: printf("Opção inválida!!\n");
	break;
    }
  } while (op != SAIR);
  return 0;
}
  