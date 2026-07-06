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

typedef enum { FICCAO = 1, CIENCIA, HISTORIA } Categoria;
typedef enum { DISPONIVEL = 1, EMPRESTADO } Situacao;

typedef struct {
    char nome[50];
    int nascimento;
} Autor;

typedef struct {
    int id;
    char titulo[100];
    Autor autor; // Aninhada
    char isbn[20];
    int ano;
    Categoria categoria;
    Situacao situacao;
    int ativo; // Remocao logica
} Livro;

void lerTxt(char *msg, char *v, int t) {
    printf("%s", msg);
    fgets(v, t, stdin);
    v[strcspn(v, "\n")] = '\0';
}

int buscarId(Livro livros[], int total, int id) {
    for(int i = 0; i < total; i++)
        if(livros[i].id == id && livros[i].ativo) return i;
    return -1;
}

// Parâmetros por ponteiro (*total e *id) mantidos obrigatoriamente
void cadastrar(Livro livros[], int *total, int *id) {
    if (*total >= MAX) return;
    Livro n;
    n.id = *id; n.ativo = 1; n.situacao = DISPONIVEL;

    getchar(); // Limpa buffer
    lerTxt("Titulo: ", n.titulo, 100);
    lerTxt("ISBN: ", n.isbn, 20);
    printf("Ano: "); scanf("%d", &n.ano); getchar();
    lerTxt("Autor: ", n.autor.nome, 50);
    printf("Nasc. Autor: "); scanf("%d", &n.autor.nascimento);
    printf("1-Ficcao 2-Ciencia 3-Historia: "); scanf("%d", (int*)&n.categoria);

    livros[(*total)++] = n;
    (*id)++;
    printf("Cadastrado!\n");
}

int main() {
    Livro livros[MAX]; // Vetor estático
    int total = 0, proximoId = 1, op, id, pos;

    do {
        printf("\n1-Add 2-Listar 3-Buscar 4-Edit Titulo 5-Remover 0-Sair\nOpcao: ");
        scanf("%d", &op);
        
        if(op == 1) cadastrar(livros, &total, &proximoId);
        
        if(op == 2) {
            for(int i = 0; i < total; i++)
                if(livros[i].ativo) printf("\nID: %d | %s | %s\n", livros[i].id, livros[i].titulo, livros[i].autor.nome);
        }
        
        if(op == 3 || op == 4 || op == 5) {
            printf("ID: "); scanf("%d", &id);
            pos = buscarId(livros, total, id);
            if(pos == -1) printf("Nao encontrado.\n");
            else if(op == 3) printf("Livro: %s | Ano: %d\n", livros[pos].titulo, livros[pos].ano);
            else if(op == 4) { getchar(); lerTxt("Novo Titulo: ", livros[pos].titulo, 100); printf("Editado!\n"); }
            else if(op == 5) { livros[pos].ativo = 0; printf("Removido!\n"); }
        }
    } while(op != 0);
    return 0;
}
