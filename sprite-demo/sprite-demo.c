#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct {
  uint16_t attr0;
  uint16_t attr1;
  uint16_t attr2;
  uint16_t attr3;
} OAMEntry;

#define REG_DISPCNT (*(volatile uint16_t *) 0x4000000)

#define DISP_MODE0  0x0000
#define DISP_OBJ    0x1000
#define DISP_OBJ_1D 0x0040

#define MEM_PALLETE_SPRITE ((uint16_t *)(0x5000200))

#define MEM_OVRAM ((uint16_t *)(0x6010000))

#define MEM_OAM ((uint16_t *)(0x7000000))

static OAMEntry objectBuffer[128];
static size_t objectBufferLen = sizeof(objectBuffer);

// 0: green (transparent), 1: light brown (flesh), 2: dark brown,
// 3: red
static uint16_t pallete[4] = {
  0x03E0, 0x269D, 0x0DF3, 0x04FA
};
static size_t palleteLen = sizeof(pallete);

static uint16_t tiles[64] = {
  // mario top-left
  0x0000, 0x3330,
  0x0000, 0x3333,
  0x0000, 0x1222,
  0x2000, 0x1121,
  0x2000, 0x1221,
  0x2000, 0x1112,
  0x0000, 0x1110,
  0x0000, 0x2322,
  
  // mario top-right
  0x0333, 0x0000,
  0x3333, 0x0033,
  0x1121, 0x0000,
  0x1121, 0x0011,
  0x1211, 0x0111,
  0x2221, 0x0022,
  0x1111, 0x0001,
  0x0222, 0x0000,

  // mario bottom-left
  0x2000, 0x2322,
  0x2200, 0x3322,
  0x1100, 0x3132,
  0x1100, 0x3331,
  0x1100, 0x3333,
  0x0000, 0x3333,
  0x2000, 0x0222,
  0x2200, 0x0222,

  // mario bottom-right
  0x2232, 0x0022,
  0x2233, 0x0222,
  0x2313, 0x0111,
  0x1333, 0x0111,
  0x3333, 0x0111,
  0x3330, 0x0003,
  0x2200, 0x0022,
  0x2200, 0x0222
};
static size_t tilesLen = sizeof(tiles);

int main() {
  OAMEntry *mar = &objectBuffer[0];
  mar->attr0 = 0b0000000000001010;
  mar->attr1 = 0b0100000000001010;

  memcpy(MEM_PALLETE_SPRITE, pallete, palleteLen);
  memcpy(MEM_OVRAM, tiles, tilesLen);
  memcpy(MEM_OAM, objectBuffer, objectBufferLen);

  REG_DISPCNT = DISP_MODE0 | DISP_OBJ | DISP_OBJ_1D;

  while (1);

  return 0;
}