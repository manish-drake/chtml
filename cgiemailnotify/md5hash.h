#ifndef MD5HASH_H
#define MD5HASH_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/md5.h>
class md5hash
{
    unsigned char result[MD5_DIGEST_LENGTH];

    // Print the MD5 sum as hex-digits.
    std::string print_md5_sum(unsigned char *md)
    {
        char hash[(MD5_DIGEST_LENGTH*2)+1] = {0};
        int i;
        for (i = 0; i < MD5_DIGEST_LENGTH; i++)
        {
            char hex[3] = {0};
            sprintf(hex, "%02x", md[i]);
            hash[i*2] = hex[0];
            hash[(i*2)+1] = hex[1];
        }
        return std::string(hash);
    }

    // Get the size of the file by its file descriptor
    unsigned long get_size_by_fd(int fd)
    {
        struct stat statbuf;
        if (fstat(fd, &statbuf) < 0)
            exit(-1);
        return statbuf.st_size;
    }

  public:
    std::string printHash(const char *fileName)
    {
        int file_descript;
        unsigned long file_size;
        char *file_buffer;

        if (!fileName)
        {
            printf("Must specify the file\n");
            exit(-1);
        }
        // printf("using file:\t%s\n", fileName);

        file_descript = open(fileName, O_RDONLY);
        if (file_descript < 0)
            exit(-1);

        file_size = get_size_by_fd(file_descript);
        // printf("file size:\t%lu\n", file_size);

        file_buffer = (char*)mmap(0, file_size, PROT_READ, MAP_SHARED, file_descript, 0);
        MD5((unsigned char *)file_buffer, file_size, result);
        munmap(file_buffer, file_size);

        return print_md5_sum(result);
    }
};

#endif //MD5HASH_H