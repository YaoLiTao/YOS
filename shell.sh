grub-file --is-x86-multiboot2 kernel 	#查看文件是否带有multiboot2头
echo $? 								#上一个程序的结果
sed -i 's/\r$//' filename				#将/ r剔除
#安装grub2
grub-install --root-directory=/mnt --no-floppy --modules="normal part_msdos ext2 multiboot biosdev" /dev/loop0
cp /home/yao/yos/bin/kernel /mnt/boot/
objdump -S bin/kernel >> kernel.txt #反编译没有符号
0x3053d
