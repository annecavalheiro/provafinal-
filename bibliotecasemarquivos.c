//Sistema de Cadastro de Livros

#include <stdio.h>
#include <string.h>

#define MAX 100
// 1. Enums obrigatorios
typedef enum { FICCAO = 1, CIENCIA, HISTORIA } Categoria;
typedef enum { DISPONIVEL = 1, EMPRESTADO } Situacao;
// 2. Struct DadosAutor obrigatoria
typedef struct {
    char nome[50];
    int nascimento;
} DadosAutor;
// 3. Struct Livro aninhada com todos os campos
typedef struct {
    int id;
    char titulo[100];
    char isbn[20];
    int ano;
    DadosAutor autor; // Aninhamento aqui
    Categoria categoria;
    Situacao situacao;
    int ativo; // Remocao logica
} Livro;
// 4. Busca por ID simples
int buscarId(Livro livros[], int total, int id) {
    for (int i = 0; i < total; i++) {
        if (livros[i].id == id && livros[i].ativo == 1) {
            return i; // Retorna a posicao se achar e estiver ativo
        }
    }
    return -1; // Nao encontrou
}
// 5. Cadastro obrigatorio usando ponteiros (*total e *id)
void cadastrar(Livro livros[], int *total, int *id) {
    if (*total >= MAX) {
        printf("Limite atingido!\n");
        return;
    }

    Livro n;
    n.id = *id;
    n.ativo = 1;
    n.situacao = DISPONIVEL;

    getchar(); // Limpa o buffer do teclado
    printf("Titulo: ");
    fgets(n.titulo, 100, stdin);
    n.titulo[strcspn(n.titulo, "\n")] = '\0'; // Remove o ENTER

    printf("ISBN: ");
    fgets(n.isbn, 20, stdin);
    n.isbn[strcspn(n.isbn, "\n")] = '\0';

    printf("Ano: ");
    scanf("%d", &n.ano);
    getchar(); // Limpa o ENTER antes do proximo texto

    printf("Nome do Autor: ");
    fgets(n.autor.nome, 50, stdin);
    n.autor.nome[strcspn(n.autor.nome, "\n")] = '\0';

    printf("Ano de Nasc. Autor: ");
    scanf("%d", &n.autor.nascimento);

    printf("Categoria (1-Ficcao, 2-Ciencia, 3-Historia): ");
    scanf("%d", (int*)&n.categoria);

    livros[*total] = n; // Salva no array estatico
    (*total)++;         // Aumenta o total usando ponteiro
    (*id)++;            // Aumenta o proximo ID usando ponteiro

    printf("Livro cadastrado!\n");
}

int main() {
    Livro livros[MAX]; // Arrays estáticos obrigatorios
    int total = 0, proximoId = 1, op, id, pos;

    do {
        printf("\n--- MENU ---\n1-Cadastrar\n2-Listar\n3-Buscar\n4-Editar Titulo\n5-Remover\n0-Sair\nOpcao: ");
        scanf("%d", &op);

        if (op == 1) {
            cadastrar(livros, &total, &proximoId);
        }
        else if (op == 2) {
            printf("\n--- LIVROS ATIVOS ---\n");
            for (int i = 0; i < total; i++) {
                if (livros[i].ativo == 1) {
                    printf("ID: %d | Titulo: %s | Autor: %s\n", livros[i].id, livros[i].titulo, livros[i].autor.nome);
                }
            }
        }
        else if (op == 3 || op == 4 || op == 5) {
            printf("Digite o ID: ");
            scanf("%d", &id);
            pos = buscarId(livros, total, id);

            if (pos == -1) {
                printf("Livro nao encontrado!\n");
            } else {
                if (op == 3) {
                    printf("Titulo: %s\nISBN: %s\nAno: %d\n", livros[pos].titulo, livros[pos].isbn, livros[pos].ano);
                }
                else if (op == 4) {
                    getchar(); // Limpa o buffer
                    printf("Novo Titulo: ");
                    fgets(livros[pos].titulo, 100, stdin);
                    livros[pos].titulo[strcspn(livros[pos].titulo, "\n")] = '\0';
                    printf("Titulo atualizado!\n");
                }
                else if (op == 5) {
                    livros[pos].ativo = 0; // Remocao logica feita aqui
                    printf("Livro removido!\n");
                }
            }
        }
    } while (op != 0); // Encerrar o programa

    return 0;
}
