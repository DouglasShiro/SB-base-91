//
//  main.c
//  base91
//

#include <stdio.h>
#include <string.h>

typedef enum _bool {
    false = 0,
    true = 1
} Bool;

int procurarTabela91(int);
char tabela[91] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!' , '#' , '$' , '>' , '?' , '@' , '[' , ']' , '^' , '_' , '`' , '{' , '|' , '}' , '~' , '"' , '%' , '&' , '(' , ')' , '*' , '+' , ',' , '.' , '/' , ':' , ';' , '<' , '='};

void codifica91(FILE*);
void decodifica91(FILE*);
int procurarTabela91(int);

void getch(void);

int main(int argc, char * argv[]) {

    int escolha;
    FILE *file;
	char* instrucao;
	char filename[50];

	if ( argc == 1) {
		do {
			printf("Programa de codificacao e decodificacao base91\n");
			printf("Escolha a opcao desejada:\n");
			printf("1.Codificar arquivo texto para arquivo binario base91;\n");
			printf("2.Decodificar arquivo binario para base91;\n");
			printf("3.Sair do programa;\n");
			scanf("%d", &escolha);
		} while (escolha > 3 || escolha < 0);
		if (escolha == 3) {
			printf("Saindo...\n");
			return 0;
		} else if (escolha == 1) {
			while(1) {
				printf("---------------------------------------------------\n");
				printf("Entre com o nome do arquivo a ser codificado\n");
				printf("Escreva exit para nao entrar com novo arquivo\n");
				scanf("%s", filename);
				if (!strcmp(filename, "exit")) {
					printf("Saindo...\n");
					break;
				}
				file = fopen(filename, "r");
				while (getchar() != '\n');
				if (!file) {
					printf("Arquivo nao encontrado!\n");
					printf("Escreva exit para nao entrar com novo arquivo\n");
				} else {
					codifica91(file);
					printf("Arquivo ");
					printf("%s", filename);
					printf(" codificado com sucesso!\n");
				}
			}
		} else if (escolha == 2) {
			while(1) {
				printf("---------------------------------------------------\n");
				printf("Entre com o nome do arquivo a ser codificado\n");
				printf("Escreva exit para nao entrar com novo arquivo\n");
				scanf("%s", filename);
				if (!strcmp(filename, "exit")) {
					printf("Saindo...\n");
					break;
				}
				file = fopen(filename, "r");
				while (getchar() != '\n');
				if (!file) {
					printf("Arquivo nao encontrado!\n");
					printf("Escreva exit para nao entrar com novo arquivo\n");
				} else {
					decodifica91(file);
					printf("Arquivo ");
					printf("%s", filename);
					printf(" codificado com sucesso!\n");
				}
			}
		}
	} else if (argc > 3) {
		instrucao = argv[1];
		strcpy(filename, argv[2]);

		file = fopen(filename, "r");

		if (!file) {
			printf("Erro: problema para encontrar arquivo\n");
		} else {
			if ( !strcmp(instrucao, "codificar")) {
				codifica91(file);
			} else if ( !strcmp(instrucao, "decodificar")) {
				decodifica91(file);
			} else {
				printf("Erro na leitura dos parametros, informe: \n");
				printf("codificar ou decodificar + nome_arquivo.ext\n");
				return 0;
			}
	        fclose(file);
	    }
	} else {
		printf("Erro: numero de parametros para o programa incorreto\n");
	}


    return 0;
}

void codifica91(FILE* file) {
	int c;
	int bufferBase91 = 0;
	int y1 = 0, y2 = 0;
	while ((c = getc(file)) != EOF){
		putchar(c);
		if (bufferBase91 == 0) {
			//estamos preenchendo o y1 de um novo bloco
			y1 = procurarTabela91(c);
			//printf(": %d; ", y1);
			bufferBase91++;
		}
		else {
			//estamos preenchendo o y2 de um novo bloco
			y2 = procurarTabela91(c);
			printf("; y1: %d, y2: %d; ", y1, y2);
			printf("%d\n", (y1 * 91 + y2));
			bufferBase91 = 0;
		}
	}
}

void decodifica91(FILE* file) {
	printf("decodificar\n");
}

int procurarTabela91(int ascii) {
    Bool procurarCaracterEspecial = false;
    if (ascii > 64) {
        if (ascii < 91) {
            //letras maiusculas
            //retornar ascii - 65
            return ascii - 65;
        }
        else if (ascii > 96 && ascii < 123) {
            //letras minusculas
            //retornar ascii - 97 + 26
            return ascii - 71;
        }
        else {
            //procurar por caracter especial
            procurarCaracterEspecial = true;
        }
    }
    else if (ascii > 47 && ascii < 58) {
        //numeros
        //retornar ascii - 48 + 52
        return ascii + 4;
    }
    else {
        //procurar por caracter especial
        procurarCaracterEspecial = true;
    }

    if (procurarCaracterEspecial) {
        for (int i = 62; i < 91; i++) {
            if (tabela[i] == ascii) {
                //encontrado
                return i;
            }
        }
    }

    //nao encontrado
    return -1;
}

void getch (void) {
  while ( getchar() != '\n' );
}
