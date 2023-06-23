#include <cstdio>

void RemoveDups(char* str) {
    if(str == nullptr || *str =='\0') {
        return;
    }

    size_t dupIndex = 0;
    for(size_t i = 1; str[i] != '\0'; ++i) {
        char cur = str[i];
        if(str[dupIndex] != cur) {
            str[++dupIndex] = cur;
        }
    }
    str[++dupIndex] = '\0';
}

int main()
{
    char data[] = "AAA BBB CCC";
    RemoveDups(data);
    printf("%s\n", data);
}
