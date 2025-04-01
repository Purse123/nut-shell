# Nut-Shell
> Not professional build still in building process
> Always accept issues
![DEMO](https://github.com/user-attachments/assets/557624c7-f217-49f8-baaf-883b49408214)

# Installation
```sh 
git clone --depth 1 https://github.com/Purse123/nut-shell.git
cd nut-shell
chmod u+x build.sh
./build.sh
```

# About Me
- Name: Pierce Neupane
- Introduction: Program speaks for itself

# Commands
| `Command`    | `Description`                                      |
|------------|--------------------------------------------------|
| `bola`     | Custom command for `echo`                      |
| `tero_tauko` | Custom command for `exit`                    |
| `wtf`     | Check if it's a built-in command, else find location of executable |

# TO-DO
1. Custom command functionality
2. Moveing cursor in terminal

# FAQ
1. **How to make cursor move?**
- install `rlwrap` package
```sh
$ sudo apt install rlwrap    # for Ubuntu/Debian
$ sudo dnf install rlwrap    # for Fedora
$ pacman -S rlwrap           # for Arch

$ rlwrap ./build.sh
```
2. **Does it work on my machine?**
- This project is designed to run on **GNU/Linux** distributions. But eventually i may make add for other OS.

# License
This project is licensed under the [MIT License](LICENSE).
