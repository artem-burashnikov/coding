#include <stdio.h>
#include <ctype.h>

/* Различные состояние, в которых может находиться каретка. */
#define BEGINNING -1
#define OUT 0

/* Конец ввода грамматики */
#define EOFGRAM 1000

/* ASCII-код одинарной кавычки */
#define SINGLE_QUOTE '\047'

/* Счетчики нетерминалов, терминалов и семантик. */
static int non_terminal = 10;
static int terminal = 50;
static int semantic = 100;

int main() {
    int state, c;

    state = BEGINNING;

    while ((c = getchar()) != EOF) {
match:
        switch (c) {
            case '\n': printf("\n");
                break;
            case ' ': printf(" ");
                break;
            case ':': printf("1");
                break;  
            case '(': printf("2");
                break;
            case ')': printf("3");
                break;
            case '.': printf("4");
                state = BEGINNING;
                break;
            case '*': printf("5");
                break;
            case ';': printf("6");
                break;
            case ',': printf("7");
                break;
            case '#': printf("8");
                break;
            case '[': printf("9");
                break;
            case ']': printf("10");
                break;
            default:
                /* Пропускаем пробелы в начале грамматической строки. */
                if (state == BEGINNING && isspace(c)) {
                    printf(" ");
                    continue;
                }
                
                /* Потенциально встретили конец программы. */
                if (state == BEGINNING && c == 'E') {
                    c = getchar();
                    /* 
                    * Если за 'E' сразу идёт 'o', то согласно грамматике
                    * предполагаем, что это конец ввода.
                    */
                    if (c == 'o') {
                        printf("%d\n", EOFGRAM);
                        goto end_prog;
                    } else {
                        ungetc(c, stdin);
                        goto non_terminal_state;
                    }
                }

                /* 
                * Если встретили нетерминал до символа ':',
                * его надо считать.
                */
                if (state == BEGINNING && isalnum(c)) {
non_terminal_state:
                    non_terminal++;
                    while ((c = getchar()) != EOF && isalnum(c))
                        continue;
                    state = OUT;
                    printf("%d", non_terminal);
                    if (c == EOF) 
			goto end_prog;
                    goto match;
                }

                /* 
                * Если встретили нетерминал, начинающийся с прописной буквы,
                * то нужно считать все прописные буквы.
                */
                if (state == OUT && c >= 'A' && c <= 'Z') {
                    non_terminal++;
                    while ((c = getchar()) != EOF && isalnum(c))
                        continue;
                    printf("%d", non_terminal);
                    if (c == EOF) 
			goto end_prog;
                    goto match;
                }

                /* 
                * Если встретили терминал, начинающийся со строчной буквы,
                * то нужно считать все строчные буквы.
                */
                if (state == OUT && c >= 'a' && c <= 'z') {
                    terminal++;
                    while ((c = getchar()) != EOF && isalnum(c))
                        continue;
                    printf("%d", terminal);
                    if (c == EOF) 
			goto end_prog;
                    goto match;
                }

                /* 
                * Если встретили терминал в одинарных кавычках,
                * нужно считать все символы между кавычками.
                */
                if (state == OUT && c == SINGLE_QUOTE) {
                    terminal++;
                    while ((c = getchar()) != EOF && c != SINGLE_QUOTE)
                        continue;
                    printf("%d", terminal);
                    if (c == EOF) 
			goto end_prog;
                    continue;
                }

                /*
                * Если встретили символ '$',
                * то нужно считать все alpanum сиволы.
                */
                if (state == OUT && c == '$') {
                    semantic++;
                    while ((c = getchar()) != EOF && isalnum(c))
                        continue;
                    printf("%d", semantic);
                    if (c == EOF) 
			goto end_prog;
                    goto match;
                }
        }
    }
end_prog:
    return 0;
}
