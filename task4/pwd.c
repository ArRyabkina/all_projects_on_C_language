#include <stdio.h>
#include <unistd.h>

int
main(void)
{
    char path[4048];
    if (getcwd(path, sizeof(path)) == NULL) {
        perror("getcwd");
        return 1;
    }
    fprintf(stdout, "%s\n", path);
    return 0;
}
