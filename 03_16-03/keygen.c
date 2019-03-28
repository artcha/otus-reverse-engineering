#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define login_len 31

bool prepare_login(char *login) {
    bool successful = true;
    
    while (*login) {
        if (*login == '\n') {
            *login = '\0';
            break;
        }

        if (*login >= 'a' && *login <= 'z') {
            (*login) -= 0x20; //conversion to uppercase
        } if (*login < 'A' || *login > 'Z') {
            printf("invalid craracter \"%c\"\n", *login);
            successful = false;
        }

        login++;
    }

    return successful;
}

int32_t compute_login_hash(char *login) {
    int32_t result = 0;

    while (*login) {
        result += *login;
        login++;
    }
    
    return result ^ 0x5678;
}

int32_t compute_passw(int32_t login_hash) {
    return login_hash ^ 0x1234;
}

int main() {
    char login[login_len] = "";

    printf("login: ");
    if (fgets(login, login_len, stdin) == NULL) {
        printf("\nempty login");
        exit(1);
    }

    puts("");

    bool success = prepare_login(login);
    if (!success) {
        printf("input contains invalid characters");
        exit(1);
    };

    if (strlen(login) == 0) {
        printf("login should contain at least 1 character\n");
        exit(1);
    }

    int32_t login_hash = compute_login_hash(login);
    //printf("login hash: %d\n", login_hash);
    printf("password: %d\n", compute_passw(login_hash));
}
