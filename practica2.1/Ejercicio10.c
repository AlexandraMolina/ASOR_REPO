#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(){
    printf("UID Real: %d\n", getuid());
    printf("UID Efectivo: %d\n",geteuid());

    struct passwd *pass = getpwuid(getuid());
    printf("Username: %s\n", pass->pw_name);
    printf("Home: %s\n", pass->pw_dir);
    printf("Descripción: %s\n", pass->pw_gecos);

    return 1;

}