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

#define REG_VCOUNT *((volatile uint16_t *) 0x4000006)

#define MEM_PALLETE_SPRITE ((uint16_t *)(0x5000200))

#define MEM_OVRAM ((uint16_t *)(0x6010000))

#define MEM_OAM ((uint16_t *)(0x7000000))

#define OAM_SET_X(oam, x) oam->attr1 = (oam->attr1) | (x & 0x00FF);
#define OAM_SET_Y(oam, y) oam->attr0 = (oam->attr0) | (y & 0x00FF);

#define OAM_ATTR0_REG 0x0000
#define OAM_ATTR0_AFF 0x0100
#define OAM_ATTR0_HID 0x0200
#define OAM_ATTR0_AFF_DBL 0x0300

#define OAM_ATTR0_GFX_NOR 0x0000
#define OAM_ATTR0_GFX_ALPH 0x0400
#define OAM_ATTR0_GFX_WIN 0x0800

#define OAM_ATTR0_MOSAIC 0x1000

#define OAM_ATTR0_COLOR_4BPP 0x0000
#define OAM_ATTR0_COLOR_8BPP 0x2000

#define OAM_ATTR0_SHAPE_SQUARE 0x0000
#define OAM_ATTR0_SHAPE_WIDE 0x4000
#define OAM_ATTR0_SHAPE_TALL 0x8000

#define OAM_ATTR1_FLIP_HORI 0x1000
#define OAM_ATTR1_FLIP_VERT 0x2000

#define OAM_ATTR1_SIZE_SQUARE_8x8 0x0000
#define OAM_ATTR1_SIZE_WIDE_16x8 0x0000
#define OAM_ATTR1_SIZE_TALL_16x8 0x0000

#define OAM_ATTR1_SIZE_SQUARE_16x16 0x4000
#define OAM_ATTR1_SIZE_WIDE_32x8 0x4000
#define OAM_ATTR1_SIZE_TALL_8x32 0x4000

#define OAM_ATTR1_SIZE_SQUARE_32x32 0x8000
#define OAM_ATTR1_SIZE_WIDE_32x16 0x8000
#define OAM_ATTR1_SIZE_TALL_16x32 0x8000

#define OAM_ATTR1_SIZE_SQUARE_64x64 0xC000
#define OAM_ATTR1_SIZE_WIDE_64x32 0xC000
#define OAM_ATTR1_SIZE_TALL_32x64 0xC000

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

static uint16_t xPos = 0;
static uint16_t yPos = 0;

int main() {
  OAMEntry *mar = &objectBuffer[0];
  mar->attr0 = OAM_ATTR0_SHAPE_SQUARE;
  mar->attr1 = OAM_ATTR1_SIZE_SQUARE_16x16;

  int i;
  for (i = 1; i < 128; ++i) {
    OAMEntry *mar = &objectBuffer[i];
    mar->attr0 = OAM_ATTR0_HID;
  }

  memcpy(MEM_PALLETE_SPRITE, pallete, palleteLen);
  memcpy(MEM_OVRAM, tiles, tilesLen);
  memcpy(MEM_OAM, objectBuffer, objectBufferLen);

  REG_DISPCNT = DISP_MODE0 | DISP_OBJ | DISP_OBJ_1D;

  while (1) {
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);

    if (xPos >= 100) xPos = 0;
    if (yPos >= 100) yPos = 0;

    OAM_SET_Y (mar, xPos);
    OAM_SET_X (mar, yPos);
    xPos++;
    yPos++;

    memcpy(MEM_OAM, objectBuffer, objectBufferLen);  
  };

  return 0;
}