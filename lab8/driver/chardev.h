#ifndef CHARDEV_H
#define CHARDEV_H

#define SUCCESS 0
#define BUFFER_LENGTH 256

#define DEVICE_NAME "chardev"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

int init_module(void);
void cleanup_module(void);

static int device_open(struct inode*, struct file*);
static int device_release(struct inode*, struct file*);
static ssize_t device_read(struct file*, char*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char*, size_t, loff_t*);

static int deviceOpen = 0;
static char message[BUFFER_LENGTH];
static char* messagePtr;
static int MAJOR;

enum DIRECTION
{
  FORWARDS,
  BACKWARDS
};

static int dir = 0;

static struct file_operations fops =
{
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release
};

MODULE_LICENSE("GPL");

#endif
