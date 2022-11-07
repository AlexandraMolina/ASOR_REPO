#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
/*El setuid se utiliza dar privilegios elevados en determinados archivos
para usuarios que no lo poseen, como por ejemplo en el archivo /etc/bin/passwd
para que todos puedan cambiar la contraseña pero que no puedan leer ni escribir 
las otras. Por lo tanto, cuando el uid es distinto del euid tiene el bit setuid 
activado*/
int main(){
    printf("UID Real: %d\n", getuid());
    printf("UID Efectivo: %d\n",geteuid());

    return 0;


}