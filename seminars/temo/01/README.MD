# Linux & Development Quick Reference

## Basic Linux Commands

```bash
pwd      # print working directory
mkdir    # make directory
rmdir    # remove directory
touch    # create file
rm       # remove file
ls       # list directory contents
mv       # move files or directories
cp       # copy files or directories
code     # open vs code editor
vim      # open vim editor (https://danielmiessler.com/blog/vim)
man      # display the manual page
```

# Gnu C Compiler
### Compile hello.c into a.out (default output)
gcc hello.c

## Compile hello.c and name the output hello.o
gcc hello.c -o hello.o

# Git
### Clone a repository into a new directory
git clone [repository url]

### Add file contents to index
git add [files]

### Record changes to repository
git commit -m "commit message"

### Update remote refs along with associated objects
git push

### Show the working tree status
git status

### Fetch from and integrate with another repository or a local branch
git pull

### git-ის დამატებითი დოკუმენტაცია [https://git-scm.com/docs](https://git-scm.com/docs)


# გარემოს გამართვა
## WSL
install wsl - https://learn.microsoft.com/en-us/windows/wsl/install

შეგიძლიათ აირჩიოთ Ubuntu-24.04 დისტრიბუცია

შეიძლება ინსტალაციის დაწყებამდე Windows Features-ში დაგჭირდეთ მონიშნოთ Virtual Machine Platform და Windows Subsystem for Linux თუ არაა მონიშნული.


## Dual Boot
dual boot-ის დასაყენებლად ეს ლინკები შეიძლება დაგეხმაროთ 
- https://www.youtube.com/watch?v=T78rCJ_i1no&list=PLSVEuMqiyyvjLxuH92Scw_LDvNTdFU5-j&index=10
- https://gcore.com/learning/dual-boot-ubuntu-windows-setup


## Mac Os
VM installation guide - https://github.com/freeuni-paradigms/2025/blob/master/vm/README.md