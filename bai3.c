#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    char path[512];
    scanf("%511s", path);

    struct stat st;

    if (stat(path, &st) != 0) {
        printf("-1\n");
        return 0;
    }

    const char *type_str;
    if (S_ISREG(st.st_mode)) {
        type_str = "REG";
    } else if (S_ISDIR(st.st_mode)) {
        type_str = "DIR";
    } else {
        type_str = "OTHER";
    }

    // Lấy quyền truy cập 9 bit cuối ở dạng bát phân
    int permissions = st.st_mode & 0777;

    // In kết quả theo đúng định dạng: <LOẠI> <KÍCH_THƯỚC_BYTE> <QUYỀN_3_CHỮ_SỐ_OCTAL>
    printf("%s %lld %03o\n", type_str, (long long)st.st_size, permissions);

    return 0;
}
