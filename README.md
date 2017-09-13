# MASM for Not-Windows platforms
## What is this?
This project is a fancy makefile, and a mingw distribution to assist any non-windows users in running a MASM-compatible assembler easily.

## How do I use it?
1. Install WINE -- This will vary based on your distribution -- See Installing WINE for more information
2. Clone this project -- `git clone https://github.com/a9rkzz/MASM-Unix.git`
3. Setup mingw -- `make mingw`
4. Write your code
5. Test your code -- `make`
6. Look at all the hard drive space saved by not setting up Visual Studio and celebrate

## Installing WINE
### MacOS
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew install wine
```

### Ubuntu
```
sudo apt-get install wine
```

### SUSE
```
sudo zypper install wine
```

### Fedora
```
sudo dnf install wine
```

### CentOS
```
sudo yum install wine
```

