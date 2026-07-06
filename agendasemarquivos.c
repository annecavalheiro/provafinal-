// ==========================================
// AGENDA DE CONTATOS (SEM USO DE ARQUIVOS)
// ==========================================

#include <stdio.h>
#include <string.h>

#define MAX 100

// --- ENUMS E ESTRUTURAS ---

typedef enum { 
    INATIVO = 0, 
    NORMAL, 
    FAVORITO, 
    BLOQUEADO 
} Status;

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

// --- FUNÇÃO PRINCIPAL ---

int main() {
    Contato ag[MAX]; // Array estático de contatos
    int tot = 0;     // Total de contatos cadastrados
    int op, id, pos;

    do {
        // Menu de opções
        printf("\n1-Add | 2-Listar | 3-Buscar | 4-Edit Fone | 5-Remover | 0-Sair\nOpcao: ");
        scanf("%d", &op);
        getchar(); // Limpa o buffer do teclado para evitar bugs no fgets

        // Opção 1: Cadastrar novo contato
        if (op == 1) {
            cadastrar(ag, &tot);
        }
        
        // Opção 2: Listar todos os contatos ativos
        else if (op == 2) {
            printf("\n--- CONTATOS ATIVOS ---\n");
            for (int i = 0; i < tot; i++) {
                if (ag[i].status != INATIVO) {
                    printf("ID: %d | %s | %s\n", ag[i].id, ag[i].nome, ag[i].telefone);
                }
            }
        }
        
        // Opções 3, 4 e 5: Operações que exigem busca por ID
        else if (op == 3 || op == 4 || op == 5) {
            printf("ID do Contato: "); 
            scanf("%d", &id); 
            getchar(); // Limpa o buffer do teclado
            
            pos = -1;
            
            // Busca linear direta por ID
            for (int i = 0; i < tot; i++) {
                if (ag[i].id == id && ag[i].status != INATIVO) { 
                    pos = i; 
                    break; 
                }
            }
            
            // Verifica o resultado da busca
            if (pos == -1) {
                printf("Contato nao encontrado.\n");
            } else {
                // Opção 3: Exibir detalhes do contato buscado
                if (op == 3) {
                    printf("Nome: %s | Rua: %s, %d\n", ag[pos].nome, ag[pos].end.rua, ag[pos].end.numero);
                } 
                // Opção 4: Editar apenas o telefone do contato
                else if (op == 4) {
                    lerTxt("Novo Fone: ", ag[pos].telefone, 20); 
                    printf("Atualizado!\n"); 
                } 
                // Opção 5: Remoção lógica (muda o status para inativo)
                else if (op == 5) {
                    ag[pos].status = INATIVO; 
                    printf("Removido logicamente!\n"); 
                }
            }
        }
    } while (op != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO REORGANIZADA DAS FUNÇÕES ---

/**
 * Lê uma string do teclado, remove a quebra de linha (\n) e trata o buffer.
 */
void lerTxt(char *msg, char *v, int t) {
    printf("%s", msg);
    fgets(v, t, stdin);
    v[strcspn(v, "\n")] = '\0'; // Remove o caractere gerado pela tecla ENTER
}

/**
 * Cadastra um novo contato na agenda e atualiza o contador total.
 */
void cadastrar(Contato ag[], int *tot) {
    if (*tot >= MAX) {
        printf("Erro: Limite de armazenamento atingido (%d contatos).\n", MAX);
        return;
    }

    Contato c;
    c.id = *tot + 1; // ID gerado sequencialmente com base na posição
    c.status = NORMAL;

    printf("\n--- NOVO CONTATO (ID: %d) ---\n", c.id);
    lerTxt("Nome: ", c.nome, 50);
    lerTxt("Telefone: ", c.telefone, 20);
    lerTxt("Rua: ", c.end.rua, 50);
    
    printf("Numero: "); 
    scanf("%d", &c.end.numero); 
    getchar(); // Limpa o buffer após ler o inteiro

    // Insere no array na posição atual e depois incrementa o ponteiro totalizador
    ag[*tot] = c;
    (*tot)++; 
    
    printf("Contato cadastrado com sucesso!\n");
}
