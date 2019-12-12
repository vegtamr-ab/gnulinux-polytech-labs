#include "chardev.h"

int init_module()
{
  MAJOR = register_chrdev(0, DEVICE_NAME, &fops);

  if (MAJOR < 0) 
  {
    printk(KERN_ALERT "ERROR: %s failed with %d\n", "Registering the character device ", MAJOR);

    return MAJOR;
  }

  printk(KERN_INFO "SUCCESS: %s%d\n", "Registered the major device ", MAJOR);
  printk(KERN_INFO "Please, create a device file to interact with the driver. Use:\n");
  printk(KERN_INFO "mknod %s c %d 0\n", DEVICE_NAME, MAJOR);

  return SUCCESS;
}

void cleanup_module()
{
  unregister_chrdev(MAJOR, DEVICE_NAME);
  printk(KERN_INFO "Unregistered the device %d\n", MAJOR);
}
