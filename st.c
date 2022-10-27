#include <fcntl.h>                   /* open() O_RDONLY */
#include <linux/input-event-codes.h> /* EV_KEY, BTN_LEFT, MSC_SERIAL */
#include <linux/input.h>             /* struct input_event */
#include <stdio.h>                   /* printf() FILE popen() fgets() */
#include <stdlib.h>                  /*exit() */
#include <string.h>                  /* strcmp() */
#include <unistd.h>                  /* read() */

#define MAXSIZE 1024

int main(void) {
  // need xlicp in wayland use wl-paste
  const char *cmd = "xclip -o";

  // cat /proc/bus/input/devices found mouse event
  int keys_fd;
  struct input_event t;
  keys_fd = open("/dev/input/event4", O_RDONLY);

  if (keys_fd <= 0) {
    printf("open /dev/input/event4 error!\n");
    return -1;
  }

  FILE *fp;
  char sentence[MAXSIZE];
  char preview[MAXSIZE];

  // store preivew sentence
  if ((fp = popen(cmd, "r")) == NULL) {
    perror("popen");
    exit(1);
  }

  fgets(preview, MAXSIZE, fp);
  pclose(fp);

  while (1) {
    read(keys_fd, &t, sizeof(t));
    // press key and mouse left and release
    if (t.type == EV_KEY && t.code == BTN_LEFT && t.value == MSC_SERIAL) {
      if ((fp = popen(cmd, "r")) == NULL) {
        perror("popen");
        exit(1);
      }

      if (fgets(sentence, MAXSIZE, fp) != NULL) {
        if (strcmp(sentence, preview) != 0) {
          strcpy(preview, sentence);
          printf("sentence : %s\n", sentence);
        }
      }
      pclose(fp);
    }
  }
}
