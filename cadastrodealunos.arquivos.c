//cadastro de aunos.arquivo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int matricula;
    char nome[50];
    int idade;
    float nota;
}Aluno;

Aluno *alunos = NULL;
int total = 0;

int buscarMatricula(int matricula){

    for(int i=0;i<total;i++){
        if(alunos[i].matricula == matricula)
            return i;
    }

    return -1;
}

void salvarArquivo(){

    FILE *arq = fopen("alunos.txt","w");

    if(arq == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fprintf(arq,"%d\n",total);

    for(int i=0;i<total;i++){

        fprintf(arq,"%d;%s;%d;%.2f\n",
                alunos[i].matricula,
                alunos[i].nome,
                alunos[i].idade,
                alunos[i].nota);
    }

    fclose(arq);
}

void carregarArquivo(){

    FILE *arq = fopen("alunos.txt","r");

    if(arq == NULL)
        return;

    fscanf(arq,"%d\n",&total);

    alunos = malloc(total*sizeof(Aluno));

    if(alunos == NULL){
        fclose(arq);
        return;
    }

    for(int i=0;i<total;i++){

        fscanf(arq,"%d;%49[^;];%d;%f\n",
               &alunos[i].matricula,
               alunos[i].nome,
               &alunos[i].idade,
               &alunos[i].nota);
    }

    fclose(arq);
}

void cadastrarAluno(){

    Aluno *temp;

    temp = realloc(alunos,(total+1)*sizeof(Aluno));

    if(temp == NULL){
        printf("Erro de memoria!\n");
        return;
    }

    alunos = temp;

    printf("Matricula: ");
    scanf("%d",&alunos[total].matricula);

    getchar();

    printf("Nome: ");
    fgets(alunos[total].nome,50,stdin);
    alunos[total].nome[strcspn(alunos[total].nome,"\n")] = '\0';

    printf("Idade: ");
    scanf("%d",&alunos[total].idade);

    printf("Nota Final: ");
    scanf("%f",&alunos[total].nota);

    total++;

    salvarArquivo();

    printf("Aluno cadastrado!\n");
}

void removerAluno(){

    int matricula;

    printf("Matricula: ");
    scanf("%d",&matricula);

    int pos = buscarMatricula(matricula);

    if(pos==-1){
        printf("Aluno nao encontrado!\n");
        return;
    }

    for(int i=pos;i<total-1;i++){
        alunos[i]=alunos[i+1];
    }

    total--;

    alunos = realloc(alunos,total*sizeof(Aluno));

    salvarArquivo();

    printf("Aluno removido!\n");
}

void listarAlunos(){

    printf("\n===== ALUNOS =====\n");

    for(int i=0;i<total;i++){

        printf("\nMatricula: %d\n",alunos[i].matricula);
        printf("Nome: %s\n",alunos[i].nome);
        printf("Idade: %d\n",alunos[i].idade);
        printf("Nota: %.2f\n",alunos[i].nota);
    }
}

int main(){

    int op;
    int matricula;
    int pos;

    carregarArquivo();

    do{

        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Buscar aluno\n");
        printf("3 - Remover aluno\n");
        printf("4 - Listar alunos\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d",&op);

        switch(op){

            case 1:
                cadastrarAluno();
                break;

            case 2:

                printf("Matricula: ");
                scanf("%d",&matricula);

                pos = buscarMatricula(matricula);

                if(pos==-1){
                    printf("Aluno nao encontrado!\n");
                }else{

                    printf("\nNome: %s\n",alunos[pos].nome);
                    printf("Idade: %d\n",alunos[pos].idade);
                    printf("Nota: %.2f\n",alunos[pos].nota);
                }

                break;

            case 3:
                removerAluno();
                break;

            case 4:
                listarAlunos();
                break;

            case 0:
                salvarArquivo();
                free(alunos);
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    }while(op!=0);

    return 0;
}