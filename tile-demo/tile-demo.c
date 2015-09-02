#include <string.h>

typedef unsigned short uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

#define REG_DISPCNT (*(volatile uint16_t *) 0x4000000)

#define DISP_MODE0 0x0000
#define DISP_BG0   0x0100 // (1 << 8)

#define REG_BG0CNT  (*(volatile uint16_t *) 0x4000008)

#define BG_TILES0     0x0000
#define BG_PALLETE16  0x0000
#define BG_MAP31      0x1f00
#define BG_SIZE_32x32 0x0000

#define MEM_PALLETE ((uint16_t *) 0x5000000)

#define MEM_VRAM ((uint16_t *) 0x6000000)
#define MEM_CHARBLOCK(x) (uint16_t *)(0x6000000 + (x * 0x4000))
#define MEM_SCREENBLOCK(x) (uint16_t *)(0x6000000 + (x * 0x800))

static uint16_t pallete[2] = {
  0x0000, 0x7E4B
};
static size_t palleteLen = sizeof(pallete);

static uint16_t tiles[1] = {
  0x0101
};
static size_t tilesLen = sizeof(tiles);

static uint16_t map[2] = {
  0x1011, 0x0100
};
static size_t mapLen = sizeof(map);

int main() {
  memcpy(MEM_PALLETE, pallete, palleteLen);
  memcpy(MEM_CHARBLOCK(0), tiles, tilesLen);
  memcpy(MEM_SCREENBLOCK(31), map, mapLen);

  REG_DISPCNT = DISP_MODE0 | DISP_BG0;
  REG_BG0CNT = BG_TILES0 | BG_PALLETE16 | BG_MAP31 | BG_SIZE_32x32;

  while (1);

  return 0;
}