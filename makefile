all: build clean

build:
	gcc main.c -o nvidia_fan_ctrl -I /opt/cuda/targets/x86_64-linux/include/ -lnvidia-ml

clean:
	rm nvidia_fan_ctrl

install: build
	sudo cp ./nvidia_fan_ctrl /usr/sbin/
	sudo cp ./nvidia_fan_ctrl.service /etc/systemd/system/
	
	sudo systemctl start nvidia_fan_ctrl
	sudo systemctl enable nvidia_fan_ctrl

change_limits: build
	sudo systemctl stop nvidia_fan_ctrl

	sudo rm /usr/sbin/nvidia_fan_ctrl
	sudo cp ./nvidia_fan_ctrl /usr/sbin/

	sudo systemctl start nvidia_fan_ctrl

uninstall:
	sudo systemctl stop nvidia_fan_ctrl

	sudo rm /etc/systemd/system/nvidia_fan_ctrl.service
	sudo rm /usr/bin/nvidia_fan_ctrl
	