#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    /* Grootte van het shared memory object */
    const int SIZE = 4096;

    /* Naam van shared memory object */
    const char* name = "/shared-mem";

    /* Strings die naar het shared memory object geschreven worden */
    const char* message_0 = "Hello";
    const char* message_1 = " World!";

    /* Shared memory object file descriptor */
    int shm_fd;

    /* Pointer die verwijst het shared memory */
    void* ptr;

    /* Shared memory object creëren.
     * Process_1 (dit proces) creëert en het shared memory object, daarom
     * moet de 'O_CREATE' mode meegeven worden. Process_1 gaat ook schrijven
     * naar het shared memory, daaro moet de 'O_RDWR' mode meegegeven worden.*/
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* Grootte instellen voor het shared memory object */
    ftruncate(shm_fd, SIZE);

    /* Shared memory object mappen naar het address space van dit proces */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    /* Strings naar het shared memory schrijven */
    sprintf(ptr, "%s", message_0);

    ptr += strlen(message_0);
    sprintf(ptr, "%s", message_1);
    ptr += strlen(message_1);

    /* Shared memory unmappen */
    munmap(ptr, SIZE);

    return 0;
}