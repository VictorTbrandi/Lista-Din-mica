#include<stdio.h>
#include<conio2.h>
#include<string.h>
#include <locale.h>
#include<ctype.h>
#include<stdlib.h>
#include "Estruturas.h"
char Menu(void){
	system("cls");
	printf("[A] - Exibir Estrutura");
	printf("\n[B] - Excluir Livro");
	printf("\n[C] - Livros de cada autor");
	printf("\n[D] - Livros de cada editora");
	printf("\n[E] - Autores que não possuem livro");
	printf("\n[F] - Ex1. Prova");
	printf("\n[ESC] - Sair");
	printf("\nSelecione uma opção: ");
	return toupper(getche());
}
void TransformaBin(void){
	Arquivo arq;
	int i,tl;
	FILE * ptrT = fopen("livros.txt", "r");
	FILE * ptrB = fopen("livros.dat", "wb");
    if (!ptrT)
    	printf("\nErro ao abrir livros.txt");
    if (!ptrB)
		printf("\nErro ao abrir livros.dat");
	else{
		fscanf(ptrT,"%[^|]|%[^|]|%[^|]|%d|%d",&arq.autor,&arq.titulo,&arq.editora,&arq.ano,&arq.pag);
		while(!feof(ptrT)){
			for(i = tl=0; i <= strlen(arq.autor);i++)
				if(arq.autor[i] >= 65 && arq.autor[i] <= 90 || arq.autor[i] >= 97 && arq.autor[i] <= 122 || arq.autor[i] == '\0' || arq.autor[i] == '.' || arq.autor[i] == ';')
					arq.autor[tl++]=arq.autor[i];
				else
					if(arq.autor[i] == ',')
						arq.autor[tl++]=',';
					else
						if(arq.autor[i] == ' ' && arq.autor[i+1] != '\0' && arq.autor[i+1] != ' ' && arq.autor[i-1] != ',' && arq.autor[i-1] != ';')
							arq.autor[tl++]=arq.autor[i];
			fwrite(&arq,sizeof(Arquivo),1,ptrB);
			fscanf(ptrT,"%[^|]|%[^|]|%[^|]|%d|%d",&arq.autor,&arq.titulo,&arq.editora,&arq.ano,&arq.pag);
		}
		fclose(ptrB);
		fclose(ptrT);
	}
}
pAutor *InsereAutor(void){
	FILE *ptr = fopen("livros.dat","rb");
	Arquivo arq;
	pAutor *aut=NULL,*aux,*novo;
	char nome[50], sobrenome[50];
	int i, tl_sobrenome,tl_nome;
	if(!ptr)
		printf("\nErro ao abrir livros.dat");
	else{
		fread(&arq,sizeof(Arquivo),1,ptr);
		while(!feof(ptr)){
			i=0;
			while(i < strlen(arq.autor)){
				for(tl_sobrenome = 0; i < strlen(arq.autor) && arq.autor[i] != ','; i++)
					sobrenome[tl_sobrenome++] = arq.autor[i];
				sobrenome[tl_sobrenome] = '\0';
				i++;
				for(tl_nome = 0; i < strlen(arq.autor) && arq.autor[i] != ';'; i++)
					nome[tl_nome++] = arq.autor[i];
				nome[tl_nome++] = '\0';
				i++;
				if(!aut){
					aut = new pAutor;
					strcpy(aut->nome,nome);
					strcpy(aut->sobrenome,sobrenome);
					aut->prox=NULL;
				}
				else{
					if(strcmp(aut->nome,nome) != 0 && strcmp(aut->sobrenome,sobrenome) != 0){
						aux = aut;
						while(aux->prox && strcmp(aux->prox->nome,nome) != 0 && strcmp(aux->prox->sobrenome,sobrenome) != 0)
							aux=aux->prox;
						if(!aux->prox){
							novo  = new pAutor;
							novo->prox=NULL;
							strcpy(novo->nome,nome);
							strcpy(novo->sobrenome,sobrenome);
							aux->prox=novo;
						}
					}
				}
			}
			fread(&arq,sizeof(Arquivo),1,ptr);
		}
		fclose(ptr);
	}
	return aut;
}
void Exibe(void){
	FILE * PtrB = fopen("livros.dat","rb");
	Arquivo arq;
	if (!PtrB)
		printf("Erro ao abrir livros.dat");
	else{
		fread(&arq,sizeof(Arquivo),1,PtrB);
		while(!feof(PtrB)){
			printf("%s|%s|%s|%d|%d\n",arq.autor,arq.titulo,arq.editora,arq.ano,arq.pag);
			fread(&arq,sizeof(Arquivo),1,PtrB);
		}
		fclose(PtrB);
	}
}
pLivros *NewLivros(Arquivo arq, pAutor *aut){
	pLivros *Livros = new pLivros;
	ppAutor *paut, *novo_autor;
	pAutor *aux,*aux2;
	int i,tl_nome,tl_sobrenome;
	char nome[50],sobrenome[50];
	
	Livros->ant = NULL;
	Livros->prox = NULL;
	strcpy(Livros->titulo,arq.titulo);
	Livros->ano = arq.ano;
	Livros->pag = arq.pag;
	Livros->autor = NULL;
	i = 0;
	while(i < strlen(arq.autor)){
		for(tl_sobrenome = 0; i < strlen(arq.autor) && arq.autor[i] != ','; i++)
			sobrenome[tl_sobrenome++] = arq.autor[i];
		sobrenome[tl_sobrenome] = '\0';
		i++;
		for(tl_nome = 0; i < strlen(arq.autor) && arq.autor[i] != ';'; i++)
			nome[tl_nome++] = arq.autor[i];
		nome[tl_nome++] = '\0';
		i++;
		if(stricmp(aut->nome,nome) != 0 && stricmp(aut->sobrenome,sobrenome) != 0){
			aux = aut;
			while(stricmp(aux->prox->nome,nome) != 0 && stricmp(aux->prox->sobrenome,sobrenome) != 0)
				aux = aux->prox;
			if(!Livros->autor){
				Livros->autor = new ppAutor;
				Livros->autor->end = aux->prox;
				Livros->autor->prox = NULL;
			}
			else{
				paut = Livros->autor;
				while(paut->prox)
					paut = paut->prox;
				novo_autor = new ppAutor;
				novo_autor->prox = NULL;
				novo_autor->end=aux->prox;
				paut->prox=novo_autor;
			}
		}
		else{
			if(!Livros->autor){
				Livros->autor=new ppAutor;
				Livros->autor->end=aut;
				Livros->autor->prox=NULL;
			}
			else{
				paut=Livros->autor;
				while(paut->prox)
					paut=paut->prox;
				novo_autor = new ppAutor;
				novo_autor->prox=NULL;
				novo_autor->end=aut;
				paut->prox=novo_autor;
			}
		}
	}
	return Livros;
}
pEditora *NewContent(Arquivo arq, pAutor *aut){
	pEditora *novo = new pEditora;
	pAutor *aux;
	strcpy(novo->editora,arq.editora);
	novo->prox=NULL;
	novo->Livros = NewLivros(arq,aut);
	return novo;
}
void *InserirDados(TpDescritor &D,pAutor *aut){
	FILE * ptr = fopen("livros.dat","rb");
	Arquivo arq;
	pEditora *novo,*aux_ed;
	pLivros *livro,*aux_li;
	
	if(!ptr)
		printf("\nErro ao abrir livros.dat");
	else{
		fread(&arq,sizeof(Arquivo),1,ptr);
		while(!feof(ptr)){
			if(D.qtde == 0){
				D.Inicio = D.Fim = NewContent(arq,aut);
				D.qtde++;
			}
			else{
				if(stricmp(arq.editora,D.Inicio->editora) == 0){
					if(!D.Inicio->Livros)
						D.Inicio->Livros = NewLivros(arq,aut);
					else{
						livro = NewLivros(arq,aut);
						aux_li = D.Inicio->Livros;
						while(aux_li->prox)
							aux_li = aux_li->prox;
						aux_li->prox = livro;
						livro->ant = aux_li;
					}
				}
				else{
					if(stricmp(arq.editora,D.Inicio->editora) < 0){
						novo = NewContent(arq,aut);
						novo->prox = D.Inicio;
						D.Inicio = novo;
						D.qtde++;
					}
					else{
						aux_ed = D.Inicio;
						while(aux_ed->prox && stricmp(arq.editora,aux_ed->prox->editora) > 0)
							aux_ed = aux_ed->prox;
						if(stricmp(arq.editora,aux_ed->prox->editora) == 0){
							if(!aux_ed->prox->Livros)
								aux_ed->prox->Livros = NewLivros(arq,aut);
							else{
								livro = NewLivros(arq,aut);
								aux_li = aux_ed->prox->Livros;
								while(aux_li->prox)
									aux_li = aux_li->prox;
								aux_li->prox = livro;
								livro->ant = aux_li;
							}
						}
						else{
							if(!aux_ed->prox){
								D.Fim->prox = novo = NewContent(arq,aut);
								D.Fim = novo;
							}
							else{
								novo = NewContent(arq,aut);
								novo->prox=aux_ed->prox;
								aux_ed->prox=novo;
							}
							D.qtde++;
						}	
					}
				}
			}
			fread(&arq,sizeof(Arquivo),1,ptr);
		}
	}
	fclose(ptr);
}
void ExibeAutores(ppAutor *a){
	printf("Nome: %s %s\n",a->end->nome,a->end->sobrenome);
	if(a->prox)
		ExibeAutores(a->prox);
}
void ExibeLivros(pLivros *l){
	printf("Titulo: %s\n",l->titulo);
	printf("Ano: %d\n",l->ano);
	printf("Paginas: %d\n",l->pag);
	if(l->autor)
		ExibeAutores(l->autor);
	if(l->prox)
		ExibeLivros(l->prox);
}
void ExibeDados(pEditora *e){
	printf("\nEditora: %s\n",e->editora);
	if(e->Livros)
		ExibeLivros(e->Livros);
	if(e->prox)
		ExibeDados(e->prox);
}
void ExibeAutor(pAutor *p){
	printf("Nome:%s|Sobrenome:%s\n",p->nome,p->sobrenome);
	if(p->prox)
		ExibeAutor(p->prox);
}
int ExcluiEstrutura(TpDescritor &d, char titulo[100]){
	pEditora *e=d.Inicio;
	pLivros *aux;
	while(e){
		aux=e->Livros;
		while(aux){
			if(strcmp(aux->titulo,titulo) == 0){
				if(!aux->prox && !aux->ant){
					delete aux;
					e->Livros=NULL;
				}
				else
					if(!aux->prox){
						aux->ant->prox=NULL;
						delete aux;
					}
					else
						if(!aux->ant){
							e->Livros=aux->prox;
							e->Livros->ant=NULL;
							delete aux;
						}
						else{
							aux->ant->prox=aux->prox;
							aux->prox->ant=aux->ant;
							delete aux;
						}
				return 1;
			}
			aux=aux->prox;
		}
		e=e->prox;
	}
	return 0;
}
void ExcluirArq(TpDescritor &d,char tit[100]){
	FILE * PtrA = fopen("livros.dat","rb");
	FILE * PtrN = fopen("novo.dat","wb");
	pEditora *e=d.Inicio;
	Arquivo arq;
	if(!PtrA)
		printf("\nErro ao abrir livros.dat");
	if(!PtrN)
		printf("\nErro ao criar novo.dat");
	else{
		while(fread(&arq,sizeof(Arquivo),1,PtrA))
			if(strcmp(arq.titulo,tit) != 0)
				fwrite(&arq,sizeof(Arquivo),1,PtrN);
		fclose(PtrA);
		fclose(PtrN);
		if(remove("livros.dat") != 0)
			printf("\nErro ao remover livros.dat");
		else
		if(rename("novo.dat","livros.dat") != 0)
			printf("\nErro ao renomear novo.dat para livros.dat");
	}
}
void ExibeLivroAutor(pAutor *aut,pEditora *e){
	pEditora *aux;
	pLivros *l;
	ppAutor *a;
	int cont;
	while(aut){
		printf("\nAutor: %s %s",aut->nome,aut->sobrenome);
		aux=e;
		cont=0;
		while(aux){
			l = aux->Livros;
			while(l){
				a=l->autor;
				while(a){
					if(strcmp(a->end->nome,aut->nome) == 0 && strcmp(a->end->sobrenome,aut->sobrenome) == 0){
						printf("\nLivro: %s",l->titulo);
						a=NULL;
						cont++;
					}
					else
						a=a->prox;
				}
				l=l->prox;
			}
			aux=aux->prox;
		}
		if(cont == 0)
			printf("\nAutor sem livros registrados !");
		printf("\n");
		aut=aut->prox;
	}
}
void ExibeAutorSemLivro(pAutor *aut,pEditora *e){
	pEditora *aux;
	pLivros *l;
	ppAutor *a;
	int cont,cont2=0;
	while(aut){
		aux=e;
		cont=0;
		while(aux){
			l = aux->Livros;
			while(l){
				a=l->autor;
				while(a){
					if(strcmp(a->end->nome,aut->nome) == 0 && strcmp(a->end->sobrenome,aut->sobrenome) == 0){
						a=NULL;
						cont++;
					}
					else
						a=a->prox;
				}
				if(cont == 0)
					l=l->prox;
				else l=NULL;
			}
			aux=aux->prox;
		}
		if(cont == 0){
			printf("\nAutor: %s %s",aut->nome,aut->sobrenome);
			cont2++;
		}
		aut=aut->prox;
	}
	if(cont2 == 0)
		printf("\nTodos autores possuem Livros registrados !");
}
void Livros(pLivros *l){
	printf("\nTitulo: %s",l->titulo);
	if(l->prox)
		Livros(l->prox);
}
void ExibeLivrosEditora(pEditora *e){
	printf("\nEditora: %s",e->editora);
	if(e->Livros){
		Livros(e->Livros);
		printf("\n");
	}
	else
		printf("\nEditora não possui Livros registrados !\n");
	if(e->prox)
		ExibeLivrosEditora(e->prox);
}
void AlteraApontamento(TpDescritor &d, char nomeEditora[50], char tit[50],char nome1[50],char nome2[50], char sob1[50],char sob2[50],pAutor* p){
	pAutor *aux = p;
	pEditora *auxE;
	pLivros *auxL;
	ppAutor *aux1,*aux2;
	
	while(aux && strcmp(aux->nome,nome1) != 0 && strcmp(aux->sobrenome,sob1) != 0)
		aux = aux->prox;
	if(aux){
		aux = p;
		while(aux && strcmp(aux->nome,nome2) != 0 && strcmp(aux->sobrenome,sob2) != 0)
			aux = aux->prox;
		if(aux){
			auxE = d.Inicio;
			while(auxE && strcmp(auxE->editora,nomeEditora) < 0)
				auxE = auxE->prox;
			if(auxE && strcmp(auxE->editora,nomeEditora) == 0){
				auxL = auxE->Livros;
				while(auxL){
					if(strcmp(tit, auxL->titulo) == 0){
						aux1 = auxL->autor;
						while(aux1 && strcmp(aux1->end->nome,nome1) != 0 && strcmp(aux1->end->sobrenome, sob1) != 0)
							aux1 = aux1->prox;
						if(aux1){
							aux2 = auxL->autor;
							while(aux2 && strcmp(aux2->end->nome,nome2) != 0 && strcmp(aux2->end->sobrenome, sob2) != 0)
								aux2 = aux2->prox;
							if(aux2){
								aux = aux1->end;
								aux1->end = aux2->end;
								aux2->end = aux;
							}
						}
					}
					auxL = auxL->prox;
				}
			}
		}
	}
}
int main(void){
	TpDescritor D;
	pAutor *Autores;
	setlocale(LC_ALL, "Portuguese");
	char op,tit[70], nome1[50], nome2[50], sobrenome1[50], sobrenome2[50], editora[50];
	
	TransformaBin();
	Inicializar(D);
	Autores = InsereAutor();
	InserirDados(D,Autores);
	do{
		op = Menu();
		switch(op){
			case 'A':
				ExibeDados(D.Inicio);
				getch();
				break;
			
			case 'B':
				printf("\nDigite o título do livro: ");
				gets(tit);
				if(ExcluiEstrutura(D,tit)){
					ExcluirArq(D,tit);
					printf("\nExclusão realizada com sucesso !");
				}
				else
					printf("\nTítulo não encontrado !");
				getch();
				break;
				
			case 'C':
				system("cls");
				printf("# # # Relátorio Livros de cada Autor # # #\n");
				ExibeLivroAutor(Autores,D.Inicio);
				getch();
				break;
				
			case 'D':
				system("cls");
				printf("# # # Relátorio Livros de cada Editora # # #\n");
				ExibeLivrosEditora(D.Inicio);
				getch();
				break;
			
			case 'E':
				system("cls");
				printf("# # # Relátorio Autores que não possuem Livro # # #\n");
				ExibeAutorSemLivro(Autores,D.Inicio);
				getch();
				break;
			
			case 'F':
				system("cls");
				printf("Digite o nome da editora: ");
				gets(editora);
				printf("Digite o titulo do livro: ");
				gets(tit);
				printf("Digite o nome e sobrenome do autor 1: ");
				gets(nome1);
				gets(sobrenome1);
				printf("Digite o nome e sobrenome do autor 2: ");
				gets(nome2);
				gets(sobrenome2);
				AlteraApontamento(D,editora,tit,nome1,nome2,sobrenome1,sobrenome2,Autores);
				break;
			case 27:
				system("cls");
				printf("\nVictor Terrengui Brandi");
				printf("\nFelipe Oliveira de Carvalho");
				printf("\nMatheus Oliveira da Silva");
				printf("\nTrabalho do DOUTOR LEANDRO !");
				break;
			default: printf("\nOpção Inválida !");
		}
	}while(op != 27);
	
	
	
	
	return 0;
}
