#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char first_byte;
    unsigned char start_chs[3];
    unsigned char partition_type;
    unsigned char end_chs[3];
    char start_sector[4];
    unsigned int length_sectors;
} __attribute((packed)) PartitionTable;

int main() {
    FILE * in = fopen("test.img", "rb");
    PartitionTable pt[4];

    int i;
    
    fseek(in, 0x1BE, SEEK_SET); // Voy al inicio... 
    fread(pt, sizeof(PartitionTable), 4, in); // leo entradas 
    
    for(i=0; i<4; i++) { // Leo las entradas
        printf("Partition entry %d: First byte %02X\n", i, pt[i].first_byte);
        printf("  Partition start in CHS: %02X:%02X:%02X\n", pt[i].start_chs[2], pt[i].start_chs[1], pt[i].start_chs[0]);
        printf("  Partition type 0x%02X\n", pt[i].partition_type);
        printf("  Partition end in CHS: %02X:%02X:%02X\n", pt[i].end_chs[0], pt[i].end_chs[1], pt[i].end_chs[2]);

        printf("  Relative LBA address 0x%08X, %u sectors long\n", pt[i].start_sector[0], pt[i].length_sectors);
    }
    
    fclose(in);
    return 0;
}
