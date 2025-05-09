#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>

static int ohmy_jack_probe(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s\n", __func__);
	return 0;
}
 
static int ohmy_jack_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s\n", __func__);
	return 0;
}

static const struct platform_device_id id_jack_table[] = {
	{"hello"},
	{},
};

static struct platform_driver ohmy_jack_driver = {
	.probe = ohmy_jack_probe,
	.remove = __exit_p(ohmy_jack_remove),
	.driver = {
		.name = "ohmy_jack",
		.owner = THIS_MODULE,
	},
	.id_table = id_jack_table,
};

static int hello_init(void)
{
	int ret;
	pr_info("Hello, jack\n");

	ret = platform_driver_register(&ohmy_jack_driver);
	if (ret < 0) {
		pr_err("Fail to register ohmy_jack_driver(%d)\n", ret);
	}

	return ret;
}
static void hello_exit(void)
{
	pr_info("Goodbye, jack\n");
	platform_driver_unregister(&ohmy_jack_driver);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

