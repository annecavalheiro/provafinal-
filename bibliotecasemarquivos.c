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

// Uso obrigatório de typedef enum
typedef enum {
    FICCAO = 1,
    CIENCIA,
    HISTORIA
} Categoria;

typedef enum {
    DISPONIVEL = 1,
    EMPRESTADO
} Situacao;

// Uso obrigatório de Struct aninhada
typedef struct {
    char nome[50];
    int nascimento;
} Autor;

typedef struct {
    int id;
    char titulo[100];
    Autor autor; // Struct aninhada aqui
    char isbn[20];
    int ano;
    Categoria categoria;
    Situacao situacao;
    int ativo; // Campo para remoção lógica
} Livro;

// Funções auxiliares de leitura e validação
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
        while (getchar() != '\n'); // Limpa o buffer em caso de erro alfabético
    }
    getchar(); // Limpa o '\n' do buffer
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

// Busca por ID (Retorna o índice no array ou -1 se não ativo/encontrado)
int buscarId(Livro livros[], int total, int id) {
    for (int i = 0; i < total; i++) {
        if (livros[i].id == id && livros[i].ativo) {
            return i;
        }
    }
    return -1;
}

// Uso obrigatório de Ponteiros nos parâmetros de cadastro
void cadastrar(Livro livros[], int *total, int *id) {
    if (*total >= MAX) {
        printf("\n[ERRO] Limite de armazenamento de livros atingido.\n");
        return;
    }

    Livro novo;
    novo.id = *id;
    novo.ativo = 1;
    novo.situacao = DISPONIVEL;

    printf("\n--- Cadastrar Novo Livro (ID: %d) ---\n", novo.id);
    lerTexto("Titulo: ", novo.titulo, 100);
    lerTexto("ISBN: ", novo.isbn, 20);
    novo.ano = lerInteiro("Ano de Publicacao: ");
    lerTexto("Nome do Autor: ", novo.autor.nome, 50);
    novo.autor.nascimento = lerInteiro("Ano de Nascimento do Autor: ");

    int opCat;
    do {
        printf("Escolha a Categoria:\n1 - Ficcao\n2 - Ciencia\n3 - Historia\n");
        opCat = lerInteiro("Opcao: ");
    } while (opCat < 1 || opCat > 3);
    novo.categoria = (Categoria)opCat;

    livros[*total] = novo;
    (*total)++;
    (*id)++;

    printf("\n[SUCESSO] Livro cadastrado com sucesso!\n");
}

// Função para exibir os detalhes de um único livro de forma organizada
void exibirLivro(Livro l) {
    printf("\n-----------------------------------");
    printf("\nID: %d", l.id);
    printf("\nTitulo: %s", l.titulo);
    printf("\nAutor: %s (Nascido em: %d)", l.autor.nome, l.autor.nascimento);
    printf("\nISBN: %s", l.isbn);
    printf("\nAno: %d", l.ano);
    printf("\nCategoria: %s", obterCategoriaTexto(l.categoria));
    printf("\nSituacao: %s", obterSituacaoTexto(l.situacao));
    printf("\n-----------------------------------\n");
}

void listar(Livro livros[], int total) {
    int exibidos = 0;
    printf("\n=== Lista de Todos os Livros Ativos ===");
    
    for (int i = 0; i < total; i++) {
        if (livros[i].ativo) {
            exibirLivro(livros[i]);
            exibidos++;
        }
    }

    if (exibidos == 0) {
        printf("\nNenhum livro cadastrado ou ativo no momento.\n");
    }
}

// Nova Função exigida pelo enunciado: Buscar por ID
void buscarPorIdMenu(Livro livros[], int total) {
    printf("\n--- Buscar Livro por ID ---\n");
    int id = lerInteiro("Digite o ID do livro: ");
    int indice = buscarId(livros, total, id);

    if (indice == -1) {
        printf("\n[ERRO] Livro com o ID %d nao foi encontrado ou foi removido.\n", id);
        return;
    }

    exibirLivro(livros[indice]);
}

void atualizar(Livro livros[], int total) {
    printf("\n--- Atualizar Titulo do Livro ---\n");
    int id = lerInteiro("Digite o ID do livro: ");
    int indice = buscarId(livros, total, id);

    if (indice == -1) {
        printf("\n[ERRO] Livro nao encontrado.\n");
        return;
    }

    printf("Titulo atual: %s\n", livros[indice].titulo);
    lerTexto("Novo titulo: ", livros[indice].titulo, 100);
    printf("\n[SUCESSO] Titulo atualizado com sucesso.\n");
}

void remover(Livro livros[], int total) {
    printf("\n--- Remover Livro (Logica) ---\n");
    int id = lerInteiro("Digite o ID do livro: ");
    int indice = buscarId(livros, total, id);

    if (indice == -1) {
        printf("\n[ERRO] Livro nao encontrado.\n");
        return;
    }

    // Remoção lógica alterando a flag 'ativo' para 0
    livros[indice].ativo = 0;
    printf("\n[SUCESSO] Livro '%s' removido logicamente do sistema.\n", livros[indice].titulo);
}

int main() {
    Livro livros[MAX]; // Arrays estáticos obrigatórios
    int total = 0;
    int proximoId = 1;
    int op;

    do {
        printf("\n===== SISTEMA DE BIBLIOTECA =====\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Listar Todos os Livros\n");
        printf("3 - Buscar Livro por ID\n");
        printf("4 - Atualizar Titulo de Livro\n");
        printf("5 - Remover Livro (Logica)\n");
        printf("0 - Encerrar Programa\n");
        printf("=================================\n");
        
        op = lerInteiro("Opcao: ");

        switch (op) {
            case 1:
                cadastrar(livros, &total, &proximoId);
                break;
            case 2:
                listar(livros, total);
                break;
            case 3:
                buscarPorIdMenu(livros, total);
                break;
            case 4:
                atualizar(livros, total);
                break;
            case 5:
                remover(livros, total);
                break;
            case 0:
                printf("\nEncerrando o programa... Ate logo!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }

    } while (op != 0);

    return 0;
}

    return 0;
}
