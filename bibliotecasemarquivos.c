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

typedef enum {
    FICCAO = 1,
    CIENCIA,
    HISTORIA
} Categoria;

typedef enum {
    DISPONIVEL = 1,
    EMPRESTADO
} Situacao;

// Struct para os Dados do Autor
typedef struct {
    char nome[50];       // CORRIGIDO: adicionado [50]
    int nascimento;
} Autor;

// Struct principal com aninhamento
typedef struct {
    int id;
    char titulo[100];    // CORRIGIDO: adicionado [100]
    Autor autor;         // Struct aninhada obrigatória
    char isbn[20];       // CORRIGIDO: adicionado [20]
    int ano;
    Categoria categoria;
    Situacao situacao;
    int ativo;           // Campo obrigatório para remoção lógica
} Livro;

// Funções de leitura segura
void lerTexto(const char msg[], char texto[], int tam) {
    printf("%s", msg);
    fgets(texto, tam, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

int lerInteiro(const char msg[]) {
    int n;
    printf("%s", msg);
    while (scanf("%d", &n) != 1) {
        printf("Entrada invalida. Digite um numero: ");
        while (getchar() != '\n'); 
    }
    getchar(); 
    return n;
}

const char* obterCategoriaTexto(Categoria cat) {
    switch (cat) {
        case FICCAO: return "Ficcao";
        case CIENCIA: return "Ciencia";
        case HISTORIA: return "Historia";
        default: return "Desconhecida";
    }
}

const char* obterSituacaoTexto(Situacao sit) {
    switch (sit) {
        case DISPONIVEL: return "Disponivel";
        case EMPRESTADO: return "Emprestado";
        default: return "Desconhecido";
    }
}

// Mecanismo de busca exigido
int buscarId(Livro livros[], int total, int id) {
    for (int i = 0; i < total; i++) {
        if (livros[i].id == id && livros[i].ativo) {
            return i;
        }
    }
    return -1;
}

// Cadastro usando ponteiros nos parametros (*total e *id)
void cadastrar(Livro livros[], int *total, int *id) {
    if (*total >= MAX) {
        printf("\n[ERRO] Limite atingido.\n");
        return;
    }

    Livro novo;
    novo.id = *id;
    novo.ativo = 1;
    novo.situacao = DISPONIVEL;

    printf("\n--- Cadastrar Livro (ID: %d) ---\n", novo.id);
    lerTexto("Titulo: ", novo.titulo, 100);
    lerTexto("ISBN: ", novo.isbn, 20);
    novo.ano = lerInteiro("Ano: ");
    lerTexto("Autor: ", novo.autor.nome, 50);
    novo.autor.nascimento = lerInteiro("Nascimento do autor: ");

    int opCat;
    do {
        printf("1-Ficcao\n2-Ciencia\n3-Historia\n");
        opCat = lerInteiro("Categoria: ");
    } while (opCat < 1 || opCat > 3);
    novo.categoria = (Categoria)opCat;

    livros[*total] = novo;
    (*total)++;
    (*id)++;

    printf("[SUCESSO] Livro cadastrado!\n");
}

void exibirLivro(Livro l) {
    printf("\nID: %d", l.id);
    printf("\nTitulo: %s", l.titulo);
    printf("\nAutor: %s (Nascimento: %d)", l.autor.nome, l.autor.nascimento);
    printf("\nISBN: %s", l.isbn);
    printf("\nAno: %d", l.ano);
    printf("\nCategoria: %s", obterCategoriaTexto(l.categoria));
    printf("\nSituacao: %s\n", obterSituacaoTexto(l.situacao));
}

void listar(Livro livros[], int total) {
    int encontrados = 0;
    for (int i = 0; i < total; i++) {
        if (livros[i].ativo) {
            exibirLivro(livros[i]);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("\nNenhum livro cadastrado.\n");
    }
}

void buscarPorIdMenu(Livro livros[], int total) {
    int id = lerInteiro("ID para busca: ");
    int indice = buscarId(livros, total, id);

    if (indice == -1) {
        printf("[ERRO] Livro nao encontrado ou removido.\n");
        return;
    }
    exibirLivro(livros[indice]);
}

void atualizar(Livro livros[], int total) {
    int id = lerInteiro("ID para atualizar: ");
    int indice = buscarId(livros, total, id);

    if (indice == -1) {
        printf("[ERRO] Livro nao encontrado.\n");
        return;
    }

    lerTexto("Novo titulo: ", livros[indice].titulo, 100);
    printf("[SUCESSO] Atualizado.\n");
}

void remover(Livro livros[], int total) {
    int id = lerInteiro("ID para remover: ");
    int indice = buscarId(livros, total, id);

    if (indice == -1) {
        printf("[ERRO] Livro nao encontrado.\n");
        return;
    }

    livros[indice].ativo = 0; // Remoção lógica realizada aqui
    printf("[SUCESSO] Removido logicamente.\n");
}

int main() {
    Livro livros[MAX]; 
    int total = 0;
    int proximoId = 1;
    int op;

    do {
        printf("\n===== MENU =====\n");
        printf("1-Cadastrar\n");
        printf("2-Listar\n");
        printf("3-Buscar por ID\n");
        printf("4-Atualizar Titulo\n");
        printf("5-Remover\n");
        printf("0-Sair\n");

        op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: cadastrar(livros, &total, &proximoId); break;
            case 2: listar(livros, total); break;
            case 3: buscarPorIdMenu(livros, total); break;
            case 4: atualizar(livros, total); break;
            case 5: remover(livros, total); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("[ERRO] Opcao invalida.\n");
        }
    } while (op != 0);

    return 0;
}
