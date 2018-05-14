//
//  main.c
//  base91
//

#include <stdio.h>
#include <string.h>
#include "ref.h"

typedef enum _bool {
    false = 0,
    true = 1
} Bool;

int procurarTabela91(int);
char tabela[91] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!' , '#' , '$' , '>' , '?' , '@' , '[' , ']' , '^' , '_' , '`' , '{' , '|' , '}' , '~' , '"' , '%' , '&' , '(' , ')' , '*' , '+' , ',' , '.' , '/' , ':' , ';' , '<' , '='};

int main(int argc, char * argv[]) {

    int c, escolha;
    FILE *file;
	char* instrucao = argv[1];
	char* filename = argv[2];

	if ( argc == 1) {
		do {
			printf("Programa de codificacao e decodificacao base91\n");
			printf("Escolha a opcao desejada:\n");
			printf("1.Codificar arquivo texto para arquivo binario base91;\n");
			printf("2.Decodificar arquivo binario para base91;\n");
			printf("3.Sair do programa;\n");
			scanf("%d", &escolha);
		} while (escolha != 3);
		if (escolha == 1) {

		} else if (escolha == 2) {

		} else if (escolha == 3) {

		}

	}

    if (argc != 3) {
		printf("Erro: numero de parametros para o programa incorreto\n");
	} else {
		file = fopen(filename, "r");
		if (!file) {
			printf("Erro: problema para encontrar arquivo\n");
		} else {

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
	        fclose(file);
	    }
	}


    return 0;
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
