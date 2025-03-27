# 默认编译所有模块
obj-m := hello.o simple.o
all:
	@echo "Building all modules..."
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# 单独编译hello
hello:
	@echo "Building hello module..."
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# 单独编译simple
simple:
	@echo "Building simple module..."
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

jiffies:
	@echo "Building jiffies module..."
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	@echo "Cleaning..."
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f *.o *.ko *.mod* *.order *.symvers .*.cmd

.PHONY: all hello simple clean
