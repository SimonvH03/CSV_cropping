# CSV_cropping
Automatically detects objects within scan result, creates cropped copies of csv file.

# How to use
- open a terminal (in VSCode) and run the command:
```
git clone https://github.com/SimonvH03/CSV_cropping.git
```

- place files you want to crop in the root directory (main folder) or wherever you like

- run the executbale 'crop' with your input file (exclude the '<' and '>' symbols, and {} means optional)
> filename may instead be the relative or absolute path to the file
```
./crop <filename> {-v > output}
```

> using the flag -v (or --verbose) adds an ascii preview to the output, it shows the borders of the cropped exported csv files.
> it's recommended to also redirect the output when using this flag

- change defined values in config.h to set parameters.
> !!! to recompile after making changes to the configuration run the command:
```
make (all, re, clean, fclean)
```
