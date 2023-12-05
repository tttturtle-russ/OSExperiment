#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

const int globalVariable = 1000;

void testFunc() {
    return;
}

unsigned long v2p(unsigned long vAddr,unsigned long *PFN) {
    unsigned long data;
    int pagesize = getpagesize();
    int fd = open("/proc/self/pagemap",O_RDONLY);
    unsigned long offset = vAddr / pagesize * sizeof(unsigned long);
    pread(fd,&data,sizeof(unsigned long),offset);
    *PFN = data & 0x7fffffffffffff;
    unsigned long paddr = *PFN * pagesize + vAddr % pagesize;
    return paddr;
}

int main() {
    unsigned long PFN;
    unsigned long paddr = v2p((unsigned long)&globalVariable,&PFN);
    printf("variable:a\tPFN:%#lx\tvaddr:%#p\tpaddr:%#lx\n",PFN,&globalVariable,paddr);
    paddr = v2p((unsigned long)&testFunc,&PFN);
    printf("func:testFunc\tPFN:%#lx\tvaddr:%#p\tpaddr:%#lx\n",PFN,&testFunc,paddr);
}
