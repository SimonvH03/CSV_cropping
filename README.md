# CSV_cropping
Automatically detects objects within scan result, creates cropped copies of csv file.

# How to install/update
### Install for the first time:
- open a terminal (in VSCode) and run the command:
```
git clone https://github.com/SimonvH03/CSV_cropping.git
```
- navigate to the cloned directory in your terminal
```
cd CSV_cropping
pwd
```

### or Update the version you already have:
- open a terminal at the cloned directory and run the commands:
> if pwd does not correspond with the folder of your current install, navigate there with the command 'cd'  
> don't forget to include the '.'
```
pwd
git checkout .
git stash
git pull
```

# How to use the tool
- place files you want to crop in the directory ./data or wherever you like

- visit config.h and read it carefully
> change defined constant values in config.h to set parameters.

- make sure your input file (relative path, data/inputfile.csv) is defined
- run the program with the provided script
```
bash run.sh
```

# Understanding the Config.h file
> to be continued, 7:07AM sleepytime
