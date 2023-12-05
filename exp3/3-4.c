#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

const int globalVariable = 1000;

void testFunc() {
    return;
}

unsigned long v2p(unsigned long vAddr) {
    unsigned long data;
    int pagesize = getpagesize();
    int fd = open("/proc/self/pagemap",O_RDONLY);
    unsigned long offset = vAddr / pagesize * sizeof(unsigned long);
    pread(fd,&data,sizeof(unsigned long),offset);
    unsigned long PFN = data & 0x7fffffffffffff;
    unsigned long paddr = PFN * pagesize + vAddr % pagesize;
    return paddr;
}

int main() {
    unsigned long paddr = v2p((unsigned long)&globalVariable);
    unsigned long paddr1 = v2p((unsigned long)&testFunc);
    printf("vaddr:%#p\tpaddr:%#lx\n",&globalVariable,paddr);
    printf("vaddr:%#p\tpaddr:%#lx\n",&testFunc,paddr1);
    getchar();
}
