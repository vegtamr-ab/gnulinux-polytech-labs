#include "chardev.h"

#ifdef DEBUG
  #define DEBUG_INFO(file, buffer, length) printk(KERN_INFO "device_read(%p, %p, %d)\n", inode, file)
#else
  #define DEBUG_INFO
#endif

static ssize_t device_read(struct file* file, char __user* buffer, size_t length, loff_t* offset)
{
  int bytes_read = 0;

  if (*messagePtr == 0)
  {
    return 0;
  }

  if (dir == FORWARDS)
  {
    while (length && *messagePtr)
    {
      put_user(*(messagePtr++), buffer++);
      --length;
      ++bytes_read;
    }
  }
  else
  {
    char* tmpPtr = messagePtr - 1;
    while (*messagePtr)
    {
      ++messagePtr;
    }
    --messagePtr;

    while (length && (messagePtr != tmpPtr))
    {
      put_user(*(messagePtr--), buffer++);
      --length;
      ++bytes_read;
    }

    *messagePtr = '\0';
  }

  printk(KERN_INFO, "Read %d bytes, %lu left\n", bytes_read, length);

  return bytes_read;
}
