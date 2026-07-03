//Sistema de Cadastro de Livros
//Desenvolva um programa em linguagem C para gerenciar o cadastro de livros de uma biblioteca.
//O programa deverá utilizar obrigatoriamente:
//typedef struct typedef enum Struct aninhada Arrays estáticos Funções
//Ponteiros nos parâmetros de cadastro Busca por ID
//O sistema deve permitir:
//Cadastrar livros. Listar todos os livros. Buscar um livro pelo ID.
//Atualizar o título de um livro. Remover logicamente um livro. Encerrar o programa.
//Utilize as seguintes estruturas:
//DadosAutor Livro
//Cada livro deverá possuir:
//ID  Título ISBN Ano
//Dados do autor Categoria Situação
//Campo ativo para remoção lógica.

#include <stdio.h>
#include <string.h>

#define MAX 100

typedef enum{
    FICCAO=1,
    CIENCIA,
    HISTORIA
}Categoria;

typedef enum{
    DISPONIVEL=1,
    EMPRESTADO
}Situacao;

typedef struct{
    char nome[50];
    int nascimento;
}Autor;

typedef struct{
    int id;
    char titulo[100];
    Autor autor;
    char isbn[20];
    int ano;
    Categoria categoria;
    Situacao situacao;
    int ativo;
}Livro;

void lerTexto(char msg[], char texto[], int tam){
    printf("%s",msg);
    fgets(texto,tam,stdin);
    texto[strcspn(texto,"\n")]='\0';
}

int lerInteiro(char msg[]){
    int n;
    printf("%s",msg);
    scanf("%d",&n);
    getchar();
    return n;
}

int buscarId(Livro livros[],int total,int id){

    int i;

    for(i=0;i<total;i++)
        if(livros[i].id==id && livros[i].ativo)
            return i;

    return -1;
}

void cadastrar(Livro livros[],int *total,int *id){

    if(*total>=MAX){
        printf("Limite atingido.\n");
        return;
    }

    Livro novo;

    novo.id=*id;
    novo.ativo=1;
    novo.situacao=DISPONIVEL;

    lerTexto("Titulo: ",novo.titulo,100);
    lerTexto("ISBN: ",novo.isbn,20);

    novo.ano=lerInteiro("Ano: ");

    lerTexto("Autor: ",novo.autor.nome,50);

    novo.autor.nascimento=
        lerInteiro("Nascimento do autor: ");

    printf("1-Ficcao\n2-Ciencia\n3-Historia\n");

    novo.categoria=
        lerInteiro("Categoria: ");

    livros[*total]=novo;

    (*total)++;
    (*id)++;

    printf("Livro cadastrado!\n");
}

void listar(Livro livros[],int total){

    int i;

    for(i=0;i<total;i++){

        if(livros[i].ativo){

            printf("\nID: %d",livros[i].id);
            printf("\nTitulo: %s",livros[i].titulo);
            printf("\nAutor: %s",livros[i].autor.nome);
            printf("\nISBN: %s",livros[i].isbn);
            printf("\nAno: %d\n",livros[i].ano);
        }
    }
}

void atualizar(Livro livros[],int total){

    int id,indice;

    id=lerInteiro("ID: ");

    indice=buscarId(livros,total,id);

    if(indice==-1){
        printf("Livro nao encontrado.\n");
        return;
    }

    lerTexto("Novo titulo: ",
             livros[indice].titulo,
             100);

    printf("Atualizado.\n");
}

void remover(Livro livros[],int total){

    int id,indice;

    id=lerInteiro("ID: ");

    indice=buscarId(livros,total,id);

    if(indice==-1){
        printf("Livro nao encontrado.\n");
        return;
    }

    livros[indice].ativo=0;

    printf("Removido.\n");
}

int main(){

    Livro livros[MAX];

    int total=0;
    int proximoId=1;
    int op;

    do{

        printf("\n===== MENU =====\n");
        printf("1-Cadastrar\n");
        printf("2-Listar\n");
        printf("3-Atualizar\n");
        printf("4-Remover\n");
        printf("0-Sair\n");

        op=lerInteiro("Opcao: ");

        switch(op){

            case 1:
                cadastrar(livros,&total,&proximoId);
                break;

            case 2:
                listar(livros,total);
                break;

            case 3:
                atualizar(livros,total);
                break;

            case 4:
                remover(livros,total);
                break;
        }

    }while(op!=0);

    return 0;
}