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

// 1. Uso obrigatorio de typedef enum
typedef enum {
    FICCAO = 1,
    CIENCIA,
    HISTORIA
} Categoria;

typedef enum {
    DISPONIVEL = 1,
    EMPRESTADO
} Situacao;

// 2. Uso obrigatorio de DadosAutor estruturado
typedef struct {
    char nome[50];       // CORRIGIDO: tamanho da string restaurado
    int nascimento;
} Autor;

// 3. Uso obrigatorio de Struct aninhada (Autor dentro de Livro)
typedef struct {
    int id;
    char titulo[100];    // CORRIGIDO: tamanho da string restaurado
    Autor autor;         // Struct aninhada aqui
    char isbn[20];       // CORRIGIDO: tamanho da string restaurado
    int ano;
    Categoria categoria;
    Situacao situacao;
    int ativo;           // Campo obrigatorio para remocao logica
} Livro;

// Funcoes auxiliares de leitura segura
void lerTexto(const char msg[], char texto[], int tam) {
    printf("%s", msg);
    fgets(texto, tam, stdin);
    texto[strcspn(texto, "\n")] = '\0'; // Remove o '\n' gerado pelo fgets
}

int lerInteiro(const char msg[]) {
    int n;
    printf("%s", msg);
    while (scanf("%d", &n) != 1) {
        printf("Entrada invalida. Digite um numero: ");
        while (getchar() != '\n'); // Limpa o buffer em caso de digitação errada
    }
    getchar(); // Limpa o '\n' restante no buffer
    return n;
}

// Conversores de Enum para Texto na listagem
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

// 4. Mecanismo de Busca por ID exigido no enunciado
int buscarId(Livro livros[], int total, int id) {
    for (int i = 0; i < total; i++) {
        // Verifica se o ID bate E se o livro nao foi excluido logicamente
        if (livros[i].id == id && livros[i].ativo) {
            return i; // Retorna a posicao no array
        }
    }
    return -1; // Retorna -1 se nao encontrar
}

// 5. Uso obrigatorio de Ponteiros nos parametros de cadastro (*total e *id)
void cadastrar(Livro livros[], int *total, int *id) {
    if (*total >= MAX) {
        printf("\n[ERRO] Limite de armazenamento atingido.\n");
        return;
    }

    Livro novo;
    novo.id = *id;
    novo.ativo = 1; // Ativa o registro do livro
    novo.situacao = DISPONIVEL;

    printf("\n--- Cadastrar Livro (ID: %d) ---\n", novo.id);
    lerTexto("Titulo: ", novo.titulo, 100);
    lerTexto("ISBN: ", novo.isbn, 20);
    novo.ano = lerInteiro("Ano: ");
    lerTexto("Autor: ", novo.autor.nome, 50);
    novo.autor.nascimento = lerInteiro("Nascimento do autor: ");

    int opCat;
    do {
        printf("Escolha a Categoria:\n1-Ficcao\n2-Ciencia\n3-Historia\n");
        opCat = lerInteiro("Opcao: ");
    } while (opCat < 1 || opCat > 3);
    novo.categoria = (Categoria)opCat;

    // Salva o novo livro no array estatico
    livros[*total] = novo;
    
    // Modifica as variaveis da main usando os ponteiros recebidos
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

// Funcao para listar todos os livros
void listar(Livro livros[], int total) {
    int encontrados = 0;
    printf("\n=== Lista de Livros Ativos ===");
    for (int i = 0; i < total; i++) {
        if (livros[i].ativo) { // Mostra apenas os que nao foram removidos logicamente
            exibirLivro(livros[i]);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("\nNenhum livro cadastrado ou ativo.\n");
    }
}

// Opcao do menu para Buscar por ID
void buscarPorIdMenu(Livro livros[], int total) {
    int id = lerInteiro("ID para busca: ");
    int indice = buscarId(livros, total, id);

    if (indice == -1) {
        printf("[ERRO] Livro nao encontrado ou removido.\n");
        return;
    }
    printf("\n--- Livro Encontrado ---");
    exibirLivro(livros[indice]);
}

// Funcao para atualizar o titulo de um livro
void atualizar(Livro livros[], int total) {
    int id = lerInteiro("ID para atualizar: ");
    int indice = buscarId(livros, total, id);

    if (indice == -1) {
        printf("[ERRO] Livro nao encontrado.\n");
        return;
    }

    printf("Titulo atual: %s\n", livros[indice].titulo);
    lerTexto("Novo titulo: ", livros[indice].titulo, 100);
    printf("[SUCESSO] Titulo atualizado.\n");
}

// Funcao para remocao logica
void remover(Livro livros[], int total) {
    int id = lerInteiro("ID para remover: ");
    int indice = buscarId(livros, total, id);

    if (indice == -1) {
        printf("[ERRO] Livro nao encontrado.\n");
        return;
    }

    // Remocao logica realizada mudando a flag ativo para 0
    livros[indice].ativo = 0; 
    printf("[SUCESSO] Livro removido logicamente do sistema.\n");
}

int main() {
    // 6. Uso obrigatorio de Arrays estaticos
    Livro livros[MAX]; 
    int total = 0;
    int proximoId = 1;
    int op;

    do {
        printf("\n===== MENU BIBLIOTECA =====\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar Todos\n");
        printf("3 - Buscar por ID\n");
        printf("4 - Atualizar Titulo\n");
        printf("5 - Remover (Logica)\n");
        printf("0 - Sair\n");
        printf("===========================\n");

        op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: cadastrar(livros, &total, &proximoId); break;
            case 2: listar(livros, total); break;
            case 3: buscarPorIdMenu(livros, total); break;
            case 4: atualizar(livros, total); break;
            case 5: remover(livros, total); break;
            case 0: printf("Encerrando programa...\n"); break;
            default: printf("[ERRO] Opcao invalida.\n");
        }
    } while (op != 0); // Requisito: Encerrar o programa

    return 0;
}
