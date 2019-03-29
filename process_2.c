#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
    /* Grote van het shared memory object */
    const int SIZE = 4096;

    /* Naam van shared memory object */
    const char* name = "/shared-mem";

    /* Shared memory object file descriptor */
    int shm_fd;

    /* Pointer die verwijst het shared memory */
    void* ptr;

    /* Shared memory object aanmaken
     * Process_1 heeft het shared memory al aangemaakt dus daarom is de 'O_CREATE' mode niet nodig.
     * Process_2 (dit process) hoeft alleen te lezen van het shared memory ddaarom wordt de 'O_RDONLY'
     * mode meegegeven*/
    shm_fd = shm_open(name, O_RDONLY, 0666);

    /* Shared memory object mappen naar het address space van dit process */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    printf("Shared memory pointer: %p.\n", ptr);

    /* Geschreven strings van Process_1 uitlezen uit het shared memory */
    printf("%s", (char*)ptr);
    printf("\n");

    /* Shared memory unmappen */
    munmap(ptr, SIZE);
    /* Shared memory verwijderen. */
    shm_unlink(name);
    return 0;
} 