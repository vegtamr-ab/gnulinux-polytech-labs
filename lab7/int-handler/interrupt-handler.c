#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#define MY_WORK_QUEUE_NAME "WQsched.c"
static struct workqueue_struct *my_workqueue;

static void got_char(void* scancode)
{
	printk(KERN_INFO "Scan Code %x %s.\n",
	       (int)*((char *)scancode) & 0x7F,
	       *((char *)scancode) & 0x80 ? "Released" : "Pressed");
}

irqreturn_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	static struct work_struct task;
	unsigned char status;
	static unsigned char scancode;

	status = inb(0x64);
	scancode = inb(0x60);
	got_char(&scancode);

	INIT_WORK(&task, (work_func_t)got_char);
	queue_work(my_workqueue, &task);

	return IRQ_HANDLED;
}

int init_module()
{
	my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);
	free_irq(1, NULL);

	return request_irq(1, (irq_handler_t)irq_handler, IRQF_SHARED, "test_keyboard_irq_handler", (void *)(irq_handler));
}

void cleanup_module()
{
	free_irq(1, NULL);
}

MODULE_LICENSE("GPL");
