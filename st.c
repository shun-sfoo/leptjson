#include <fcntl.h>                   /* open() O_RDONLY */
#include <linux/input-event-codes.h> /* EV_KEY, BTN_LEFT, MSC_SERIAL */
#include <linux/input.h>             /* struct input_event */
#include <stdio.h>                   /* printf() FILE popen() fgets() */
#include <stdlib.h>                  /*exit() */
#include <string.h>                  /* strcmp() */
#include <unistd.h>                  /* read() */

#include "caiyun.h"

#define MAXSIZE 1024

char event[18] = "/dev/input/";
char authorization[44] = "x-authorization: token ";

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("must input event and caiyun token");
    return -1;
  }

  strcat(event, argv[1]);
  strcat(authorization, argv[2]);

  // need xlicp in wayland use wl-paste
#if WAYLAND
  const char *cmd = "wl-paste";
#else
  const char *cmd = "xclip -o";
#endif

  // cat /proc/bus/input/devices found mouse event
  int keys_fd;
  struct input_event t;
  keys_fd = open(event, O_RDONLY);

  if (keys_fd <= 0) {
    printf("open %s error!\n", event);
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
          printf("原句: %s\n", sentence);
          fanyi(sentence);
        }
      }
      pclose(fp);
    }
  }
}
