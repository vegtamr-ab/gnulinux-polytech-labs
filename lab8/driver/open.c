#include "chardev.h"

#ifdef DEBUG
  #define DEBUG_INFO(file) printk(KERN_INFO "device_open(%p)\n", file)
#else
  #define DEBUG_INFO
#endif

static int device_open(struct inode* inode, struct file* file)
{
  DEBUG_INFO(file);

  if (deviceOpen)
  {
    return -EBUSY;
  }

  ++deviceOpen;

  messagePtr = message;
  try_module_get(THIS_MODULE);

  return SUCCESS;  
}
