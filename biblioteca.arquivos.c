#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Livro *bib = NULL;
int total = 0, proxId = 1;

int buscar(int id) {
    for(int i = 0; i < total; i++)
        if(bib[i].id == id && bib[i].ativo) return i;
    return -1;
}

void salvar() {
    FILE *f = fopen("livros.txt", "w");
    if(!f) return;
    fprintf(f, "%d;%d\n", total, proxId);
    for(int i = 0; i < total; i++) {
        fprintf(f, "%d;%s;%s;%d;%s;%d;%d;%d;%d\n", bib[i].id, bib[i].titulo, 
                bib[i].autor.nome, bib[i].autor.nascimento, bib[i].isbn, 
                bib[i].ano, bib[i].categoria, bib[i].situacao, bib[i].ativo);
    }
    fclose(f);
}

void carregar() {
    FILE *f = fopen("livros.txt", "r");
    if(!f) return;
    fscanf(f, "%d;%d\n", &total, &proxId);
    bib = malloc(total * sizeof(Livro));
    for(int i = 0; i < total; i++) {
        int c, s;
        fscanf(f, "%d;%99[^;];%49[^;];%d;%19[^;];%d;%d;%d;%d\n", &bib[i].id, 
               bib[i].titulo, bib[i].autor.nome, &bib[i].autor.nascimento, 
               bib[i].isbn, &bib[i].ano, &c, &s, &bib[i].ativo);
        bib[i].categoria = (Categoria)c; bib[i].situacao = (Situacao)s;
    }
    fclose(f);
}

void lerString(char *msg, char *v, int tam) {
    printf("%s", msg);
    fgets(v, tam, stdin);
    v[strcspn(v, "\n")] = '\0';
}

void adicionar() {
    bib = realloc(bib, (total + 1) * sizeof(Livro));
    bib[total].id = proxId++;
    bib[total].ativo = 1;
    bib[total].situacao = DISPONIVEL;

    getchar(); // Limpa buffer
    lerString("Titulo: ", bib[total].titulo, 100);
    lerString("ISBN: ", bib[total].isbn, 20);
    printf("Ano: "); scanf("%d", &bib[total].ano); getchar();
    lerString("Autor: ", bib[total].autor.nome, 50);
    printf("Nasc. Autor: "); scanf("%d", &bib[total].autor.nascimento);
    printf("1-Ficcao 2-Ciencia 3-Historia: "); scanf("%d", (int*)&bib[total].categoria);

    total++;
    salvar();
    printf("Cadastrado!\n");
}

void listar() {
    for(int i = 0; i < total; i++) {
        if(bib[i].ativo)
            printf("\nID: %d | %s | %s | Ano: %d\n", bib[i].id, bib[i].titulo, bib[i].autor.nome, bib[i].ano);
    }
}

int main() {
    int op, id, pos;
    carregar();
    do {
        printf("\n1-Add 2-Listar 3-Buscar 4-Edit Titulo 5-Remover 0-Sair\nOpcao: ");
        scanf("%d", &op);
        if(op == 1) adicionar();
        if(op == 2) listar();
        if(op == 3 || op == 4 || op == 5) {
            printf("ID: "); scanf("%d", &id);
            pos = buscar(id);
            if(pos == -1) printf("Nao encontrado.\n");
            else if(op == 3) printf("Livro: %s - Autor: %s\n", bib[pos].titulo, bib[pos].autor.nome);
            else if(op == 4) { getchar(); lerString("Novo Titulo: ", bib[pos].titulo, 100); salvar(); }
            else if(op == 5) { bib[pos].ativo = 0; salvar(); printf("Removido!\n"); }
        }
    } while(op != 0);
    free(bib);
    return 0;
}


    return 0;
}
