//biblioteca.arquivo 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char titulo[50];
    char autor[50];
    int quantidade;
} Livro;

Livro *biblioteca = NULL;
int total = 0;

int buscarPorId(int id) {
    for(int i = 0; i < total; i++) {
        if(biblioteca[i].id == id)
            return i;
    }
    return -1;
}

void salvarArquivo() {

    FILE *arq = fopen("livros.txt", "w");

    if(arq == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    fprintf(arq, "%d\n", total);

    for(int i = 0; i < total; i++) {
        fprintf(arq,"%d;%s;%s;%d\n",
                biblioteca[i].id,
                biblioteca[i].titulo,
                biblioteca[i].autor,
                biblioteca[i].quantidade);
    }

    fclose(arq);
}

void carregarArquivo() {

    FILE *arq = fopen("livros.txt", "r");

    if(arq == NULL)
        return;

    fscanf(arq, "%d\n", &total);

    biblioteca = malloc(total * sizeof(Livro));

    for(int i = 0; i < total; i++) {
        fscanf(arq,"%d;%49[^;];%49[^;];%d\n",
               &biblioteca[i].id,
               biblioteca[i].titulo,
               biblioteca[i].autor,
               &biblioteca[i].quantidade);
    }

    fclose(arq);
}

void adicionarLivro() {

    Livro *temp = realloc(biblioteca,
                         (total + 1) * sizeof(Livro));

    if(temp == NULL) {
        printf("Erro de memoria.\n");
        return;
    }

    biblioteca = temp;

    printf("ID: ");
    scanf("%d", &biblioteca[total].id);

    getchar();

    printf("Titulo: ");
    fgets(biblioteca[total].titulo,50,stdin);
    biblioteca[total].titulo[
        strcspn(biblioteca[total].titulo,"\n")] = '\0';

    printf("Autor: ");
    fgets(biblioteca[total].autor,50,stdin);
    biblioteca[total].autor[
        strcspn(biblioteca[total].autor,"\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d",&biblioteca[total].quantidade);

    total++;

    salvarArquivo();

    printf("Livro cadastrado!\n");
}

void removerLivro() {

    int id;

    printf("ID para remover: ");
    scanf("%d",&id);

    int pos = buscarPorId(id);

    if(pos == -1) {
        printf("Livro nao encontrado.\n");
        return;
    }

    for(int i = pos; i < total - 1; i++) {
        biblioteca[i] = biblioteca[i + 1];
    }

    total--;

    biblioteca = realloc(biblioteca,
                        total * sizeof(Livro));

    salvarArquivo();

    printf("Livro removido.\n");
}

void listarLivros() {

    printf("\n===== LIVROS =====\n");

    for(int i = 0; i < total; i++) {

        printf("\nID: %d\n", biblioteca[i].id);
        printf("Titulo: %s\n", biblioteca[i].titulo);
        printf("Autor: %s\n", biblioteca[i].autor);
        printf("Quantidade: %d\n",
               biblioteca[i].quantidade);
    }
}

int main() {

    int op, id, pos;

    carregarArquivo();

    do {

        printf("\n=== BIBLIOTECA ===\n");
        printf("1 - Adicionar livro\n");
        printf("2 - Buscar livro\n");
        printf("3 - Remover livro\n");
        printf("4 - Listar livros\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d",&op);

        switch(op) {

            case 1:
                adicionarLivro();
                break;

            case 2:

                printf("ID: ");
                scanf("%d",&id);

                pos = buscarPorId(id);

                if(pos == -1) {
                    printf("Livro nao encontrado.\n");
                } else {

                    printf("\nTitulo: %s\n",
                           biblioteca[pos].titulo);

                    printf("Autor: %s\n",
                           biblioteca[pos].autor);

                    printf("Quantidade: %d\n",
                           biblioteca[pos].quantidade);
                }

                break;

            case 3:
                removerLivro();
                break;

            case 4:
                listarLivros();
                break;

            case 0:
                salvarArquivo();
                free(biblioteca);
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(op != 0);

    return 0;
}