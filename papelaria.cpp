#include <iostream>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <stdio.h>
#include <locale.h>

using namespace std;

/**
	
	Declarando fun��es por organiza��o do c�digo
	para que a fun��o int main possa chama-las

**/

/*
	Fun��o replace_char - replace = substituir, recebe uma string do tipo char
	 um caracter a ser encontrado na string
	 e um caracter a ser alterado pelo mesmo que fora encontrado
*/
void replace_char(char string[], char caracter, char replace);
/*
	Fun��o validar_login, recebe um string e verifica se a mesma
	esta contida no "banco de dados"
*/
bool validar_login(string dados_login);
/*
	Fun��o fazer_login - pede dados do login
	e manda a fun��o validar_login verificar a veracidade dos 
	dados
*/
int fazer_login();
/*
	Funcao bool para verificar se o codigo digitado ja existe 
	no banco de dados, recebe um c�digo para verificar a veracidade
	dos dados
*/
bool existe(int codigo);
/*
	Fun��o que cadastra produtos no "banco de dados"
*/
int cadastrar_produto();
/*
	Fun��o que faz o manejo do "banco de dados"
	e como o pr�prio nome diz, "vende"
*/
int vender();
/*
	Fun��o que consulta os produtos existentes
	no "banco de dados"
*/
string consultar_produtos();
/*
	int main - e como m�gica o progama come�a a funcionar
	esse scopo junto ao switch chama as fun��es de acordo
	com que o usu�rio queira
*/
int main(void)
{
    setlocale(LC_ALL, "");
    fazer_login(); 
    int acao = 0;
    while (acao == 0) { 
        acao = -acao;
        system("cls");
        cout << "\tBem vindo ao sistema de controle da papelaria RCGA !\n\n-O que voc� deseja fazer?\n";
        cout << "\n"
             << "\n[0] - Sair \t\t\t[1] - Vender\n[2] - Cadastrar Produtos\t[3] - Consultar produtos\n\nComando: ";
        cin >> acao;
        switch (acao) {
        case 0:
            exit(0);
        case 1:
            system("cls");
            cout << "----------------------------------------------------------------" << endl;
            cout << "\tBem vindo ao sistema de venda de produtos da papelaria RCGA\n\n";
            cout << "----------------------------------------------------------------" << endl;
            vender();
            continue;
        case 2:
        	cout << "----------------------------------------------------------------" << endl;
            cout << "\t\tBem vindo ao sistema de cadastro de produtos da papelaria RCGA\n";
            cout << "----------------------------------------------------------------" << endl;
            cadastrar_produto();
            continue;
        case 3:
            consultar_produtos();
            continue;
        default:
            cout << "\n\n\tComando n�o encontrado\n\n";
            system("pause");
            continue;
        } // switch
    } // while
} // int main

void replace_char(char string[], char caracter, char replace)
{
    while (*string)
	{
        if (*string == caracter)
            *string = replace;
        string++;
    }//while
} // void replace

bool validar_login(string dados_login)
{
    string dados_lidos;
    ifstream arquivo("usuarios.txt"); // cria um objeto de fluxo inout que � referente a um arquivo
    if (arquivo.is_open()) { 
        while (!arquivo.eof()) {
            getline(arquivo, dados_lidos);
            if (dados_login.compare(dados_lidos) == 0) {
                arquivo.close();
                return true; // retorna verdade se o usu�rio e senha dogitados estiverem no arquivo
            }
        }
        arquivo.close();
    }
    else {
        cout << "\n\n\t\aImposs�vel abrir o arquivo de db!\n";
        exit(0);
    }
    arquivo.close();
    return false;
}

int fazer_login()
{
    int i = 1;
    while(i)
	{
        string dados_login;
        system("cls");
        cout << "----------------------------------------------------------------" << endl;
        cout << "\t\tTELA DE LOGIN - PAPELARIA RCGA" << endl;
        cout << "----------------------------------------------------------------" << endl;
        cout << "\n\t\tUsuario : Senha" << endl
             << "\t\t    ";
        getline(cin, dados_login);
        if (validar_login(dados_login))
		{ // se o login for aprovado, ou seja, se a funcao validar_login retornar true, o progama continua, senao ele avisa e fecha.
            system("cls");
            cout << "login successfully" << endl;
            break;
        }
        else
		{
            cout << "Falha no login! \nVerifique se voc� preencheu todos os campos corretamente\n" << endl;
            system("pause");
			continue;
        } // else
    }//while
    return 0;
} // int fazer_login

/**
	Estrutura para agrupar as informa��es do produto
	no banco de dados
**/

typedef struct st_produto {
    int codigo;
    string descricao;
    float preco;
} produto;

bool existe(int codigo)
{ 
    int codigo_lido;
    char buf[1024];
    FILE* arquivo; // ponteiro do arquivo
    arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL)
	{
        cout << "\n\t\tOcorreu algum erro na configura��o do arquivo, por favor contate o suporte!\n";
        system("pause");
        exit(0);
    } //if
    while (fgets(buf, sizeof(buf), arquivo))
	{ // while que captura a linha com o aux. buf
        if (buf[0] == '\n')
            continue;

        sscanf(buf, "%d", &codigo_lido); // atribui a string lida a vairavel codigo_lido
        if (codigo == codigo_lido)
		{
            fclose(arquivo); // fecha o arquivo inicialmente aberto
            return true;
        } // if
    } // while
    fclose(arquivo); // fecha o arquivo inicialmente aberto
    return false; // caso nada seja encontrado, retorna falso
} // existe

int cadastrar_produto()
{
    ofstream arquivo; // cria um objeto de fluxo de output
    arquivo.open("produtos.txt", ofstream::app);
    if(arquivo.is_open())
	{
        int i = 1;
        arquivo.close(); // fecha o arquivo, pois inicialmente fora feito apenas um teste
        while(i != 0)
		{

            arquivo.open("produtos.txt", ofstream::app); // objeto que aponta para o arquivo
            produto novo;

            /**
				No trecho de codigo abaixo grava-se os dado na estrutura
			**/
			
            cout << "Codigo...: ";
            scanf("%d", &novo.codigo);
            cin.ignore();
            cout << "Descri��o: ";
            getline(cin, novo.descricao);
            replace(novo.descricao.begin(), novo.descricao.end(), ' ', '_');
            cout << "Pre�o....: ";
            scanf("%f", &novo.preco);
            if(!existe(novo.codigo))
			{
                arquivo << novo.codigo << " " << novo.descricao << " " << novo.preco << "\n"; // envia os dados agrupados ao arquivo
                arquivo.close(); // fecha o arquivo
                cout << "\n\t\tProduto cadastrado!\n\nDigite:\n\t\t[1] - Continuar \t [0] - Sair\n:: ";
                cin >> i; // vari�vel que controla o loop
            }
            else
			{
                cout << "\n\t\tO codigo deste produto ja existe!\n\n" << endl;
                exit(0);
            } //if else
        } //while
    } // if
    return 0;
} // cadastrar_produto();

int vender()
{
    int codigo, codigo_lido, quantidade, i = 1;
    char descricao[100];
    float preco, dinheiro, total_a_pagar = 0.0;
    while(i == 1)
	{
        system("cls");
        cout << "Codigo do produto: ";
        cin >> codigo;
        cout << "Quantidade.......: ";
        cin >> quantidade;

        char buf[1024];
        FILE* arquivo; // ponteiro do arquivo
        arquivo = fopen("produtos.txt", "r");
        while(fgets(buf, sizeof(buf), arquivo))
        {
            if (buf[0] == '\n')
                continue;

            sscanf(buf, "%d %s %f", &codigo_lido, descricao, &preco);
            if(codigo == codigo_lido)
			{

                total_a_pagar += quantidade * preco;
                cout << "\n\n\t\tProduto adicionado ao carrinho!\nValor atual: R$" << total_a_pagar << "\n\nDigite:\n\t[1] - Continuar comprando \t[0] - Sair\n:: ";
                cin >> i;
                if(!i)
				{
                    cout << fixed << "\nTotal a pagar: R$" << setprecision(2) << total_a_pagar << "\nDinheiro do cliente: ";
                    cin >> dinheiro;
                    if (dinheiro < total_a_pagar)
					{
                        cout << "\nO cliente deve R$" << total_a_pagar - dinheiro << endl;
                        system("pause");
                        break;
                	 }
               	  else
					 {
                     	cout << "\nTroco: R$" << dinheiro - total_a_pagar << endl;
                     	system("pause");
                     	break;
               	   } //else
                }//if
                fclose(arquivo);
                fflush(stdin);
            } //while
        }//while
    }//while
    return 0;
}//int vender

string consultar_produtos()
{
    int i = 1;
    while(i)
	{
		system("cls");
		cout << "----------------------------------------------------------------" << endl;
		cout << "\t\tBem vindo ao sistema de cadastro de produtos da papelaria RCGA\n";
        cout << "----------------------------------------------------------------" << endl;
        int codigo, codigo_lido;
        char descricao[100];
        float preco;
        char buf[1024];
        cout << "Entre com o c�digo do produto: ";
        cin >> codigo;

        FILE* arquivo;
        arquivo = fopen("produtos.txt", "r");

        if(arquivo == NULL)
            return "\nN�o foi poss�vel acessar o arquivo de db!\n";

        while(fgets(buf, sizeof(buf), arquivo))
		{ // while que captura a linha com o aux. buf
            if (buf[0] == '\n')
                continue;

            sscanf(buf, "%d %s %f", &codigo_lido, descricao, &preco);
            if(codigo == codigo_lido)
			{
                replace_char(descricao, '_', ' ');
                cout << fixed << "\nC�digo do produto: " << codigo << "\nDescri��o........: " << descricao << "\nPre�o............: R$" << setprecision(2) << preco << "\n\nDeseja continuar? \n\t[0] - Parar \t[1] - Continuar\n:: ";
                //system("cls");
				cin >> i;
                if (i == 0) {
                	system("pause");
                    return "\nConsulta executada!\n";
                }//if
            }//if
        }//while
        fclose(arquivo);
        fflush(stdin);
    } //while
    system("pause");
    return "\nNenhum c�digo foi encontrado!\n";
}//consultar_produtos