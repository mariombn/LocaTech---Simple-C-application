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
#include <string.h>

// Variáveis Globais de Apoio
int op, i, e, encontrou;
// Variáveis de Parametro
float porcentagemMultaAtraso;
// Variáveis Globais do Carro
int carros[10];
int nCarros;
int status[10];
int clienteCarro[10];
int diasReserva[10];
int diasEfetivo[10];
float valorDiaria[10];
char placaCarro[10][256];
char marcaCarro[10][256];
char modeloCarro[10][256];
// Variáveis Globais do Cliente
int clientes[10];
int nCliente;
int idadeClientes[10];
char nomeCliente[10][256];


/**
 * Main
 */
int main()
{
	bootstrap();
	mock();
    menu();
}

/**
 * Bootstrap do sistema, carrega todas as variaveis iniciais
 */
void bootstrap()
{
	setlocale(LC_ALL, "Portuguese"); // Permite o Output de caracteres especiais
	
	//Processa todos os valores iniciais do Sistema
	porcentagemMultaAtraso = 10;         // Porcentagem de atraso definido no inicio do programa
	
    for (i = 0; i < 10; i++) {
        status[i] = 0;                   // true = Livre / false = Alugado
        carros[i] = i + 1;               // Preenche o array com os números dos Carros
        clientes[i] = i + 1;             // Preenche o array com os números dos Clientes
        idadeClientes[i] = 0;            // Clientes com Idade 0 = Não Cadastrado
        clienteCarro[i] = -1;            // -1 = Cliente sem Carro
        diasReserva[i] = 0;              // Valor de dias solicitado na hora da reserva
        diasEfetivo[i] = 0;              // Valor real de dias que o carro foi alugado
        valorDiaria[i] = 10 * (i + 1);   // Define o valor padrão da diária de cada carro.
    }
}

/**
 * Calcula o Valor (sem descontos) a ser pago na devolução do veiculo
 * @param int dReserva
 * @param int dEfetivo
 * @param float valorVeiculo
 * @return float valorTotal
 */
float calculaPrecoLocacao(int dReserva, int dEfetivo, float valorVeiculo)
{
	int diasReais = 0;
	int diasExcedente = 0;
	float valorTotal = 0;
	if (dReserva < dEfetivo) {
		diasExcedente = dEfetivo - dReserva;
	}
	valorTotal = (float) valorVeiculo * dReserva;
	if (diasExcedente > 0) {
		valorTotal += (float) (valorVeiculo * diasExcedente) * ((porcentagemMultaAtraso / 100) + 1);
	}
	return (float) valorTotal;
}

/**
 * Aluga um determinado carro no sistema
 */
void alugarCarro()
{
	float valorTotal;
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
	        	do {
	        		printf("\nQuanto dias o cliente pretende ficar com o carro?: ");
	        		scanf("%d", &diasReserva[i]);
	        		if (diasReserva[i] < 0 || diasReserva[i] > 365) {
	        			printf("\nO valor de dias deve ser entre 1 e 365 dias.");
					}
				} while (diasReserva[i] < 0 || diasReserva[i] > 365);
	        	printf("\nValor previsto a ser pago na devolução é de R$%f\n", (float) diasReserva[i] * valorDiaria[i]);
	        	clienteCarro[nCarros-1] = nCliente-1;
	            printf("Reserva realizada com sucesso!");
	        }
	    }
	}
}

/**
 * Libera um determinado carro alugado no sistema
 */
void liberarCarro()
{
	int e, idadeCliente, diasReais;
	float total = 0;
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
            	
            	do {
            		printf("\nInforme o número de dias reais da locação: ");
            		scanf("%d", &diasReais);
            		if (diasReais < 1) {
            			printf("O minimo de dias possivel de locação é de 1 dia.");
					}
				} while (diasReais < 1);
				
				total = calculaPrecoLocacao(diasReserva[i], diasEfetivo[i], valorDiaria[i]);
				
				printf("Valor Total a ser pago é de R$%f", total);
            	
            	
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

/**
 * Lista todos os carros alugados no sistema
 */
void listarCarrosOcupados()
{
    echo("Carros Ocupados\n");
    encontrou = 0;
    for (e = 0; e < 10; e++) {
        if (status[e] == 1) {
            printf("[ %d ] - %s - %s - %s - Alugado - Valor: R$%f\n", carros[e], placaCarro[e], marcaCarro[e], modeloCarro[e], valorDiaria[e]);
            encontrou = 1;
        }
    }
    if (encontrou==0) {
        printf("Todas as carros estão disponiveis");
    }
}

/**
 * Lista todos os carros livres no Sistema
 */
void listarCarrosLivres()
{
	echo("Carros Disponiveis\n");
	encontrou = 0;
	for (e = 0; e < 10; e++)  {
	    if (status[e] == 0) {
	        printf("[ %d ] - %s - %s - %s - Disponivel - Valor: R$%f\n", carros[e], placaCarro[e], marcaCarro[e], modeloCarro[e], valorDiaria[e]);
	        encontrou = 1;
	    }
	}
	if(encontrou == 0) {
	    printf("Todas as carros estão alugados");
	}
}

/**
 * Lista todos os carros cadastrados no Sistema
 */
void listarCarros()
{
    echo("Listagem de Carros\n");
    for (e = 0; e < 10; e++) {
        if (status[e] == 1)  {
            printf("[ %d ] - %s - %s - %s - Alugado - Valor: R$%f\n", carros[e], placaCarro[e], marcaCarro[e], modeloCarro[e], valorDiaria[e]);
        }
        else {
            printf("[ %d ] - %s - %s - %s - Disponivel - Valor: R$%f\n", carros[e], placaCarro[e], marcaCarro[e], modeloCarro[e], valorDiaria[e]);
        }
    }
}

/**
 * Cadastra um novo cliente no sistema
 */
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
			scanf(" %[^\n]",nomeCliente[i]);
			//scanf("%s" , nome);
			
			//nomeCliente[i] = nome;
			
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

/**
 * Lista todos os clientes na tela
 */
void listarClientes()
{
	echo("Listagem de Clientes\n");
	encontrou = 0;
	for (e = 0; e < 10; e++) {
		if (idadeClientes[e] != 0) {
			printf("[ %d ] - ", e+1);
			printf("%s ", nomeCliente[e]);
			printf(" - %d anos\n", idadeClientes[e]);
			encontrou = 1;
		}
	}
	if (encontrou == 0) {
		echo ("Nenhum cliente cadastrado no sistema");
	}
}

/**
 * Gera um relatório geral do Sistema
 */
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

/**
 * Metodo para controlar a porcentagem da multa por dias de atraso na devolução do veículo
 */
void porcentagemMulta()
{
	char opcao;
	int mudou = 0;
	echo("Porcentagem de Multa por Atraso\n");
	printf("O Valor atual é de %f%%\n\nDeseja Mudar o valor? 's' ou 'n': ", porcentagemMultaAtraso);
	scanf("  %c", &opcao); // Não sei por que precisa desses dois espaços em branco, mas só assim deu certo
	
	if (opcao == 's') {
		while((porcentagemMultaAtraso <= 0 || porcentagemMultaAtraso >= 100) ||  mudou == 0) {
			mudou = 1;
			printf("\n\nQual o novo valor desejado? ");
			scanf("%f", &porcentagemMultaAtraso);
			if (porcentagemMultaAtraso <= 0 || porcentagemMultaAtraso >= 100) {
				printf("\nValor invalido. Ele precisa ser um valor entre 1 e 100\n");
			}
		}
		printf("\nValor atualizado com sucesso!\n");
	}
}

/**
 * Metodo para gerenciamento de veículos (Edição das informações)
 */
void controleVeiculos()
{
	int opcao;
	encontrou = 0;
	echo("Valores das diárias \n");
	listarCarros();
	printf("\nDeseja mudar algum dos valores? (0 para não ou o ID do veículo que deseja mudar): ");
	scanf("%d", &opcao);
	
	if (opcao != 0) {
		for (i = 0; i < 10; i++) {
			if (opcao == carros[i]) {
				encontrou = 1;
				inputDadosCarro(i);
				printf("\nValor atual do carro selecionado é de R$%f.\nQual o novo valor desejado? ", valorDiaria[i]);
				do {
					scanf("%f", &valorDiaria[i]);
					
					if (valorDiaria[i] < 0 || valorDiaria[i] > 1000) {
						printf("\nValor informado invalido! O valor deve estar entre R$1,00 e R$1000,00");
					}
				} while(valorDiaria[i] < 0 || valorDiaria[i] > 1000);
				printf("\nValor atualizado com sucesso!");
			}
		}
		if (encontrou == 0) {
			printf("\nO id digitado não foi encontrado!");
		}
	}
}

/**
 * Armazena as informações de texto referentes a um veiculo
 * @param int indice
 */
void inputDadosCarro(int indice)
{
	printf("\n\nInforme a Marca do Carro: ");
	scanf(" %[^\n]",marcaCarro[indice]);
	
	printf("\n\nInforme o Modelo do Carro: ");
	scanf(" %[^\n]",modeloCarro[indice]);
	
	printf("\n\nInforme a Placa do Carro: ");
	scanf(" %[^\n]",placaCarro[indice]);
}

/**
 * Monta o menu principal do sistema
 */
void menu()
{
	op = 1;
	while (op!=0) {
		limpaTela();
		bemVindo();
        printf("\n\n            +-----------------------------------+\n");
		printf("            ¦ MENU PRINCIPAL                   ¦\n");
		printf("            ¦----------------------------------¦\n");
		printf("            ¦  1 ¦ Alugar Carro                ¦\n");
		printf("            ¦  2 ¦ Liberar Carro               ¦\n");
		printf("            ¦  3 ¦ Listar Carros Ocupadas      ¦\n");
		printf("            ¦  4 ¦ Listar Carros Livres        ¦\n");
		printf("            ¦  5 ¦ Listar Todas as Carros      ¦\n");
		printf("            ¦  6 ¦ Cadastrar Novo Cliente      ¦\n");
		printf("            ¦  7 ¦ Listar Clientes             ¦\n");
		printf("            ¦  8 ¦ Relatório de Aluguéis       ¦\n");
		printf("            ¦  9 ¦ Porcentagem Multa Atraso    ¦\n");
		printf("            ¦ 10 ¦ Informações de Veiculos     ¦\n");
		printf("            ¦  0 ¦ SAIR                        ¦\n");
		printf("            +----------------------------------+\n");
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
	        	porcentagemMulta();
	        	break;
	        case 10:
	        	controleVeiculos();
	        	break;
	        case 0:
	        	exit(0);
	            break;
	        default:
	            printf("\n\nOpção Invalida!\n\n");
        }
        fim();
    }
}

/**
 * Apresenta o logotipo do Sistema
 */
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

/**
 * Metodo final para o loop do Menu
 */
void fim()
{
	printf("\nPrecione qualquer tecla para voltar ao Menu\n");
	getch();
}

/**
 * Faz um printf com quebra de linha n ofinal
 */
void echo(char mensagem[])
{
	printf("%s\n", mensagem);
}

/**
 * Limpa a tela do Console
 */
void limpaTela()
{
	system("cls");
}

/**
 * Função responsavel por fazer o mock de dados inicial do sistema.
 * Caso deseje que não seje feito nenhum input de informações automatico, basta comentar essa função na main()
 */
void mock()
{
	char marcas[4][256];
	
	strcpy(marcas[0], "Chevrolet");
	strcpy(marcas[1], "Volkswagen");
	strcpy(marcas[2], "Fiat");
	strcpy(marcas[3], "Ford");
	
	strcpy(placaCarro[0], "AEU5856");
	strcpy(marcaCarro[0], marcas[1]);
	strcpy(modeloCarro[0], "Gol");
	
	strcpy(placaCarro[1], "EUD9055");
	strcpy(marcaCarro[1], marcas[0]);
	strcpy(modeloCarro[1], "Onix");
	
	strcpy(placaCarro[2], "BCA4321");
	strcpy(marcaCarro[2], marcas[2]);
	strcpy(modeloCarro[2], "Palio");
	
	strcpy(placaCarro[3], "LKI9584");
	strcpy(marcaCarro[3], marcas[0]);
	strcpy(modeloCarro[3], "Cobalt");
	
	strcpy(placaCarro[4], "KLI4242");
	strcpy(marcaCarro[4], marcas[1]);
	strcpy(modeloCarro[4], "Up");
	
	strcpy(placaCarro[5], "OIU2511");
	strcpy(marcaCarro[5], marcas[3]);
	strcpy(modeloCarro[5], "New Fiesta");
	
	strcpy(placaCarro[6], "EFG2541");
	strcpy(marcaCarro[6], marcas[0]);
	strcpy(modeloCarro[6], "Cruzer");
	
	strcpy(placaCarro[7], "LKJ1233");
	strcpy(marcaCarro[7], marcas[3]);
	strcpy(modeloCarro[7], "Fusion");
	
	strcpy(placaCarro[8], "EFF9999");
	strcpy(marcaCarro[8], marcas[0]);
	strcpy(modeloCarro[8], "Impala");
	
	strcpy(placaCarro[9], "ABC1234");
	strcpy(marcaCarro[9], marcas[3]);
	strcpy(modeloCarro[9], "Mustang V8");
	
	idadeClientes[0] = 25;
	strcpy(nomeCliente[0], "Ricardo Dias");
	
	idadeClientes[1] = 21;
	strcpy(nomeCliente[1], "Aline Alves");
	
	idadeClientes[2] = 75;
	strcpy(nomeCliente[2], "Jose Algusto dos Santos");
}
