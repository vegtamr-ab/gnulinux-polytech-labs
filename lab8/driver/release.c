#include "chardev.h"

#ifdef DEBUG
  #define DEBUG_INFO(inode, file) printk(KERN_INFO "device_release(%p, %p)\n", inode, file)
#else
  #define DEBUG_INFO
#endif

static int device_release(struct inode* inode, struct file* file)
{
  DEBUG_INFO(inode, file);

  --deviceOpen;

  module_put(THIS_MODULE);

  return SUCCESS;  
}
