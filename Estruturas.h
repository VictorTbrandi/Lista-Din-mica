struct pAutor{
	char nome[50],sobrenome[50];
	pAutor *prox;
};
struct ppAutor{
	pAutor *end;
	ppAutor *prox;
};
struct pLivros{
	char titulo[70];
	int ano,pag;
	ppAutor *autor;
	pLivros *ant,*prox;
};
struct pEditora{
	char editora[50];
	pLivros *Livros;
	pEditora *prox;
};
struct TpDescritor{
	pEditora *Inicio,*Fim;
	int qtde;
};
struct Arquivo{
	char autor[100],titulo[100],editora[40];
	int ano,pag;
};
void Inicializar(TpDescritor &d){
	d.Inicio = d.Fim = NULL;
	d.qtde = 0;
}
