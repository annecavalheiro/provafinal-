// agenda sem arquivos

#include <stdio.h>
#include <string.h>
#define MAX 100

typedef enum { INATIVO = 0, NORMAL, FAVORITO, BLOQUEADO } Status;
typedef struct {
    char rua[50];
    int numero;
} Endereco;

typedef struct {
    int id;
    char nome[50];
    char telefone[20];
    Endereco end; // Struct aninhada
    Status status;
} Contato;

// --- PROTÓTIPOS OBRIGATÓRIOS DAS FUNÇÕES ---
void lerTxt(char *msg, char *v, int t);
void cadastrar(Contato ag[], int *tot);

int main() {
    Contato ag[MAX]; // Array estático
    int tot = 0, op, id, pos;

    do {
        printf("\n1-Add 2-Listar 3-Buscar 4-Edit Fone 5-Remover 0-Sair\nOpcao: ");
        scanf("%d", &op);
        getchar(); // Limpa o buffer do teclado

        if(op == 1) cadastrar(ag, &tot); // Cadastro passando ponteiro (*tot)
        
        else if(op == 2) {
            printf("\n--- CONTATOS ATIVOS ---\n");
            for(int i = 0; i < tot; i++)
                if(ag[i].status != INATIVO) 
                    printf("ID: %d | %s | %s\n", ag[i].id, ag[i].nome, ag[i].telefone);
        }
        
        else if(op == 3 || op == 4 || op == 5) {
            printf("ID do Contato: "); scanf("%d", &id); getchar();
            pos = -1;
            // Busca por ID integrada e direta
            for(int i = 0; i < tot; i++) {
                if(ag[i].id == id && ag[i].status != INATIVO) { pos = i; break; }
            }
            
            if(pos == -1) {
                printf("Nao encontrado.\n");
            } else {
                if(op == 3) printf("Nome: %s | Rua: %s, %d\n", ag[pos].nome, ag[pos].end.rua, ag[pos].end.numero);
                else if(op == 4) { lerTxt("Novo Fone: ", ag[pos].telefone, 20); printf("Atualizado!\n"); }
                else if(op == 5) { ag[pos].status = INATIVO; printf("Removido logicamente!\n"); }
            }
        }
    } while(op != 0);
    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

void lerTxt(char *msg, char *v, int t) {
    printf("%s", msg);
    fgets(v, t, stdin);
    v[strcspn(v, "\n")] = '\0'; // Remove o ENTER
}

void cadastrar(Contato ag[], int *tot) {
    if (*tot >= MAX) return;
    Contato c;
    c.id = *tot + 1; 
    c.status = NORMAL;

    printf("\n--- NOVO CONTATO (ID: %d) ---\n", c.id);
    lerTxt("Nome: ", c.nome, 50);
    lerTxt("Telefone: ", c.telefone, 20);
    lerTxt("Rua: ", c.end.rua, 50);
    printf("Numero: "); scanf("%d", &c.end.numero); getchar();

    ag[(*tot)++] = c; // Insere e incrementa o total via ponteiro
    printf("Contato cadastrado com sucesso!\n");
}
