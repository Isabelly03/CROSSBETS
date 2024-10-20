#include <iostream>  // Inclui a biblioteca de entrada e saída padrão em C++
#include <cstdlib>   // Inclui funções úteis como rand() e srand() para gerar números aleatórios
#include <ctime>     // Inclui a função time() para inicializar o gerador de números aleatórios com base no tempo atual
#include <windows.h>  // Biblioteca do Windows necessária para alterar a codificação do console

using namespace std;  // Evita ter que digitar std:: toda vez que usamos funções da biblioteca padrão

void roleta();
void jogo_dos_dados();
void roda_da_fortuna();
void limparTela();
void solicitarSaldo();
void apostado();
int saldo, aposta, opcao;
char continuar;

int main() {
    // Configura o console para codificação UTF-8, garantindo a exibição correta de caracteres acentuados
    SetConsoleOutputCP(CP_UTF8);
    cout << "Bem-vindo(a) ao Cassino Virtual!\n";
    solicitarSaldo();  // Solicita o saldo inicial do jogador
    
    // Loop principal do menu do jogo
    while (true) {
        limparTela();  // Limpa a tela para uma interface mais limpa
        cout << "\nEscolha um jogo para jogar:" << endl;
        cout << "1. Roleta" << endl;
        cout << "2. Roda da Fortuna" << endl;
        cout << "3. Jogo dos Dados" << endl;
        cout << "4. Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> opcao;

        // Verifica se a opção escolhida é válida
        if (opcao < 1 or opcao > 4) {
        	limparTela();
            printf("Opção inválida. Tente novamente.\n");
            system("pause");  // Pausa até o usuário apertar uma tecla
    		continue;  // Volta para o início do loop
        }

        // Se o jogador escolher sair, encerra o jogo
        if (opcao == 4) {
        	limparTela();
            printf("Obrigado por jogar! Até a próxima!");
            break;  // Encerra o loop principal e o programa
        }

        limparTela();  // Limpa a tela após escolher o jogo

        // Escolhe o jogo com base na opção selecionada
        switch (opcao) {
            case 1:
                cout << "Você escolheu Roleta!" << endl;
                cout << "Um número entre 0 e 36 será gerado aleatoriamente" << endl;
                cout << "Tente adivinhar qual número foi gerado" << endl;
                roleta();  // Chama a função do jogo Roleta
                break;
            case 2:
                cout << "Você escolheu Roda da Fortuna!" << endl;
                cout << "Os prêmios possíveis são:\n{R$0, R$10, R$20, R$50, -R$10, -R$20, -R$50 e 2x}" << endl;
                cout << "Ao perder, você perde tanto o valor apostado quanto o valor do prêmio e vice-versa" << endl;
                cout << "Aposte o valor que quiser e boa sorte!\n" << endl;
                roda_da_fortuna();  // Chama a função do jogo Roda da Fortuna
                break;
            case 3:
                cout << "Você escolheu Jogo dos Dados!" << endl;
                cout << "Dois dados serão lançados aleatoriamente" << endl;
                cout << "Tente acertar a soma dos dois dados. (2 a 12)" << endl;
                jogo_dos_dados();  // Chama a função do jogo dos Dados
                break;
        }

        // Verifica se o saldo do jogador acabou e solicita novo saldo, se necessário
        if (saldo <= 0) {
            cout << "Saldo esgotado! Precisamos de um novo valor para continuar.\n";
            solicitarSaldo();
        }
    }
    return 0;  // Encerra o programa
}

// Função para limpar a tela
void limparTela() {
    system("CLS");  // Comando para limpar a tela no Windows
}

// Função para solicitar o saldo inicial do jogador
void solicitarSaldo() {
    cout << "Digite seu saldo inicial: ";
    cin >> saldo;
}
void apostado(){
	do {
        cout << "Digite o valor da aposta: ";
        cin >> aposta;

        // Verifica se a aposta é válida em relação ao saldo
        if (aposta > saldo) {
        	limparTela();
            printf("Aposta inválida! Seu saldo atual é: R$%d\n", saldo);
            cout << "Tente novamente.\n";
        }
    } while (aposta > saldo);  // Repete até o jogador digitar uma aposta válida
}	

// Função do jogo Roleta
void roleta() {
    do {
        srand(time(0));  // Inicializa o gerador aleatório com base no tempo
        int numero = rand() % 37;  // Gera um número aleatório entre 0 e 36
        int apostaNumero;
        apostado();
        limparTela();

        cout << "Aposte em um número entre 0 e 36: ";
        cin >> apostaNumero;

        // Verifica se o número apostado está dentro do intervalo permitido
        if (apostaNumero < 0 or apostaNumero > 36) {
            printf("Aposta inválida! Tente novamente: ");
            cin >> apostaNumero;
        }

        limparTela();  // Limpa a tela para exibir o resultado
        printf("O número sorteado foi: %d\n", numero);

        // Verifica se o jogador acertou o número sorteado
        if (apostaNumero == numero) {
            printf("Parabéns! Você venceu!\n");
            saldo += aposta;  // Adiciona o valor da aposta ao saldo
        } else {
            printf("Você perdeu!\n");
            saldo -= aposta;  // Subtrai o valor da aposta do saldo
        }

        printf("Seu saldo atual é: R$%d\n", saldo);

        // Se o saldo acabar, solicita novo saldo
        if (saldo <= 0) {
            cout << "Saldo esgotado! Precisamos de um novo valor para continuar.\n";
            solicitarSaldo();
        }

        cout << "Deseja jogar novamente? (s/n): ";
        cin >> continuar;
        limparTela();
    } 
	while (continuar == 's' or continuar == 'S');
}

// Função do jogo dos Dados
void jogo_dos_dados() {
    do {
        srand(time(0));
        int dado1 = rand() % 7;  // Gera um número entre 1 e 6
        int dado2 = rand() % 7;
        int resultado = dado1 + dado2;
        int apostaDados;
        apostado();

		limparTela();
        cout << "Aposte em um número entre 2 e 12: ";
        cin >> apostaDados;

        if (apostaDados < 2 or apostaDados > 12) {
            printf("Aposta inválida! Tente novamente: ");
            cin >> apostaDados;
        }

        limparTela();
        cout << "Dados lançados! Dado 1: " << dado1 << " + Dado 2: " << dado2 << " = " << resultado << endl;

        if (resultado == apostaDados) {
            printf("Parabéns! Você ganhou!\n");
            saldo += aposta;
        } else {
            printf("Você perdeu!\n");
            saldo -= aposta;
        }
        printf("Seu saldo atual é: R$%d\n", saldo);

        cout << "Deseja jogar novamente? (s/n): ";
        cin >> continuar;
        limparTela();

    } while (continuar == 's' || continuar == 'S');
}

// Função da Roda da Fortuna
void roda_da_fortuna() {
	const int NUM_SECOES = 9; // Total de seções na roda
    int premios[NUM_SECOES] = {0, 10, 20, 50, -10, -20, -50, 2}; // Prêmios correspondentes às seções (ganhos e perdas)
    do {
        srand(time(0));
        apostado();
        limparTela();
        cout << "Girando a roda...\n";

        for (int i = 3; i > 0; --i) {
            cout << i << "...\n";
            Sleep(1000);
        }
        limparTela();
		int resultado = rand() % NUM_SECOES;
    	if (premios[resultado] > 0 && premios[resultado] != 2) {
            int ganho = aposta + premios[resultado]; // Ganho total
            printf("Parabéns! Você ganhou R$%d, seu saldo atual é: R$%d\n", premios[resultado], saldo + ganho);
            saldo += ganho; // Atualiza o saldo com o ganho total
        } 
        if (premios[resultado] < 0) {
            int perda = aposta + (-premios[resultado]); // Perda total
            printf("Perdeu tudo! Você perdeu R$%d e sua aposta, seu saldo atual é: R$%d\n", -premios[resultado], saldo - perda);
            saldo -= perda; // Atualiza o saldo com a perda total
        } 
        if (premios[resultado] == 0) {
            printf("Você não ganhou nada desta vez. Seu saldo permanece: R$%d\n", saldo); // Não perdeu nem ganhou
        }
        if (premios[resultado]==2){
        	printf("Parabéns! Você dobrou o seu valor, seu saldo atual é: R$%d\n", saldo); // dobra o valor da aposta
        	saldo += aposta*2;
		}

        // Checa se o saldo ficou negativo
        if (saldo <= 0) {
            printf("Você não tem mais saldo para jogar. Jogo encerrado.\n");
            solicitarSaldo();
        }
		cout << "Deseja jogar novamente? (s/n): ";
        cin >> continuar;
        limparTela();
    }
	while (continuar == 's' || continuar == 'S');
    cout << "Obrigado por jogar!\n";
}