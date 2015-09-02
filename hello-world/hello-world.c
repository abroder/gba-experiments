int main() {
  volatile unsigned char *ioram = (unsigned char *)0x04000000;
  ioram[0] = 0x03; // video mode 3 - bitmap (240x360, 16bpp, no page flipping)
  ioram[1] = 0x04; // background 2

  volatile unsigned short *vram = (unsigned short *)0x06000000;
  vram[80*240 + 115] = 0x001F; // (115, 80), 000000000011111
  vram[80*240 + 120] = 0x03E0; // (120, 80), 000001111100000
  vram[80*240 + 125] = 0x7C00; // (125, 80), 111110000000000

  while (1);
  
  return 0; 
}
