## my_ls

---
**Compilation**

To compile the project, use the provided Makefile:

* **Compile:** `make`
* **Clean object files:** `make clean`
* **Full clean (objects + binary):** `make fclean`
* **Rebuild:** `make re`
---

```bash
./my_ls -l -a -d -t
```
---
```bash
jean@XFinity$ ./my_ls -l
total 60
drwxrwxr-x 2 jean jean  4096  Nov  3 11:13 tests
-rw-rw-r-- 1 jean jean  1112  Nov  6 11:07 main.o
-rw-rw-r-- 1 jean jean   157  Nov  6 10:30 main.c
-rw-rw-r-- 1 jean jean   957  Nov  6 10:53 lib.h
-rw-rw-r-- 1 jean jean    45  Nov  4 15:04 README.md
drwxrwxr-x 2 jean jean  4096  Nov  6 11:32 lib
-rw-rw-r-- 1 jean jean   535  Nov  6 10:41 Makefile
-rwxrwxr-x 1 jean jean 22184  Nov  6 11:32 my_ls
-rw-rw-r-- 1 jean jean  3680  Nov  6 11:15 my_ls.o
-rw-rw-r-- 1 jean jean  3046  Nov  6 11:34 my_ls.c
```
---
```bash
jean@XFinity$ ./my_ls -a
tests  
main.o  
main.c  
lib.h  
.git  
.  
README.md  
lib  
.gitignore  
Makefile  
my_ls  
my_ls.o  
..  
my_ls.c  
```
---
```bash
jean@XFinity$ ./my_ls -d
.  
```
---

**How it works**

First, `my_ls()` parses the flags and adds them to a structure. Then, the `findpath()` function is called to search for the different arguments. It adds every argument to the files_t structure by allocating new memory. After that, the `executeflags()` function applies filters to display the files with the specified arguments.