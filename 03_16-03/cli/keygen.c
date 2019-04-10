#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define max_login_len 32

uint32_t compute_login_hash(char *login) {
    uint32_t res = 0xFFFFFFFF;

    while (*login) {
        res ^= *login;

        for (int i = 7; i >= 0; i--) {
            res =  ((0 - (res & 1)) & 0xEDB88320) ^ (res >> 1);
        }

        login++;
    }


    return (~res) & 0xFF;
}

uint32_t compute_pwd_hash(char *pwd) {
    uint32_t res = 0;
    
    while (*pwd) {
        res += *pwd ^ 0x99;

        pwd++;
    }

    return res & 0xFF;
}

void print_nums(char *str) {
    while (*str) {
        printf("%x ", *str);
        str++;
    };

    printf("%x ", *str);

    puts("");
}

int main() {
    char login[max_login_len] = "";


    printf("login: ");
    if (fgets(login, max_login_len, stdin) == NULL) {
        printf("\nempty login");
        exit(1);
    }

    if (login[strlen(login) - 1] == '\n') {
        login[strlen(login) - 1] = '\0';
    } else {
        puts("");
    }


    uint32_t login_hash = compute_login_hash(login);

    //printf("login hash: %x\n", login_hash);

    for (uint32_t pwd_num = 0; pwd_num < UINT32_MAX; pwd_num++) {
        char pwd[11] = "";

        sprintf(pwd, "%u", pwd_num);

        uint32_t pwd_hash = compute_pwd_hash(pwd);

        if (login_hash == pwd_hash) {
            printf("password: %s\n", pwd);
            exit(0);
        }
    }

    printf("can't find password for this login.\n");
}
