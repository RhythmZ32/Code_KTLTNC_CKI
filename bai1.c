#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main() {
    char file_path[256];
    scanf("%255s", file_path);

    int fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        printf("-1\n");
        return 0;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    long long total_bytes = 0;
    long long newline_count = 0;
    long long digit_count = 0;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        total_bytes += bytes_read;

        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                newline_count++;
            }
            if (buffer[i] >= '0' && buffer[i] <= '9') {
                digit_count++;
            }
        }
    }

    if (bytes_read < 0) {
        close(fd);
        printf("-1\n");
        return 0;
    }
    close(fd);

    printf("%lld %lld %lld\n", total_bytes, newline_count, digit_count);
    return 0;
}