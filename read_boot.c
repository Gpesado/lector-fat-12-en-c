#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char first_byte;
    unsigned char start_chs[3];
    unsigned char partition_type;
    unsigned char end_chs[3];
    char start_sector[4];
    char length_sectors[4];
} __attribute((packed)) PartitionTable;

typedef struct {
    unsigned char jmp[3];
    char oem[8];
    unsigned short sector_size; // 2 bytes
    unsigned char sector_cluster;
    unsigned short reserved_sectors;
    unsigned char number_of_fats;
    unsigned short root_dir_entries;
    unsigned short sector_volumen;
    unsigned char descriptor;
    unsigned short fat_size_sectors;
    unsigned short sector_track;
    unsigned short headers;
    unsigned int sector_hidden;
    unsigned int sector_partition;
    unsigned char physical_device;
    unsigned char current_header;
    unsigned char firm;
    unsigned int volume_id;
    char volume_label[11];
    char fs_type[8]; // Type in ascii
    char boot_code[448];
    unsigned short boot_sector_signature;
} __attribute((packed)) Fat12BootSector;

int main() {
    FILE * in = fopen("test.img", "rb");
    int i;
    PartitionTable pt[4];
    Fat12BootSector bs;
    
    fseek(in, 0x1BE, SEEK_SET); // Ir al inicio de la tabla de particiones
    fread(pt, sizeof(PartitionTable), 4, in); // leo entradas 
    
    for(i=0; i<4; i++) {        
        printf("Partiion type: %d\n", pt[i].partition_type);
        if(pt[i].partition_type == 1) {
            printf("Encontrado FAT12 %d\n", i);
            break;
        }
    }
    
    if(i == 4) {
        printf("No FAT12 filesystem found, exiting...\n");
        return -1;
    }
    
    fseek(in, 0, SEEK_SET);
    fread(&bs, sizeof(Fat12BootSector), 1, in);
    
    printf("  Jump code: %02X:%02X:%02X\n", bs.jmp[0], bs.jmp[1], bs.jmp[2]);
    printf("  OEM code: [%.8s]\n", bs.oem);
    printf("  Sector size: %d\n", bs.sector_size);
    printf("  Sector cluster: %hhu\n", bs.sector_cluster);
    printf("  Sector reserverd: %d\n", bs.reserved_sectors);
    printf("  Number of FAT's: %hhu\n", bs.number_of_fats);
    printf("  Root dir entries: %d\n", bs.root_dir_entries);
    printf("  Sector volumen: %d\n", bs.sector_volumen);
    printf("  Descriptor: %hhu\n", bs.descriptor);
    printf("  Sector fat: %d\n", bs.fat_size_sectors);
    printf("  Sector track: %d\n", bs.sector_track);
    printf("  Headers: %d\n", bs.headers);
    printf("  Sector hidden: %u\n", bs.sector_hidden);
    printf("  Sector partition: %u\n", bs.sector_partition);
    printf("  Physical device: %hhu\n", bs.physical_device);
    printf("  Current header: %hhu\n", bs.current_header);
    printf("  Firm: %hhu\n", bs.firm);
    printf("  Volume ID: %u\n", (unsigned int)bs.volume_id);
    printf("  Volume label: [%.11s]\n", bs.volume_label);
    printf("  Filesystem type: [%.8s]\n", bs.fs_type);
    printf("  Boot sector signature: 0x%04X\n", bs.boot_sector_signature);
    
    fclose(in);
    return 0;
}
