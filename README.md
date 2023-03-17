# risc-v
This is risc-v. It receives data and interprets commands. It is then stored and loaded in registers and memory.


# how to use
Create riscv-sim using the make command in the linux environment. I wrote a makefile.

Use the ./riscv-sim ./data/proj3_1_inst.bin > my_output.txt command to generate execution results as text files.

You can freely use the files in the data folder to see various results.
If you have both the inst and data files, such as the proj3_3 file, you can also see how you access memory by typing ./riscv-sim./data/proj3_3_inst.bin proj3_data.bin > my_output.txt. (sw, lw, etc.)
