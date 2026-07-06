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
    char nome[50];       // Garantindo o tamanho correto das strings
    int nascimento;
} Autor;
typedef struct {
    int id;
    char titulo[100];    // Garantindo o tamanho correto das strings
    Autor autor;         // Struct aninhada obrigatória
    char isbn[20];       // Garantindo o tamanho correto das strings
    int ano;
    Categoria categoria;
    Situacao situacao;
    int ativo;           // Campo para remoção lógica
} Livro;
void lerTxt(const char *msg, char *v, int t) {
    printf("%s", msg);
    fgets(v, t, stdin);
    v[strcspn(v, "\n")] = '\0';
}
int buscarId(Livro livros[], int total, int id) {
    for(int i = 0; i < total; i++)
        if(livros[i].id == id && livros[i].ativo) return i;
    return -1;
}
// Parâmetros por ponteiro (*total e *id) conforme exigido
void cadastrar(Livro livros[], int *total, int *id) {
    if (*total >= MAX) {
        printf("\n[ERRO] Limite de armazenamento atingido!\n");
        return;
    }
    Livro n;
    n.id = *id; n.ativo = 1; n.situacao = DISPONIVEL;

    printf("\n--- NOVO CADASTRO (ID: %d) ---\n", n.id);
    getchar(); // Limpa o buffer antes de ler texto
    lerTxt("Titulo: ", n.titulo, 100);
    lerTxt("ISBN: ", n.isbn, 20);
    printf("Ano de Publicacao: "); scanf("%d", &n.ano); getchar();
    lerTxt("Nome do Autor: ", n.autor.nome, 50);
    printf("Ano de Nasc. Autor: "); scanf("%d", &n.autor.nascimento);
    
    printf("Categoria (1-Ficcao, 2-Ciencia, 3-Historia): "); 
    scanf("%d", (int*)&n.categoria);

    livros[(*total)++] = n;
    (*id)++;
    printf("\n[SUCESSO] Livro cadastrado com sucesso!\n");
}

int main() {
    Livro livros[MAX]; // Array estático
    int total = 0, proximoId = 1, op, id, pos;
    do {
        printf("\n MENU BIBLIOTECA \n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Listar Livros\n");
        printf("3 - Buscar por ID\n");
        printf("4 - Atualizar Titulo\n");
        printf("5 - Remover (Logica)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);
        
        if(op == 1) cadastrar(livros, &total, &proximoId);
        if(op == 2) {
            printf("\n=== LIVROS ATIVOS NO SISTEMA ===\n");
            int enc = 0;
            for(int i = 0; i < total; i++) {
                if(livros[i].ativo) {
                    printf("ID: %d | Título: %s | Autor: %s (Ano: %d)\n", 
                           livros[i].id, livros[i].titulo, livros[i].autor.nome, livros[i].ano);
                    enc++;
                }
            }
            if(enc == 0) printf("Nenhum livro cadastrado ou ativo.\n");
        }
        if(op == 3 || op == 4 || op == 5) {
            printf("\nDigite o ID do Livro: "); scanf("%d", &id);
            pos = buscarId(livros, total, id); 
            if(pos == -1) {
                printf("\n[ERRO] Livro nao encontrado ou inativo.\n");
            } else {
                if(op == 3) {
                    printf("\n--- DADOS DO LIVRO ---\n");
                    printf("ID: %d\nTitulo: %s\nAutor: %s\nAno: %d\n", 
                           livros[pos].id, livros[pos].titulo, livros[pos].autor.nome, livros[pos].ano);
                }
                else if(op == 4) { 
                    getchar(); 
                    lerTxt("Digite o Novo Titulo: ", livros[pos].titulo, 100); 
                    printf("\n[SUCESSO] Titulo atualizado!\n"); 
                }
                else if(op == 5) { 
                    livros[pos].ativo = 0; 
                    printf("\n[SUCESSO] Livro removido logicamente!\n"); 
                }
            }
        }
    } while(op != 0);   
    printf("\nPrograma encerrado.\n");
    return 0;
}
