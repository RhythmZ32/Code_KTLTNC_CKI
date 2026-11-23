#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    char src_path[256];
    char dst_path[256];
    long long offset, max_bytes;

    scanf("%255s %255s %lld %lld", src_path, dst_path, &offset, &max_bytes);

    // Nếu offset < 0 hoặc max_bytes < 0 thì báo lỗi (-1)
    if (offset < 0 || max_bytes < 0) {
        printf("-1\n");
        return 0;
    }

    int fd_src = open(src_path, O_RDONLY);
    if (fd_src < 0) {
        printf("-1\n");
        return 0;
    }

    // Kiểm tra kích thước tệp nguồn
    struct stat st;
    if (fstat(fd_src, &st) < 0) {
        close(fd_src);
        printf("-1\n");
        return 0;
    }

    // Nếu offset >= kích thước tệp hoặc max_bytes == 0:
    // Vẫn tạo/đè tệp đích rỗng (0 byte) và in 0
    if (offset >= st.st_size || max_bytes == 0) {
        int fd_dst = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_dst < 0) {
            close(fd_src);
            printf("-1\n");
            return 0;
        }
        close(fd_dst);
        close(fd_src);
        printf("0\n");
        return 0;
    }

    // Mở tệp đích với cờ O_WRONLY | O_CREAT | O_TRUNC và quyền 0644
    int fd_dst = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dst < 0) {
        close(fd_src);
        printf("-1\n");
        return 0;
    }

    // Định vị con trỏ tệp nguồn đến vị trí offset bằng lseek
    if (lseek(fd_src, (off_t)offset, SEEK_SET) == (off_t)-1) {
        close(fd_src);
        close(fd_dst);
        printf("-1\n");
        return 0;
    }

    // Tiến hành sao chép dữ liệu (tối đa max_bytes byte, xử lý short writes)
    char buffer[4096];
    long long total_copied = 0;
    int error = 0;

    while (total_copied < max_bytes) {
        long long to_read = max_bytes - total_copied;
        if (to_read > (long long)sizeof(buffer)) {
            to_read = sizeof(buffer);
        }

        ssize_t bytes_read = read(fd_src, buffer, (size_t)to_read);
        if (bytes_read < 0) {
            error = 1;
            break;
        }
        if (bytes_read == 0) {
            // Đã đọc tới cuối tệp nguồn (EOF)
            break;
        }

        // Vòng lặp đảm bảo ghi đủ số byte vừa đọc (short writes)
        ssize_t bytes_written = 0;
        while (bytes_written < bytes_read) {
            ssize_t res = write(fd_dst, buffer + bytes_written, bytes_read - bytes_written);
            if (res <= 0) {
                error = 1;
                break;
            }
            bytes_written += res;
        }

        if (error)
            break;
        total_copied += bytes_read;
    }

    // Đóng tệp và in tổng số byte đã sao chép (hoặc -1 nếu gặp lỗi đọc/ghi)
    close(fd_src);
    close(fd_dst);

    if (error) {
        printf("-1\n");
    } else {
        printf("%lld\n", total_copied);
    }

    return 0;
}
