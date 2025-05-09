#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>

static void hello_release(struct device *dev)
{
	dev_info(dev, "%s\n", __func__);
}

static struct platform_device hello_device = {
	.name = "hello",
	.id = -1,
	.dev = {
		.release = hello_release,
	}
};

static int hello_dev_init(void)
{
	int ret;
	pr_info("Hello, world\n");

	ret = platform_device_register(&hello_device);
	if (ret < 0) {
		pr_err("Fail to register hello_device(%d)\n", ret);
	}

	return ret;
}

static void hello_dev_exit(void)
{
	pr_info("Goodbye, cruel world\n");
	platform_device_unregister(&hello_device);
}

module_init(hello_dev_init);
module_exit(hello_dev_exit);

MODULE_LICENSE("GPL");

