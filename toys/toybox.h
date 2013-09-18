typedef struct {
  char toy1[30];
  char toy2[30];
  char toy3[30];
} toybox;

// shared memory key
#define TOYBOX_KEY 0x666
#define BOX_SIZE sizeof(toybox)
