// controle de estoque em  arquivos 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

Produto *estoque = NULL;
int total = 0;

int buscarPorId(int id) {
    int i;
    for(i = 0; i < total; i++) {
        if(estoque[i].id == id)
            return i;
    }
    return -1;
}

void salvarArquivo() {
    FILE *arq = fopen("estoque.txt", "w");

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arq, "%d\n", total);

    int i;
    for(i = 0; i < total; i++) {
        fprintf(arq,"%d;%s;%d;%.2f\n",
                estoque[i].id,
                estoque[i].nome,
                estoque[i].quantidade,
                estoque[i].preco);
    }

    fclose(arq);
}

void carregarArquivo() {

    FILE *arq = fopen("estoque.txt","r");

    if(arq == NULL)
        return;

    fscanf(arq,"%d\n",&total);

    estoque = (Produto*) malloc(total * sizeof(Produto));

    if(estoque == NULL){
        fclose(arq);
        return;
    }

    int i;

    for(i=0;i<total;i++){
        fscanf(arq,"%d;%49[^;];%d;%f\n",
               &estoque[i].id,
               estoque[i].nome,
               &estoque[i].quantidade,
               &estoque[i].preco);
    }

    fclose(arq);
}

void adicionarProduto(){

    Produto *temp;

    temp = realloc(estoque,(total+1)*sizeof(Produto));

    if(temp==NULL){
        printf("Erro de memoria!\n");
        return;
    }

    estoque = temp;

    printf("ID: ");
    scanf("%d",&estoque[total].id);

    if(buscarPorId(estoque[total].id)!=-1){
        printf("ID ja existe!\n");
        return;
    }

    getchar();

    printf("Nome: ");
    fgets(estoque[total].nome,50,stdin);
    estoque[total].nome[strcspn(estoque[total].nome,"\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d",&estoque[total].quantidade);

    printf("Preco: ");
    scanf("%f",&estoque[total].preco);

    total++;

    salvarArquivo();

    printf("Produto cadastrado!\n");
}

void removerProduto(){

    int id;

    printf("ID para remover: ");
    scanf("%d",&id);

    int pos = buscarPorId(id);

    if(pos==-1){
        printf("Produto nao encontrado!\n");
        return;
    }

    int i;

    for(i=pos;i<total-1;i++){
        estoque[i]=estoque[i+1];
    }

    total--;

    estoque = realloc(estoque,total*sizeof(Produto));

    salvarArquivo();

    printf("Produto removido!\n");
}

void imprimirRelatorio(){

    int i;
    float valorTotal=0;

    printf("\n===== RELATORIO =====\n");
    printf("ID\tNome\t\tQtd\tPreco\tTotal\n");

    for(i=0;i<total;i++){

        float subtotal = estoque[i].quantidade * estoque[i].preco;

        printf("%d\t%-15s\t%d\t%.2f\t%.2f\n",
                estoque[i].id,
                estoque[i].nome,
                estoque[i].quantidade,
                estoque[i].preco,
                subtotal);

        valorTotal += subtotal;
    }

    printf("\nValor total: R$ %.2f\n",valorTotal);
}

int main(){

    int op,id,pos;

    carregarArquivo();

    do{

        printf("\n===== MENU =====\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Buscar produto\n");
        printf("3 - Remover produto\n");
        printf("4 - Relatorio\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d",&op);

        switch(op){

            case 1:
                adicionarProduto();
                break;

            case 2:

                printf("Digite o ID: ");
                scanf("%d",&id);

                pos = buscarPorId(id);

                if(pos==-1){
                    printf("Produto nao encontrado!\n");
                }else{
                    printf("\nID: %d\n",estoque[pos].id);
                    printf("Nome: %s\n",estoque[pos].nome);
                    printf("Quantidade: %d\n",estoque[pos].quantidade);
                    printf("Preco: %.2f\n",estoque[pos].preco);
                }

                break;

            case 3:
                removerProduto();
                break;

            case 4:
                imprimirRelatorio();
                break;

            case 0:
                salvarArquivo();
                free(estoque);
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    }while(op!=0);

    return 0;
}