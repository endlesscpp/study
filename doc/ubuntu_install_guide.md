Install ubuntu on R7000P
========================
1. disable 'Secure Boot' in BIOS
2. During install, press 'e' on 'ubuntu', add 'nouveau.modeset=0' after splash. F10 save and install.
3. After install, when reboot system on the first time, enter 'recovery mode', and press resume
4. After reboot, edit '/etc/default/grub', add 'nouveau.modeset=0' after splash.
5. You can also disable nouveau after reboot. If do that, do not need to do step 4.
6. If brightness cannot be adjusted, edit file: /usr/share/X11/xorg.conf.d/10-nvidia.conf
Section "OutputClass"
    Identifier "nvidia"
    MatchDriver "nvidia-drm"
    Driver "nvidia"
    Option "AllowEmptyInitialConfiguration"
    Option "RegistryDwords" "EnableBrightnessControl=1;" 
    ModulePath "/usr/lib/x86_64-linux-gnu/nvidia/xorg"
EndSection


utils:
====================
ubuntu-drivers devices
lshw -c video

#disable nouveau
sudo gedit /etc/modprobe.d/blacklist.conf

blacklist nouveau
options nouveau modeset=0

sudo update-initramfs -u

#reboot, check if nouveau is disabled
lsmod | grep nouveau


Install cuda and driver
=======================

- CTRL-ALT-F1
- /etc/X11/default-display-manager
	- sudo service lightdm stop
	- sudo service gdm3 stop // after 16.10
- sudo init 3 [optional] (sudo init 5 back to ui)
- disable nouveau
- sudo sh xxx.run --no-opengl-files



## uninstall drivers
### apt
- sudo apt remove --purge nvidia*
- sudo apt autoremove
- reboot

## install driver by run
- sudo xxx.run --silent --driver


## verify
- nvidia-smi



edit grub file to enter text mode or disable nouveau
====================================================
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash nouveau.modeset=0"

