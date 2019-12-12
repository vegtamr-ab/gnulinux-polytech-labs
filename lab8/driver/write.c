#include "chardev.h"

const char* DirStr = "direction";
const char* FrwStr = "forward";
const char* BckStr = "back";

const char* MsgStr = "message";
const char* DelStr = "msg_delete";

static ssize_t device_write(struct file* file, const char __user* buffer, size_t length, loff_t* offset)
{
  int i = 0;
  char command[256];
  copy_from_user(command, buffer, length);
  command[length] = '\0';

  if (strncmp(command, DirStr, strlen(DirStr)) == 0)
  {
    i = strlen(DirStr);

    while ((i < length) && (command[i] == ' '))
    {
      ++i;
    }

    if (strncmp(command + i, FrwStr, strlen(FrwStr)) == 0)
    {
      dir = FORWARDS;
      printk(KERN_INFO "Forwards direction\n");
    }
    else if (strncmp(command + i, BckStr, strlen(BckStr)) == 0)
    {
      dir = BACKWARDS;
      printk(KERN_INFO "Backwards direction\n");
    }
    else
    {
      printk(KERN_INFO "Direction undefined\n");
    }
  }
  else if (strncmp(command, MsgStr, strlen(MsgStr)) == 0)
  {
    i = strlen(MsgStr);

    while ((i < length) && (command[i] == ' '))
    {
      ++i;
    }

    strcpy(message, command + i);
    printk(KERN_INFO "Message has been written\n");
  }
  else if (strncmp(command, DelStr, strlen(DelStr)) == 0)
  {
    message[0] = '\0';
    printk(KERN_INFO "Message has been deleted\n");
  }
  else
  {
    printk(KERN_INFO "Command undefined\n");
  }

  messagePtr = message;

  return length;
}