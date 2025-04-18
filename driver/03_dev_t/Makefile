obj-m 			+= dev_t.o
KDIR 			:= /home/guangzhao/Public/kernel-rockchip
PWD 			?= $(shell pwd)
ARCH 			:= arm64
CROSS_COMPILE 	:= /opt/aarch64-toolchain/bin/aarch64-linux-gnu-

all:
	make ARCH=arm64 CROSS_COMPILE=$(CROSS_COMPILE)  -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.ko *.o *.mod.o *.mod.c *.symvers *.order \.*.cmd
