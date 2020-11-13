# ft_ls

My own implementation of the famous Unix command: ls, using the C programming language.

![Example](https://i.ibb.co/6bBqj1s/Screen-Shot-2020-11-13-at-2-31-41-PM.png)

### Requirements
As for software Requirements, you'll need:
- GNU make
- GCC

No specific versions, just update them to the latest version if you still can't build the program.

### Building the program

1. Download/Clone the source code
2. `cd` into the root directory
3. Run `make`

### Running the program

It's pretty simple, instead of calling `ls`, call `./ft_ls` from the root directory of the source code after building it.

#### Supported flags

- Long listing display: `-l`
- Display recursively: `-R`
- Display all files: `-a`
- Output is not sorted.  This option turns on the -a option : `-f`
- Directories are listed as plain files (not searched recursively): `-d`
- Reverse sort: `-r`
- Sort by modification date: `-t`
- Suppress owner: `-g`
- Sort by creation date: `-u`
- Sort by file size: `-S`
- Colorized output: `-G`
- Display extended attribute keys and sizes in long (`-l`) output: `-@`

### Notes

- You can find the project instructions by clicking on [subject](https://cdn.intra.42.fr/pdf/pdf/1797/ft_ls.en.pdf)
