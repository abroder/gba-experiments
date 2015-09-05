#include <string.h>

#include "graphics.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#define REG_DISPCNT (*(volatile uint16_t *) 0x4000000)

#define DISP_MODE0 0x0000
#define DISP_BG0   0x0100 // (1 << 8)

#define REG_BG0HOFS (*(volatile uint16_t *) 0x4000010)
#define REG_BG0VOFS (*(volatile uint16_t *) 0x4000012)

#define REG_BG0CNT  (*(volatile uint16_t *) 0x4000008)

#define BG_TILES0     0x0000
#define BG_PALLETE16  0x0000
#define BG_MAP31      0x1f00
#define BG_SIZE_32x32 0x0000

#define MEM_PALLETE_BG ((uint16_t *)(0x5000000))

#define MEM_VRAM ((uint16_t *)(0x6000000))
#define MEM_CHARBLOCK(x) ((uint16_t *)(0x6000000 + (x * 0x4000)))
#define MEM_SCREENBLOCK(x) ((uint16_t *)(0x6000000 + (x * 0x800)))

int main() {
  // TODO(aaron): pallete copies single bytes over twice
  memcpy(MEM_PALLETE, pallete, palleteLen);
  memcpy(MEM_CHARBLOCK(0), tiles, tilesLen);
  memcpy(MEM_SCREENBLOCK(31), map, mapLen);

  REG_DISPCNT = DISP_MODE0 | DISP_BG0;
  REG_BG0CNT = BG_TILES0 | BG_PALLETE16 | BG_MAP31 | BG_SIZE_32x32;
  REG_BG0VOFS = 0x60;

  while (1);

  return 0;
}