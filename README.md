<h1>NVIDIA Fan Controller</h1>
A simple program to control fan curve of Nvidia GPUs through systemd on Linux. Made specifically because I couldn't get a fan curve to operate through NVIDIA's software on Arch Linux.

<h2>To Install</h2>
Run the command:

```
make install
```
This creates the executable, moves it to /usr/sbin, sets up a systemd service to control it, and enables that systemd service on boot. If the need arises to check the service, use its id `nvidia_fan_ctrl`.

<h2>To Change the Fan Curve</h2>

First, change the `config` array in the following structure:

```
tempConf config[] = {
  {<max>, <speed>}, 
  ...
};
```
Then, run the following command:

```
make change_limits
```

<h2>To Uninstall</h2>
Run the command:

```
make uninstall
```
This removes the systemd service and executable.
