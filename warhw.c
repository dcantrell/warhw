/*
 * War Hardware (WARHW) kernel module
 * Copyright (C) 2016  David Cantrell <dcantrell@redhat.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_AUTHOR("David Cantrell <dcantrell@redhat.com>");
MODULE_DESCRIPTION("War Hardware support");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");
MODULE_INFO(warhw, "War Hardware");

static int warhw_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "WARHW\n23-Oct-2017 through 27-Oct-2017\n");
    return 0;
}

static int warhw_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, warhw_proc_show, NULL);
}

static const struct file_operations warhw_proc_fops = {
    .owner   = THIS_MODULE,
    .open    = warhw_proc_open,
    .read    = seq_read,
    .llseek  = seq_lseek,
    .release = single_release,
};

static int __init warhw_init(void)
{
    proc_create("warhw", 0, NULL, &warhw_proc_fops);
    printk(KERN_INFO "War Hardware activated\n");
    return 0;
}

static void __exit warhw_exit(void)
{
    remove_proc_entry("warhw", NULL);
    printk(KERN_INFO "War Hardware deactivated\n");
}

module_init(warhw_init);
module_exit(warhw_exit);
