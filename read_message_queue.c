// compile with
// gcc read_message_queue.c -lrt -o read_message_queue

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define LEN 8192

int main(int argc , char *argv[])
{
  mqd_t fd;
  char buff[LEN];
  int sterr, i, len;
  memset(buff,0,LEN);
  if (argc < 2) {
    printf("\nPlease enter the name of message queue\n");
    exit(0);
  }
  else {
    fd = mq_open(argv[1], O_RDONLY);
    if (fd == -1) {
      sterr = errno;
      printf("\nCouldn't open the message queue. Error : %s\n",strerror(sterr));
      exit(0);
    }
    else {
      for (;;) {
	len = mq_receive(fd, buff, sizeof(buff), NULL);
	if (len == -1) {
	  printf("\nMessage could not be received\n");
	  //mq_close(fd);
	  //exit(0);
	  usleep(100000);
	}   
	else {
	  printf("Received Message: %d bytes,", len);
	  for (i = 0; i < len; i++) {
	    printf(" %02x", buff[i]);
	  }
	  printf("\n");
	}
      }
    }
  }
  exit(0);
}
