//sistema petshop

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int codigo;
    char nome[50];
    char especie[30];
    int idade;
}Pet;

Pet *pets = NULL;
int total = 0;

int buscarCodigo(int codigo){

    for(int i=0;i<total;i++){
        if(pets[i].codigo == codigo)
            return i;
    }

    return -1;
}

void salvarArquivo(){

    FILE *arq = fopen("pets.txt","w");

    if(arq == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fprintf(arq,"%d\n",total);

    for(int i=0;i<total;i++){

        fprintf(arq,"%d;%s;%s;%d\n",
                pets[i].codigo,
                pets[i].nome,
                pets[i].especie,
                pets[i].idade);
    }

    fclose(arq);
}

void carregarArquivo(){

    FILE *arq = fopen("pets.txt","r");

    if(arq == NULL)
        return;

    fscanf(arq,"%d\n",&total);

    pets = malloc(total*sizeof(Pet));

    if(pets == NULL){
        fclose(arq);
        return;
    }

    for(int i=0;i<total;i++){

        fscanf(arq,"%d;%49[^;];%29[^;];%d\n",
               &pets[i].codigo,
               pets[i].nome,
               pets[i].especie,
               &pets[i].idade);
    }

    fclose(arq);
}

void cadastrarPet(){

    Pet *temp;

    temp = realloc(pets,(total+1)*sizeof(Pet));

    if(temp == NULL){
        printf("Erro de memoria!\n");
        return;
    }

    pets = temp;

    printf("Codigo: ");
    scanf("%d",&pets[total].codigo);

    getchar();

    printf("Nome: ");
    fgets(pets[total].nome,50,stdin);
    pets[total].nome[strcspn(pets[total].nome,"\n")] = '\0';

    printf("Especie: ");
    fgets(pets[total].especie,30,stdin);
    pets[total].especie[strcspn(pets[total].especie,"\n")] = '\0';

    printf("Idade: ");
    scanf("%d",&pets[total].idade);

    total++;

    salvarArquivo();

    printf("Pet cadastrado!\n");
}

void removerPet(){

    int codigo;

    printf("Codigo: ");
    scanf("%d",&codigo);

    int pos = buscarCodigo(codigo);

    if(pos==-1){
        printf("Pet nao encontrado!\n");
        return;
    }

    for(int i=pos;i<total-1;i++){
        pets[i]=pets[i+1];
    }

    total--;

    pets = realloc(pets,total*sizeof(Pet));

    salvarArquivo();

    printf("Pet removido!\n");
}

void listarPets(){

    printf("\n===== PETS =====\n");

    for(int i=0;i<total;i++){

        printf("\nCodigo: %d\n",pets[i].codigo);
        printf("Nome: %s\n",pets[i].nome);
        printf("Especie: %s\n",pets[i].especie);
        printf("Idade: %d\n",pets[i].idade);
    }
}

int main(){

    int op;
    int codigo;
    int pos;

    carregarArquivo();

    do{

        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar Pet\n");
        printf("2 - Buscar Pet\n");
        printf("3 - Remover Pet\n");
        printf("4 - Listar Pets\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d",&op);

        switch(op){

            case 1:
                cadastrarPet();
                break;

            case 2:

                printf("Codigo: ");
                scanf("%d",&codigo);

                pos = buscarCodigo(codigo);

                if(pos==-1){
                    printf("Pet nao encontrado!\n");
                }else{

                    printf("\nNome: %s\n",pets[pos].nome);
                    printf("Especie: %s\n",pets[pos].especie);
                    printf("Idade: %d\n",pets[pos].idade);
                }

                break;

            case 3:
                removerPet();
                break;

            case 4:
                listarPets();
                break;

            case 0:
                salvarArquivo();
                free(pets);
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    }while(op!=0);

    return 0;
}