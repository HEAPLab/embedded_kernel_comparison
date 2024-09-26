
# Add the arm-linux-gcc to PATH
cd ..; source setenv.sh; cd security_linux

# Compile
make

# Then copy the resulting binary on an SD card, connect it to the board, mount it
# and run fuzer from the shell
