## Zorro git - Step by step

1. Create Zorro folder

2. Clone git repo to new folder

git clone https://github.com/zuongthaotn/zorro .

3. Clone git submodule

git submodule update --init --recursive

 
4. Download & Install Zorro into Zorro folder

5. Rename the Strategy to Strategy.old

6. Move all code from git folder to Zorro folder

7. run _deploy_repo.cmd

## Using
1. Copying file price data and rename it to a assest name
Example: History/AAA.csv

2. Convert data to Zorro format
Example: Using Zorro with script "CSVtoHistory" and asset AAA => click Test button

3. Using custom Strategy
Now, you can using your own Strategy

