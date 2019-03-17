#ifndef READ_ALL_H_
#define READ_ALL_H_

#include <unistd.h>

ssize_t read_all(int fd, void * const buf, size_t n);
#endif
