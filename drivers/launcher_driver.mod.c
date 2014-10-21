#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xcf380a00, "module_layout" },
	{ 0x81534dff, "noop_llseek" },
	{ 0x22ef54e3, "usb_deregister" },
	{ 0x1a967ad0, "usb_register_driver" },
	{ 0x86c8ad2e, "malloc_sizes" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x8a12c364, "usb_register_dev" },
	{ 0x7cb2fd60, "usb_get_dev" },
	{ 0x275ef902, "__init_waitqueue_head" },
	{ 0xde8fc4e3, "__mutex_init" },
	{ 0x9bf67b84, "kmem_cache_alloc" },
	{ 0xedd9df33, "usb_autopm_put_interface" },
	{ 0xd5ec350b, "_dev_info" },
	{ 0x452162a0, "usb_deregister_dev" },
	{ 0x24aed0e2, "dev_set_drvdata" },
	{ 0x37a0cba, "kfree" },
	{ 0x9c18a634, "usb_put_dev" },
	{ 0xd4669fad, "complete" },
	{ 0x98082893, "__copy_to_user" },
	{ 0x1fab5905, "wait_for_completion" },
	{ 0xfd5683b9, "wait_for_completion_interruptible" },
	{ 0xe9c986f9, "mutex_lock_interruptible" },
	{ 0x5fc56a46, "_raw_spin_unlock" },
	{ 0x9c0bd51f, "_raw_spin_lock" },
	{ 0x56e7530, "usb_free_coherent" },
	{ 0x4be7fb63, "up" },
	{ 0xfe94c791, "usb_free_urb" },
	{ 0x191ddced, "usb_unanchor_urb" },
	{ 0x75161842, "usb_anchor_urb" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x17a142df, "__copy_from_user" },
	{ 0xc393a7c2, "usb_alloc_coherent" },
	{ 0x1246e504, "usb_alloc_urb" },
	{ 0x976e700f, "down_trylock" },
	{ 0x6915eb38, "down_interruptible" },
	{ 0xf8de72f3, "dev_err" },
	{ 0x704615cc, "usb_submit_urb" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x47954357, "usb_autopm_get_interface" },
	{ 0x27e1a049, "printk" },
	{ 0xa3dd2b5a, "usb_find_interface" },
	{ 0x1a1431fd, "_raw_spin_unlock_irq" },
	{ 0x3507a132, "_raw_spin_lock_irq" },
	{ 0xf3c48537, "mutex_lock" },
	{ 0xd407c4f4, "usb_kill_urb" },
	{ 0x78cf4589, "usb_kill_anchored_urbs" },
	{ 0x7c9ad2eb, "usb_wait_anchor_empty_timeout" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xed3e8562, "mutex_unlock" },
	{ 0x2f9dac41, "dev_get_drvdata" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v2123p1010d*dc*dsc*dp*ic*isc*ip*in*");
