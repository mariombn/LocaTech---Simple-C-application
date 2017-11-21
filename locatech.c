/***
 *     __                                 ________                    __       
 *    |  \                               |        \                  |  \      
 *    | $$       ______    _______  ______\$$$$$$$$______    _______ | $$____  
 *    | $$      /      \  /       \|      \ | $$  /      \  /       \| $$    \ 
 *    | $$     |  $$$$$$\|  $$$$$$$ \$$$$$$\| $$ |  $$$$$$\|  $$$$$$$| $$$$$$$\
 *    | $$     | $$  | $$| $$      /      $$| $$ | $$    $$| $$      | $$  | $$
 *    | $$_____| $$__/ $$| $$_____|  $$$$$$$| $$ | $$$$$$$$| $$_____ | $$  | $$
 *    | $$     \\$$    $$ \$$     \\$$    $$| $$  \$$     \ \$$     \| $$  | $$
 *     \$$$$$$$$ \$$$$$$   \$$$$$$$ \$$$$$$$ \$$   \$$$$$$$  \$$$$$$$ \$$   \$$
 *                                                                             
 *    @autor: Aline Alves de Freitas <>
 *                                                                             
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int op, i, encontrou;                                           // Variaveis de Apoio
int carros[10], nCarros, status[10], clienteCarro[10];                               // Variaveis Carros
int clientes[10], nCliente, idadeClientes[10];    // Variaveis Cliente
char nomeCliente[10][256];                                         // Array com o Nome do Cliente

int main()
{
	setlocale(LC_ALL, "Portuguese");	
    for (i = 0; i < 10; i++) {
        status[i] = 0;         // true = Livre / false = Alugado
        carros[i] = i+1;       // Preenche o array com os números dos Carros
        clientes[i] = i+1;     // Preenche o array com os números dos Clientes
        idadeClientes[i] = 0;  // Clientes com Idade 0 = Não Cadastrado
        clienteCarro[i] = -1;  //-1 = Cliente sem Carro
    }
    menu();
}

void debug()
{
	for (i = 0; i < 10; i++) {
		printf("Carro: %d - Cliente: %d\n", i, clienteCarro[i]);
	}
}

void alugarCarro()
{
	listarCarrosLivres();
	printf("Informe o número do carro que deseja reservar: ");
	scanf("%d", &nCarros);
	if (status[nCarros-1]==1) {
	    printf("Carro já reservada. Verifique outra opção.");
	}
	else {
	    for (i = 0; i < 10; i++) {
	        if (nCarros == carros[i]) {
	        	status[i] = 1;
	        	listarClientes();
	        	printf("Selecione o cliente que está alugando o carro: ");
	        	scanf("%d", &nCliente);
	        	
	        	printf("\n\nnCliente: [%d]\n\n", nCliente);
	        	
	        	clienteCarro[nCarros-1] = nCliente-1;
	            printf("Reserva realizada com sucesso!");
	        }
	    }
	}
}

void liberarCarro()
{
	int e, idadeCliente;
	idadeCliente = 0;
	listarCarrosOcupados();
    printf("Informe o numero do carro que deseja liberar: ");
    scanf("%d", &nCarros);
    if (status[nCarros-1] == 0) {
        printf("Este carro ja esta livre. Verifique outra opção.");
    }
    else  {
        for (i = 0; i < 10; i++) {
            if (nCarros == carros[i]) {
                status[i] = 0;
                
                idadeCliente = idadeClientes[clienteCarro[i]];
                
                if (idadeCliente >= 65) {
                	printf("\n\nPARABÉNS!! VOCÊ GANHOU 10%% DE DESCONTO\n\n");
				}
                
                printf("Liberacao realizada com sucesso!");
            }
        }
    }
}

void listarCarrosOcupados()
{
    echo("Carros Ocupados\n");
    encontrou = 0;
    for (i = 0; i < 10; i++) {
        if (status[i] == 1) {
            printf("[ %d ] - Alugado\n", carros[i]);
            encontrou = 1;
        }
    }
    if (encontrou==0) {
        printf("Todas as carros estão disponiveis");
    }
    
}

void listarCarrosLivres()
{
	echo("Carros Disponiveis\n");
	encontrou = 0;
	for (i = 0; i < 10; i++)  {
	    if (status[i] == 0) {
	        printf("[ %d ] - Disponivel\n", carros[i]);
	        encontrou = 1;
	    }
	}
	if(encontrou == 0) {
	    printf("Todas as carros estão alugados");
	}
}

void listarCarros()
{
    echo("Listagem de Carros\n");
    for (i = 0; i < 10; i++) {
        if (status[i] == 1)  {
            printf("[ %d ] - Alugado\n", carros[i]);
        }
        else {
            printf("[ %d ] - Disponivel\n", carros[i]);
        }
    }
}

void cadastrarCliente()
{
	echo("Cadastrar novo Cliente\n");
	encontrou = 0;
	int idade = 0;
	char nome[256];
	for (i = 0; i < 10; i++) {
		if (idadeClientes[i] == 0 && encontrou == 0) {
			encontrou = 1;
			printf("Você está cadastrando o cliente de id [%d]\n", i+1);
			
			printf("Nome do Cliente: ");
			scanf("%s" , nome);
			
			nomeCliente[i][0] = nome;
			
			while (idade <= 0) {
				printf("Informe a idade do Cliente: ");
				scanf("%d", &idade);
				if (idade <= 0) {
					printf("Idade inválida.\n");
				}
			}
			idadeClientes[i] = idade;
		}
	}
	if (encontrou == 0) {
		printf("Não é possivel cadastrar mais clientes no sistema.\n");
	}
}

void listarClientes()
{
	echo("Listagem de Clientes\n");
	encontrou = 0;
	for (i = 0; i < 10; i++) {
		if (idadeClientes[i] != 0) {
			printf("[ %d ] - ", i+1);
			printf("%s ", nomeCliente[i]);
			printf(" - %d anos\n", idadeClientes[i]);
			encontrou = 1;
		}
	}
	if (encontrou == 0) {
		echo ("Nenhum cliente cadastrado no sistema");
	}
}

void relatorioAlugueis()
{
	echo("Relatório geral de Aluguéis");
	echo("---------------------------\n\n");
	
	for (i = 0; i < 10; i++) {
		if (status[i] == 0) {
			printf("Id Carro: [ %d ] - Status: [  Disponivel  ]\n", i+1);
		} else {
			printf("Id Carro: [ %d ] - Status: [ Indisponivel ] - Id Cliente: [ %d ] - Nome Cliente: [ %s ] - Idade: [%d]\n", i+1, clienteCarro[i]+1, nomeCliente[clienteCarro[i]], idadeClientes[clienteCarro[i]]);
		}
		
	}
}

void menu()
{
	op = 1;
	while (op!=0) {
		limpaTela();
		bemVindo();
        printf("\n\n            +------------------------------+\n");
		printf("            ¦ MENU PRINCIPAL               ¦\n");
		printf("            ¦------------------------------¦\n");
		printf("            ¦  1 ¦ Alugar Carro            ¦\n");
		printf("            ¦  2 ¦ Liberar Carro           ¦\n");
		printf("            ¦  3 ¦ Listar Carros Ocupadas  ¦\n");
		printf("            ¦  4 ¦ Listar Carros Livres    ¦\n");
		printf("            ¦  5 ¦ Listar Todas as Carros  ¦\n");
		printf("            ¦  6 ¦ Cadastrar Novo Cliente  ¦\n");
		printf("            ¦  7 ¦ Listar Clientes         ¦\n");
		printf("            ¦  8 ¦ Relatório de Aluguéis   ¦\n");
		printf("            ¦  0 ¦ SAIR                    ¦\n");
		printf("            +------------------------------+\n");
		printf("\n\n  Opção: ");
        scanf("%d", &op);
        printf("\n");
        limpaTela();
        switch (op) {
	        case 1:
	        	alugarCarro();
	            break;
	        case 2:
	        	liberarCarro();
	            break;
	        case 3:
	        	listarCarrosOcupados();
	            break;
	        case 4:
	        	listarCarrosLivres();
	            break;
	        case 5:
	        	listarCarros();
	            break;
	        case 6:
	        	cadastrarCliente();
	            break;
	        case 7:
	        	listarClientes();
	            break;
	        case 8:
	        	relatorioAlugueis();
	        	break;
	        case 9:
	        	debug();
	        	break;
	        case 0:
	            break;
	        default:
	            printf("\n\nOpção Invalida!\n\n");
        }
        fim();
    }
}

void bemVindo()
{
	printf("    __                                 ________                    __        \n");
	printf("   |  \\                               |        \\                  |  \\       \n");
	printf("   | $$       ______    _______  ______\\$$$$$$$$______    _______ | $$____   \n");
	printf("   | $$      /      \\  /       \\|      \\ | $$  /      \\  /       \\| $$    \\  \n");
	printf("   | $$     |  $$$$$$\\|  $$$$$$$ \\$$$$$$\\| $$ |  $$$$$$\\|  $$$$$$$| $$$$$$$\\ \n");
	printf("   | $$     | $$  | $$| $$      /      $$| $$ | $$    $$| $$      | $$  | $$ \n");
	printf("   | $$_____| $$__/ $$| $$_____|  $$$$$$$| $$ | $$$$$$$$| $$_____ | $$  | $$ \n");
	printf("   | $$     \\\\$$    $$ \\$$     \\\\$$    $$| $$  \\$$     \\ \\$$     \\| $$  | $$ \n");
	printf("    \\$$$$$$$$ \\$$$$$$   \\$$$$$$$ \\$$$$$$$ \\$$   \\$$$$$$$  \\$$$$$$$ \\$$   \\$$ \n");
	printf("\n\n");
}

void fim()
{
	printf("\nPrecione qualquer tecla para voltar ao Menu\n");
	getch();
}

void echo(char mensagem[])
{
	printf("%s\n", mensagem);
}

void limpaTela()
{
	system("cls");
}
