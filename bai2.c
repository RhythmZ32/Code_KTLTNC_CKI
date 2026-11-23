#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    char src_path[256];
    char dst_path[256];
    scanf("%255s %255s", src_path, dst_path);

    int fd_in = open(src_path, O_RDONLY);
    int fd_out = open(dst_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_in < 0) {
        printf("-1\n");
        return 0;
    }
    if (fd_out < 0) {
        close(fd_in);
        printf("-1\n");
        return 0;
    }

    char buffer[4096];
    ssize_t nbytes;
    int error = 0;

    while ((nbytes = read(fd_in, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = 0;
        while (bytes_written < nbytes) {
            ssize_t res = write(fd_out, buffer + bytes_written, nbytes - bytes_written);
            if (res <= 0) {
                error = 1;
                break;
            }
            bytes_written += res;
        }
        if (error)
            break;
    }
    if (nbytes < 0) {
        error = 1;
    }
    if (error) {
        close(fd_in);
        close(fd_out);
        printf("-1\n");
        return 0;
    }

    struct stat st;
    if (fstat(fd_out, &st) < 0) {
        printf("-1\n");
    } else {
        printf("%lld\n", (long long)st.st_size);
    }

    close(fd_in);
    close(fd_out);
    return 0;
}
