#sample driver module  
obj-m := hello.o  
KDIR = /home/paul/work/Andriod/kernel/goldfish
all:
	$(MAKE) -C $(KDIR) M=$(PWD) 

.PHONY:clean  
clean:
	rm -f *.mod.c *.mod.o *.ko *.o *.tmp_versions  
